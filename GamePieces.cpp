//
// Created by Jason on 2023/05/13.
//

#include "GamePieces.hpp"

namespace Utils {

    int min (int first, int second){
        return first < second ? first : second;
    }

    int max (int first, int second) {
        return first > second ? first : second;
    }
}

GamePiece::GamePiece(Team colour) :  pieceColour(colour){

}


bool GamePiece::isEnemyPiece(GamePiece *otherPiece) const{
    return pieceColour != otherPiece->pieceColour;

}

bool GamePiece::isFriendlyPiece(GamePiece *otherPiece) const {
    return pieceColour == otherPiece -> pieceColour;
}

std::vector<Position>
GamePiece::getLinearMoves(const GameBoard &board, Position currentPosition, Position startPosition,
                          Position endPosition, int horizontalStep, int verticalStep) const {
    std::vector<Position> answer;
    bool pastCurrentPiecePosition = false;

    Position loopPosition (startPosition);

    while (loopPosition != endPosition){
        if (loopPosition == currentPosition) { //At the piece.
            pastCurrentPiecePosition = true;
            continue;
        }
        GamePiece *otherPiece = board.getPiece(loopPosition);
        if (!pastCurrentPiecePosition) {
            if (otherPiece == nullptr) {
                answer.push_back(loopPosition);
            } else if (isEnemyPiece(otherPiece)) {
                answer.clear();
                answer.push_back(loopPosition);
            } else {                                        //Friendly piece condition
                answer.clear();
            }
        }

        if (pastCurrentPiecePosition) {
            if (otherPiece == nullptr) {
                answer.push_back(loopPosition);
                continue;
            }

            //Friend and Enemy conditions
            if (isEnemyPiece(otherPiece)) {
                answer.push_back(loopPosition); //In the case of an enemy we can capture (valid move)
            }

            break;                                          //But in both cases, stop looking further;
        }
        loopPosition.move(horizontalStep,verticalStep);
    }
    return answer;
}

std::vector<Position> GamePiece::getHorizontalMoves(const GameBoard& board, Position currentPosition, int range) {
    using Utils::max, Utils::min;
    Position startPosition (currentPosition.row, max(currentPosition.col - range, 0));
    Position endPosition (currentPosition.row,min(currentPosition.col + range, GameBoard::NUM_COLS - 1));
    return getLinearMoves(board, currentPosition, startPosition, endPosition, 1, 0);
}

std::vector<Position> GamePiece::getVerticalMoves(const GameBoard& board, Position currentPosition, int range) {
    using Utils::max, Utils::min;
    Position startPosition (max(currentPosition.row - range, 0),currentPosition.col);
    Position endPosition (min(currentPosition.row + range, GameBoard::NUM_ROWS - 1), currentPosition.col);
    return getLinearMoves(board, currentPosition, startPosition, endPosition, 0, 1);
}

std::vector<Position> GamePiece::getDiagonalMoves(const GameBoard& board, Position currentPosition, int range) {
    using Utils::max, Utils::min;
    std::vector<Position> answer;
    //Upwards diagonal (left-to-right)
    int backStep = min(min(currentPosition.row,range),  min(currentPosition.col, range));
    int forwardStep = min(min(board.NUM_ROWS - 1 - currentPosition.row, range),min(board.NUM_COLS - 1 - currentPosition.col, range));
    Position startPosition = currentPosition.offset(backStep, backStep);
    Position endPosition = currentPosition.offset(forwardStep, forwardStep);
    answer = getLinearMoves(board, currentPosition, startPosition, endPosition, 1, 1);

    //Downwards diagonal (left-to-right)
    backStep = min(min(currentPosition.row,range),  min(board.NUM_COLS - 1 - currentPosition.col, range));
    forwardStep = min(min(board.NUM_ROWS - 1 - currentPosition.row, range),min(currentPosition.col, range));
    startPosition = currentPosition.offset(backStep, backStep);
    endPosition = currentPosition.offset(forwardStep, forwardStep);
    std::vector<Position> secondSet = getLinearMoves(board, currentPosition, startPosition, endPosition, 1, -1);
    answer.insert(answer.end(), secondSet.begin(), secondSet.end());
    return answer;
}

GameBoard::GameBoard(){zeroBoard();}

GameBoard::~GameBoard(){ deleteAllPieces();}

