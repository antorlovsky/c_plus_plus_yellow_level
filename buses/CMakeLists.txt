cmake_minimum_required(VERSION 3.20)
project(buses)

set(CMAKE_CXX_STANDARD 17)

add_executable(buses main.cpp query.h query.cpp responses.h responses.cpp bus_manager.h bus_manager.cpp)
