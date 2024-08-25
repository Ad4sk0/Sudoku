#pragma once
#include <SFML/Graphics.hpp>

class ModalWindow
{
protected:

	sf::RenderWindow& window;
	sf::Font font;
	sf::Vector2f size;
	sf::RectangleShape backgroundRectangle;
	bool modalWindowOpen = false;

	virtual void drawInternal() = 0;

public:

	virtual void handleEvent(sf::Event evnt) = 0;

	void draw();

	ModalWindow(sf::RenderWindow& window, const sf::Vector2f& size);

	void show();
};

