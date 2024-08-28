#include "components/modal_window/DialogBox.h"

void DialogBox::handleButtonLeftClick()
{
	modalWindowOpen = false;
	leftButtonAction();
}

void DialogBox::handleButtonRightClick()
{
	modalWindowOpen = false;
	rightButtonAction();
}

void DialogBox::handleEvent(sf::Event evnt)
{
	if (evnt.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (buttonLeft.getGlobalBounds().contains(mousePos)) {
			handleButtonLeftClick();
		}
		else if (buttonRight.getGlobalBounds().contains(mousePos)) {
			handleButtonRightClick();
		}
	}
}

sf::RectangleShape DialogBox::drawTextButton(float width, float height, float x, float y, std::string text, sf::Color color)
{
	sf::RectangleShape button(sf::Vector2f(width, height));
	button.setPosition(x, y);
	button.setFillColor(color);
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(1.f);

	sf::Text buttonText(text, font, 20);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setOutlineColor(sf::Color::White);
	buttonText.setOutlineThickness(2.f);

	buttonText.setOrigin(buttonText.getLocalBounds().left + buttonText.getLocalBounds().width / 2.0f, buttonText.getLocalBounds().top + buttonText.getLocalBounds().height / 2.0f);
	buttonText.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);

	window.draw(button);
	window.draw(buttonText);
	return button;
}

sf::Text DialogBox::createMessageText(float x, float y, std::string text, sf::Color color)
{
	sf::Text messageText(text, font, 24);
	messageText.setFillColor(color);
	messageText.setOutlineColor(sf::Color::White);
	messageText.setOutlineThickness(2.f);

	messageText.setOrigin(messageText.getLocalBounds().left + messageText.getLocalBounds().width / 2.0f, messageText.getLocalBounds().top);
	messageText.setPosition(x, y);
	return messageText;
}

void DialogBox::drawInternal()
{

	float margin = 20.f;

	float messageTextX = backgroundRectangle.getPosition().x + backgroundRectangle.getSize().x / 2.0f;
	float messageTextY = backgroundRectangle.getPosition().y + margin;

	std::vector<std::string> messageLines = {
		"Sudoku is correctly solved.",
		"Congratulations!"
	};

	for (std::string textLine : messageLines)
	{
		sf::Text messageText = createMessageText(messageTextX, messageTextY, textLine, sf::Color::Black);
		messageTextY += messageText.getGlobalBounds().getSize().y;
		window.draw(messageText);
	}


	float gap = 40.f;
	float buttonWidth = (backgroundRectangle.getSize().x - margin * 2.f - gap) / 2.f;
	float buttonHeight = 50.f;
	float buttonY = backgroundRectangle.getPosition().y + backgroundRectangle.getSize().y - buttonHeight - margin;

	float buttonLeftX = backgroundRectangle.getPosition().x + margin;
	float buttonRightX = buttonLeftX + buttonWidth + gap;

	buttonLeft = drawTextButton(buttonWidth, buttonHeight, buttonLeftX, buttonY, "Play again", sf::Color::Green);
	buttonRight = drawTextButton(buttonWidth, buttonHeight, buttonRightX, buttonY, "End game", sf::Color::Red);
}