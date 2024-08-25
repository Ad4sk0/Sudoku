#include "Game.h"

std::vector<std::vector<Cell>> Game::generateSudokuGridCells() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(INITIAL_FILLED_VALUES_NUMBER_MIN, INITIAL_FILLED_VALUES_NUMBER_MAX);
	int initialFilledValuesNumber = dis(gen);

	SudokuGenerator sudokuGenerator;
	vector<vector<int>> grid = sudokuGenerator.generate(initialFilledValuesNumber);

	std::vector<std::vector<Cell>> result(GRID_SIZE, std::vector<Cell>());
	for (size_t row = 0; row < GRID_SIZE; row++)
	{
		for (size_t col = 0; col < GRID_SIZE; col++)
		{
			int value = grid[row][col];
			Cell cell = Cell(value, value > 0);
			result[row].emplace_back(value, value > 0);
		}
	}
	return result;
}

void Game::initialize()
{

	double marginY = window.getSize().x * 0.05;
	double marginX = window.getSize().x * 0.1;

	bool isXSmaller = window.getSize().x < window.getSize().y;
	bool isYSmaller = window.getSize().y < window.getSize().x;

	double smallerDimension = min(window.getSize().x, window.getSize().y);

	double smallerMargin;
	if (isXSmaller)
	{
		smallerMargin = marginX;
	}
	else {
		smallerMargin = marginY;
	}

	double cellSize = (smallerDimension - 4 * LINE_TICKNESS_BIG - 6 * LINE_TICKNESS_SMALL - smallerMargin * 2) / GRID_SIZE;

	if (isXSmaller)
	{
		smallerMargin = marginX;
	}
	else {
		smallerMargin = marginY;
	}


	if (isXSmaller)
	{
		marginY = (window.getSize().y - (cellSize * GRID_SIZE + 4 * LINE_TICKNESS_BIG + 6 * LINE_TICKNESS_SMALL)) / 2;
	}
	else {
		marginX = (window.getSize().x - (cellSize * GRID_SIZE + 4 * LINE_TICKNESS_BIG + 6 * LINE_TICKNESS_SMALL)) / 2;
	}


	GridDimensions gridDimensions(
		GRID_SIZE,
		static_cast<float>(cellSize),
		static_cast<float>(marginX),
		static_cast<float>(marginY),
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

	grid = new Grid(window, gridDimensions, gridStyle, generateSudokuGridCells());
}

void Game::restart()
{
	delete grid;
	initialize();
}

void Game::handleNewValueEntry(int value)
{
	grid->handleNewValueEntry(value);
	if (grid->getEmptyCellsNumber() == 0 && !isSolved())
	{
		auto validationResult = SudokuValidator::isGridValid(grid->getGridValues());
		printf("The cell: (%i, %i) is not valid\n", validationResult.notValidCell.first, validationResult.notValidCell.second);
	}
}

void Game::handleNewSelection(pair<int, int> cellPosition)
{
	grid->handleCellClick(cellPosition);
}

void Game::handlNewKeyPressed(sf::Event::KeyEvent keyEvent)
{
	grid->handleNewKeyEntry(keyEvent);
}

bool Game::isSolved()
{
	return SudokuValidator::isGridValid(grid->getGridValues()).isValid;
}

std::vector<std::vector<sf::RectangleShape>> Game::draw()
{
	return grid->draw();
}
