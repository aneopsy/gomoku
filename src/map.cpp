#include <cstring>
#include <map.hpp>
#include <other/global.hpp>

Board::Board(unsigned int x, unsigned int y) {
  _size_x = x;
  _size_y = y;
  _map = new int[y * x];
  clearMap();
}

Board::~Board() {}

void Board::clearMap() {
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    _map[i] = 0;
  }
}

void Board::printMap() {
  std::cout << "+" << std::endl;
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    if (i % _size_x == 0 && i != 0)
      std::cout << std::endl;
    if (_map[i] == 0)
      std::cout << ".";
    else
      std::cout << _map[i];
  }
  std::cout << "\n+" << std::endl;
}

void Board::printLinearMap() {
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    if (_map[i] == 0)
      std::cout << ".";
    else
      std::cout << _map[i];
  }
}

bool Board::put(unsigned int x, unsigned int y, const int c) {
  if (x > _size_x || y > _size_y)
    return false;
  _map[_size_x * y + x] = c;
  return true;
}

int *Board::getMap() {
  int *tmp = _map;
  return (tmp);
}

int Board::getSize() {
    return (_size_x);
}
