#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

class ClickHandler
{
public:
	static std::optional<std::pair<int, int>> getSelectedCell(sf::Event::MouseButtonEvent& mouseEvent, std::vector<std::vector<sf::RectangleShape>>& cellRectangles);

private:
	static bool isBetween(int coordinate, float position, float size);
	static bool isPointInRectangle(sf::Event::MouseButtonEvent& mouseEvent, sf::RectangleShape& rectangle);
};

