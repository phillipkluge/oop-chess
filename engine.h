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
    void generateMoves();

private:
    Board playBoard;
    std::vector<Move> moves;
    int colourToMove;
    int friendlyColour;
    int enemyColour;

    void generateSlidingMoves(int stSqr, int piece);
};
