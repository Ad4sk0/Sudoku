#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <optional>
#include "./components/Cell.h"
#include "./components/GridDimensions.h"
#include "./components/Grid.h"
#include "handlers/ClickHandler.h"
#include "handlers/TextEnteredHandler.h"


std::vector<std::vector<Cell>> generateSudokuGrid(const int gridSize) {
	std::vector<std::vector<Cell>> result(gridSize, std::vector<Cell>(gridSize));
	/*for (size_t row = 0; row < gridSize; row++)
	{
		for (size_t col = 0; col < gridSize; col++)
		{
		}
	}*/
	return result;
}



int main() {

	const int GRID_SIZE = 9;
	const float CELL_SIZE = 100;
	const float GRID_MARGIN_X = 200;
	const float GRID_MARGIN_Y = 100;
	const float LINE_TICKNESS_SMALL = 1;
	const float LINE_TICKNESS_BIG = 5;

	GridDimensions gridDimensions(
		GRID_SIZE,
		CELL_SIZE,
		GRID_MARGIN_X,
		GRID_MARGIN_Y,
		LINE_TICKNESS_SMALL,
		LINE_TICKNESS_BIG
	);	

	const std::string WINDOW_TITLE = "Sudoku";
	const int WINDOW_WIDTH = static_cast<int>(gridDimensions.getGridWidth() + gridDimensions.getMarginX() * 2);
	const int WINDOW_HEIGHT = static_cast<int>(gridDimensions.getGridHeight() + gridDimensions.getMarginY() * 2);
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	std::vector<std::vector<sf::RectangleShape>> cellRectangles;
	Grid grid(window, gridDimensions, generateSudokuGrid(GRID_SIZE));

	
	
	std::optional<std::pair<int, int>> newSelection;
	std::optional<int> newValueEntry;

	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		newSelection = std::nullopt;
		newValueEntry = std::nullopt;
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				printf("Width: %i Height: %i\n", evnt.size.width, evnt.size.height);
				break;
			case sf::Event::TextEntered:
				newValueEntry = TextEnteredHandler::getEnteredValue(evnt.text);
				break;
			case sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					newSelection = ClickHandler::getSelectedCell(evnt.mouseButton, cellRectangles);
				}
			}
		}

		window.clear();
		if (newSelection) {
			grid.handleCellClick(newSelection.value());
		}
		if (newValueEntry) {
			grid.handleNewValueEntry(newValueEntry.value());
		}
		
		cellRectangles = grid.draw();
		window.display();

	}
	return 0;
}