//
// IOManager.cpp for IOManager in /home/alexandre/rendu/Tek3/IA/gomoku
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 14:43:05 2017 Alexandre
// Last update Thu Nov 30 14:49:08 2017 Alexandre
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

  line = getline(std::cin, line, "\r\n");
  return (line);
}

bool		IOManager::ioWrite(std::string line)
{
  std::cout << line << std::endl;
}
