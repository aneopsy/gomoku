//
// IOManager.hpp for IOManager in /home/alexandre/rendu/Tek3/IA/gomoku
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 14:39:12 2017 Alexandre
// Last update Thu Nov 30 15:08:13 2017 Alexandre
//

#ifndef IOMANAGER_HPP_
# define IOMANAGER_HPP_

#include <string>
#include <iostream>

class	IOManager
{
public:
  IOManager();
  ~IOManager();
  static std::string	ioRead();
  static bool		ioWrite(std::string);

};

#endif /* !IOMANAGER_HPP_ */
