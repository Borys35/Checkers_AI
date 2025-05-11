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
	int minimax(Board board, int depth, int alpha, int beta, bool isMaximizing);
	// Move alphaBeta(Board& board, int depth, int alpha, int beta, bool isMaximizing);
};

