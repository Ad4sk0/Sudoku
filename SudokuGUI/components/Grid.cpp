#include "Grid.h"

void Grid::draw_grid_lines()
{
	float x = marginX;
	float y = marginY;
	for (int i = 0; i < gridSize + 1; i++)
	{
		float lineThickness = lineThicknessSmall;
		auto color = lineThinColor;
		if (i % smallGridSize == 0) {
			lineThickness = lineThicknessBig;

			if (i == 0 || i == gridSize)
			{
				color = outsideBorderColor;
			}
			else
			{
				color = lineThickColor;
			}
		}

		sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, gridHeight));
		verticalLine.setPosition(x, marginY);
		verticalLine.setFillColor(color);
		window.draw(verticalLine);

		sf::RectangleShape horizontalLine(sf::Vector2f(gridWidth, lineThickness));
		horizontalLine.setPosition(marginX, y);
		horizontalLine.setFillColor(color);
		window.draw(horizontalLine);

		x += cellSize + lineThickness;
		y += cellSize + lineThickness;
	}
}

std::vector<std::vector<sf::RectangleShape>> Grid::draw_grid_cells()
{
	std::vector<std::vector<sf::RectangleShape>> result(gridSize, std::vector<sf::RectangleShape>(gridSize));


	float y = marginY + lineThicknessBig;
	for (int row = 0; row < gridSize; row++)
	{
		float x = marginX + lineThicknessBig;
		for (int col = 0; col < gridSize; col++)
		{
			sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
			rectangle.setPosition(x, y);
			rectangle.setFillColor(cellColor);

			if (currentlySelectedCell && currentlySelectedCell->first == row && currentlySelectedCell->second == col) {
				rectangle.setFillColor(cellSelectedColor);
			}

			window.draw(rectangle);
			result[row][col] = rectangle;

			drawValueIfDefined(rectangle, gridCells[row][col].value, gridCells[row][col].isConstant);

			float lineThickness = lineThicknessSmall;
			if ((col + 1) % smallGridSize == 0) {
				lineThickness = lineThicknessBig;
			}
			x += cellSize + lineThickness;
		}

		float lineThickness = lineThicknessSmall;
		if ((row + 1) % smallGridSize == 0) {
			lineThickness = lineThicknessBig;
		}
		y += cellSize + lineThickness;
	}
	return result;
}

void Grid::drawValueIfDefined(sf::RectangleShape& rectangle, int value, bool isConstant)
{
	if (value < 1) {
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(value));
	text.setCharacterSize(static_cast<int>(cellSize / 2.0f));
	if (isConstant)
	{
		text.setFillColor(gridTextColor);
		text.setStyle(gridTextStyle);
	}
	else
	{
		text.setFillColor(gridEditableTextColor);
		text.setStyle(gridEditableTextStyle);
	}
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f, rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
	window.draw(text);
}

std::optional<std::pair<int, int>> Grid::findEmptyCell(DirectionEnum direction, bool jump) {
	int rowChange = 0;
	int colChange = 0;

	switch (direction)
	{
	case LEFT:
		colChange = -1;
		break;
	case RIGHT:
		colChange = 1;
		break;
	case UP:
		rowChange = -1;
		break;
	case DOWN:
		rowChange = 1;;
		break;
	default:
		break;
	}

	auto start = lastCellSelection;
	if (!start) {
		start = std::pair<int, int>(0 - rowChange, 0 - colChange);
	}
	int row = start->first;
	int col = start->second;


	while (true)
	{
		row = row + rowChange;
		col = col + colChange;

		if (jump) {
			if (col < 0 || col >= gridSize)
			{
				row = row + colChange;
				col = colChange > 0 ? 0 : gridSize - 1;
			}
		}

		if (row < 0 || row >= gridSize || col < 0 || col >= gridSize)
		{
			break;
		}

		if (jump) {
			if (gridCells[row][col].value < 1)
			{
				return std::pair<int, int>(row, col);
			}
		}
		else {
			return std::pair<int, int>(row, col);
		}
	}
	return std::optional<std::pair<int, int>>();
}

void Grid::selectCell(std::pair<int, int>& cell)
{
	currentlySelectedCell = cell;
	lastCellSelection = cell;
}

