//
// Logger.cpp for Logger in /home/alexandre/rendu/Tek3/IA/gomoku/test
//
// Made by Alexandre
// Login   <alexandre@epitech.net>
//
// Started on  Thu Nov 30 15:57:12 2017 Alexandre
// Last update Thu Nov 30 16:28:18 2017 Alexandre
//

#include "Logger.hpp"

Logger::Logger()
{
}

Logger::~Logger()
{
}

// std::string	Logger::ioRead()
// {
//   std::string	line;

//   std::getline(std::cin, line, '\r');
//   return (line);
// }

const std::string currentDateTime()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];

  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}

bool		Logger::logWrite(logType typeNum, std::string line)
{
  std::fstream	file;
  std::string	type;

  switch (typeNum)
    {
    case 0:
      {
	type = "INFO";
	break;
      }
    case 1:
      {
	type = "WARNING";
	break;
      }
    case 2:
      {
	type = "ERROR";
      }
    }

  file.open("log.txt", std::fstream::out | std::fstream::app);

  if (!file.is_open() && line.empty())
    return (false);
  file <<  currentDateTime() << " " << type << ": " << line << std::endl;
  return (true);
}
