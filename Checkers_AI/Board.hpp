#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Piece.hpp"

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
	void makeMove(Move& move, bool madeByAI);
	void restart(bool switchSides);
	void restart(bool switchSides, bool vsAI);
	bool isGameOver() const;
	bool isBottomPlayerWhite() const;
	bool isVsAI() const;
	int evaluateBoard() const;

private:
	void capture(Piece& piece);
	int width = 8;
	int height = 8;
	int whitePiecesCount = 12;
	int blackPiecesCount = 12;
	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;
	PieceColor currentColor = WHITE;
	bool bottomPlayerWhite = true;
	bool gameOver = false;
	bool vsAI = false;
};