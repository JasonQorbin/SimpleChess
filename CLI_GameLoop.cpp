//
// Created by Jason on 2023/05/21.
//

#include "CLI_GameLoop.hpp"
#include "GamePieces.hpp"
#include <iostream>
#include <string>
#include <windows.h>

void printBoard(const GameBoard& board) {
    const char* columnLabels = "    A(1) B(2) C(3) D(4)  E(5) F(6) G(7) H(8)\n";
    const char* topBorder =    "   ╔════╤════╤════╤════╤════╤════╤════╤════╗\n";
    const char* middleBorder = "   ╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
    const char* bottomBorder = "   ╚════╧════╧════╧════╧════╧════╧════╧════╝\n";
    //TODO: print the row and column numbers;
    std::string buffer;
    buffer.reserve(850);
    buffer += columnLabels;
    buffer += topBorder;
    for (int currentRow = GameBoard::NUM_ROWS -1 ; currentRow >= 0 ; currentRow--) {
        buffer += currentRow + 49;
        buffer += "  ║";
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
        if (currentRow != 0) buffer += middleBorder;
    }
    buffer += bottomBorder;
    buffer += "\n\n";
    std::cout << buffer << std::flush;
}

bool isInteger(const char* str) {
    bool answer = true;
    short length = strlen(str);
    for (int i = 0; i < length; ++i) {
        char c = str[i];
        if (c > 57 || (c < 48 && c != 43 && c != 45)){
            answer = false;
            break;
        }
    }
    return answer;
}

bool printMovePrompt(const GamePiece::Team currentPlayer, Position* src, Position* dest, const GameBoard& board) {
    using std::cout, std::cin , std::endl;
    const unsigned int INPUT_LIMIT = 10;
    cout << "Current player : " << (currentPlayer == GamePiece::WHITE ? "White" : "Black") <<endl;
    cout << "Piece to move [row;col] : ";
    char start[INPUT_LIMIT];
    cin.getline(start, INPUT_LIMIT);

    char* delimiterPosition = strchr(start, ';');
    if (delimiterPosition == nullptr) return false; //No semicolon found

    char start_first [10];
    char start_second  [10];
    int bytesToCopy = delimiterPosition - start;
    strncpy(start_first, start, bytesToCopy);
    start_first[bytesToCopy] = '\0';
    bytesToCopy =  start + strlen(start) - delimiterPosition - 1;
    strncpy(start_second, delimiterPosition + 1,bytesToCopy);
    start_second[bytesToCopy] = '\0';

    if (!isInteger(start_first)) return false; //Bad input
    if (!isInteger(start_second)) return false; //Bad input

    Position srcPosition (atoi(start_first) - 1, atoi (start_second) -1);
    GamePiece* srcPiece = board.getPiece(srcPosition);
    if (srcPiece == nullptr) {
        cout << "Empty square\n Press enter to try again." << endl;
        cin.get();
        return false;
    } else {
        cout << srcPiece -> printColour() << " " << srcPiece -> getName() << endl;
        if (srcPiece -> pieceColour != currentPlayer) {
            cout << "Selected the opponent's piece instead of your own\n"
                 << "Press enter to try again" << endl;
            cin.get();
            return false;
        }
    }

    char target[INPUT_LIMIT];
    cout << "Destination [row;col]: ";
    cin.getline(target, INPUT_LIMIT);

    delimiterPosition = strchr(target, ';');
    if (delimiterPosition == nullptr) return false; //No semicolon found
    char target_first [10];
    char target_second  [10];
    bytesToCopy =  delimiterPosition - target;
    strncpy(target_first, target,bytesToCopy);
    target_first[bytesToCopy] = '\0';
    bytesToCopy =  target + strlen(target) - delimiterPosition -1;
    strncpy(target_second, delimiterPosition +1, bytesToCopy);
    target_second[bytesToCopy] = '\0';

    if (!isInteger(target_first)) return false; //Bad input
    if (!isInteger(target_second)) return false; //Bad input

    Position destPosition(atoi(target_first) -1, atoi (target_second) -1);

    src-> set(srcPosition.row, srcPosition.col);
    dest-> set(destPosition.row, destPosition.col);

    return true;
}

void enterGameLoop(GameBoard& board){
    GamePiece::Team currentPlayer = GamePiece::WHITE;
    bool running = true;

    while (running) {

        Position src(-1, -1), dest(-1,-1); //These are obviously invalid so don't use them unless successfulInput returns as true.
        bool successfulInput = true;
        // TODO: See if the active player is in check, checkmate or stalemate
        // TODO: reset enpassant flags at the beginning of a player's turn
        while (successfulInput) {
            system("cls");
            printBoard(board);
            successfulInput = printMovePrompt(currentPlayer, &src, &dest, board);
            if (successfulInput) {
                GamePiece* somePiece = board.getPiece(src);
                somePiece->movePiece(src,dest, board);
                currentPlayer = currentPlayer == GamePiece::WHITE ? GamePiece::BLACK : GamePiece::WHITE;
            }
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