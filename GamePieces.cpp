//
// Created by Jason on 2023/05/13.
//

#include "GamePieces.h"

GamePiece::GamePiece(char* sym, colour col, int row, int column) : symbol(sym), pieceColour(col){
    position.row = row;
    position.col = column;
}


std::string GamePiece::getPaddedSymbol() const {
    std::string buffer;

    if (strlen(symbol) == 0) {
        buffer += "    "; //four spaces
        return buffer;
    }

    buffer += " ";
    int counter = 0;
    while (symbol[counter] != '\0'){
        buffer += symbol[counter];
        counter++;
    }
    buffer += " ";
    if (buffer.size() < 4) buffer += " ";
    return buffer;
}


GameBoard::GameBoard(){zeroBoard();}

GameBoard::~GameBoard(){ deleteAllPieces();}

GameBoard::GameBoard( const GameBoard& otherBoard) {
    for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
        for (int currentCol = 0; currentCol < NUM_COLS; currentCol++) {
            GamePiece* pieceToCopy = otherBoard.getPiece(currentRow, currentCol);
            if (pieceToCopy == nullptr) {
                board[currentRow][currentCol] = nullptr;
            } else {
                board[currentRow][currentCol] = new GamePiece(pieceToCopy->symbol, pieceToCopy->pieceColour, currentRow, currentCol);
            }
        }
    }
}

GamePiece* GameBoard::getPiece (int row, int col) const{
    return board[row] [col];
}

void GameBoard::printBoard() {
    const char *topBorder = "╔════╤════╤════╤════╤════╤════╤════╤════╗\n";
    const char *middleBorder = "╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
    const char *bottomBorder = "╚════╧════╧════╧════╧════╧════╧════╧════╝\n";

    std::string buffer;
    buffer.reserve(750);
    buffer += topBorder;
    for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
        buffer += "║";
        for (int currentCol = 0; currentCol < NUM_COLS; currentCol++) {
            GamePiece *currentPiece = board[currentRow][currentCol];
            if (currentPiece != nullptr) {
                buffer += currentPiece->getPaddedSymbol();
            } else {
                buffer += "    "; //four spaces
            }
            buffer += currentCol == NUM_COLS - 1 ? "║" : "│";
        }
        buffer += "\n";
        if (currentRow != NUM_ROWS - 1) buffer += middleBorder;
    }
    buffer += bottomBorder;
    buffer += "\n";
    std::cout << buffer << std::flush;

}

void GameBoard::zeroBoard() {
    for (int rows = 0; rows < NUM_ROWS; rows++) {
        for (int cols = 0; cols < NUM_COLS; cols++) {
            board[rows][cols] = nullptr;

        }
    }
}

void GameBoard::deleteAllPieces() {
    for (int rows = 0; rows < NUM_ROWS; rows++) {
        for (int cols = 0; cols < NUM_COLS; cols++) {
            GamePiece* toRemove = board[rows][cols];
            if (toRemove != nullptr) {delete toRemove;}
        }
    }
}

void GameBoard::deletePiece(GamePiece* toDelete){
    if (toDelete != nullptr) delete toDelete;
}

void GameBoard::deletePiece(int row, int col) {
    deletePiece(getPiece(row, col));
}

void GameBoard::initializeChessBoard(){
    const char* backLine [] = {"R", "Kn", "Bi", "Ki", "Qu", "Bi", "Kn", "R"};
    const char* pawnLine [] = {"p", "p", "p", "p", "p", "p", "p", "p"};
    for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
        for (int currentColumn = 0; currentColumn < NUM_COLS; currentColumn++) {
            switch (currentRow){
                case 0:
                    board[currentRow][currentColumn] = new GamePiece((char*)(backLine[currentColumn]), GamePiece::colour::BLACK, currentRow, currentColumn);
                    break;

                case 1:
                    board[currentRow][currentColumn] = new GamePiece((char*)(pawnLine[currentColumn]), GamePiece::colour::BLACK, currentRow, currentColumn);
                    break;

                case 6:
                    board[currentRow][currentColumn] = new GamePiece((char*)(pawnLine[currentColumn]), GamePiece::colour::WHITE, currentRow, currentColumn);
                    break;

                case 7:
                    board[currentRow][currentColumn] = new GamePiece((char*)(backLine[currentColumn]), GamePiece::colour::WHITE, currentRow, currentColumn);
                    break;
                default:
                    board[currentRow][currentColumn] = nullptr;
            }
        }
    }
}
