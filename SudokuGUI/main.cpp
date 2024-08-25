#include <SFML/Graphics.hpp>
#include "GameController.h"


int main() {
	const std::string WINDOW_TITLE = "Sudoku";

	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), WINDOW_TITLE);

	GameController gameController(window);
	gameController.startGame();

	return 0;
}