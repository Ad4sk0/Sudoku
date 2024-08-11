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

			drawValueIfDefined(rectangle, gridCells[row][col].value);

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

void Grid::drawValueIfDefined(sf::RectangleShape& rectangle, int value)
{
	if (value < 1) {
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(value));
	text.setCharacterSize(static_cast<int>(cellSize / 2.0f));
	text.setFillColor(gridTextColor);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f, rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
	window.draw(text);
}

std::vector<std::vector<sf::RectangleShape>> Grid::draw()
{
	draw_grid_lines();
	return draw_grid_cells();
}

void Grid::handleCellClick(std::pair<int, int> cell)
{
	if (currentlySelectedCell && currentlySelectedCell->first == cell.first && currentlySelectedCell->second == cell.second) {
		currentlySelectedCell = std::nullopt;
	}
	else {
		currentlySelectedCell = cell;
	}
}

void Grid::handleNewValueEntry(int value)
{
	if (currentlySelectedCell) {
		gridCells[currentlySelectedCell->first][currentlySelectedCell->second].value = value;
		currentlySelectedCell = std::nullopt;
	}
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
	outsideBorderColor(gridStyle.getOutsideBorderColor()),
	lineThinColor(gridStyle.getLineThinColor()),
	lineThickColor(gridStyle.getLineThickColor()),
	gridTextStyle(gridStyle.getGridTextStyle())
{

	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		printf("Unable to load font\n");
		throw std::runtime_error("Unable to load font");
	}

}
