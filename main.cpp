#include <iostream>
#include "engine.h"

int main()
{
    Engine e = Engine();
    int numMoves = e.moveGenerationTest(6);
    std::cout << numMoves << std::endl;
    return 0;
}
