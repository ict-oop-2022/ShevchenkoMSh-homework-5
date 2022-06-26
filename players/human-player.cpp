#include "players/human-player.h"

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;
  while (true) {
    std::string s;
    std::getline(input_stream, s);
    int x, y;
    if (s.size() == 3) {
      if (s[0] == '1' && s[1] == '0' && s[2] >= 'A' && s[2] <= 'J') {
        x = 10 + (s[1] - '0');
        y = s[2] - 'A';
        return {x-1, y};
      }
    } else if (s.size() == 2) {
      if (s[0] >= '1' && s[0] <= '9' && s[1] >= 'A' && s[1] <= 'J') {
        x = s[0] - '0';
        y = s[1] - 'A';
        return {x-1, y};
      }
    }
    output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
  }
}

void human_player_t::on_incorrect_move(int x, int y) {
  assert(false);
}

void human_player_t::on_duplicate_move(int x, int y) {
  char ch = y +'A';
  output_stream << x+1 << ch << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  char ch = y +'A';
  output_stream << x+1 << ch << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y) {
  char ch = y +'A';
  output_stream << x+1 << ch << " HIT! Your next move!" << std::endl;
}
void human_player_t::on_kill(int x, int y) {
  char ch = y +'A';
  output_stream << x+1 << ch << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}
void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}