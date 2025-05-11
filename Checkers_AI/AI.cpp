#include "AI.h"

AI::AI() {
}

AI::~AI() {
}

//int AI::evaluateBoard(Board& board) {
//	board.
//}

int AI::minimax(Board board, int depth, int alpha, int beta, bool isMaximizing) {
	if (depth == 0 || board.isGameOver()) {
		return board.evaluateBoard();
	}

	if (isMaximizing) {
		int maxEval = -1000;
		auto moves = board.getAllValidMoves();
		for (auto& move : moves) {
			board.makeMove(move);
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
			board.makeMove(move);
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