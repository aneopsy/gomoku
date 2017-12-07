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

void  API::apiStart(int size, int a)
{
  std::string	answer;

  this->map = Board(size - 1, size - 1);
  answer = "OK - everything is good";
  IOManager::ioWrite(answer);
  Logger::logWrite(INFO, answer);
}

void API::apiBegin(int a, int b)
{
  int	x;
  int	y;
  std::string answer;

    x = this->map.getsSize() / 2;
    y = x;
    answer = std::to_string(x) + " " + std::to_string(y);
    IOManager::ioWrite(answer);
    this->map.put(x, y , '1');
}

void  API::apiTurn(int x, int y)
{
  int	my_x;
  int	my_y;


    this->map.put(x, y, '2');

    // SEARCH POSITIONS
  // SEND POSITIONS
    // MISE A JOUR MAP
}

void  API::apiBoard(int a, int b)
{
    std::string line;
    std::string newline;

    while ((line = IOManager::IORead()) != "DONE")
    {
        line.substr(0, line.find(","));
        std::cout << line << std::cout;
    }
  // RECUP INFOS

  // SEND POSITIONS

  // MISE A JOUR MAP
}

void  API::apiEnd(int a, int b)
{
  // DELETE TEMP FILES
  //IOManager::ioWrite("I received End");

}

void    API::apiNothing(int a, int b)
{
    std::string line;
    //std::cout << "NOTHING" << std::endl;
    line = "UNKNOWN";
    IOManager::IOWrite(line);
}

void    API::apiInfo(int a, int b)
{
    std::cout << "INFO" << std::endl;
}

std::unordered_map<std::string, API::memFct> const API::fctMap = {
        { "START", &API::apiStart },
        { "BEGIN", &API::apiBegin },
        { "TURN", &API::apiTurn },
        { "INFO", &API::apiInfo },
        { "BOARD", &API::apiBoard },
        { "END", &API::apiEnd }
};