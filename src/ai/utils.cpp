#include <ai/utils.hpp>
#include <random>

bool AIUtils::remoteCell(const int *maps, int r, int c) {
    if (maps == nullptr) return false;
    for (int i = r - 2; i <= r + 2; ++i) {
        if (i < 0 || i >= g_board_size) continue;
        for (int j = c - 2; j <= c + 2; ++j) {
            if (j < 0 || j >= g_board_size) continue;
            if (maps[g_board_size * i + j] > 0) return false;
        }
    }
    return true;
}
