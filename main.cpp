#include <vector>
#include <iostream>
#include <string>
#include <cstring>

struct Position {
    int row;
    int col;
};

class GameBoard;

class Piece {
public:
    enum colour {
        WHITE,
        BLACK
    };

    char* symbol;
    colour pieceColour;
    Position position;
    Piece(char* sym, colour col, int row, int column) : symbol(sym), pieceColour(col){
        position.row = row;
        position.col = column;
    };


    std::string getPaddedSymbol(){
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


};

class GameBoard {
public:
    static const int NUM_ROWS = 8;
    static const int NUM_COLS = 8;
    Piece* board[NUM_ROWS][NUM_COLS];

    GameBoard(){zeroBoard();}

    ~GameBoard(){ deleteAllPieces();}

    GameBoard( const GameBoard& otherBoard) {
        for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
            for (int currentCol = 0; currentCol < NUM_COLS; currentCol++) {
                Piece* pieceToCopy = otherBoard.getPiece(currentRow, currentCol);
                if (pieceToCopy == nullptr) {
                    board[currentRow][currentCol] = nullptr;
                } else {
                    board[currentRow][currentCol] = new Piece( pieceToCopy->symbol, pieceToCopy->pieceColour, currentRow, currentCol);
                }
            }
        }
    }

    Piece* getPiece (int row, int col) const{
        return board[row] [col];
    }

    void printBoard() {
        const char *topBorder = "╔════╤════╤════╤════╤════╤════╤════╤════╗\n";
        const char *middleBorder = "╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        const char *bottomBorder = "╚════╧════╧════╧════╧════╧════╧════╧════╝\n";

        std::string buffer;
        buffer.reserve(750);
        buffer += topBorder;
        for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
            buffer += "║";
            for (int currentCol = 0; currentCol < NUM_COLS; currentCol++) {
                Piece *currentPiece = board[currentRow][currentCol];
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

    void zeroBoard() {
        for (int rows = 0; rows < NUM_ROWS; rows++) {
            for (int cols = 0; cols < NUM_COLS; cols++) {
                board[rows][cols] = nullptr;

            }
        }
    }

    void deleteAllPieces() {
        for (int rows = 0; rows < NUM_ROWS; rows++) {
            for (int cols = 0; cols < NUM_COLS; cols++) {
                Piece* toRemove = board[rows][cols];
                if (toRemove != nullptr) {delete toRemove;}
            }
        }
    }

    void deletePiece(Piece* toDelete){
        if (toDelete != nullptr) delete toDelete;
    }

    void deletePiece(int row, int col) {
        deletePiece(getPiece(row, col));
    }

    void initializeChessBoard(){
        const char* backLine [] = {"R", "Kn", "Bi", "Ki", "Qu", "Bi", "Kn", "R"};
        const char* pawnLine [] = {"p", "p", "p", "p", "p", "p", "p", "p"};
        for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
            for (int currentColumn = 0; currentColumn < NUM_COLS; currentColumn++) {
                switch (currentRow){
                    case 0:
                        board[currentRow][currentColumn] = new Piece((char*)(backLine[currentColumn]), Piece::colour::BLACK, currentRow, currentColumn);
                        break;

                    case 1:
                        board[currentRow][currentColumn] = new Piece((char*)(pawnLine[currentColumn]), Piece::colour::BLACK, currentRow, currentColumn);
                        break;

                    case 6:
                        board[currentRow][currentColumn] = new Piece((char*)(pawnLine[currentColumn]), Piece::colour::WHITE, currentRow, currentColumn);
                        break;

                    case 7:
                        board[currentRow][currentColumn] = new Piece((char*)(backLine[currentColumn]), Piece::colour::WHITE, currentRow, currentColumn);
                        break;
                    default:
                        board[currentRow][currentColumn] = nullptr;
                }
            }
        }
    }
};


int main(){
    GameBoard gameBoard;
    gameBoard.initializeChessBoard();
    gameBoard.printBoard();
    std::cout <<"This is the Copy : \n";
    GameBoard copy(gameBoard);
    copy.printBoard();
    std::cin.get();
    return 0;
}