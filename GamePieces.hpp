//
// Created by Jason on 2023/05/13.
//

#ifndef WINCHESS_GAMEPIECES_HPP
#define WINCHESS_GAMEPIECES_HPP

#include <string>
#include <cstring>
#include <utility>
#include <vector>
#include <iostream>


class GamePiece;
class Position;

class GameBoard {
public:
    static const int NUM_ROWS = 8;
    static const int NUM_COLS = 8;
    GamePiece* board[NUM_ROWS][NUM_COLS];

    GameBoard();
    ~GameBoard();
    GameBoard( const GameBoard& otherBoard);
    GamePiece* getPiece (int row, int col) const;
    GamePiece* getPiece (const Position& position) const;
//    void printBoard();
    void zeroBoard();
    void deleteAllPieces();
    void initializeChessBoard();
    void movePiece(Position src, Position dest);

private:
    void setPiece(GamePiece* piece, Position position);
    void deletePiece(Position position);
    void deletePiece(int row, int col);
};

struct Position {
    int row;
    int col;

    Position(int row, int col) {
        set(row, col);
    }

    void set(int row, int col) {
        this -> row = row;
        this -> col = col;
    }

    void move(int horizontalShift, int verticalShift){
        col += horizontalShift;
        row += verticalShift;
    }

    bool positionValid(){
        return (row >= 0 && row < GameBoard::NUM_ROWS && col >= 0 && col < GameBoard::NUM_COLS);
    }

    std::string toString() {
        std::string answer;
        answer += "[ ";
        answer += std::to_string(row);
        answer += " ; ";
        answer += std::to_string(col);
        answer  += " ]";
        return answer;
    }

    Position offset(int horizontalShift, int verticalShift) const{
        return Position(row + horizontalShift, col + verticalShift);
    }

    bool operator==(const Position& otherPosition) const{
        return row == otherPosition.row && col == otherPosition.col;
    }

    bool operator!=(const Position& otherPosition) const {
        return row != otherPosition.row || col != otherPosition.col;
    }

    int distanceBetween(const Position& otherPosition) const {
        int rowDiff = row - otherPosition.row;
        if (rowDiff < 0) rowDiff *= -1;


        int colDiff = col - otherPosition.col;
        if (colDiff < 0) colDiff *= -1;

        return rowDiff > colDiff ? rowDiff : colDiff;
    }
};

class GamePiece{
public:
    enum Team {
        WHITE,
        BLACK
    };

    Team pieceColour;
    std::vector<Position> possibleMoves;

    GamePiece() {
        pieceColour = WHITE;
        name = "None";
    }
    GamePiece(Team col);
    virtual ~GamePiece(){}
    bool isEnemyPiece(GamePiece* otherPiece) const;
    bool isFriendlyPiece(GamePiece* otherPiece) const;
    virtual std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) = 0;
    virtual std::string getPaddedSymbol() {return "";} ;
    std::string getName() {return name;}
    virtual void movePiece(Position currentPosition, Position dest, GameBoard& board);
    std::string printColour() {
        return pieceColour == WHITE ? "White" : "Black";
    }
protected:
    std::string name;
    std::vector<Position> getHorizontalMoves(const GameBoard& board, Position currentPosition, int range);
    std::vector<Position> getVerticalMoves(const GameBoard& board, Position currentPosition, int range);
    std::vector<Position> getDiagonalMoves(const GameBoard& board, Position currentPosition, int range);

    std::vector<Position> getLinearMoves(const GameBoard &board, Position currentPosition, Position startPosition,
                                         Position endPosition, int horizontalStep, int verticalStep) const;
};

class Rook : public GamePiece{
private:
    bool castlingRights;

public:
    Rook(Team side) {
        pieceColour = side;
        castlingRights = true;
        name = "Rook";
    }

    std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) override;
    std::string getPaddedSymbol() override;
    void movePiece(Position currentPosition, Position dest, GameBoard& board) override {
        GamePiece::movePiece(currentPosition, dest, board);
        onMove();
    }
    void onMove();
};

class Bishop : public GamePiece{
public:
    Bishop(Team side) {
        pieceColour = side;
        name = "Bishop";
    }

    std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) override;
    std::string getPaddedSymbol() override;
};

class Queen : public GamePiece{
public:
   Queen(Team side) {
        pieceColour = side;
        name = "Queen";
    }

    std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) override;
    std::string getPaddedSymbol() override;
};

class King : public GamePiece{
private:
    bool castlingRights;

public:
    King(Team side) {
        pieceColour = side;
        castlingRights = true;
        name = "King";
    }

    std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) override;
    std::string getPaddedSymbol() override;
    void movePiece(Position currentPosition, Position dest, GameBoard& board) override {
        GamePiece::movePiece(currentPosition, dest, board);
        onMove();
    }
    void onMove();

};

class Knight : public GamePiece{
public:
    Knight(Team side) {
        pieceColour = side;
        name = "Knight";
    }

    std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) override;
    std::string getPaddedSymbol() override;
};

class Pawn : public GamePiece{
private:
    bool hasMoved;
    bool enPassantAllowed;
public:
    Pawn(Team side) {
        pieceColour = side;
        hasMoved = false;
        enPassantAllowed = false;
        name = "Pawn";
    }

    std::vector<Position> getPossibleMoves(const GameBoard& board, Position currentPosition) override;
    std::string getPaddedSymbol() override;
    void movePiece(Position currentPosition, Position dest, GameBoard& board) override{
        GamePiece::movePiece(currentPosition, dest, board);
        onMove(currentPosition.distanceBetween(dest));
    }
    void onMove(int distanceMoved);

    bool enPassantIsAllowed();
};

#endif //WINCHESS_GAMEPIECES_HPP
