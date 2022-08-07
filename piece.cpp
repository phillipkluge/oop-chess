#include "piece.h"

bool Piece::isColour(int p1, int p2)
{
    int mask = 24;
    int colour_1 = mask & p1;
    int colour_2 = mask & p2;

    return (colour_1 == colour_2);
}

bool Piece::isType(int p1, int p2)
{
    int mask = 7;
    int type_1 = mask & p1;
    int type_2 = mask & p2;

    return (type_1 == type_2);
}

bool Piece::isSlidingPiece(int p)
{
    return (isType(p, Piece::Bishop) || isType(p, Piece::Rook) || isType(p, Piece::Queen));
}
