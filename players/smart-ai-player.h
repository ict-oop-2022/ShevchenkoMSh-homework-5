#pragma once

#include "players/player-interface.h"

#include <random>

class smart_ai_player_t : public player_interface_t {
public:
  smart_ai_player_t() : enemy(0) {
    for (int i = 0; i < field_t::FIELD_SIZE; i++) {
      for (int j= 0;j < field_t::FIELD_SIZE; j++) {
        enemy[i][j] = field_t::EMPTY_CELL;
      }
    }
    last_hit.first = -1;
    last_hit.second = -1;
  }

  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;
  void on_incorrect_move(int x, int y) override;
  void on_duplicate_move(int x, int y) override;
  void on_miss(int x, int y) override;
  void on_hit(int x, int y) override;
  void on_kill(int x, int y) override;

  void on_win() override;
  void on_lose() override;

private:
  field_t enemy;
  std::pair<int, int> last_hit;
  std::vector<std::pair<int, int>> next_move;
};