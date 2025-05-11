#pragma once

#include "Board.hpp"

class AI
{
public:
	AI();
	~AI();
	void makeMove(Board& board);

private:
	// int evaluateBoard(const Board& board);
	// std::vector<Move> getAllPossibleMoves(const Board& board, PieceColor color);
	// Move minimax(Board& board, int depth, bool isMaximizing);
	// Move alphaBeta(Board& board, int depth, int alpha, int beta, bool isMaximizing);
};

