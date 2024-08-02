#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class TextEnteredHandler
{
public:
	static std::optional<int> getEnteredValue(sf::Event::TextEvent textEvent);
};

