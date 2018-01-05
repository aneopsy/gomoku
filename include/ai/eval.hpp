#ifndef INCLUDE_AI_EVAL_H_
#define INCLUDE_AI_EVAL_H_

#define AiEvalWinningScore 10000
#define AiEvalThreateningScore 300

class AIEval {
public:
  AIEval();
  ~AIEval();

  static int evalState(const int *gs, int player);

  static int evalMove(const int *gs, int r, int c, int player);

  static int winningPlayer(const int *gs);

  struct DirectionMeasurement {
    char length;
    char block_count;
    char space_count;
  };

  struct DirectionPattern {
    char min_occurrence;
    char length;
    char block_count;
    char space_count;
  };

  static DirectionPattern *pat;

  static int *preset_scores;
  static void generatePresetPatterns(DirectionPattern **preset_patterns,
                                     int **preset_scores,
                                     int *preset_patterns_size,
                                     int *preset_patterns_skip);

  static int evalADM(DirectionMeasurement *all_direction_measurement);

  static int matchPattern(DirectionMeasurement *all_direction_measurement,
                          DirectionPattern *patterns);

  static void measureAllDirections(const int *gs, int r, int c, int player,
                                   bool consecutive,
                                   AIEval::DirectionMeasurement *adm);

  static void measureDirection(const int *gs, int r, int c, int dr, int dc,
                               int player, bool consecutive,
                               AIEval::DirectionMeasurement *result);
};

#endif
