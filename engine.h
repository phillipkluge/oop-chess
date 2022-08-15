#pragma once
#include <vector>
#include "board.h"

struct Move
{
    int stSqr;
    int endSqr;
    int movedPiece;
    int capturedPiece;
};

class Engine
{
public:
    Engine();
    void printAllTargetSqr(std::vector<Move> &moves);
    int moveGenerationTest(int depth);
    std::vector<Move> generateMoves();

private:
    Board playBoard;
    std::vector<Move> moveList;
    int colourToMove;
    int friendlyColour;
    int enemyColour;

    void makeMove(Move m);
    void unmakeMove();
    void switchPlayers();
    void generatePawnMoves(int stSqr, int piece, std::vector<Move> &moves);
    void generateKnightMoves(int stSqr, int piece, std::vector<Move> &moves);
    void generateSlidingMoves(int stSqr, int piece, std::vector<Move> &moves);
    void generateKingMoves(int stSqr, int piece, std::vector<Move> &moves);
    int isValidKnightMove(int sqr, int dir);
};
