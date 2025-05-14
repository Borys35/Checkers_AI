#include <iostream>
#include <filesystem>

#include "Display.h"
#include "Board.hpp"
#include "Piece.hpp"

Display::Display(Board& board) : board(board) {
}

Display::~Display() {
}

void Display::recordMouseClick(const sf::Event::MouseButtonPressed* event) {
	sf::Vector2i mousePos = event->position;

	if (mousePos.x > 768 && mousePos.x <= 1024 && mousePos.y > 600 && mousePos.y <= 768) {
		// Switch sides
		selectedPiece = nullptr;
		board.restart(true);
	}
	else if (mousePos.x > 768 && mousePos.x <= 896 && mousePos.y > 500 && mousePos.y <= 600) {
		// vs AI
		selectedPiece = nullptr;
		board.restart(false, true);
	}
	else if (mousePos.x > 896 && mousePos.x <= 1024 && mousePos.y > 500 && mousePos.y <= 600) {
		// vs Player
		selectedPiece = nullptr;
		board.restart(false, false);
	}

	int x = mousePos.x / 96;
	int y = mousePos.y / 96;
	if (x >= 0 && x < width && y >= 0 && y < height) {
		auto piece = board.getPieceAt({ x, y });
		if (piece) {
			selectedPiece = &piece->get();
		}
		else if (selectedPiece) {
			std::vector<Move> moves = board.getValidMoves(*selectedPiece, true);
			for (auto& move : moves) {
				if (move.newPos.x == x && move.newPos.y == y) {
					// Move the piece
					board.makeMove(move, false);
					selectedPiece = nullptr;
					break;
				}
			}
		}
	}
}

void Display::drawBoard(sf::RenderWindow& window) {
	sf::RectangleShape rect({ 96, 96 });
	rect.setFillColor(sf::Color::White);

	sf::CircleShape circle(32.f);
	circle.setFillColor(sf::Color::Red);

	sf::CircleShape smallCircle(8.f);
	smallCircle.setFillColor(sf::Color::Blue);

	sf::Font font;
	if (!font.openFromFile("inter.ttf")) {
		std::cerr << "Font loading failed in Release mode\n";
	}

	sf::Text text(font);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Draw tiles
			if ((i + j) % 2 == 0) {
				rect.setFillColor(sf::Color::White);
			}
			else {
				rect.setFillColor(sf::Color::Black);
			}
			rect.setPosition({ i * 96.f, j * 96.f });
			window.draw(rect);

			// Draw pieces
			auto piece = board.getPieceAt({ i, j });
			if (piece) {
				if ((piece->get().getColor() == WHITE && board.isBottomPlayerWhite()) ||
					(piece->get().getColor() == BLACK && !board.isBottomPlayerWhite())) {
					if (piece->get().getType() == KING) {
						circle.setFillColor(sf::Color(33, 130, 33));
					}
					else {
						circle.setFillColor(sf::Color::Green);
					}
				}
				else {
					if (piece->get().getType() == KING) {
						circle.setFillColor(sf::Color(130, 33, 33));
					}
					else {
						circle.setFillColor(sf::Color::Red);
					}
				}
				circle.setPosition({ i * 96.f + 16.f, j * 96.f + 16.f });
				window.draw(circle);
			}

			// Draw valid moves
			if (selectedPiece != nullptr) {
				std::vector<Move> moves = board.getValidMoves(*selectedPiece, true);

				for (auto &move : moves) {
					smallCircle.setPosition({ move.newPos.x * 96.f + 40.f, move.newPos.y * 96.f + 40.f });
					window.draw(smallCircle);
				}
			}
		}
	}

	// Draw buttons
	rect.setFillColor(sf::Color::Black);
	rect.setPosition({ 768.f, 600.f });
	rect.setSize({ 256.f, 168.f });
	window.draw(rect);


	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition({ 768.f, 500.f });
	rect.setSize({ 128.f, 100.f });
	window.draw(rect);

	rect.setFillColor(sf::Color::Green);
	rect.setPosition({ 896.f, 500.f });
	rect.setSize({ 128.f, 100.f });
	window.draw(rect);

	// Draw text
	text.setString("Checkers");
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 768.f, 0.f });
	window.draw(text);

	if (board.isVsAI()) {
		text.setString("vs AI");
	}
	else {
		text.setString("Player vs Player");
	}
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 768.f, 40.f });
	window.draw(text);

	text.setString("Current Pos Eval: " + std::to_string(board.evaluateBoard()));
	text.setCharacterSize(16);
	text.setPosition({ 768.f, 80.f });
	window.draw(text);

	if (board.isGameOver()) {
		text.setString("Game Over");
		text.setCharacterSize(32);
		text.setFillColor(sf::Color::Red);
		text.setPosition({ 768.f, 120.f });
		window.draw(text);
	}

	// TODO: Add switch sides functionality
	text.setString("Switch sides");
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 768.f, 600.f });
	window.draw(text);

	text.setString("vs AI");
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 768.f, 500.f });
	window.draw(text);

	text.setString("vs Player");
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 896.f, 500.f });
	window.draw(text);
}
