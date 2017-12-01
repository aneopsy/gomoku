#include <controller.hpp>
#include <cstring>
#include <iostream>
#include <map.hpp>
#include <other/global.hpp>

void performAndWriteMove(Board map, int time_limit) {
  int move_r, move_c, winning_player, actual_depth;
  unsigned int node_count, eval_count;
  bool success = Controller::generateMove(
      map.getMap(), 1, -1, time_limit, 1, &actual_depth, &move_r, &move_c,
      &winning_player, &node_count, &eval_count, nullptr);

  if (success) {
    std::cout << "MESSAGE"
              << " d=" << actual_depth << " node_cnt=" << node_count
              << " eval_cnt=" << eval_count << std::endl;

    map.put(move_r, move_c, '1');

    std::cout << move_c << "," << move_r << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }
}

int main(int ac, char const *av[]) {
  Board map = Board(19, 19);
  while (getchar()) {
    performAndWriteMove(map, 100);
    map.printMap();
  }
  ac = ac;
  av = av;
  return 0;
}
