//
// IOManager.cpp for IOManager in /home/alexandre/rendu/Tek3/IA/gomoku
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 14:43:05 2017 Alexandre
// Last update Fri Jan  5 17:19:56 2018 Alexandre
//

#include "IOManager.hpp"

IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

std::string	IOManager::ioRead()
{
  std::string	line;

  std::getline(std::cin, line);
  if (line[line.size() - 1] == '\r')
    {
      line = line.substr(0, line.size() - 1);
      return (line);
    }
  return (NULL);
}

bool		IOManager::ioWrite(std::string line)
{
  if (line.empty())
    return (false);
  std::cout << line << std::endl;
  return (true);
}
