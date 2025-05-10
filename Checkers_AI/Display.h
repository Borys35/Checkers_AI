#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Board.hpp"
#include "Piece.hpp"


class Display
{
public:
	Display(Board& board);
	~Display();
	void drawBoard(sf::RenderWindow& window);
	void recordMouseClick(const sf::Event::MouseButtonPressed *event);

private:
	Piece* selectedPiece = nullptr;
	Board& board;
	int width = 8;
	int height = 8;
};

