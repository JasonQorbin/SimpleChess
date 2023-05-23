//
// Created by Jason on 2023/05/23.
//

#include <map>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "../GamePieces.hpp"

enum Test {
    CaptureTest,
    PawnNormalMoveTest,
    PawnCaptureMoveTest,
    PawnEnPassantTest,
    PawnPromotionTest,
    KnightMoveTest,
    BishopMoveTest,
    RookNormalMoveTest,
    KingNormalMoveTest,
    KingShortCastleTest,
    KingLongCastleTest,
    KingCastleCheckBlockTest_1,
    KingCastleCheckBlockTest_2,
    KingCastleCheckBlockTest_3

};

std::map<std::string, Test> argsMap = {
        {"CaptureTest",CaptureTest},
        {"PawnNormalMoveTest",PawnNormalMoveTest},
        {"PawnCaptureMoveTest",PawnCaptureMoveTest},
        {"PawnEnPassantTest",PawnEnPassantTest},
        {"PawnPromotionTest",PawnPromotionTest},
        {"KnightMoveTest",KnightMoveTest},
        {"BishopMoveTest",BishopMoveTest},
        {"RookNormalMoveTest",RookNormalMoveTest},
        {"KingNormalMoveTest",KingNormalMoveTest},
        {"KingShortCastleTest",KingShortCastleTest},
        {"KingLongCastleTest",KingLongCastleTest},
        {"KingCastleCheckBlockTest_1",KingCastleCheckBlockTest_1},
        {"KingCastleCheckBlockTest_2",KingCastleCheckBlockTest_2},
        {"KingCastleCheckBlockTest_",KingCastleCheckBlockTest_3}
};

int test_PawnNormalMoveTest(){
    GameBoard board;
    board.initializeChessBoard();


}

int main(int argsc, char** argsv) {
    if  (argsc > 1) {
        int option = atoi(argsv[1]);
        switch (option) {
            case CaptureTest:
                return test_CaptureTest();
            case PawnNormalMoveTest:
                return test_PawnNormalMoveTest();
            case PawnCaptureMoveTest:
                return test_PawnCaptureMoveTest();
            case PawnEnPassantTest:
                return test_PawnEnPassantTest();
            case PawnPromotionTest:
                return test_PawnPromotionTest();
            case KnightMoveTest:
                return test_KnightMoveTest();
            case BishopMoveTest:
                return test_BishopTest();
            case RookNormalMoveTest:
                return test_RookTest();
            case KingNormalMoveTest:
                return test_KingNormalMoveTest();
            case KingShortCastleTest:
                return test_KingShortCastleTest();
            case KingLongCastleTest:
                return test_KingLongCastleTest();
            case KingCastleCheckBlockTest_1:
                return test_KingCaslteBlockTest_1();
            case KingCastleCheckBlockTest_2:
                return test_KingCaslteBlockTest_2();
            case KingCastleCheckBlockTest_3:
                return test_KingCaslteBlockTest_3();
            default:
                std::cout << "Invalid test selection " << option << std::endl;
                return 1;
        }

    }
}