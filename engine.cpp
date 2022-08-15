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

void Engine::printAllTargetSqr(std::vector<Move> &moves)
{
    for (int i = 0; i < moves.size(); i++)
    {
        std::cout << moves[i].endSqr << " ";
    }
    std::cout << std::endl;
}

int Engine::moveGenerationTest(int depth)
{
    if (depth == 0)
    {
        return 1;
    }

    std::vector<Move> moves = this->generateMoves();
    int numPositions = 0;

    for (const Move &m : moves)
    {
        this->makeMove(m);
        // playBoard.printBoard();
        numPositions += this->moveGenerationTest(depth - 1);
        this->unmakeMove();
    }

    return numPositions;
}

void Engine::makeMove(Move m)
{
    playBoard.setSqr(m.stSqr, Piece::None);
    playBoard.setSqr(m.endSqr, m.movedPiece);
    this->moveList.push_back(m);
    this->switchPlayers();
}

void Engine::unmakeMove()
{
    if (!moveList.empty())
    {
        Move m = moveList.back();
        playBoard.setSqr(m.endSqr, m.capturedPiece);
        playBoard.setSqr(m.stSqr, m.movedPiece);
        moveList.pop_back();
        this->switchPlayers();
    }
}

void Engine::switchPlayers()
{
    int colourSwitch = (this->colourToMove == Piece::White) ? Piece::Black : Piece::White;
    this->enemyColour = colourToMove;
    this->friendlyColour = colourSwitch;
    this->colourToMove = colourSwitch;
}

std::vector<Move> Engine::generateMoves()
{
    std::vector<Move> moves;
    for (int stSqr = 0; stSqr < 64; stSqr++)
    {
        int piece = playBoard.getPiece(stSqr);
        if (Piece::isColour(piece, this->colourToMove))
        {
            if (Piece::isSlidingPiece(piece))
            {
                generateSlidingMoves(stSqr, piece, moves);
            }
            else if (Piece::isType(piece, Piece::Pawn))
            {
                generatePawnMoves(stSqr, piece, moves);
            }
            else if (Piece::isType(piece, Piece::Knight))
            {
                generateKnightMoves(stSqr, piece, moves);
            }
            else if (Piece::isType(piece, Piece::King))
            {
                generateKingMoves(stSqr, piece, moves);
            }
        }
    }
    return moves;
}

void Engine::generatePawnMoves(int stSqr, int piece, std::vector<Move> &moves)
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

        moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr, .movedPiece = piece, .capturedPiece = pieceOnTargetSqr});
    }

    // left captures
    if (playBoard.numSqrToEdge[stSqr][leftDir] != 0)
    {
        int targetSqr = stSqr + this->playBoard.dirOffsets[leftDir];
        int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

        if (Piece::isColour(pieceOnTargetSqr, this->enemyColour))
        {
            moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr, .movedPiece = piece, .capturedPiece = pieceOnTargetSqr});
        }
    }

    // right captures
    if (playBoard.numSqrToEdge[stSqr][rightDir] != 0)
    {
        int targetSqr = stSqr + this->playBoard.dirOffsets[rightDir];
        int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

        if (Piece::isColour(pieceOnTargetSqr, this->enemyColour))
        {
            moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr, .movedPiece = piece, .capturedPiece = pieceOnTargetSqr});
        }
    }
}

void Engine::generateKnightMoves(int stSqr, int piece, std::vector<Move> &moves)
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
                moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr, .movedPiece = piece, .capturedPiece = pieceOnTargetSqr});
            }
        }
    }
}

void Engine::generateSlidingMoves(int stSqr, int piece, std::vector<Move> &moves)
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

            moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr, .movedPiece = piece, .capturedPiece = pieceOnTargetSqr});

            if (Piece::isColour(pieceOnTargetSqr, enemyColour))
            {
                break;
            }
        }
    }
}

void Engine::generateKingMoves(int stSqr, int piece, std::vector<Move> &moves)
{
    for (int direction = 0; direction < 8; direction++)
    {
        if (this->playBoard.numSqrToEdge[stSqr][direction] != 0)
        {
            int targetSqr = stSqr + this->playBoard.dirOffsets[direction];
            int pieceOnTargetSqr = this->playBoard.getPiece(targetSqr);

            if (Piece::isColour(pieceOnTargetSqr, this->friendlyColour))
            {
                continue;
            }

            moves.push_back(Move{.stSqr = stSqr, .endSqr = targetSqr, .movedPiece = piece, .capturedPiece = pieceOnTargetSqr});

            if (Piece::isColour(pieceOnTargetSqr, enemyColour))
            {
                continue;
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
