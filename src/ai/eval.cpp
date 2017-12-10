#include <ai/eval.hpp>
#include <ai/utils.hpp>
#include <algorithm>
#include <climits>
#include <cstring>
#include <other/global.hpp>
#include <stdlib.h>

AIEval::DirectionPattern *AIEval::pat = nullptr;
int *AIEval::preset_scores = nullptr;
int pat_size = 0;
int pat_skip[6] = {0};

int AIEval::evalState(const int *maps, int player) {
  if (maps == nullptr || player < 1 || player > 2)
    return 0;
  int score = 0;
  for (int r = 0; r < g_board_size; ++r) {
    for (int c = 0; c < g_board_size; ++c) {
      score += evalMove(maps, r, c, player);
    }
  }
  return score;
}

int AIEval::evalMove(const int *maps, int r, int c, int player) {
  if (maps == nullptr || player < 1 || player > 2)
    return 0;
  ++g_eval_count;
  if (pat == nullptr) {
    generatePresetPatterns(&pat, &preset_scores, &pat_size, pat_skip);
  }
  DirectionMeasurement adm[4];
  int max_score = 0;
  for (bool consecutive = false;; consecutive = true) {
    measureAllDirections(maps, r, c, player, consecutive, adm);
    int score = evalADM(adm);
    max_score = std::max(max_score, score);
    if (consecutive)
      break;
  }
  return max_score;
}

int AIEval::evalADM(DirectionMeasurement *all_direction_measurement) {
  int score = 0;
  int size = pat_size;

  int max_measured_len = 0;
  for (int i = 0; i < 4; i++) {
    int len = all_direction_measurement[i].length;
    max_measured_len = len > max_measured_len ? len : max_measured_len;
    score += len - 1;
  }
  int start_pattern = pat_skip[max_measured_len];

  for (int i = start_pattern; i < size; ++i) {
    score +=
        matchPattern(all_direction_measurement, &pat[2 * i]) * preset_scores[i];

    if (score >= AiEvalThreateningScore)
      break;
  }

  return score;
}

int AIEval::matchPattern(DirectionMeasurement *all_direction_measurement,
                         DirectionPattern *patterns) {
  if (all_direction_measurement == nullptr)
    return -1;
  if (patterns == nullptr)
    return -1;

  g_pm_count++;

  int match_count = INT_MAX, single_pattern_match = 0;

  for (int i = 0; i < 2; ++i) {
    auto p = patterns[i];
    if (p.length == 0)
      break;

    single_pattern_match = 0;

    for (int j = 0; j < 4; ++j) {
      auto dm = all_direction_measurement[j];

      if (dm.length == p.length &&
          (p.block_count == -1 || dm.block_count == p.block_count) &&
          (p.space_count == -1 || dm.space_count == p.space_count)) {
        single_pattern_match++;
      }
    }
    single_pattern_match /= p.min_occurrence;
    match_count = match_count >= single_pattern_match ? single_pattern_match
                                                      : match_count;
  }
  return match_count;
}

void AIEval::measureAllDirections(const int *maps, int r, int c, int player,
                                  bool consecutive,
                                  AIEval::DirectionMeasurement *adm) {
  if (maps == nullptr)
    return;
  if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size)
    return;
  measureDirection(maps, r, c, 0, 1, player, consecutive, &adm[0]);
  measureDirection(maps, r, c, 1, 1, player, consecutive, &adm[1]);
  measureDirection(maps, r, c, 1, 0, player, consecutive, &adm[2]);
  measureDirection(maps, r, c, 1, -1, player, consecutive, &adm[3]);
}

void AIEval::measureDirection(const int *maps, int r, int c, int dr, int dc,
                              int player, bool consecutive,
                              AIEval::DirectionMeasurement *result) {
  if (maps == nullptr)
    return;
  if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size)
    return;
  if (dr == 0 && dc == 0)
    return;
  int cr = r, cc = c;
  result->length = 1, result->block_count = 2, result->space_count = 0;

  int space_allowance = 1;
  if (consecutive)
    space_allowance = 0;

  for (bool reversed = false;; reversed = true) {
    while (true) {
      cr += dr;
      cc += dc;
      if (cr < 0 || cr >= g_board_size || cc < 0 || cc >= g_board_size)
        break;
      int cell = maps[g_board_size * cr + cc];
      if (cell == 0) {
        if (space_allowance > 0 &&
            AIUtils::getCell(maps, cr + dr, cc + dc) == player) {
          space_allowance--;
          result->space_count++;
          continue;
        } else {
          result->block_count--;
          break;
        }
      }
      if (cell != player)
        break;
      result->length++;
    }
    if (reversed)
      break;
    cr = r;
    cc = c;
    dr = -dr;
    dc = -dc;
  }
  if (result->length >= 5) {
    if (result->space_count == 0) {
      result->length = 5;
      result->block_count = 0;
    } else {
      result->length = 4;
      result->block_count = 1;
    }
  }
}

void AIEval::generatePresetPatterns(DirectionPattern **pat, int **preset_scores,
                                    int *pat_size, int *pat_skip) {
  const int _size = 11;
  pat_skip[5] = 0;
  pat_skip[4] = 1;
  pat_skip[3] = 7;
  pat_skip[2] = 10;

  pat_skip[1] = _size;
  pat_skip[0] = _size;

  DirectionPattern patterns[_size * 2] = {
      {1, 5, 0, 0},
      {0, 0, 0, 0}, // 10000
      {1, 4, 0, 0},
      {0, 0, 0, 0}, // 700
      {2, 4, 1, 0},
      {0, 0, 0, 0}, // 700
      {2, 4, -1, 1},
      {0, 0, 0, 0}, // 700
      {1, 4, 1, 0},
      {1, 4, -1, 1}, // 700
      {1, 4, 1, 0},
      {1, 3, 0, -1}, // 500
      {1, 4, -1, 1},
      {1, 3, 0, -1}, // 500
      {2, 3, 0, -1},
      {0, 0, 0, 0}, // 300
      // {1, 4,  1,  0}, {0, 0,  0,  0},  // 1
      // {1, 4, -1,  1}, {0, 0,  0,  0},  // 1
      {3, 2, 0, -1},
      {0, 0, 0, 0}, // 50
      {1, 3, 0, -1},
      {0, 0, 0, 0}, // 20
      {1, 2, 0, -1},
      {0, 0, 0, 0} // 9
  };

  int scores[_size] = {10000, 700, 700, 700, 700, 500, 500, 300, 50, 20, 9};

  *pat = new DirectionPattern[_size * 2];
  *preset_scores = new int[_size];

  memcpy(*pat, patterns, sizeof(DirectionPattern) * _size * 2);
  memcpy(*preset_scores, scores, sizeof(int) * _size);

  *pat_size = _size;
}

int AIEval::winningPlayer(const int *maps) {
  if (maps == nullptr)
    return 0;
  for (int r = 0; r < g_board_size; ++r) {
    for (int c = 0; c < g_board_size; ++c) {
      int cell = maps[g_board_size * r + c];
      if (cell == 0)
        continue;
      for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
          if (dr == 0 && dc <= 0)
            continue;
          DirectionMeasurement dm;
          measureDirection(maps, r, c, dr, dc, cell, 1, &dm);
          if (dm.length >= 5)
            return cell;
        }
      }
    }
  }
  return 0;
}
