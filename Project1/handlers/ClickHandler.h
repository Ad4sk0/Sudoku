#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

class ClickHandler
{
public:
	std::optional<std::pair<int, int>> getSelectedCell(sf::Event::MouseButtonEvent& mouseEvent, std::vector<std::vector<sf::RectangleShape>>& cellRectangles);

private:
	const sf::RenderWindow& window;

	bool isBetween(float coordinate, float position, float size);
	bool isPointInRectangle(sf::Vector2f& clickCoordinates, sf::RectangleShape& rectangle);
public:
	ClickHandler(const sf::RenderWindow& window)
		: window(window) {};
};

