#pragma once
#include <vector>
#include "board.h"

struct Move
{
    int stSqr;
    int endSqr;
};

class Engine
{
public:
    Engine();
    void printAllTargetSqr();
    void generateMoves();

private:
    Board playBoard;
    std::vector<Move> moves;
    int colourToMove;
    int friendlyColour;
    int enemyColour;

    void generatePawnMoves(int stSqr, int piece);
    void generateKnightMoves(int stSqr, int piece);
    void generateSlidingMoves(int stSqr, int piece);
    int isValidKnightMove(int sqr, int dir);
};
