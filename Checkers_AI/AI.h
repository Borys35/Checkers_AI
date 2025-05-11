#pragma once

class Board;
struct Move;

class AI
{
public:
	AI();
	~AI();
	void makeMove(Board& board);
	Move getBestMove(Board& board, int depth);

private:
	int minimax(Board board, int depth, int alpha, int beta, bool isMaximizing);
};

