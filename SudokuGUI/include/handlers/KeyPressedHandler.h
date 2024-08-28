#pragma once

#include <unordered_set>
#include <optional>
#include <SFML/Graphics.hpp>

class KeyPressedHandler
{
private:

	inline static const std::unordered_set<sf::Keyboard::Key> supportedKeys = {
		sf::Keyboard::Up,
		sf::Keyboard::Down,
		sf::Keyboard::Left,
		sf::Keyboard::Right,
		sf::Keyboard::Tab
	};

public:

	static std::optional<sf::Event::KeyEvent> getPressedKey(sf::Event::KeyEvent keyEvent);
};

