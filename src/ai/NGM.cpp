#include <ai/NGM.hpp>
#include <ai/eval.hpp>
#include <ai/utils.hpp>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <other/global.hpp>

int AINGM::pat[5] = {17, 7, 5, 3, 3};

#define kAvgBranchingFactor 3
#define kMaximumDepth 16
#define kScoreDecayFactor 0.95f

void AINGM::heuristicNegamax(const int *maps, int player, int depth,
                             int time_limit, bool enable_ab_pruning,
                             int *actual_depth, int *move_r, int *move_c) {
  if (maps == nullptr || player < 1 || player > 2 || depth == 0 || depth < -1 ||
      time_limit < 0)
    return;

  int *_maps = new int[g_maps_size];
  memcpy(_maps, maps, g_maps_size);

  int _cnt = 0;
  for (int i = 0; i < static_cast<int>(g_maps_size); i++)
    if (_maps[i] != 0)
      _cnt++;

  if (_cnt <= 2)
    depth = 6;

  if (depth > 0) {
    if (actual_depth != nullptr)
      *actual_depth = depth;
    heuristicNegamax(_maps, player, depth, depth, enable_ab_pruning,
                     INT_MIN / 2, INT_MAX / 2, move_r, move_c);
  } else {
    std::clock_t c_start = std::clock();
    for (int d = 6;; d += 2) {
      std::clock_t c_iteration_start = std::clock();
      memcpy(_maps, maps, g_maps_size);
      heuristicNegamax(_maps, player, d, d, enable_ab_pruning, INT_MIN / 2,
                       INT_MAX / 2, move_r, move_c);
      std::clock_t c_iteration =
          (std::clock() - c_iteration_start) * 1000 / CLOCKS_PER_SEC;
      std::clock_t c_elapsed = (std::clock() - c_start) * 1000 / CLOCKS_PER_SEC;
      if (c_elapsed +
                  (c_iteration * kAvgBranchingFactor * kAvgBranchingFactor) >
              time_limit ||
          d >= kMaximumDepth) {
        if (actual_depth != nullptr)
          *actual_depth = d;
        break;
      }
    }
  }
  delete[] _maps;
}

int AINGM::heuristicNegamax(int *maps, int player, int initial_depth, int depth,
                            bool enable_ab_pruning, int alpha, int beta,
                            int *move_r, int *move_c) {
  ++g_node_count;
  int max_score = INT_MIN;
  int opponent = player == 1 ? 2 : 1;
  std::vector<Move> moves_player, moves_opponent, candidate_moves;
  searchMovesOrdered(maps, player, &moves_player);
  searchMovesOrdered(maps, opponent, &moves_opponent);
  if (moves_player.size() == 0)
    return 0;
  if (moves_player.size() == 1 ||
      moves_player[0].heuristic_val >= AiEvalWinningScore) {
    auto move = moves_player[0];
    if (move_r != nullptr)
      *move_r = move.r;
    if (move_c != nullptr)
      *move_c = move.c;
    return move.heuristic_val;
  }
  bool block_opponent = false;
  int tmp_size = std::min(static_cast<int>(moves_opponent.size()), 2);
  if (moves_opponent[0].heuristic_val >= AiEvalThreateningScore) {
    block_opponent = true;
    for (int i = 0; i < tmp_size; ++i) {
      auto move = moves_opponent[i];
      move.heuristic_val = AIEval::evalMove(maps, move.r, move.c, player);
      candidate_moves.push_back(move);
    }
  }
  int breadth = (initial_depth >> 1) - ((depth + 1) >> 1);
  if (breadth > 4)
    breadth = pat[4];
  else
    breadth = pat[breadth];
  tmp_size = std::min(static_cast<int>(moves_player.size()), breadth);
  for (int i = 0; i < tmp_size; ++i)
    candidate_moves.push_back(moves_player[i]);
  int size = static_cast<int>(candidate_moves.size());
  for (int i = 0; i < size; ++i) {
    auto move = candidate_moves[i];
    AIUtils::setCell(maps, move.r, move.c, player);
    int score = 0;
    if (depth > 1)
      score = heuristicNegamax(maps, opponent, initial_depth, depth - 1,
                               enable_ab_pruning,
                               -beta, //
                               -alpha + move.heuristic_val, nullptr, nullptr);

    if (score >= 2)
      score = static_cast<int>(score * kScoreDecayFactor);
    move.actual_score = move.heuristic_val - score;
    candidate_moves[i].actual_score = move.actual_score;
    AIUtils::setCell(maps, move.r, move.c, 0);
    if (move.actual_score > max_score) {
      max_score = move.actual_score;
      if (move_r != nullptr)
        *move_r = move.r;
      if (move_c != nullptr)
        *move_c = move.c;
    }
    int max_score_decayed = max_score;
    if (max_score >= 2)
      max_score_decayed =
          static_cast<int>(max_score_decayed * kScoreDecayFactor);
    if (max_score > alpha)
      alpha = max_score;
    if (enable_ab_pruning && max_score_decayed >= beta)
      break;
  }
  if (depth == initial_depth && block_opponent && max_score < 0) {
    auto blocking_move = candidate_moves[0];
    int b_score = blocking_move.actual_score;
    if (b_score == 0)
      b_score = 1;
    if ((max_score - b_score) / static_cast<float>(std::abs(b_score)) < 0.2) {
      if (move_r != nullptr)
        *move_r = blocking_move.r;
      if (move_c != nullptr)
        *move_c = blocking_move.c;
      max_score = blocking_move.actual_score;
    }
  }
  return max_score;
}

