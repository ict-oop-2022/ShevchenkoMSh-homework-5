#pragma once

#include <memory>

#include "game/field.h"
#include "players/player-interface.h"

class sea_battle_t {
public:
  enum turn_t { FIRST_PLAYER = 0, SECOND_PLAYER = 1 };

  sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1, std::shared_ptr<player_interface_t> player2,
               field_t field2) : player1_(player1), field1_(field1), player2_(player2), field2_(field2){}

  ~sea_battle_t() = default;

  void play();

  static turn_t change_turn(turn_t current_turn);
  static std::string get_player_name(turn_t turn);

private:
  std::shared_ptr<player_interface_t> player1_;
  field_t field1_;
  std::shared_ptr<player_interface_t> player2_;
  field_t field2_;
};