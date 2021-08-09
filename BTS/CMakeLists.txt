cmake_minimum_required(VERSION 3.14)
project(BTS)

set(CMAKE_CXX_STANDARD 14)

add_executable(BTS BTS.cpp mylib.h config.h algo.h load_data.h)