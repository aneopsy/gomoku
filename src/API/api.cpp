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

API::API()
{
}

API::~API()
{
}

API::apiStart(int size)
{
  std::string	answer;

  answer = "OK - everything is good";
  IOManager::ioWrite(answer);
  Logger::logWrite(INFO, answer);
}

API::apiBegin()
{
  int	x;
  int	y;

  // SEND POSITIONS
}

API::apiTurn(int x, int y)
{
  // MISE A JOUR MAP

  int	my_x;
  int	my_y;

  // SEND POSITIONS
}

API::apiBoard()
{
  // RECUP INFOS

  // SEND POSITIONS
}

API::apiEnd()
{
  // DELETE TEMP FILES

}