std::vector<std::vector<sf::RectangleShape>> Grid::draw()
{
	draw_grid_lines();
	return draw_grid_cells();
}

void Grid::handleCellClick(std::pair<int, int> cell)
{
	if (gridCells[cell.first][cell.second].isConstant)
	{
		return;
	}
	if (currentlySelectedCell && currentlySelectedCell->first == cell.first && currentlySelectedCell->second == cell.second) {
		currentlySelectedCell = std::nullopt;
	}
	else {
		selectCell(cell);
	}
}

void Grid::handleNewValueEntry(int value)
{
	if (!currentlySelectedCell) {
		return;
	}
	if (gridCells[currentlySelectedCell->first][currentlySelectedCell->second].isConstant) {
		return;
	}
	gridCells[currentlySelectedCell->first][currentlySelectedCell->second].value = value;
	currentlySelectedCell = std::nullopt;
}

void Grid::handleNewKeyEntry(sf::Event::KeyEvent keyEvent)
{
	std::optional<std::pair<int, int>> nextCell;

	switch (keyEvent.code)
	{
	case sf::Keyboard::Up:
		nextCell = findEmptyCell(UP, false);
		break;
	case sf::Keyboard::Left:
		nextCell = findEmptyCell(LEFT, false);
		break;
	case sf::Keyboard::Right:
		nextCell = findEmptyCell(RIGHT, false);
		break;
	case sf::Keyboard::Down:
		nextCell = findEmptyCell(DOWN, false);
		break;
	case sf::Keyboard::Tab:
		if (keyEvent.shift) {
			nextCell = findEmptyCell(LEFT, true);
		}
		else {
			nextCell = findEmptyCell(RIGHT, true);
		}
		
		break;
	default:
		break;
	}

	if (nextCell) {
		selectCell(nextCell.value());
	}
}

std::vector<std::vector<int>> Grid::getGridValues()
{
	std::vector<std::vector<int>> valuesGrid(9, std::vector<int>(9));

	for (size_t row = 0; row < 9; row++)
	{
		for (size_t col = 0; col < 9; col++)
		{
			valuesGrid[row][col] = gridCells[row][col].value;
		}
	}
	return valuesGrid;
}

int Grid::getEmptyCellsNumber()
{
	auto gridValues = getGridValues();
	int sum = 0;
	for (auto& row : gridValues) {
		sum += count(row.begin(), row.end(), 0);
	}
	return sum;
}

const sf::Color cellColor;
const sf::Color cellSelectedColor;
const sf::Color gridTextColor;
const sf::Color outsideBorderColor;
const sf::Color lineThinColor;
const sf::Color lineThickColor;

Grid::Grid(sf::RenderWindow& window, const GridDimensions& gridDimensions, const GridStyle& gridStyle, std::vector<std::vector<Cell>> initialGridCels)
	: window(window),
	gridCells(initialGridCels),

	gridSize(gridDimensions.getGridSize()),
	smallGridSize(gridSize / 3),
	cellSize(gridDimensions.getCellSize()),
	marginX(gridDimensions.getMarginX()),
	marginY(gridDimensions.getMarginY()),
	lineThicknessSmall(gridDimensions.getLineThicknessSmall()),
	lineThicknessBig(gridDimensions.getLineThicknessBig()),
	gridHeight(gridDimensions.getGridHeight()),
	gridWidth(gridDimensions.getGridWidth()),
	cellColor(gridStyle.getCellColor()),
	cellSelectedColor(gridStyle.getCellSelectedColor()),
	gridTextColor(gridStyle.getGridTextColor()),
	gridEditableTextColor(gridStyle.getGridEditableTextColor()),
	outsideBorderColor(gridStyle.getOutsideBorderColor()),
	lineThinColor(gridStyle.getLineThinColor()),
	lineThickColor(gridStyle.getLineThickColor()),
	gridTextStyle(gridStyle.getGridTextStyle()),
	gridEditableTextStyle(gridStyle.getGridEditableTextStyle())
{

	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		printf("Unable to load font\n");
		throw std::runtime_error("Unable to load font");
	}

}
