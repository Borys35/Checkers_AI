#include <iostream>

#include "AI.h"
#include "Board.hpp"

AI::AI() {
}

AI::~AI() {
}

void AI::makeMove(Board& board) {
	Move move = getBestMove(board, 1);
	std::cout << "AI move: " << move.newPos.x << ", " << move.newPos.y << std::endl;
	board.makeMove(move, true);
}

int AI::minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing) {
	if (depth == 0 || board.isGameOver()) {
		return board.evaluateBoard();
	}

	if (isMaximizing) {
		int maxEval = -1000;
		auto moves = board.getAllValidMoves();
		for (auto& move : moves) {
			board.makeMove(move, true);
			int eval = minimax(board, depth - 1, alpha, beta, false);
			maxEval = std::max(maxEval, eval);
			alpha = std::max(alpha, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return maxEval;
	}
	else {
		int minEval = 1000;
		auto moves = board.getAllValidMoves();
		for (auto& move : moves) {
			board.makeMove(move, true);
			int eval = minimax(board, depth - 1, alpha, beta, true);
			minEval = std::min(minEval, eval);
			beta = std::min(beta, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return minEval;
	}
}

Move AI::getBestMove(Board& board, int depth) {  
	// TODO: make AI smarter  
	Move bestMove;  
	bool isMaximizing = !board.isBottomPlayerWhite();  
	int bestValue = -1000;  
	Board tempBoard = board.clone();
	auto moves = tempBoard.getAllValidMoves();  
	int bestIndex = -1;
	for (int i = 0; i < moves.size(); i++) {
		 // Create a deep copy of the board 
		tempBoard.makeMove(moves[i], true);
		int moveValue = minimax(tempBoard, depth - 1, -1000, 1000, !isMaximizing);  
		if (moveValue > bestValue) {  
			bestValue = moveValue;  
			bestMove = moves[i];
			bestIndex = i;
		}
	}
	if (bestIndex == -1) {
		std::cout << "No valid moves available." << std::endl;
		return bestMove; // Return an empty move or handle it as needed
	}
	bestMove = board.getAllValidMoves()[bestIndex];
	return bestMove;  
}