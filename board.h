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
	int getPiece(int idx);
	bool isEmptySqr(int sqr);

private:
	int board[64] = {0};

	void initializeBoardFromArray(std::string boardArray[8][8]);
	void precalculateData();
};
