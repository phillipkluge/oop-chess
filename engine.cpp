#include "engine.h"

Engine::Engine()
{
    this->playBoard = Board();
    this->colourToMove = Piece::White;
    this->friendlyColour = Piece::White;
    this->enemyColour = Piece::Black;
}

void Engine::generateMoves()
{
    for (int stSqr = 0; stSqr < 64; stSqr++)
    {
        int piece = playBoard.getPiece(stSqr);
        if (Piece::isColour(piece, this->colourToMove))
        {
            if (Piece::isSlidingPiece(piece))
            {
                generateSlidingMoves(stSqr, piece);
            }

            else if (Piece::isType(piece, Piece::Pawn))
            {
                // TODO: finish pawn move generation
            }
        }
    }
}

void Engine::generateSlidingMoves(int stSqr, int piece)
{
    int startDir = (Piece::isType(piece, Piece::Bishop)) ? 4 : 0;
    int endDir = (Piece::isType(piece, Piece::Rook)) ? 4 : 8;
    
    for (int direction = startDir; direction < endDir; direction++)
    {
        for (int n = 0; n < this->playBoard.numSqrToEdge[stSqr][direction]; n++)
        {
            int targetSqr = stSqr + this->playBoard.dirOffsets[direction] * (n + 1);
            int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

            // if blocked by a friendly piece
            if (Piece::isColour(pieceOnTargetSqr, this->enemyColour))
            {
                break;
            }

            this->moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr});

            if (Piece::isColour(pieceOnTargetSqr, enemyColour))
            {
                break;
            }
        }
    }
}
