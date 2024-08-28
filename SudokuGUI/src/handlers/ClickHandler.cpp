#include "handlers/ClickHandler.h"

std::optional<std::pair<int, int>> ClickHandler::getSelectedCell(sf::Event::MouseButtonEvent& mouseEvent, std::vector<std::vector<sf::RectangleShape>>& cellRectangles)
{
	if (mouseEvent.button != sf::Mouse::Left)
	{
		return std::nullopt;
	}

	for (int row = 0; row < cellRectangles.size(); row++)
	{
		for (int col = 0; col < cellRectangles[row].size(); col++)
		{
			sf::RectangleShape rectangle = cellRectangles[row][col];
			sf::Vector2f convertedClickCoordinates = window.mapPixelToCoords(sf::Vector2i(mouseEvent.x, mouseEvent.y));
			if (isPointInRectangle(convertedClickCoordinates, rectangle)) {
				return std::pair(row, col);
			}
		}
	}
	return std::nullopt;
}

bool ClickHandler::isBetween(float coordinate, float position, float size)
{
	return coordinate >= position && coordinate < position + size;
}

bool ClickHandler::isPointInRectangle(sf::Vector2f& clickCoordinates, sf::RectangleShape& rectangle)
{
	return isBetween(clickCoordinates.x, rectangle.getPosition().x, rectangle.getSize().x) && isBetween(clickCoordinates.y, rectangle.getPosition().y, rectangle.getSize().y);
}
