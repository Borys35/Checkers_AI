#include <iostream>
#include "AI.h"
#include "Board.hpp"

AI::AI() {
}

AI::~AI() {
}

int AI::minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing) {
    if (depth == 0 || board.isGameOver()) {
        return board.evaluateBoard();
    }

    std::vector<Move> moves = board.getAllValidMoves();

    if (moves.empty()) {
        return board.evaluateBoard();
    }

    if (board.getCurrentColor() == WHITE) {
        int maxEval = -10000;
        for (auto& move : moves) {
            Board clonedBoard = board.clone();
            clonedBoard.setVsAI(false);

            Move clonedMove;
            if (move.capturePiece != nullptr) {
                auto pieceOpt = clonedBoard.getPieceAt(move.piece->getPosition());
                auto captureOpt = clonedBoard.getPieceAt(move.capturePiece->getPosition());

                if (pieceOpt && captureOpt) {
                    clonedMove = {
                        &pieceOpt->get(),
                        move.newPos,
                        &captureOpt->get()
                    };
                }
                else {
                    continue;
                }
            }
            else {
                auto pieceOpt = clonedBoard.getPieceAt(move.piece->getPosition());
                if (pieceOpt) {
                    clonedMove = {
                        &pieceOpt->get(),
                        move.newPos,
                        nullptr
                    };
                }
                else {
                    continue;
                }
            }

            clonedBoard.makeMove(clonedMove, false);

			int newDepth = clonedBoard.getCurrentColor() == BLACK ? depth - 1 : depth;
            int eval = minimax(clonedBoard, newDepth, alpha, beta, false);
            maxEval = std::max(maxEval, eval);

            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    }
    else {
        int minEval = 10000;
        for (auto& move : moves) {
            Board clonedBoard = board.clone();
            clonedBoard.setVsAI(false);

            Move clonedMove;
            if (move.capturePiece != nullptr) {
                auto pieceOpt = clonedBoard.getPieceAt(move.piece->getPosition());
                auto captureOpt = clonedBoard.getPieceAt(move.capturePiece->getPosition());

                if (pieceOpt && captureOpt) {
                    clonedMove = {
                        &pieceOpt->get(),
                        move.newPos,
                        &captureOpt->get()
                    };
                }
                else {
                    continue;
                }
            }
            else {
                auto pieceOpt = clonedBoard.getPieceAt(move.piece->getPosition());
                if (pieceOpt) {
                    clonedMove = {
                        &pieceOpt->get(),
                        move.newPos,
                        nullptr
                    };
                }
                else {
                    continue;
                }
            }

            clonedBoard.makeMove(clonedMove, false);

            int newDepth = clonedBoard.getCurrentColor() == WHITE ? depth - 1 : depth;
            int eval = minimax(clonedBoard, newDepth, alpha, beta, true);
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
    int bestValue = 10000; // lower = better for AI
    Move bestMove;
    auto moves = board.getAllValidMoves();

    if (moves.empty()) {
        return bestMove;
    }

    bestMove = moves[0];

    for (auto& move : moves) {
        Board clonedBoard = board.clone();
        clonedBoard.setVsAI(false);

        Move clonedMove;
        if (move.capturePiece != nullptr) {
            auto pieceOpt = clonedBoard.getPieceAt(move.piece->getPosition());
            auto captureOpt = clonedBoard.getPieceAt(move.capturePiece->getPosition());

            if (pieceOpt && captureOpt) {
                clonedMove = {
                    &pieceOpt->get(),
                    move.newPos,
                    &captureOpt->get()
                };
            }
            else {
                continue;
            }
        }
        else {
            auto pieceOpt = clonedBoard.getPieceAt(move.piece->getPosition());
            if (pieceOpt) {
                clonedMove = {
                    &pieceOpt->get(),
                    move.newPos,
                    nullptr
                };
            }
            else {
                continue;
            }
        }

        clonedBoard.makeMove(clonedMove, false);

        int newDepth = clonedBoard.getCurrentColor() == WHITE ? depth - 1 : depth;
        int moveValue = minimax(clonedBoard, newDepth, -10000, 10000, false);

        std::cout << "Move: (" << move.piece->getPosition().x << "," << move.piece->getPosition().y
            << ") -> (" << move.newPos.x << "," << move.newPos.y
            << ") Value: " << moveValue << std::endl;

        if (moveValue < bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    std::cout << "Best move value: " << bestValue << std::endl;
    return bestMove;
}