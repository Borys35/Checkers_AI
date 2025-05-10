#pragma once

#include <vector>

enum PieceType {
	MAN,
	KING
};

enum PieceColor {
	WHITE,
	BLACK
};

struct Position {
	int x;
	int y;

	bool operator ==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};

class Piece {
public:
	Piece(PieceType t, PieceColor c, Position pos);
	~Piece();
	PieceType getType() const;
	PieceColor getColor() const;
	Position getPosition() const;
	void setPosition(Position pos);
	void setType(PieceType t);
private:
	PieceType type;
	PieceColor color;
	Position position = { 0, 0 };
};