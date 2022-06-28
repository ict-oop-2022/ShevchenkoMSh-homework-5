#include "game/sea-battle.h"

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}

void sea_battle_t::play() {
  turn_t current_turn = FIRST_PLAYER;

  std::pair<int, int> move;
  std::shared_ptr<player_interface_t> current_player = player1_;
  std::shared_ptr<player_interface_t> enemy_player;
  field_t copy_enemy(0), current_field(field1_), enemy_field(field2_);
  //  std::shared_ptr<int> current_kills;
  while (true) {
    if (current_turn == FIRST_PLAYER) {
      if (current_player == player2_) {
        field_t tmp = current_field;
        current_field = enemy_field;
        enemy_field = tmp;
      }

      current_player = player1_;
      enemy_player = player2_;

      copy_enemy = enemy_field;
    } else {
      if (current_player == player1_) {
        field_t tmp = current_field;
        current_field = enemy_field;
        enemy_field = tmp;
      }

      current_player = player2_;
      enemy_player = player1_;

      copy_enemy = enemy_field;
    }

    for (int i = 0; i < field_t::FIELD_SIZE; i++) {
      for (int j = 0; j < field_t::FIELD_SIZE; j++) {
        if (copy_enemy[i][j] == field_t::SHIP_CELL) {
          copy_enemy[i][j] = field_t::EMPTY_CELL;
        }
      }
    }
    move = current_player->make_move(current_field, copy_enemy);
    int x = move.first;
    int y = move.second;

    if (!field_t::is_cell_valid(x, y)) {
      current_player->on_incorrect_move(x, y);
      continue;
    }
    if (enemy_field[x][y] == field_t::HIT_CELL) {
      current_player->on_duplicate_move(x, y);
      continue;
    }
    if (enemy_field[x][y] == field_t::EMPTY_CELL) {
      enemy_field[x][y] = field_t::MISS_CELL;
      current_player->on_miss(x, y);
      current_turn = change_turn(current_turn);
      continue;
    }
    if (enemy_field[x][y] == field_t::SHIP_CELL) {
      enemy_field[x][y] = field_t::HIT_CELL;
      // влево
      bool flag = false;
      for(int i = y-1; i >= 0; i--) {
        if (enemy_field[x][i] == field_t::SHIP_CELL) {
          flag = true;
          break;
        } else if (enemy_field[x][i] == field_t::EMPTY_CELL || enemy_field[x][i] == field_t::MISS_CELL) {
          break;
        }
      }
      // вправо
      for(int i = y+1; i < field_t::FIELD_SIZE; i++) {
        if (enemy_field[x][i] == field_t::SHIP_CELL) {
          flag = true;
          break;
        } else if (enemy_field[x][i] == field_t::EMPTY_CELL || enemy_field[x][i] == field_t::MISS_CELL) {
          break;
        }
      }
      // вверх
      for(int i = x-1; i >=0; i--) {
        if (enemy_field[i][y] == field_t::SHIP_CELL) {
          flag = true;
          break;
        } else if (enemy_field[i][y] == field_t::EMPTY_CELL || enemy_field[i][y] == field_t::MISS_CELL) {
          break;
        }
      }
      // вниз
      for(int i = x+1; i < field_t::FIELD_SIZE; i++) {
        if (enemy_field[i][y] == field_t::SHIP_CELL) {
          flag = true;
          break;
        } else if (enemy_field[i][y] == field_t::EMPTY_CELL || enemy_field[i][y] == field_t::MISS_CELL) {
          break;
        }
      }
      if (flag) {
        current_player->on_hit(x, y);
      } else {
        current_player->on_kill(x, y);

        bool won = true;
        for (int i = 0; i < field_t::FIELD_SIZE; i++) {
          for (int j = 0; won == true && j < field_t::FIELD_SIZE; j++) {
            if (enemy_field[i][j] == field_t::SHIP_CELL) {
              won = false;
            }
          }
        }
        if (won) {
          current_player->on_win();
          enemy_player->on_lose();
          return;
        }
      }
    }
  }
}