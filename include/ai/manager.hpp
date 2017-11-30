#ifndef INCLUDE_AI_AI_CONTROLLER_H_
#define INCLUDE_AI_AI_CONTROLLER_H_

class AIManager {
public:
  AIManager();
  ~AIManager();

  static void generateMove(const char *gs, int player, int search_depth,
                           int time_limit, int *actual_depth, int *move_r,
                           int *move_c, int *winning_player,
                           unsigned int *node_count, unsigned int *eval_count,
                           unsigned int *pm_count);
};

#endif
