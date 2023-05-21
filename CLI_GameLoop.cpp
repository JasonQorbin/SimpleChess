//
// Created by Jason on 2023/05/21.
//

#include "CLI_GameLoop.hpp"
#include "GamePieces.hpp"
#include <iostream>
#include <string>

void printBoard(const GameBoard& board) {
    const char *topBorder = "╔════╤════╤════╤════╤════╤════╤════╤════╗\n";
    const char *middleBorder = "╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
    const char *bottomBorder = "╚════╧════╧════╧════╧════╧════╧════╧════╝\n";
    //TODO: print the row and column numbers;
    std::string buffer;
    buffer.reserve(750);
    buffer += topBorder;
    for (int currentRow = 0; currentRow < GameBoard::NUM_ROWS; currentRow++) {
        buffer += "║";
        for (int currentCol = 0; currentCol < GameBoard::NUM_COLS; currentCol++) {
            GamePiece *currentPiece = board.getPiece(currentRow,currentCol);
            if (currentPiece != nullptr) {
                buffer += currentPiece->getPaddedSymbol();
            } else {
                buffer += "    "; //four spaces
            }
            buffer += currentCol == GameBoard::NUM_COLS - 1 ? "║" : "│";
        }
        buffer += "\n";
        if (currentRow != GameBoard::NUM_ROWS - 1) buffer += middleBorder;
    }
    buffer += bottomBorder;
    buffer += "\n\n";
    std::cout << buffer << std::flush;
}

bool isInteger(const char* str) {
    bool answer = true;
    char c = *str;
    while (c != '\0') {
        if (c > 57 || (c < 48 && c != 43 && c != 45)){
            answer = false;
            break;
        }
    }
    return answer;
}

bool printMovePrompt(const GamePiece::Team currentPlayer, Position* src, Position* dest) {
    using std::cout, std::cin , std::endl;
    const unsigned int INPUT_LIMIT = 10;
    cout << "Current player : " << (currentPlayer == GamePiece::WHITE ? "White" : "Black") <<endl;
    cout << "Piece to move [ row; col] : ";
    char start[INPUT_LIMIT];
    cin.getline(start, INPUT_LIMIT);

    char* delimiterPosition = strchr(start, ';');
    if (delimiterPosition == nullptr) return false; //No semicolon found

    char start_first [10];
    char start_second  [10];
    strncpy(start_first, start, delimiterPosition - start);
    strncpy(start_second, start, start + strlen(start) - delimiterPosition);

    if (!isInteger(start_first)) return false; //Bad input
    if (!isInteger(start_second)) return false; //Bad input

    char target[INPUT_LIMIT];
    cout << "Destination : ";
    cin.getline(target, INPUT_LIMIT);

    char target_first [10];
    char target_second  [10];
    strncpy(target_first, target, delimiterPosition - target);
    strncpy(target_second, target, target + strlen(target) - delimiterPosition);

    if (!isInteger(target_first)) return false; //Bad input
    if (!isInteger(target_second)) return false; //Bad input
    src-> set(atoi(start_first), atoi (start_second));
    dest-> set(atoi(target_first), atoi (target_second));
    return true;
}

void enterGameLoop(const GameBoard& board){
    GamePiece::Team currentPlayer = GamePiece::WHITE;
    bool running = true;

    while (running) {
        //Position to get the desired player move
        Position src(-1, -1), dest(-1,-1); //These are obviously invalid so don't use them unless successfulInput returns as true.
        bool successfulInput = false;
        // TODO: See if the active player is in check, checkmate or stalemate
        // TODO: reset enpassant flags
        while (!successfulInput) {
            system("cls");
            printBoard(board);
            successfulInput = printMovePrompt(currentPlayer, &src, &dest);
        }

        /*
         * Find the piece at src
         * get its move list
         * if dest is in the list then  ask the board to do the move.
         * do onMove calls
         * repeat
        */
        running = false;
    }

}