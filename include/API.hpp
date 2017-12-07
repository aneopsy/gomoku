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
#define API_HPP

#include "IOManager.hpp"
#include "Logger.hpp"
#include "map.hpp"
#include <array>
#include <map>
#include <unordered_map>

class API {
public:
  // void  (API::*memFct[7])(int, int);

  void apiStart(int, int);   // int
  void apiBegin(int, int);   // Nothing
  void apiTurn(int, int);    // int, int
  void apiInfo(int, int);    // Nothing
  void apiBoard(int, int);   // Nothing
  void apiEnd(int, int);     // Nothing
  void apiNothing(int, int); // Nothing

  // void  init_memFct(void (API::* )(int, int));

  API();
  ~API();

  // static void  (API::* memFct[7])(int, int);
  // typedef void    (API::* memFct)(int, int);
  //  memFct  a[7]{&API::apiStart, &API::apiBegin, &API::apiTurn, &API::apiInfo,
  //  &API::apiBoard, &API::apiEnd, &API::apiNothing};

  // static unordered map std::string memFct
  // memFct  *test;
  typedef void (API::*memFct)(int, int);
  static std::unordered_map<std::string, memFct> const fctMap;

  Board map = Board(0, 0);
};

// fctMap["START"] = &API::apiStart;

#endif /* !API_HPP */
