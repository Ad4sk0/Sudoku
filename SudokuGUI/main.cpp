#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <optional>
#include "./components/Cell.h"
#include "./components/GridDimensions.h"
#include "./components/GridStyle.h"
#include "./components/Grid.h"
#include "handlers/ClickHandler.h"
#include "handlers/TextEnteredHandler.h"
#include "../Sudoku/generator/SudokuGenerator.h"
#include "../Sudoku/validator/SudokuValidator.h"
#include "./components/modal_window/DialogBox.h"
#include "handlers/KeyPressedHandler.h"


bool endGame = false;
bool isRestartGame = false;

static void restartGame()
{
	printf("Restarting game!\n");
	isRestartGame = true;
}

static void closeGame()
{
	printf("Closing game!\n");
	endGame = true;
}

std::vector<std::vector<Cell>> generateSudokuGrid(const int gridSize, const int initialFilledValuesNumber) {
	SudokuGenerator sudokuGenerator;
	vector<vector<int>> grid = sudokuGenerator.generate(initialFilledValuesNumber);
	
	std::vector<std::vector<Cell>> result(gridSize, std::vector<Cell>());
	for (size_t row = 0; row < gridSize; row++)
	{
		for (size_t col = 0; col < gridSize; col++)
		{
			int value = grid[row][col];
			Cell cell = Cell(value, value > 0);
			result[row].emplace_back(value, value > 0);
		}
	}
	return result;
}

int main() {

	const int GRID_SIZE = 9;
	const int INITIAL_FILLED_VALUES_NUMBER_MIN = 45;
	const int INITIAL_FILLED_VALUES_NUMBER_MAX = 55;
	const float CELL_SIZE = 50;
	const float GRID_MARGIN_X = 200;
	const float GRID_MARGIN_Y = 100;
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

	const sf::Color BACKGROUND_COLOR = sf::Color::White;

	GridDimensions gridDimensions(
		GRID_SIZE,
		CELL_SIZE,
		GRID_MARGIN_X,
		GRID_MARGIN_Y,
		LINE_TICKNESS_SMALL,
		LINE_TICKNESS_BIG
	);

	GridStyle gridStyle(
		CELL_COLOR,
		CELL_SELECTED_COLOR,
		GRID_TEXT_COLOR,
		GRID_EDITABLE_TEXT_COLOR,
		OUTISDE_BORDER_COLOR,
		LINE_THIN_COLOR,
		LINE_THICK_COLOR,
		GRID_TEXT_STYLE,
		GRID_EDITABLE_TEXT_STYLE
	);

	const std::string WINDOW_TITLE = "Sudoku";
	const int WINDOW_WIDTH = static_cast<int>(gridDimensions.getGridWidth() + gridDimensions.getMarginX() * 2);
	const int WINDOW_HEIGHT = static_cast<int>(gridDimensions.getGridHeight() + gridDimensions.getMarginY() * 2);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

	ClickHandler clickHandler(window);

	std::vector<std::vector<sf::RectangleShape>> cellRectangles;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(INITIAL_FILLED_VALUES_NUMBER_MIN, INITIAL_FILLED_VALUES_NUMBER_MAX);
	int initialFilledValuesNumber = dis(gen);
	Grid grid(window, gridDimensions, gridStyle, generateSudokuGrid(GRID_SIZE, initialFilledValuesNumber));

	std::optional<std::pair<int, int>> newSelection;
	std::optional<int> newValueEntry;
	std::optional<sf::Event::KeyEvent> newKeyPressed;

	window.setFramerateLimit(60);

	DialogBox* dialogBox = nullptr;
	bool isFinished = false;

	while (window.isOpen())
	{
		if (endGame)
		{
			window.close();
		}

		if (isRestartGame) {
			delete dialogBox;
			dialogBox = nullptr;
			isFinished = false;
			isRestartGame = false;
			grid.reset(generateSudokuGrid(GRID_SIZE, initialFilledValuesNumber));
		}

		newSelection = std::nullopt;
		newValueEntry = std::nullopt;
		newKeyPressed = std::nullopt;

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
					newSelection = clickHandler.getSelectedCell(evnt.mouseButton, cellRectangles);
				}
			case sf::Event::KeyReleased:
				newKeyPressed = KeyPressedHandler::getPressedKey(evnt.key);
				break;
			}

			if (dialogBox != nullptr) {
				dialogBox->handleEvent(evnt);
			}
		}

		window.clear(BACKGROUND_COLOR);

		if (newSelection) {
			grid.handleCellClick(newSelection.value());
		}
		if (newValueEntry) {
			grid.handleNewValueEntry(newValueEntry.value());
		}
		if (newKeyPressed) {
			grid.handleNewKeyEntry(newKeyPressed.value());
		}

		cellRectangles = grid.draw();

		if (!isFinished) {
			auto validationResult = SudokuValidator::isGridValid(grid.getGridValues());
			if (validationResult.isValid)
			{
				dialogBox = new DialogBox(window, sf::Vector2f(400, 200), restartGame, closeGame);
				dialogBox->show();
				isFinished = true;
			}
			else if (newValueEntry && grid.getEmptyCellsNumber() == 0) {
				printf("The cell: (%i, %i) is not valid\n", validationResult.notValidCell.first, validationResult.notValidCell.second);
			}
		}

		if (dialogBox != nullptr) {
			dialogBox->draw();
		}

		window.display();
	}
	return 0;
}