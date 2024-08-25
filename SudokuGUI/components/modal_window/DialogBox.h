#pragma once
#include "ModalWindow.h"

class DialogBox :
	public ModalWindow
{

private:
	sf::RectangleShape buttonLeft;
	sf::RectangleShape buttonRight;
	void (*leftButtonAction)();
	void (*rightButtonAction)();

	void handleButtonLeftClick();

	void handleButtonRightClick();

public:

	DialogBox(sf::RenderWindow& window, const sf::Vector2f& size, void (*leftButtonAction)(), void (*rightButtonAction)())
		: ModalWindow(window, size), leftButtonAction(leftButtonAction), rightButtonAction(rightButtonAction) {};

	void handleEvent(sf::Event evnt) override;

	sf::RectangleShape drawTextButton(float width, float height, float x, float y, std::string text, sf::Color color);

	sf::Text createMessageText(float x, float y, std::string text, sf::Color color);

	void drawInternal() override;
};

