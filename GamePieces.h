//
// Created by Jason on 2023/05/13.
//

#ifndef WINCHESS_GAMEPIECES_H
#define WINCHESS_GAMEPIECES_H

#include <string>
#include <cstring>
#include <vector>
#include <iostream>

struct Position {
    int row;
    int col;
};

class GameBoard;

class GamePiece{
public:
    enum colour {
        WHITE,
        BLACK
    };

    char* symbol;
    colour pieceColour;
    Position position;

    GamePiece(char* sym, colour col, int row, int column);
    std::string getPaddedSymbol() const;
    std::vector<Position> getPossibleMoves(GameBoard board) const;
};


class GameBoard {
public:
    static const int NUM_ROWS = 8;
    static const int NUM_COLS = 8;
    GamePiece* board[NUM_ROWS][NUM_COLS];

    GameBoard();
    ~GameBoard();
    GameBoard( const GameBoard& otherBoard);
    GamePiece* getPiece (int row, int col) const;
    void printBoard();
    void zeroBoard();
    void deleteAllPieces();
    void deletePiece(GamePiece* toDelete);
    void deletePiece(int row, int col);
    void initializeChessBoard();
};



#endif //WINCHESS_GAMEPIECES_H
