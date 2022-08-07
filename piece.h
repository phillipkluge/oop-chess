#pragma once
#include "consts.h"
using namespace consts;

class Piece
{
public:
    Piece();
    Piece(Type t, Colour c);

    Type getType();
    Colour getColour();

private:
    Type type;
    Colour colour;
};
