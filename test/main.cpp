#include "IOManager.hpp"
#include "Logger.hpp"

int	main()
{
  int	i = 0;
  while (i++ < 1)
    {
      // IOManager::ioWrite(IOManager::ioRead());
      std::cout << IOManager::ioRead();
      IOManager::ioWrite("salut");
      Logger::logWrite(WARNING, "test");
      Logger::logWrite(INFO, "test");
      Logger::logWrite(ERROR, "test");
    }
}
