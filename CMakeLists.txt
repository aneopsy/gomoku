cmake_minimum_required(VERSION 3.5)
project(gomoku)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -W -Wall -Wl,--no-as-needed")

include_directories(include)

SET(SRCS src/main.cpp
         src/other/global.cpp
         src/ai/eval.cpp
         src/ai/manager.cpp
         src/ai/NGM.cpp
         src/ai/utils.cpp
         src/controller.cpp
         src/map.cpp

          include/other/global.hpp
          include/ai/eval.hpp
          include/ai/manager.hpp
          include/ai/NGM.hpp
          include/ai/utils.hpp
          include/controller.hpp
          include/map.hpp
)
add_executable(gomoku "${SRCS}")
