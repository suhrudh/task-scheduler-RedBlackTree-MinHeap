cmake_minimum_required(VERSION 3.15)
project(ADS)

set(CMAKE_CXX_STANDARD 14)

add_executable(ADS risingCity.cpp structure.h Building.h structure.cpp Nodes.h)