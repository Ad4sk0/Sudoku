#include "GameController.h"

void GameController::startGameLoop()
{
	window.setFramerateLimit(60);
	isGameRunning = true;
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
			{
				auto newValueEntryOptional = TextEnteredHandler::getEnteredValue(evnt.text);
				if (newValueEntryOptional) {
					game.handleNewValueEntry(newValueEntryOptional.value());
				}
				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				auto newSelectionOptional = clickHandler.getSelectedCell(evnt.mouseButton, cellRectangles);
				if (newSelectionOptional) {
					game.handleNewSelection(newSelectionOptional.value());
				}
				break;
			}
			case sf::Event::KeyReleased:
			{
				auto newKeyPressedOptional = KeyPressedHandler::getPressedKey(evnt.key);
				if (newKeyPressedOptional) {
					game.handlNewKeyPressed(newKeyPressedOptional.value());
				}
				break;
			}
			}

			if (dialogBox != nullptr) {
				dialogBox->handleEvent(evnt);
			}
		}

		if (game.isSolved())
		{
			handleGameSolved();
		}

		draw();
	}
}

void GameController::draw()
{
	window.clear(BACKGROUND_COLOR);
	cellRectangles = game.draw();
	if (dialogBox != nullptr) {
		dialogBox->draw();
	}
	window.display();
}

void GameController::handleGameSolved()
{
	dialogBox = new DialogBox(window, sf::Vector2f(400, 200), [this]() { this->restartGame(); }, [this]() { this->closeGame(); });
	dialogBox->show();
	isGameRunning = false;
}

void GameController::startGame()
{
	game.initialize();
	startGameLoop();
}

void GameController::restartGame()
{
	printf("Restarting game!\n");
	delete dialogBox;
	dialogBox = nullptr;
	game.restart();
	isGameRunning = true;
}

void GameController::closeGame()
{
	printf("Closing game!\n");
	window.close();
}
