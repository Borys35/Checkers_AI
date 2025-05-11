#include <iostream>

#include "Board.hpp"

bool Board::isGameOver() const {
	return gameOver;
}

bool Board::isBottomPlayerWhite() const {
	return bottomPlayerWhite;
}

int Board::evaluateBoard() const {
	return whitePiecesCount - blackPiecesCount;
}

void Board::restart(bool switchSides) {
	whitePieces.clear();
	blackPieces.clear();
	whitePiecesCount = 12;
	blackPiecesCount = 12;
	gameOver = false;

	if (switchSides) {
		bottomPlayerWhite = !bottomPlayerWhite;
		if (bottomPlayerWhite) {
			currentColor = WHITE;
		}
		else {
			currentColor = BLACK;
		}
	}

	whitePieces.push_back(Piece(MAN, WHITE, { 0, 7 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 0, 5 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 1, 6 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 2, 7 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 2, 5 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 3, 6 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 4, 7 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 4, 5 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 5, 6 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 6, 7 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 6, 5 }));
	whitePieces.push_back(Piece(MAN, WHITE, { 7, 6 }));


	blackPieces.push_back(Piece(MAN, BLACK, { 0, 1 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 1, 0 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 1, 2 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 2, 1 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 3, 0 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 3, 2 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 4, 1 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 5, 0 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 5, 2 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 6, 1 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 7, 0 }));
	blackPieces.push_back(Piece(MAN, BLACK, { 7, 2 }));
}

Board::Board() {
	restart(false);
}
 
Board::~Board() {
	blackPieces.clear();
	whitePieces.clear();
}

void Board::capture(Piece& piece) {
	if (piece.getColor() == WHITE) {
		whitePiecesCount--;
		whitePieces.erase(
			std::remove_if(whitePieces.begin(), whitePieces.end(),
				[&piece](Piece& p) { return p.getPosition() == piece.getPosition(); }),
			whitePieces.end()
		);
	}
	else {
		blackPiecesCount--;
		blackPieces.erase(
			std::remove_if(blackPieces.begin(), blackPieces.end(),
				[&piece](Piece& p) { return p.getPosition() == piece.getPosition(); }),
			blackPieces.end()
		);
	}

	if (blackPiecesCount == 0 || whitePiecesCount == 0) {
		gameOver = true;
		std::cout << "Game Over!" << std::endl;
	}
}

std::optional<std::reference_wrapper<Piece>> Board::getPieceAt(const Position pos) {
	for (auto& piece : whitePieces) {
		if (piece.getPosition() == pos) {
			return piece;
		}
	}
	for (auto& piece : blackPieces) {
		if (piece.getPosition() == pos) {
			return piece;
		}
	}
	return std::nullopt;
}

void Board::makeMove(Move& move) {
	auto changeTurn = [](Board *board) {
		if (board->currentColor == WHITE) {
			board->currentColor = BLACK;
		}
		else {
			board->currentColor = WHITE;
		}
	};

	// new position
	move.piece->setPosition(move.newPos);

	// capture
	if (move.capturePiece != nullptr) {
		capture(*move.capturePiece);

		// check for more captures for selected piece.
		std::vector<Move> validMoves = getValidMoves(*move.piece, false);
		bool changeTurnFlag = true;
		if (validMoves.empty()) {
			// change turn
			changeTurn(this);
		}
		else {
			for (auto& validMove : validMoves) {
				if (validMove.capturePiece != nullptr) {
					changeTurnFlag = false;
					break;
				}
			}
			if (changeTurnFlag) {
				changeTurn(this);
			}
		}
	}
	else {
		// change turn
		changeTurn(this);
	}

	// promote to king
	if (move.piece->getColor() == WHITE && move.piece->getPosition().y == 0) {
		move.piece->setType(KING);
	}
	else if (move.piece->getColor() == BLACK && move.piece->getPosition().y == height - 1) {
		move.piece->setType(KING);
	}
}

