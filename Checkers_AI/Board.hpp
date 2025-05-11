#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Piece.hpp"

//class Piece;
//struct Position;

struct Move {
	Piece *piece;
	Position newPos;
	Piece *capturePiece = nullptr;
};

class Board {
public:
	Board();
	~Board();
	std::vector<Move> getValidMoves(Piece& piece, bool checkAllMoves);
	std::vector<Move> getAllValidMoves();
	std::optional<std::reference_wrapper<Piece>> getPieceAt(const Position pos);
	void makeMove(Move& move);
	void restart();

private:
	void capture(Piece& piece);
	int board[8][8] = { 0 };
	int width = 8;
	int height = 8;
	int whitePiecesCount = 12;
	int blackPiecesCount = 12;
	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;
	PieceColor currentColor = WHITE;
	bool gameOver = false;
};