void AINGM::searchMovesOrdered(const int *maps, int player,
                               std::vector<Move> *result) {
  result->clear();
  int min_r = INT_MAX, min_c = INT_MAX, max_r = INT_MIN, max_c = INT_MIN;
  for (int r = 0; r < g_board_size; ++r) {
    for (int c = 0; c < g_board_size; ++c) {
      if (maps[g_board_size * r + c] != 0) {
        if (r < min_r)
          min_r = r;
        if (c < min_c)
          min_c = c;
        if (r > max_r)
          max_r = r;
        if (c > max_c)
          max_c = c;
      }
    }
  }

  if (min_r - 2 < 0)
    min_r = 2;
  if (min_c - 2 < 0)
    min_c = 2;
  if (max_r + 2 >= g_board_size)
    max_r = g_board_size - 3;
  if (max_c + 2 >= g_board_size)
    max_c = g_board_size - 3;

  for (int r = min_r - 2; r <= max_r + 2; ++r) {
    for (int c = min_c - 2; c <= max_c + 2; ++c) {
      if (maps[g_board_size * r + c] != 0)
        continue;
      if (AIUtils::remoteCell(maps, r, c))
        continue;
      Move m;
      m.r = r;
      m.c = c;
      m.heuristic_val = AIEval::evalMove(maps, r, c, player);
      result->push_back(m);
    }
  }
  std::sort(result->begin(), result->end());
}

int AINGM::negamax(int *maps, int player, int depth, int *move_r, int *move_c) {
  int max_score = INT_MIN;
  if (depth == 0)
    return AIEval::evalState(maps, player);
  for (int r = 0; r < g_board_size; ++r) {
    for (int c = 0; c < g_board_size; ++c) {
      if (AIUtils::getCell(maps, r, c) != 0)
        continue;
      if (AIUtils::remoteCell(maps, r, c))
        continue;
      AIUtils::setCell(maps, r, c, player);
      int s = -negamax(maps,                // Game state
                       player == 1 ? 2 : 1, // Change player
                       depth - 1,           // Reduce depth by 1
                       nullptr,             // Result move not required
                       nullptr);
      AIUtils::setCell(maps, r, c, 0);
      if (s > max_score) {
        max_score = s;
        if (move_r != nullptr)
          *move_r = r;
        if (move_c != nullptr)
          *move_c = c;
      }
    }
  }
  return max_score;
}
