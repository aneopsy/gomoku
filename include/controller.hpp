#ifndef INCLUDE_API_RENJU_API_H_
#define INCLUDE_API_RENJU_API_H_

#include <string>
#include <map.hpp>

class Controller {
public:
  Controller();
  ~Controller();

  static bool generateMove(Board map, int ai_player_id,
                           int search_depth, int time_limit, int num_threads,
                           int *actual_depth, int *move_r, int *move_c,
                           int *winning_player, unsigned int *node_count,
                           unsigned int *eval_count, unsigned int *pm_count);
};

#endif
