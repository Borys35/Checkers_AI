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

}

std::vector<Move> Board::getValidMoves(const Piece& piece) {
	if (piece.getColor() == currentColor) {
		if (piece.getColor() == WHITE) {
			if (piece.getType() == MAN) {

			}
			else if (piece.getType() == KING) {

			}
		}
	}
}