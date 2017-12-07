#include <cstring>
#include <map.hpp>
#include <other/global.hpp>

Board::Board(unsigned int x, unsigned int y) {
  _size_x = x;
  _size_y = y;
  _map = new char[y * x];
  clearMap();
}

Board::~Board() {}

void Board::clearMap() {
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    _map[i] = '0';
  }
}

void Board::printMap() {
  std::cout << "+" << std::endl;
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    if (i % _size_x == 0 && i != 0)
      std::cout << std::endl;
    if (_map[i] == '0')
      std::cout << ".";
    else
      std::cout << _map[i];
  }
  std::cout << "\n+" << std::endl;
}

void Board::printLinearMap() {
  for (unsigned int i = 0; i < _size_y * _size_x; ++i) {
    if (_map[i] == '0')
      std::cout << ".";
    else
      std::cout << _map[i];
  }
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

char *Controller::gsFromString() {
  char *cmap = new char[_size_x * _size_y];
  std::memcpy(cmap, _map, _size_x * _size_y);
  if (strlen(gs_string) != g_gs_size)
    return;
  for (int i = 0; i < static_cast<int>(g_gs_size); i++) {
    gs[i] = gs_string[i] - '0';
  }
  return cmap;
}