// Copy constructor
GameBoard::GameBoard( const GameBoard& otherBoard) {
    for (int currentRow = 0; currentRow < NUM_ROWS; currentRow++) {
        for (int currentCol = 0; currentCol < NUM_COLS; currentCol++) {
            GamePiece* pieceToCopy = otherBoard.getPiece(currentRow, currentCol);
            if (pieceToCopy == nullptr) {
                board[currentRow][currentCol] = nullptr;
            } else {
                board[currentRow][currentCol] = otherBoard.getPiece(currentRow,currentCol);
            }
        }
    }
}

GamePiece* GameBoard::getPiece (int row, int col) const{
    return board[row] [col];
}

GamePiece* GameBoard::getPiece (Position position) const {
    return board[position.row][position.col];
}


std::string Rook::getPaddedSymbol() { return " R  ";}
std::string Knight::getPaddedSymbol() { return " Kn ";}
std::string Bishop::getPaddedSymbol() { return " Bi ";}
std::string Queen::getPaddedSymbol() { return " Qu ";}
std::string King::getPaddedSymbol() { return " Ki ";}
std::string Pawn::getPaddedSymbol() { return " p  ";}

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

void GameBoard::deletePiece(Position position){
    GamePiece* piece = getPiece(position);
    if (piece != nullptr) deletePiece(piece);
}

void GameBoard::deletePiece(int row, int col) {
    deletePiece(getPiece(row, col));
}

void GameBoard::setPiece(GamePiece* piece, Position position){
    board[position.row][position.col] = piece;
}

void GamePiece::movePiece(Position currentPosition, Position dest, GameBoard board){
    std::vector<Position> moves = getPossibleMoves(board, currentPosition);

    bool destinationValid = false;
    for (Position check: moves) {
        if (check == dest){
            destinationValid = true;
            break;
        }
    }

    if (destinationValid){
        board.movePiece(currentPosition, dest);
    }
}

void GameBoard::movePiece(Position src, Position dest) {
    GamePiece* piece = getPiece(src);

    GamePiece* otherPiece = getPiece(dest);
    if (otherPiece != nullptr) deletePiece(otherPiece);

    setPiece(piece, dest);
    setPiece(nullptr, src);
}

GamePiece** initBackLine (GamePiece::Team side){
    GamePiece** answer = new GamePiece* [GameBoard::NUM_COLS];
    answer[0] = new Rook(side);
    answer[1] = new Knight(side);
    answer[2] = new Bishop(side);
    answer[3] = new Queen(side);
    answer[4] = new King(side);
    answer[5] = new Bishop(side);
    answer[6] = new Knight(side);
    answer[7] = new Rook(side);
    return answer;
}

GamePiece** initPawnLine (GamePiece::Team side) {
    GamePiece** answer = new GamePiece* [GameBoard::NUM_COLS];
    for (int i = 0; i < GameBoard::NUM_COLS; ++i) {
        answer[i] = new Pawn(side);
    }
    return answer;
}


void GameBoard::initializeChessBoard(){
    deleteAllPieces();
    GamePiece** whiteBackLine = initBackLine(GamePiece::WHITE);
    GamePiece** blackBackLine = initBackLine(GamePiece::BLACK);
    GamePiece** whitePawnLine = initPawnLine(GamePiece::WHITE);
    GamePiece** blackPawnLine = initPawnLine(GamePiece::BLACK);

    for (int rows = 0; rows < GameBoard::NUM_ROWS; ++rows) {
        for (int cols = 0; cols < GameBoard::NUM_COLS; ++cols) {

            switch (rows) {
                case 0:
                    board[rows][cols]  = whiteBackLine[cols];
                    break;
                case 1:
                    board[rows][cols]  = whitePawnLine[cols];
                    break;
                case 6:
                    board[rows][cols]  = blackPawnLine[cols];
                    break;
                case 7:
                    board[rows][cols]  = blackBackLine[cols];
                    break;
                default:
                    board[rows][cols] = nullptr;
            }
        }
    }

    delete[] whitePawnLine;
    delete[] blackPawnLine;
    delete[] whiteBackLine;
    delete[] blackBackLine;
}

std::vector<Position> Rook::getPossibleMoves(const GameBoard& board, Position currentPosition) {
    std::vector<Position> moves = getHorizontalMoves(board, currentPosition, 7);
    std::vector<Position> vertMoves = getVerticalMoves(board, currentPosition, 7);
    moves.insert(moves.end(), vertMoves.begin(), vertMoves.end());

    return moves;
}

void Rook::onMove(){
    castlingRights = false;
}


std::vector<Position> Bishop::getPossibleMoves(const GameBoard& board, Position currentPosition) {
    std::vector<Position> moves = getDiagonalMoves(board, currentPosition, 7);
    return moves;
}

