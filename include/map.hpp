#ifndef INCLUDE_MAP_HPP_
#define INCLUDE_MAP_HPP_

#include <iostream>
#include <map>
#include <string>

class Board {
  int *_map;
  unsigned int _size_y;
  unsigned int _size_x;

public:
  Board(unsigned int x, unsigned y);
  ~Board();
  void printMap();
  void clearMap();
  bool put(unsigned int x, unsigned int y, const int c);
  int *getMap();
  int getSize();
  void printLinearMap();
  char *convert();
};

#endif
