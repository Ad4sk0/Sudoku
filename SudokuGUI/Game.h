#pragma once

#include <SFML/Graphics.hpp>
#include "./components/Cell.h"
#include "./components/GridDimensions.h"
#include "./components/GridStyle.h"
#include "./components/Grid.h"
#include "../Sudoku/validator/SudokuValidator.h"
#include "../Sudoku/generator/SudokuGenerator.h"
#include <random>

class Game
{
private:
	sf::RenderWindow& window;
	Grid* grid = nullptr;

	const int GRID_SIZE = 9;
	const int INITIAL_FILLED_VALUES_NUMBER_MIN = 45;
	const int INITIAL_FILLED_VALUES_NUMBER_MAX = 55;
	const float LINE_TICKNESS_SMALL = 1;
	const float LINE_TICKNESS_BIG = 5;
	const sf::Color CELL_COLOR = sf::Color::White;
	const sf::Color CELL_SELECTED_COLOR = sf::Color::Green;
	const sf::Color GRID_TEXT_COLOR = sf::Color::Black;
	const sf::Color GRID_EDITABLE_TEXT_COLOR = sf::Color::Red;
	const sf::Color OUTISDE_BORDER_COLOR = sf::Color::Black;
	const sf::Color LINE_THIN_COLOR = sf::Color::Black;
	const sf::Color LINE_THICK_COLOR = sf::Color::Black;
	const sf::Text::Style GRID_TEXT_STYLE = sf::Text::Bold;
	const sf::Text::Style GRID_EDITABLE_TEXT_STYLE = sf::Text::Bold;

	std::vector<std::vector<Cell>> generateSudokuGridCells();

public:

	Game(sf::RenderWindow& window) : window(window) {}

	void initialize();

	void restart();

	void handleNewValueEntry(int value);

	void handleNewSelection(pair<int, int> cellPosition);

	void handlNewKeyPressed(sf::Event::KeyEvent keyEvent);

	bool isSolved();

	std::vector<std::vector<sf::RectangleShape>> draw();
};

