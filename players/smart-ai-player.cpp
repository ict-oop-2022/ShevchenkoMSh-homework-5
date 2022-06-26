#include "players/smart-ai-player.h"

std::pair<int, int> smart_ai_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  if (last_hit.first == -1) {
    std::vector<std::pair<int, int>> empty_cells;
    for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
      for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
        if (enemy[i][j] == field_t::EMPTY_CELL) {
          return {i, j};
        }
      }
    }
  } else {
    std::pair<int, int> next = *(next_move.end()-1);
    next_move.pop_back();
    return next;
  }
}

void smart_ai_player_t::on_incorrect_move(int x, int y) {
};

void smart_ai_player_t::on_duplicate_move(int x, int y) {
};

void smart_ai_player_t::on_miss(int x, int y) {
  enemy[x][y] = field_t::MISS_CELL;
};

void smart_ai_player_t::on_hit(int x, int y) {
  enemy[x][y] = field_t::HIT_CELL;
  last_hit.first = x;
  last_hit.second = y;

  for (const auto &dir : field_t::DIRECTIONS) {
    next_move.push_back({x + dir.first, y + dir.second});
  }
}

void smart_ai_player_t::on_kill(int x, int y) {
  enemy[x][y] = field_t::HIT_CELL;

  // влево
  for(int i = y-1; i >= 0; i--) {
    if (enemy[x][i] == field_t::MISS_CELL) {
      break;
    } else if (enemy[x][i] == field_t::EMPTY_CELL) {
      enemy[x][i] = field_t::MISS_CELL;
      break;
    }
  }
  // вправо
  for(int i = y+1; i < field_t::FIELD_SIZE; i++) {
    if (enemy[x][i] == field_t::MISS_CELL) {
      break;
    } else if (enemy[x][i] == field_t::EMPTY_CELL) {
      enemy[x][i] = field_t::MISS_CELL;
      break;
    }
  }
  // вверх
  for(int i = x-1; i >=0; i--) {
    if (enemy[i][y] == field_t::MISS_CELL) {
      break;
    } else if (enemy[i][y] == field_t::EMPTY_CELL) {
      enemy[i][y] = field_t::MISS_CELL;
      break;
    }
  }
  // вниз
  for(int i = x+1; i < field_t::FIELD_SIZE; i++) {
    if (enemy[i][y] == field_t::MISS_CELL) {
      break;
    } else if (enemy[i][y] == field_t::EMPTY_CELL) {
      enemy[i][y] = field_t::MISS_CELL;
      break;
    }
  }

  last_hit.first = -1;
  last_hit.second = -1;
  next_move.clear();
};

void smart_ai_player_t::on_win() {
};

void smart_ai_player_t::on_lose() {
};