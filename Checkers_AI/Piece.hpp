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
};

class Piece {
public:
	Piece(PieceType t, PieceColor c, Position pos);
	~Piece();
	PieceType getType() const;
	PieceColor getColor() const;
	Position getPosition() const;
private:
	PieceType type;
	PieceColor color;
	Position position = { 0, 0 };
};