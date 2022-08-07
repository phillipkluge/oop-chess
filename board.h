#pragma once
#include <string>
#include <vector>
#include "piece.h"

class Board
{
public:
	std::vector<std::vector<int>> numSqrToEdge;
	std::vector<int> dirOffsets;
	
	Board();
	void initializeBoardFromArray(std::string boardArray[8][8]);

private:
	Piece board[64];
	void precalculateData();
};
