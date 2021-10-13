cmake_minimum_required(VERSION 3.20)
project(final)

set(CMAKE_CXX_STANDARD 17)

add_executable(final main.cpp token.cpp token.h condition_parser.cpp condition_parser.h condition_parser_test.cpp test_runner.h date.cpp date.h database.cpp database.h node.cpp node.h)
