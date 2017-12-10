#ifndef INCLUDE_AI_UTILS_H_
#define INCLUDE_AI_UTILS_H_

#include <other/global.hpp>

class AIUtils {
public:
  AIUtils();
  ~AIUtils();

  static inline int getCell(const int *gs, int r, int c) {
    if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size)
      return -1;
    return gs[g_board_size * r + c];
  }

  static inline bool setCell(int *gs, int r, int c, int value) {
    if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size)
      return false;
    gs[g_board_size * r + c] = value;
    return true;
  }

  static bool remoteCell(const int *gs, int r, int c);
};

#endif
