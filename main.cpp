#include <vector>
#include <iostream>
#include <string>
#include <cstring>



class GameBoard;

class Piece {
public:
    enum colour {
        WHITE,
        BLACK
    };

    char* symbol;
    colour pieceColour;
    Piece(char* sym) : symbol(sym){};
    Piece(char* sym, colour col) : symbol(sym), pieceColour(col){};

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
    ~GameBoard(){deletePieces();}
    Piece* getPiece (int row, int col){
        return board[row] [col];
    }

    void printBoard(){
        const char* topBorder = "╔════╤════╤════╤════╤════╤════╤════╤════╗\n";
        const char* middleBorder = "╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        const char* bottomBorder = "╚════╧════╧════╧════╧════╧════╧════╧════╝\n";


        std::string buffer;
        buffer.reserve(750);
        buffer += topBorder;
        for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
            buffer += "║";
            for (int currentCol = 0; currentCol < NUM_COLS; currentCol++) {
                Piece* currentPiece = board[currentRow][currentCol];
                if (currentPiece!= nullptr) {
                    buffer += currentPiece->getPaddedSymbol();
                } else {
                    buffer += "    "; //four spaces
                }
                buffer += currentCol == NUM_COLS-1 ? "║" : "│";
            }
            buffer += "\n";
            if (currentRow != NUM_ROWS - 1 ) buffer += middleBorder;
        }
        buffer += bottomBorder;
        buffer += "\n";
        std::cout << buffer <<std::flush;
    }

    void zeroBoard(){
        for (int rows = 0; rows < NUM_ROWS; rows++) {
            for (int cols = 0; cols < NUM_COLS; cols++) {
                board[rows][cols] = nullptr;

            }
        }
    }

    void deletePieces(){
        for (int rows = 0; rows < NUM_ROWS; rows++) {
            for (int cols = 0; cols < NUM_COLS; cols++) {
                Piece* toRemove = board[rows][cols];
                if (toRemove != nullptr) {delete toRemove;}
            }
        }
    }

    void initializeChessBoard(){
        const char* backLine [] = {"R", "Kn", "Bi", "Ki", "Qu", "Bi", "Kn", "R"};
        const char* pawnLine [] = {"p", "p", "p", "p", "p", "p", "p", "p"};
        for (int rows = 0; rows < NUM_ROWS; rows++) {
            for (int cols = 0; cols < NUM_COLS; cols++) {
                switch (rows){
                    case 0:
                        board[rows][cols] = new Piece((char*)(backLine[cols]), Piece::colour::BLACK);
                        break;

                    case 1:
                        board[rows][cols] = new Piece((char*)(pawnLine[cols]), Piece::colour::BLACK);
                        break;

                    case 6:
                        board[rows][cols] = new Piece((char*)(pawnLine[cols]), Piece::colour::WHITE);
                        break;

                    case 7:
                        board[rows][cols] = new Piece((char*)(backLine[cols]), Piece::colour::WHITE);
                        break;
                    default:
                        board[rows][cols] = nullptr;
                }
            }
        }
    }
};


int main(){
    GameBoard gameBoard;
    gameBoard.initializeChessBoard();
    gameBoard.printBoard();
    std::cin.get();
}