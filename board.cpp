#include <iostream>
#include "board.h"
#include "consts.h"
using namespace consts;

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
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{"B", " ", " ", " ", " ", " ", " ", " "}
	};
	initializeBoardFromArray(boardArray);
	precalculateData();
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
					board[position] = Piece(Type::Empty,Colour::None);
				}
				else if ((isupper(s))) // white pieces
				{
					switch (s)
					{
						case 'K':
							board[position] = Piece(Type::King,Colour::White);
							break;
						case 'P':
							board[position] = Piece(Type::Pawn,Colour::White);
							break;
						case 'N':
							board[position] = Piece(Type::Knight,Colour::White);
							break;
						case 'B':
							board[position] = Piece(Type::Bishop,Colour::White);
							break;
						case 'R':
							board[position] = Piece(Type::Rook,Colour::White);
							break;
						case 'Q':
							board[position] = Piece(Type::Queen,Colour::White);
							break;
					}
				}
				else // black pieces
				{
					switch (s)
					{
						case 'K':
							board[position] = Piece(Type::King,Colour::Black);
							break;
						case 'P':
							board[position] = Piece(Type::Pawn,Colour::Black);
							break;
						case 'N':
							board[position] = Piece(Type::Knight,Colour::Black);
							break;
						case 'B':
							board[position] = Piece(Type::Bishop,Colour::Black);
							break;
						case 'R':
							board[position] = Piece(Type::Rook,Colour::Black);
							break;
						case 'Q':
							board[position] = Piece(Type::Queen,Colour::Black);
							break;
					}
				}
			}
		}
}

void Board::precalculateData()
{
	std::vector<std::vector<int> > temp(64, std::vector<int>(0));

	numSqrToEdge = temp;

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

	dirOffsets.push_back(8);
	dirOffsets.push_back(-8);
	dirOffsets.push_back(-1);
	dirOffsets.push_back(1);
	dirOffsets.push_back(7);
	dirOffsets.push_back(-7);
	dirOffsets.push_back(9);
	dirOffsets.push_back(-9);
}
