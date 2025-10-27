cmake_minimum_required(VERSION 4.0)
project(connect_four_strategies)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(connect_four_strategies
        ConnectFour.cpp
        ConnectFour.h
        Player.cpp
        Player.h
        strategies.cpp)
