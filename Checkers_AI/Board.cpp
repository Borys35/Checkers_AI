#include "Board.hpp"

Board::Board() {
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
	move.piece->setPosition(move.newPos);
	capture(*move.capturePiece);
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
								moves.push_back({ &piece, newLeftPos, &leftPiece->get() });
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
								moves.push_back({ &piece, newRightPos, &rightPiece->get() });
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
								moves.push_back({ &piece, newLeftPos, &leftPiece->get() });
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
								moves.push_back({ &piece, newRightPos, &rightPiece->get() });
							}
						}
					}
					else {
						moves.push_back({ &piece, rightMovePos, nullptr });
					}
				}
			}
		}
		/*else if (piece.getType() == KING) {
			Position leftUpMovePos = { piece.getPosition().x - 1, piece.getPosition().y - 1 };
			Position leftDownMovePos = { piece.getPosition().x - 1, piece.getPosition().y + 1 };
			Position rightUpMovePos = { piece.getPosition().x + 1, piece.getPosition().y - 1 };
			Position rightDownMovePos = { piece.getPosition().x + 1, piece.getPosition().y + 1 };

			if (leftUpMovePos.x >= 0 && leftUpMovePos.y >= 0) {
				auto leftUpPiece = getPieceAt(leftUpMovePos);
				if (leftUpPiece) {
					if (leftUpPiece->get().getColor() != currentColor) {
						Position newLeftUpPos = { leftUpMovePos.x - 1, leftUpMovePos.y - 1 };
						if (newLeftUpPos.x >= 0 && newLeftUpPos.y >= 0) {
							moves.push_back({ &piece, newLeftUpPos, &leftUpPiece->get() });
						}
					}
				}
				else {
					moves.push_back({ &piece, leftUpMovePos, nullptr });
				}
			}
		}*/
	}

	return moves;
}