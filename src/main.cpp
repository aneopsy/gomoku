#include "API.hpp"
#include <controller.hpp>
#include <cstring>
#include <iostream>
#include <map.hpp>
#include <other/global.hpp>
#include <vector>

std::string	splitCmd(std::string line)
{
  std::string	cmd;
  int		pos;

  pos = line.find(' ');
  cmd = line.substr(0, pos);
  return (cmd);
}

std::vector<int>	haveArgs(std::string line)
{
  int		pos;
  int		pos2;
  std::vector<int>	args(2);
  std::string		fir;
  std::string		sec;

  pos = line.find(' ');
  if (pos != std::string::npos)
    {
      pos2 = line.find(',');
      if (pos2 != std::string::npos)
	{
	  fir = line.substr(pos + 1, pos2);
	  sec = line.substr(pos2);
	    // std::cout << fir << std::endl;
	    // std::cout << sec << std::endl;

	}
      else
	{
	  fir = line.substr(pos + 1);
	    // std::cout << fir << std::endl;
	}
    }
  args.push_back(std::atoi(fir.c_str()));
  args.push_back(std::atoi(sec.c_str()));
  return (args);
}

int main(int ac, char const *av[]) {
  int i = 0;
  std::string line;
  std::string cmd;
  std::vector<int>	args(2);
  API a;

  while ((line = IOManager::ioRead()) != "END") {
    Logger::logWrite(INFO, line);
    cmd = splitCmd(line);
    // std::cout << cmd << std::endl;
    args = haveArgs(line);
    std::unordered_map<std::string, API::memFct>::const_iterator result =
        API::fctMap.find(cmd);
    if (result != API::fctMap.end())
      (a.*(result->second))(args[0], args[1]);
    else
      a.apiNothing(0, 0);
    args.clear();
  }
}
