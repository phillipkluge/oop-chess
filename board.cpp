#include <iostream>
#include "board.h"

Board::Board()
{
	// for now, set the board up in a standard way
	std::string boardArray[8][8] = {
		// {"r", "n", "b", "q", "k", "b", "n", "r"},
		// {"p", "p", "p", "p", "p", "p", "p", "p"},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {"P", "P", "P", "P", "P", "P", "P", "P"},
		// {"R", "N", "B", "Q", "K", "B", "N", "R"} 

		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", "K", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "}
	};
	initializeBoardFromArray(boardArray);
	precalculateData();
}

int Board::getPiece(int idx)
{
	return this->board[idx];
}

void Board::initializeBoardFromArray(std::string boardArray[8][8])
{
	for (int i = 7; i >= 0; --i)
		{
			for (int j = 0; j < 8; ++j)
			{
				std::string piece = boardArray[i][j];
				char& s = piece[0];

				int position = (((7 - i) * 8) + j);

				if (s == ' ') // empty pieces
				{
					this->board[position] = Piece::None;
				}
				else if (isupper(s)) // white pieces
				{
					switch (s)
					{
						case 'K':
							this->board[position] = Piece::White | Piece::King;
							break;
						case 'P':
							this->board[position] = Piece::White | Piece::Pawn;
							break;
						case 'N':
							this->board[position] = Piece::White | Piece::Knight;
							break;
						case 'B':
							this->board[position] = Piece::White | Piece::Bishop;
							break;
						case 'R':
							this->board[position] = Piece::White | Piece::Rook;
							break;
						case 'Q':
							this->board[position] = Piece::White | Piece::Queen;
							break;
					}
				}
				else // black pieces
				{
					switch (s)
					{
						case 'k':
							this->board[position] = Piece::Black | Piece::King;
							break;
						case 'p':
							this->board[position] = Piece::Black | Piece::Queen;
							break;
						case 'n':
							this->board[position] = Piece::Black | Piece::Knight;
							break;
						case 'b':
							this->board[position] = Piece::Black | Piece::Bishop;
							break;
						case 'r':
							this->board[position] = Piece::Black | Piece::Rook;
							break;
						case 'q':
							this->board[position] = Piece::Black | Piece::Queen;
							break;
					}
				}
			}
		}
}

bool Board::isEmptySqr(int sqr)
{
	return this->board[sqr] == Piece::None;
}

bool Board::getKnightBoard(int kSqr)
{
	return this->knightArray[kSqr];
}

void Board::precalculateData()
{
	std::vector<std::vector<int> > temp(64, std::vector<int>(0));

	this->numSqrToEdge = temp;

	for (int file = 0; file < 8; ++file)
	{
		for (int rank = 0; rank < 8; ++rank)
		{
			int index = rank * 8 + file;

			int North = 7 - rank;
			int South = rank;
			int West = file;
			int East = 7 - file;

			numSqrToEdge[index].push_back(North);
			numSqrToEdge[index].push_back(South);
			numSqrToEdge[index].push_back(West);
			numSqrToEdge[index].push_back(East);
			numSqrToEdge[index].push_back(std::min(North, West));
			numSqrToEdge[index].push_back(std::min(South, East));
			numSqrToEdge[index].push_back(std::min(North, East));
			numSqrToEdge[index].push_back(std::min(South, West));
		}
	}

	this->dirOffsets.push_back(8);
	this->dirOffsets.push_back(-8);
	this->dirOffsets.push_back(-1);
	this->dirOffsets.push_back(1);
	this->dirOffsets.push_back(7);
	this->dirOffsets.push_back(-7);
	this->dirOffsets.push_back(9);
	this->dirOffsets.push_back(-9);
	//knights
	this->dirOffsets.push_back(6);
	this->dirOffsets.push_back(15);
	this->dirOffsets.push_back(17);
	this->dirOffsets.push_back(10);
	this->dirOffsets.push_back(-6);
	this->dirOffsets.push_back(-15);
	this->dirOffsets.push_back(-17);
	this->dirOffsets.push_back(-10);

	this->knightArrayOffsets.push_back(10);
	this->knightArrayOffsets.push_back(23);
	this->knightArrayOffsets.push_back(25);
	this->knightArrayOffsets.push_back(15);
	this->knightArrayOffsets.push_back(-10);
	this->knightArrayOffsets.push_back(-23);
	this->knightArrayOffsets.push_back(-25);
	this->knightArrayOffsets.push_back(-15);
}
