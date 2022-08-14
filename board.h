#pragma once
#include <string>
#include <vector>
#include "piece.h"

class Board
{
public:
	std::vector<std::vector<int>> numSqrToEdge;
	std::vector<int> dirOffsets;
	std::vector<int> knightArrayOffsets;
	
	Board();
	int getPiece(int idx);
	bool isEmptySqr(int sqr);
	bool getKnightBoard(int kSqr);

private:
	int board[64] = {0};
	bool knightArray[144] = {
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0
	};

	void initializeBoardFromArray(std::string boardArray[8][8]);
	void precalculateData();
};
