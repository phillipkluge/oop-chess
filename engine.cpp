#include "engine.h"
#include <iostream>
#include <math.h>

Engine::Engine()
{
    this->playBoard = Board();
    this->colourToMove = Piece::White;
    this->friendlyColour = Piece::White;
    this->enemyColour = Piece::Black;
}

void Engine::printAllTargetSqr()
{
    for (int i = 0; i < moves.size(); i++)
    {
        std::cout << moves[i].endSqr << " ";
    }
    std::cout << std::endl;
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
                generatePawnMoves(stSqr, piece);
            }
            else if (Piece::isType(piece, Piece::Knight))
            {
                generateKnightMoves(stSqr, piece);
            }
        }
    }
}

void Engine::generatePawnMoves(int stSqr, int piece)
{
    int forwardDir,rightDir,leftDir;
    if (Piece::isColour(piece, Piece::White))
    {
        forwardDir = 0; rightDir = 6; leftDir = 4;
    }
    else
    {
        forwardDir = 1; rightDir = 7; leftDir = 5;
    }

    bool doublePushAllowed;
    switch (forwardDir)
    {
        case 0:
            doublePushAllowed = ((stSqr >= 8) && (stSqr <= 15)) ? true : false;
            break;
        case 1:
            doublePushAllowed = ((stSqr >= 48) && (stSqr <= 56)) ? true : false;
            break;
    }

    // forward moves
    int numSquaresAllowed;;
    numSquaresAllowed = (doublePushAllowed) ? 2 : 1;

    for (int n = 0; n < numSquaresAllowed; ++n)
    {
        int targetSqr = stSqr + this->playBoard.dirOffsets[forwardDir] * (n + 1);
        int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

        if (!playBoard.isEmptySqr(targetSqr))
        {
            break;
        }

        this->moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr});
    }

    // left captures
    if (playBoard.numSqrToEdge[stSqr][leftDir] != 0)
    {
        int targetSqr = stSqr + this->playBoard.dirOffsets[leftDir];
        int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

        if (Piece::isColour(pieceOnTargetSqr, this->enemyColour))
        {
            this->moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr});
        }
    }

    // right captures
    if (playBoard.numSqrToEdge[stSqr][rightDir] != 0)
    {
        int targetSqr = stSqr + this->playBoard.dirOffsets[rightDir];
        int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

        if (Piece::isColour(pieceOnTargetSqr, this->enemyColour))
        {
            this->moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr});
        }
    }
}

void Engine::generateKnightMoves(int stSqr, int piece)
{
    for (int direction = 8; direction < 16; direction++)
    {
        int targetSqr = this->isValidKnightMove(stSqr, direction);
        if (targetSqr != -1)
        {
            int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

            if (Piece::isColour(pieceOnTargetSqr, this->friendlyColour))
            {
                continue;
            }
            else
            {
                this->moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr});
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
            if (Piece::isColour(pieceOnTargetSqr, this->friendlyColour))
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

int Engine::isValidKnightMove(int sqr, int dir)
{
    int rank = std::floor(sqr / 8);

    int translation = (sqr + 26) + (4 * rank);
    int targetSqr = translation + playBoard.knightArrayOffsets[dir - 8];

    if (!playBoard.getKnightBoard(targetSqr))
    {
        return -1;
    }
    else
    {
        return sqr + playBoard.dirOffsets[dir];
    }
}
