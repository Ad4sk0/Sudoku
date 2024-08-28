#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "handlers/ClickHandler.h"
#include "handlers/TextEnteredHandler.h"
#include "components/modal_window/DialogBox.h"
#include "handlers/KeyPressedHandler.h"
#include "Game.h"
#include <functional>

class GameController
{
	const sf::Color BACKGROUND_COLOR = sf::Color::White;
	sf::RenderWindow& window;
	ClickHandler clickHandler;
	DialogBox* dialogBox = nullptr;
	std::vector<std::vector<sf::RectangleShape>> cellRectangles;
	Game game;
	bool isGameRunning = false;

	void startGameLoop();

	void draw();

	void handleGameSolved();

public:

	GameController(sf::RenderWindow& window) : window(window), clickHandler(window), game(window) {
	}

	void startGame();;

	void restartGame();

	void closeGame();
};