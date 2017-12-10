//
// api.cpp for API in /home/alexandre/rendu/Tek3/IA/gomoku/test
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 16:55:45 2017 Alexandre
// Last update Thu Nov 30 17:03:53 2017 Alexandre
//

#include "API.hpp"
#include "map.hpp"
#include <controller.hpp>
#include <cstring>
#include <iostream>
#include <map.hpp>
#include <other/global.hpp>

API::API() {}

API::~API() {}

void play(Board map, int time_limit) {
  int move_r, move_c, winning_player, actual_depth;
  unsigned int node_count, eval_count;

  bool success = Controller::generateMove(
      map, 1, -1, time_limit, 1, &actual_depth, &move_r, &move_c,
      &winning_player, &node_count, &eval_count, nullptr);

  if (success) {
    std::cout << 1 << " : MESSAGE"
              << " d=" << actual_depth << " node_cnt=" << node_count
              << " eval_cnt=" << eval_count << std::endl;

    map.put(move_r, move_c, 1);

    std::cout << move_c << "," << move_r << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }
}

void splitLine(const char *line, int *output) {
  size_t in_length = strlen(line);
  char *_line = new char[in_length];
  memcpy(_line, line, in_length);

  int pos = 0, seg_idx = 0, seg_begin = 0;

  while (_line[pos] != 0) {
    if (_line[pos] == ',') {
      _line[pos] = 0;
      output[seg_idx++] = atoi(&_line[seg_begin]);
      seg_begin = pos + 1;
    }
    ++pos;
  }
  output[seg_idx] = atoi(&line[seg_begin]);
  delete[] _line;
}

void API::apiStart(int size, int a) {
  std::string answer;

  this->map = Board(size, size);
  answer = "OK - everything is good";
  IOManager::ioWrite(answer);
  Logger::logWrite(INFO, answer);
}

void API::apiBegin(int a, int b) {
  int x;
  int y;
  std::string answer;

  x = this->map.getSize() / 2;
  y = x;
  answer = std::to_string(x) + " " + std::to_string(y);
  IOManager::ioWrite(answer);
  this->map.put(x, y, 1);
}

void API::apiTurn(int x, int y) {
  this->map.put(x, y, 2);
  play(this->map, 5000);
}

void API::apiBoard(int a, int b) {
  char line[256];

  this->map.clearMap();
  while (std::cin.getline(line, 256)) {
    if (strncmp(line, "DONE", 4) == 0) {
      break;
    } else {
      int values[3] = {-1, -1, -1};
      splitLine(line, values);
      this->map.put(values[0], values[1], values[2]);
    }
  }
  play(this->map, 5000);
}

void API::apiEnd(int a, int b) {
  // DELETE TEMP FILES
  // IOManager::ioWrite("I received End");
}

void API::apiNothing(int a, int b) {
  std::string line;
  // std::cout << "NOTHING" << std::endl;
  line = "UNKNOWN";
  IOManager::ioWrite(line);
}

void API::apiInfo(int a, int b) { std::cout << "INFO" << std::endl; }

std::unordered_map<std::string, API::memFct> const API::fctMap = {
    {"START", &API::apiStart}, {"BEGIN", &API::apiBegin},
    {"TURN", &API::apiTurn},   {"INFO", &API::apiInfo},
    {"BOARD", &API::apiBoard}, {"END", &API::apiEnd}};
