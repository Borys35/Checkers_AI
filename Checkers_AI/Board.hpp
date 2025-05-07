#pragma once

#include <vector>
#include "Piece.hpp"

struct Move {
	Piece& piece;
	Position newPos;
	bool isCapture;
};

class Board {
public:
	Board();
	~Board();
	std::vector<Move> getValidMoves(const Piece& piece);
	void makeMove(const Move& move);

private:
	int board[8][8] = { 0 };
	int whitePieces = 12;
	int blackPieces = 12;
	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;
	PieceColor currentColor = WHITE;
	bool gameOver = false;
};