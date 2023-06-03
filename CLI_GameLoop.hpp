//
// Created by Jason on 2023/05/21.
//

#ifndef WINCHESS_CLI_GAMELOOP_HPP
#define WINCHESS_CLI_GAMELOOP_HPP

#include "GamePieces.hpp"

void enterGameLoop(GameBoard& board);
void printBoard(const GameBoard& board);
bool printMovePrompt(const GamePiece::Team currentPlayer, Position* src, Position* dest, const GameBoard& board);
bool isInteger(const char* str);

#endif //WINCHESS_CLI_GAMELOOP_HPP
