#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.hpp"
#include "Display.h"

int main()
{
    Board board = Board();
	Display display = Display(board);

    sf::RenderWindow window(sf::VideoMode({ 1024, 768 }), "Checkers");

	std::cout << "Window created" << std::endl;


    while (window.isOpen())
    {
        sf::Vector2i mouseClickPos = sf::Vector2i(-1, -1);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
					display.recordMouseClick(mouseButtonPressed);
                }
            }
        }

        window.clear(sf::Color(100, 0, 0, 255));

        // board.draw(window, mouseClickPos);
        display.drawBoard(window);

        window.display();
    }
}