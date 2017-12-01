#include <ai/manager.hpp>
#include <ai/eval.hpp>
#include <ai/NGM.hpp>
#include <ai/utils.hpp>
#include <other/global.hpp>
#include <cstring>

void AIManager::generateMove(const char *gs, int player, int search_depth, int time_limit,
                           int *actual_depth, int *move_r, int *move_c, int *winning_player,
                           unsigned int *node_count, unsigned int *eval_count, unsigned int *pm_count) {
    if (gs == nullptr ||
        player  < 1 || player > 2 ||
        search_depth == 0 || search_depth > 10 ||
        time_limit < 0 ||
        move_r == nullptr || move_c == nullptr) return;

    g_eval_count = 0;
    g_pm_count = 0;

    *move_r = -1;
    *move_c = -1;
    int _winning_player = 0;
    if (actual_depth != nullptr) *actual_depth = 0;

    _winning_player = AIEval::winningPlayer(gs);
    if (_winning_player != 0) {
        if (winning_player != nullptr) *winning_player = _winning_player;
        return;
    }

    char *_gs = new char[g_gs_size];
    std::memcpy(_gs, gs, g_gs_size);

    AINGM::heuristicNegamax(_gs, player, search_depth, time_limit, true, actual_depth, move_r, move_c);

    std::memcpy(_gs, gs, g_gs_size);
    AIUtils::setCell(_gs, *move_r, *move_c, static_cast<char>(player));

    _winning_player = AIEval::winningPlayer(_gs);

    if (winning_player != nullptr) *winning_player = _winning_player;
    if (node_count != nullptr) *node_count = g_node_count;
    if (eval_count != nullptr) *eval_count = g_eval_count;
    if (pm_count != nullptr) *pm_count = g_pm_count;

    delete[] _gs;
}