std::vector<Position> Queen::getPossibleMoves(const GameBoard& board, Position currentPosition) {
    std::vector<Position> moves = getHorizontalMoves(board, currentPosition, 7);
    std::vector<Position> vertMoves = getVerticalMoves(board, currentPosition, 7);
    std::vector<Position> diagMoves = getDiagonalMoves(board, currentPosition, 7);

    moves.insert(moves.end(), vertMoves.begin(), vertMoves.end());
    moves.insert(moves.end(), diagMoves.begin(), diagMoves.end());

    return moves;
}

std::vector<Position> King::getPossibleMoves(const GameBoard& board, Position currentPosition) {
    std::vector<Position> moves = getHorizontalMoves(board, currentPosition, 1);
    std::vector<Position> vertMoves = getVerticalMoves(board, currentPosition, 1);
    std::vector<Position> diagMoves = getDiagonalMoves(board, currentPosition, 1);

    moves.insert(moves.end(), vertMoves.begin(), vertMoves.end());
    moves.insert(moves.end(), diagMoves.begin(), diagMoves.end());

    return moves;
}

std::vector<Position>Knight::getPossibleMoves(const GameBoard& board, Position currentPosition) {
    std::vector<Position> answer;
    std::vector<Position> toTest;

    toTest.push_back(currentPosition.offset(-1,2));
    toTest.push_back(currentPosition.offset(1,2));
    toTest.push_back(currentPosition.offset(-1,-2));
    toTest.push_back(currentPosition.offset(1,2));
    toTest.push_back(currentPosition.offset(-2,-1));
    toTest.push_back(currentPosition.offset(-2,1));
    toTest.push_back(currentPosition.offset(2,-1));
    toTest.push_back(currentPosition.offset(2,1));

    for (Position possible: toTest) {
        if( !possible.positionValid()) continue;
        GamePiece* otherPiece = board.getPiece(possible);
        if (otherPiece == nullptr || this->isEnemyPiece(otherPiece)){
            answer.push_back(possible);
        }
    }

    return answer;
}

std::vector<Position>Pawn::getPossibleMoves(const GameBoard &board, Position currentPosition) {
    //Check normal movement
    std::vector<Position> answer;
    int direction = pieceColour == WHITE ? 1 : -1;
    Position toTest = currentPosition.offset(0, direction);
    if (board.getPiece(toTest) == nullptr) {
        answer.push_back(toTest);
        if (!hasMoved) {
            Position toTest = currentPosition.offset(0, direction * 2);
            if (board.getPiece(toTest) == nullptr) {
                answer.push_back(toTest);
            }
        }
    }

    //Check for capture moves

    toTest = currentPosition.offset(-1, direction);
    if (toTest.positionValid()) {
        GamePiece *otherPiece = board.getPiece(toTest);
        if (otherPiece != nullptr && isEnemyPiece(otherPiece)) answer.push_back(toTest);
    }

    toTest = currentPosition.offset(1, direction);
    if (toTest.positionValid()) {
        GamePiece* otherPiece = board.getPiece(toTest);
        if (otherPiece != nullptr && isEnemyPiece(otherPiece)) answer.push_back(toTest);
    }

    //Check for en passant

    GamePiece* neighbourPiece = board.getPiece(currentPosition.offset(-1,0));
    if (neighbourPiece != nullptr && neighbourPiece -> getName() == "Pawn"){
        Pawn* otherPawn = (Pawn*) neighbourPiece;
        if (otherPawn->enPassantIsAllowed()){
            toTest = currentPosition.offset(-1, direction);
            if (board.getPiece(toTest) == nullptr) {
                answer.push_back(toTest);
            }
        }
    }

    neighbourPiece = board.getPiece(currentPosition.offset(1,0));
    if (neighbourPiece != nullptr && neighbourPiece -> getName() == "Pawn"){
        Pawn* otherPawn = (Pawn*) neighbourPiece;
        if (otherPawn->enPassantIsAllowed()){
            toTest = currentPosition.offset(1, direction);
            if (board.getPiece(toTest) == nullptr) {
                answer.push_back(toTest);
            }
        }
    }
    return answer;
}

void King::onMove(){
    castlingRights = false;
}

void Pawn::onMove(int distanceMoved){
    if (!hasMoved && distanceMoved == 2) {
        enPassantAllowed = true;
    }

    hasMoved = true;
}

bool Pawn::enPassantIsAllowed() {
    return enPassantAllowed;
}