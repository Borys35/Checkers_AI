#include <iostream>

#include "Display.h"

Display::Display(Board& board) : board(board) {
}

Display::~Display() {
}

void Display::recordMouseClick(const sf::Event::MouseButtonPressed* event) {
	sf::Vector2i mousePos = event->position;

	if (mousePos.x > 768 && mousePos.x <= 1024 && mousePos.y > 600 && mousePos.y <= 768) {
		selectedPiece = nullptr;
		board.restart();
	}

	int x = mousePos.x / 96;
	int y = mousePos.y / 96;
	if (x >= 0 && x < width && y >= 0 && y < height) {
		auto piece = board.getPieceAt({ x, y });
		if (piece) {
			selectedPiece = &piece->get();
		}
		else if (selectedPiece) {
			std::vector<Move> moves = board.getValidMoves(*selectedPiece);
			for (auto& move : moves) {
				if (move.newPos.x == x && move.newPos.y == y) {
					// Move the piece
					board.makeMove(move);
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

	sf::Font font("inter.ttf");
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
				if (piece->get().getColor() == WHITE) {
					circle.setFillColor(sf::Color::Green);
				}
				else {
					circle.setFillColor(sf::Color::Red);
				}
				circle.setPosition({ i * 96.f + 16.f, j * 96.f + 16.f });
				window.draw(circle);
			}

			// Draw valid moves
			if (selectedPiece != nullptr) {
				std::vector<Move> moves = board.getValidMoves(*selectedPiece);

				for (auto &move : moves) {
					smallCircle.setPosition({ move.newPos.x * 96.f + 40.f, move.newPos.y * 96.f + 40.f });
					window.draw(smallCircle);
				}
			}
		}
	}

	// Draw restart button
	rect.setFillColor(sf::Color::Black);
	rect.setPosition({ 768.f, 600.f });
	rect.setSize({ 256.f, 168.f });
	window.draw(rect);

	// Draw text
	text.setString("Checkers");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 768.f, 0.f });
	window.draw(text);

	text.setString("Restart");
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 768.f, 600.f });
	window.draw(text);
}
