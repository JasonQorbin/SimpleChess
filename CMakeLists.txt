cmake_minimum_required(VERSION 3.25)
project(WinChess)

set(CMAKE_CXX_STANDARD 17)

add_executable(WinChess main.cpp GamePieces.cpp GamePieces.hpp CLI_GameLoop.cpp CLI_GameLoop.hpp)
