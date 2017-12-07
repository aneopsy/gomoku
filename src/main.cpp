#include <controller.hpp>
#include <cstring>
#include <iostream>
#include <map.hpp>
#include <other/global.hpp>

void performAndWriteMove(Board map, int time_limit, int player_id) {
  int move_r, move_c, winning_player, actual_depth;
  unsigned int node_count, eval_count;
  bool success = Controller::generateMove(
      map, player_id, -1, time_limit, 1, &actual_depth, &move_r,
      &move_c, &winning_player, &node_count, &eval_count, nullptr);

  if (success) {
    std::cout << player_id << " : MESSAGE"
              << " d=" << actual_depth << " node_cnt=" << node_count
              << " eval_cnt=" << eval_count << std::endl;

    map.put(move_r-1, move_c-1, player_id+'0');

    std::cout << move_c << "," << move_r << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }
}

int main(int ac, char const *av[]) {
  Board map = Board(19, 19);
  map.put(rand() % 20, rand() % 20, '2');
  map.put(rand() % 20, rand() % 20, '1');
  while (getchar()) {
    performAndWriteMove(map, 5000, 1);
    performAndWriteMove(map, 5000, 2);
    map.printMap();
  }
  ac = ac;
  av = av;
  return 0;
}
