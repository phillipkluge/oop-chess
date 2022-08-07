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
    std::vector<Move> generateMoves();

private:
    Board playBoard;
    std::vector<Move> moves;

    void generateSlidingMoves(int stSqr, int piece);
};
