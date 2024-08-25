#pragma once
#include "ModalWindow.h"
#include <functional>

class DialogBox :
	public ModalWindow
{

private:
	sf::RectangleShape buttonLeft;
	sf::RectangleShape buttonRight;
	std::function<void()> leftButtonAction;
	std::function<void()> rightButtonAction;

	void handleButtonLeftClick();

	void handleButtonRightClick();

public:

	DialogBox(sf::RenderWindow& window, const sf::Vector2f& size, std::function<void()> leftButtonAction, std::function<void()> rightButtonAction)
		: ModalWindow(window, size), leftButtonAction(leftButtonAction), rightButtonAction(rightButtonAction) {};

	void handleEvent(sf::Event evnt) override;

	sf::RectangleShape drawTextButton(float width, float height, float x, float y, std::string text, sf::Color color);

	sf::Text createMessageText(float x, float y, std::string text, sf::Color color);

	void drawInternal() override;
};

