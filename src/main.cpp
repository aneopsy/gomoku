#include "API.hpp"
#include <controller.hpp>
#include <cstring>
#include <iostream>
#include <map.hpp>
#include <other/global.hpp>

int main(int ac, char const *av[]) {
  int i = 0;
  std::string line;

  API a;

  while ((line = IOManager::ioRead()) != "END") {
      std::cout << "ok" <<std::endl;
    std::unordered_map<std::string, API::memFct>::const_iterator result =
        API::fctMap.find(line);

    if (result != API::fctMap.end())
      (a.*(result->second))(0, 0);
    else
      a.apiNothing(0, 0);
  }
}