std::vector<Move> Board::getAllValidMoves() {
	std::vector<Move> allMoves;
	std::vector<Move> allJumps;

	if (currentColor == WHITE) {
		for (auto& piece : whitePieces) {
			auto moves = getValidMoves(piece, false);
			if (!moves.empty()) {
				for (auto& move : moves) {
					if (move.capturePiece != nullptr) {
						allJumps.push_back(move);
					}
					else {
						allMoves.push_back(move);
					}
				}
			}
		}
	}
	else {
		for (auto& piece : blackPieces) {
			auto moves = getValidMoves(piece, false);
			if (!moves.empty()) {
				for (auto& move : moves) {
					if (move.capturePiece != nullptr) {
						allJumps.push_back(move);
					}
					else {
						allMoves.push_back(move);
					}
				}
			}
		}
	}

	if (!allJumps.empty()) {
		return allJumps;
	}
	else {
		return allMoves;
	}
}

std::vector<Move> Board::getValidMoves(Piece& piece, bool checkValidMoves) {
	std::vector<Move> moves;

	if (checkValidMoves) {
		std::vector<Move> allValidMoves = getAllValidMoves();
		for (auto& move : allValidMoves) {
			if (*move.piece == piece) {
				moves.push_back(move);
			}
		}
		return moves;
	}

	if (piece.getColor() == currentColor) {
		if (piece.getType() == MAN) {
			if (piece.getColor() == WHITE) {
				// Move white piece
				Position leftMovePos = { piece.getPosition().x - 1, piece.getPosition().y - 1 };
				Position rightMovePos = { piece.getPosition().x + 1, piece.getPosition().y - 1 };

				if (leftMovePos.x >= 0 && leftMovePos.y >= 0) {
					auto leftPiece = getPieceAt(leftMovePos);
					if (leftPiece) {
						if (leftPiece->get().getColor() == BLACK) {
							Position newLeftPos = { leftMovePos.x - 1, leftMovePos.y - 1 };
							if (newLeftPos.x >= 0 && newLeftPos.y >= 0) {
								auto nextPiece = getPieceAt(newLeftPos);
								if (!nextPiece) {
									moves.push_back({ &piece, newLeftPos, &leftPiece->get() });
								}
							}
						}
					}
					else {
						moves.push_back({ &piece, leftMovePos, nullptr });
					}
				}

				if (rightMovePos.x < width && rightMovePos.y >= 0) {
					auto rightPiece = getPieceAt(rightMovePos);
					if (rightPiece) {
						if (rightPiece->get().getColor() == BLACK) {
							Position newRightPos = { rightMovePos.x + 1, rightMovePos.y - 1 };
							if (newRightPos.x < width && newRightPos.y >= 0) {
								auto nextPiece = getPieceAt(newRightPos);
								if (!nextPiece) {
									moves.push_back({ &piece, newRightPos, &rightPiece->get() });
								}
							}
						}
					}
					else {
						moves.push_back({ &piece, rightMovePos, nullptr });
					}
				}
			}
			else {
				// Move black piece
				Position leftMovePos = { piece.getPosition().x - 1, piece.getPosition().y + 1 };
				Position rightMovePos = { piece.getPosition().x + 1, piece.getPosition().y + 1 };
				if (leftMovePos.x >= 0 && leftMovePos.y < height) {
					auto leftPiece = getPieceAt(leftMovePos);
					if (leftPiece) {
						if (leftPiece->get().getColor() == WHITE) {
							Position newLeftPos = { leftMovePos.x - 1, leftMovePos.y + 1 };
							if (newLeftPos.x >= 0 && newLeftPos.y < height) {
								auto nextPiece = getPieceAt(newLeftPos);
								if (!nextPiece) {
									moves.push_back({ &piece, newLeftPos, &leftPiece->get() });
								}
							}
						}
					}
					else {
						moves.push_back({ &piece, leftMovePos, nullptr });
					}
				}

				if (rightMovePos.x < width && rightMovePos.y < height) {
					auto rightPiece = getPieceAt(rightMovePos);
					if (rightPiece) {
						if (rightPiece->get().getColor() == WHITE) {
							Position newRightPos = { rightMovePos.x + 1, rightMovePos.y + 1 };
							if (newRightPos.x < width && newRightPos.y < height) {
								auto nextPiece = getPieceAt(newRightPos);
								if (!nextPiece) {
									moves.push_back({ &piece, newRightPos, &rightPiece->get() });
								}
							}
						}
					}
					else {
						moves.push_back({ &piece, rightMovePos, nullptr });
					}
				}
			}
		}
		else if (piece.getType() == KING) {
			Position leftUpMovePos = { piece.getPosition().x - 1, piece.getPosition().y - 1 };
			Position leftDownMovePos = { piece.getPosition().x - 1, piece.getPosition().y + 1 };
			Position rightUpMovePos = { piece.getPosition().x + 1, piece.getPosition().y - 1 };
			Position rightDownMovePos = { piece.getPosition().x + 1, piece.getPosition().y + 1 };

			if (leftUpMovePos.x >= 0 && leftUpMovePos.y >= 0) {
				auto leftPiece = getPieceAt(leftUpMovePos);
				if (leftPiece) {
					if (leftPiece->get().getColor() != piece.getColor()) {
						Position newLeftPos = { leftUpMovePos.x - 1, leftUpMovePos.y - 1 };
						if (newLeftPos.x >= 0 && newLeftPos.y >= 0) {
							auto nextPiece = getPieceAt(newLeftPos);
							if (!nextPiece) {
								moves.push_back({ &piece, newLeftPos, &leftPiece->get() });
							}
						}
					}
				}
				else {
					moves.push_back({ &piece, leftUpMovePos, nullptr });
				}
			}

			if (rightUpMovePos.x < width && rightUpMovePos.y >= 0) {
				auto rightPiece = getPieceAt(rightUpMovePos);
				if (rightPiece) {
					if (rightPiece->get().getColor() != piece.getColor()) {
						Position newRightPos = { rightUpMovePos.x + 1, rightUpMovePos.y - 1 };
						if (newRightPos.x < width && newRightPos.y >= 0) {
							auto nextPiece = getPieceAt(newRightPos);
							if (!nextPiece) {
								moves.push_back({ &piece, newRightPos, &rightPiece->get() });
							}
						}
					}
				}
				else {
					moves.push_back({ &piece, rightUpMovePos, nullptr });
				}
			}

			if (leftDownMovePos.x >= 0 && leftDownMovePos.y < height) {
				auto leftPiece = getPieceAt(leftDownMovePos);
				if (leftPiece) {
					if (leftPiece->get().getColor() != piece.getColor()) {
						Position newLeftPos = { leftDownMovePos.x - 1, leftDownMovePos.y + 1 };
						if (newLeftPos.x >= 0 && newLeftPos.y < height) {
							auto nextPiece = getPieceAt(newLeftPos);
							if (!nextPiece) {
								moves.push_back({ &piece, newLeftPos, &leftPiece->get() });
							}
						}
					}
				}
				else {
					moves.push_back({ &piece, leftDownMovePos, nullptr });
				}
			}

			if (rightDownMovePos.x < width && rightDownMovePos.y < height) {
				auto rightPiece = getPieceAt(rightDownMovePos);
				if (rightPiece) {
					if (rightPiece->get().getColor() != piece.getColor()) {
						Position newRightPos = { rightDownMovePos.x + 1, rightDownMovePos.y + 1 };
						if (newRightPos.x < width && newRightPos.y < height) {
							auto nextPiece = getPieceAt(newRightPos);
							if (!nextPiece) {
								moves.push_back({ &piece, newRightPos, &rightPiece->get() });
							}
						}
					}
				}
				else {
					moves.push_back({ &piece, rightDownMovePos, nullptr });
				}
			}
		}
	}

	return moves;
}