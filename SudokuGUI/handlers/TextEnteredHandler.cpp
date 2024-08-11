#include "TextEnteredHandler.h"

std::optional<int> TextEnteredHandler::getEnteredValue(sf::Event::TextEvent textEvent)
{
    if (textEvent.unicode == 8)
    {
        return 0;
    }
    if (textEvent.unicode >= '1' && textEvent.unicode <= '9')
    {
        return textEvent.unicode - '0';
    }
    return std::optional<int>();
}
