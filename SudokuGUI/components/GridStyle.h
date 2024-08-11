#pragma once
#include <SFML/Graphics.hpp>

class GridStyle
{
private:
	const sf::Color cellColor;
	const sf::Color cellSelectedColor;
	const sf::Color gridTextColor;
	const sf::Color gridEditableTextColor;
	const sf::Color outsideBorderColor;
	const sf::Color lineThinColor;
	const sf::Color lineThickColor;
	const sf::Text::Style gridTextStyle;
	const sf::Text::Style gridEditableTextStyle;

public:
	sf::Color getCellColor() const;
	sf::Color getCellSelectedColor() const;
	sf::Color getGridTextColor() const;
	sf::Color getGridEditableTextColor() const;
	sf::Color getOutsideBorderColor() const;
	sf::Color getLineThinColor() const;
	sf::Color getLineThickColor() const;
	sf::Text::Style getGridTextStyle() const;
	sf::Text::Style getGridEditableTextStyle() const;

	GridStyle(const sf::Color& cellColor, const sf::Color& cellSelectedColor, const sf::Color& gridTextColor, const sf::Color& gridEditableTextColor, const sf::Color& outsideBorderColor, const sf::Color& lineThinColor, const sf::Color& lineThickColor, const sf::Text::Style& gridTextStyle, const sf::Text::Style& gridEditableTextStyle)
		: cellColor(cellColor), cellSelectedColor(cellSelectedColor), gridTextColor(gridTextColor), gridEditableTextColor(gridEditableTextColor), outsideBorderColor(outsideBorderColor), lineThinColor(lineThinColor), lineThickColor(lineThickColor), gridTextStyle(gridTextStyle), gridEditableTextStyle(gridEditableTextStyle) {};
};

