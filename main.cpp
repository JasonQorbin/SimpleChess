#include <iostream>
#include "GamePieces.hpp"



int main(){
    GameBoard gameBoard;
    gameBoard.initializeChessBoard();
    gameBoard.printBoard();
    std::cin.get();
    gameBoard.deleteAllPieces();
    return 0;
}