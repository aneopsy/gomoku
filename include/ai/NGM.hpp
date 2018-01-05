#ifndef INCLUDE_AI_NEGAMAX_H_
#define INCLUDE_AI_NEGAMAX_H_

#include <vector>

class AINGM {
public:
  AINGM();
  ~AINGM();

  static void heuristicNegamax(const int *gs, int player, int depth,
                               int time_limit, bool enable_ab_pruning,
                               int *actual_depth, int *move_r, int *move_c);

private:
  static int pat[5];

  struct Move {
    int r;
    int c;
    int heuristic_val;
    int actual_score;

    bool operator<(Move other) const {
      return heuristic_val > other.heuristic_val;
    }
  };

  static int heuristicNegamax(int *gs, int player, int initial_depth,
                              int depth, bool enable_ab_pruning, int alpha,
                              int beta, int *move_r, int *move_c);

  static void searchMovesOrdered(const int *gs, int player,
                                 std::vector<Move> *result);

  static int negamax(int *gs, int player, int depth, int *move_r, int *move_c);
};

#endif
