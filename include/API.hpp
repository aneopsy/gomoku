//
// API.hpp for API in /home/alexandre/rendu/Tek3/IA/gomoku/test
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 16:30:36 2017 Alexandre
// Last update Thu Nov 30 16:58:55 2017 Alexandre
//

#ifndef API_HPP
# define API_HPP

#include "IOManager.hpp"
#include "Logger.hpp"

class	API
{
private:
  apiStart(int);
  apiBegin();
  apiTurn(int, int);
  apiInfo();
  apiBoard();
  apiEnd();

public:
  API();
  ~API();

};

#endif /* !API_HPP */
