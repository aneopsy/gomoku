#include "IOManager.hpp"
#include "Logger.hpp"
#include "API.hpp"

void    init_fctMap()
{
    //fctMap.emplace("START", &API::apiStart);
    //fctMap.emplace("BEGIN", &API::apiBegin);
    //fctMap.emplace("TURN", &API::apiTurn);
    //fctMap.emplace("INFO", &API::apiInfo);
    //fctMap.emplace("BOARD", &API::apiBoard);
    //fctMap.emplace("END", &API::apiEnd);
    //fctMap.emplace("NOTHING", &API::apiNothing);
}

//void    addInFctMap(memFct function, std::string name)
//{
//    fctMap.insert(name, function);


//}

int	main()
{
  int	i = 0;
    std::string line;

  API a;
  //API *b = new API;

  //  memFct  test;

  while ((line = IOManager::ioRead()) != "END")
    {
      // IOManager::ioWrite(IOManager::ioRead());

        // IOMANAGER
      //std::cout << IOManager::ioRead();
      //IOManager::ioWrite("salut");

        // LOGGER
      //Logger::logWrite(WARNING, "test");
      //Logger::logWrite(INFO, "test");
      //Logger::logWrite(ERROR, "test");


        // API
      //API::memFct[2](0,0);
      //API::a[2](0, 0);
      //API::memFct[2](0, 0);
      //(a.*memFct)[2](0, 0);
        //API::*memFct[2](0,0);
        //(b.*test[1])(0, 0)
        //API::test[1](0, 0);
        //(b->*(b->test[1]))(0, 0);

        //b->apiStart(0, 0);

        //addInFctMap(&b->apiStart, "START");
        //addInFctMap(&API::apiStart, "START");
        //addInFctMap(&b->*b->apiStart, "START");

        //fctMap.insert("START", &API::apiStart);
        //init_fctMap();
        //fctMap.find("START");
        //test = fctMap["START"];
        //fctMap[]
        //fctMap["START"](0, 0);
        //test.second(0, 0);
        //std::string str = "START";
        //fctMap.at[str]->second(0,0);

        //std::unordered_map<std::string, memFct>::iterator i;
        //i = fctMap.begin();
        //(*i->second)(0, 0);


        std::unordered_map<std::string, API::memFct>::const_iterator result = API::fctMap.find(line);

        if(result != API::fctMap.end())
            (a.*(result->second))(0, 0);
        else
            a.apiNothing(0, 0);

        //std::cout << result << std::endl;

        //API::fctMap[0](0, 0);

        //std::cout << (*b).a << std::endl;
    }

}
