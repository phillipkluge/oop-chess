#include "engine.h"

Engine::Engine()
{
    this->playBoard = Board();
}

std::vector<Move> Engine::generateMoves()
{
    std::vector<Move> moves;

    for (int stSqr = 0; stSqr < 64; stSqr++)
    {
        int piece = playBoard.getPiece(stSqr);
        if (Piece::isColour(piece, playBoard.colourToMove))
        {
            if (Piece::isSlidingPiece(piece))
            {
                generateSlidingMoves(stSqr, piece);
            }
        }
    }

    return moves;
}

void Engine::generateSlidingMoves(int stSqr, int piece)
{
    // TODO: Finish sliding move generation
}
