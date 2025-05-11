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

void Piece::setPosition(Position pos) {
	position = pos;
}

void Piece::setType(PieceType t) {
	type = t;
}

bool Piece::operator==(const Piece& other) const {
	return position == other.position && type == other.type && color == other.color;
}