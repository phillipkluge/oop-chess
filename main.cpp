#include <iostream>
#include "engine.h"

int main()
{
    Engine e = Engine();
    e.generateMoves();
    e.printAllTargetSqr();
    return 0;
}
