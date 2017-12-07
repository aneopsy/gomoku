//
// Logger.hpp for Logger in /home/alexandre/rendu/Tek3/IA/gomoku/test
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 15:54:09 2017 Alexandre
// Last update Thu Nov 30 16:14:29 2017 Alexandre
//

#ifndef LOGGER_HPP_
# define LOGGER_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

enum	logType
  {
    INFO = 0,
    WARNING,
    ERROR,
  };

class   Logger
{
public:
  Logger();
  ~Logger();
  // static std::string	ioRead();
  static bool		logWrite(logType, std::string);

};

#endif /* !LOGGER_HPP_ */
