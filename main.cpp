#include <iostream>
#include "GamePieces.h"



int main(){
    GameBoard gameBoard;
    gameBoard.initializeChessBoard();
    gameBoard.printBoard();
    std::cin.get();
    return 0;
}