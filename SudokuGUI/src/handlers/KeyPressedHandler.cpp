#include "handlers/KeyPressedHandler.h"

std::optional<sf::Event::KeyEvent> KeyPressedHandler::getPressedKey(sf::Event::KeyEvent keyEvent)
{
	if (supportedKeys.find(keyEvent.code) != supportedKeys.end())
	{
		return keyEvent;
	}
	return std::optional<sf::Event::KeyEvent>();
}
