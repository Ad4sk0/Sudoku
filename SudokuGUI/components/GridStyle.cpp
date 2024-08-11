#include "GridStyle.h"

sf::Color GridStyle::getCellColor() const
{
    return cellColor;
}

sf::Color GridStyle::getCellSelectedColor() const
{
    return cellSelectedColor;
}

sf::Color GridStyle::getGridTextColor() const
{
    return gridTextColor;
}

sf::Color GridStyle::getGridEditableTextColor() const
{
    return gridEditableTextColor;
}

sf::Color GridStyle::getOutsideBorderColor() const
{
    return outsideBorderColor;
}

sf::Color GridStyle::getLineThinColor() const
{
    return lineThinColor;
}

sf::Color GridStyle::getLineThickColor() const
{
    return lineThickColor;
}

sf::Text::Style GridStyle::getGridTextStyle() const
{
    return gridTextStyle;
}

sf::Text::Style GridStyle::getGridEditableTextStyle() const
{
    return gridEditableTextStyle;
}
