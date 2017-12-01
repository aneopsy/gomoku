#include <cstring>
#include <map.hpp>
#include <other/global.hpp>

Board::Board(unsigned int x, unsigned int y) {
  _size_x = x;
  _size_y = y;
  _map = new char[y*x];
  clearMap();
}

Board::~Board() {}

void Board::clearMap() {
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    _map[i] = '.';
  }
}

void Board::printMap() {
  std::cout << "+" << std::endl;
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    if (i % _size_x == 0 && i != 0)
        std::cout << std::endl;
    std::cout << _map[i];
  }
  std::cout << "\n+" << std::endl;
}

bool Board::put(unsigned int x, unsigned int y, const char c) {
  if (x > _size_x || y > _size_y)
    return false;
  _map[_size_x * y + x] = c;
  return true;
}

char *Board::getMap() {
    char *tmp = _map;
    return (tmp);
}
