#include <controller.hpp>
#include <ai/manager.hpp>
#include <ai/utils.hpp>
#include <other/global.hpp>
#include <map.hpp>
#include <cstring>
#include <iostream>

bool Controller::generateMove(Board map, int ai_player_id,
                            int search_depth, int time_limit, int num_threads,
                            int *actual_depth, int *move_r, int *move_c, int *winning_player,
                            unsigned int *node_count, unsigned int *eval_count, unsigned int *pm_count) {
    if (ai_player_id  < 1 || ai_player_id > 2 ||
        search_depth == 0 || search_depth > 10 ||
        time_limit < 0    ||
        num_threads  < 1) {
        return false;
    }
    AIManager::generateMove(map.getMap(), ai_player_id, search_depth, time_limit, actual_depth,
                                    move_r, move_c, winning_player, node_count, eval_count, pm_count);
    return true;
}
