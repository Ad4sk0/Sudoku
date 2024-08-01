#include "ClickHandler.h"

std::optional<std::pair<int, int>> ClickHandler::getSelectedCell(sf::Event::MouseButtonEvent& mouseEvent, std::vector<std::vector<sf::RectangleShape>>& cellRectangles)
{

	for (int row = 0; row < cellRectangles.size(); row++)
	{
		for (int col = 0; col < cellRectangles[row].size(); col++)
		{
			sf::RectangleShape rectangle = cellRectangles[row][col];
			if (isPointInRectangle(mouseEvent, rectangle)) {
				return std::pair(row, col);
			}
		}
	}
	return std::nullopt;
}

bool ClickHandler::isBetween(int coordinate, float position, float size)
{
	return coordinate >= position && coordinate < position + size;
}

bool ClickHandler::isPointInRectangle(sf::Event::MouseButtonEvent& mouseEvent, sf::RectangleShape& rectangle)
{
	return isBetween(mouseEvent.x, rectangle.getPosition().x, rectangle.getSize().x) && isBetween(mouseEvent.y, rectangle.getPosition().y, rectangle.getSize().y);
}
