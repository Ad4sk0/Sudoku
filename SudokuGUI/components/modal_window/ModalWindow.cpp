#include "ModalWindow.h"

void ModalWindow::draw()
{
	window.draw(backgroundRectangle);
	drawInternal();
}

ModalWindow::ModalWindow(sf::RenderWindow& window, const sf::Vector2f& size)
	: window(window), size(size)
{
	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		throw std::runtime_error("Unable to load font");
	}

	sf::Vector2f boxPosition((window.getSize().x - size.x) / 2, (window.getSize().y - size.y) / 2);

	backgroundRectangle = sf::RectangleShape(size);
	backgroundRectangle.setPosition(boxPosition);
	backgroundRectangle.setFillColor(sf::Color::White);
	backgroundRectangle.setOutlineColor(sf::Color::Black);
	backgroundRectangle.setOutlineThickness(2.f);
}

void ModalWindow::show()
{
	modalWindowOpen = true;
}
