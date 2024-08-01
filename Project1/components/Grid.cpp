#include "Grid.h"

void Grid::draw_grid_lines()
{
	float x = marginX;
	float y = marginY;
	for (int i = 0; i < gridSize + 1; i++)
	{
		float lineThickness = lineThicknessSmall;
		if (i % smallGridSize == 0) {
			lineThickness = lineThicknessBig;
		}

		sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, gridHeight));
		verticalLine.setPosition(x, marginY);
		window.draw(verticalLine);

		sf::RectangleShape horizontalLine(sf::Vector2f(gridWidth, lineThickness));
		horizontalLine.setPosition(marginX, y);
		window.draw(horizontalLine);

		x += cellSize + lineThickness;
		y += cellSize + lineThickness;
	}
}

std::vector<std::vector<sf::RectangleShape>> Grid::draw_grid_cells(std::vector<std::vector<Cell>>& gridCells)
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
			rectangle.setFillColor(sf::Color::Red);

			if (currentlySelectedCell && currentlySelectedCell->first == row && currentlySelectedCell->second == col) {
				rectangle.setFillColor(sf::Color::Yellow);
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
	if (value < 0) {
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(value));
	text.setCharacterSize(static_cast<int>(cellSize / 2.0f));
	text.setFillColor(sf::Color::Black);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f, rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
	window.draw(text);
}

std::vector<std::vector<sf::RectangleShape>> Grid::draw(std::vector<std::vector<Cell>>& gridCells)
{
	draw_grid_lines();
	return draw_grid_cells(gridCells);
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

Grid::Grid(sf::RenderWindow& window, const GridDimensions& gridDimensions)
	: window(window),
	gridSize(gridDimensions.getGridSize()),
	smallGridSize(gridSize / 3),
	cellSize(gridDimensions.getCellSize()),
	marginX(gridDimensions.getMarginX()),
	marginY(gridDimensions.getMarginY()),
	lineThicknessSmall(gridDimensions.getLineThicknessSmall()),
	lineThicknessBig(gridDimensions.getLineThicknessBig()),
	gridHeight(gridDimensions.getGridHeight()),
	gridWidth(gridDimensions.getGridWidth())
{

	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		printf("Unable to load font\n");
		throw std::runtime_error("Unable to load font");
	}

}
