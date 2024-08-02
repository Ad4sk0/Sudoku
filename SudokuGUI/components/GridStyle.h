#pragma once
#include <SFML/Graphics.hpp>

class GridStyle
{
private:
	const sf::Color cellColor;
	const sf::Color cellSelectedColor;
	const sf::Color gridTextColor;
	const sf::Color outsideBorderColor;
	const sf::Color lineThinColor;
	const sf::Color lineThickColor;
	const sf::Text::Style gridTextStyle;

public:
	sf::Color getCellColor() const;
	sf::Color getCellSelectedColor() const;
	sf::Color getGridTextColor() const;
	sf::Color getOutsideBorderColor() const;
	sf::Color getLineThinColor() const;
	sf::Color getLineThickColor() const;
	sf::Text::Style getGridTextStyle() const;

	GridStyle(const sf::Color& cellColor, const sf::Color& cellSelectedColor, const sf::Color& gridTextColor, const sf::Color& outsideBorderColor, const sf::Color& lineThinColor, const sf::Color& lineThickColor, const sf::Text::Style& gridTextStyle)
		: cellColor(cellColor), cellSelectedColor(cellSelectedColor), gridTextColor(gridTextColor), outsideBorderColor(outsideBorderColor), lineThinColor(lineThinColor), lineThickColor(lineThickColor), gridTextStyle(gridTextStyle) {};
};

