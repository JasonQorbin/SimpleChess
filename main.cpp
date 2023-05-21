#include <iostream>
#include "GamePieces.hpp"
#include "CLI_GameLoop.hpp"

int main(){
    GameBoard gameBoard;
    gameBoard.initializeChessBoard();

    enterGameLoop(gameBoard);



    std::cin.get();
    gameBoard.deleteAllPieces();
    return 0;
}
