#include <iostream>

#include "Board.hpp"

void Board::restart() {
	whitePieces.clear();
	blackPieces.clear();
	whitePiecesCount = 12;
	blackPiecesCount = 12;
	currentColor = WHITE;
	gameOver = false;

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
	restart();
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
	// new position
	move.piece->setPosition(move.newPos);

	// capture
	if (move.capturePiece != nullptr) {
		capture(*move.capturePiece);
	}

	// promote to king
	if (move.piece->getColor() == WHITE && move.piece->getPosition().y == 0) {
		move.piece->setType(KING);
	}
	else if (move.piece->getColor() == BLACK && move.piece->getPosition().y == height - 1) {
		move.piece->setType(KING);
	}

	// change turn
	if (move.piece->getColor() == WHITE) {
		currentColor = BLACK;
	}
	else {
		currentColor = WHITE;
	}
}

std::vector<Move> Board::getValidMoves(Piece& piece) {
	std::vector<Move> moves;

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