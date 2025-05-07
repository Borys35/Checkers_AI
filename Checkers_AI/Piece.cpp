#include "Piece.hpp"

Piece::Piece(PieceType t, PieceColor c, Position pos) {
	position = pos;
	type = t;
	color = c;
}

Piece::~Piece() {

}

PieceColor Piece::getColor() const {
	return color;
}

PieceType Piece::getType() const {
	return type;
}

Position Piece::getPosition() const {
	return position;
}