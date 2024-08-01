#pragma once
#include <SFML/Graphics.hpp>
#include "GridDimensions.h"
#include "Cell.h"
#include <optional>


class Grid
{
private:
	std::vector<std::vector<Cell>> gridCells;
	sf::RenderWindow& window;
	sf::Font font;
	int gridSize;
	int smallGridSize;
	float cellSize;
	float marginX;
	float marginY;
	float lineThicknessSmall;
	float lineThicknessBig;
	float gridHeight;
	float gridWidth;

	std::optional<std::pair<int, int>> currentlySelectedCell;

	void draw_grid_lines();
	std::vector<std::vector<sf::RectangleShape>> draw_grid_cells();

	void drawValueIfDefined(sf::RectangleShape& rectangle, int value);

public:
	Grid(sf::RenderWindow& window, const GridDimensions& gridDimensions, std::vector<std::vector<Cell>> initialGridCels);

	std::vector<std::vector<sf::RectangleShape>> draw();
	void handleCellClick(std::pair<int, int> cell);
	void handleNewValueEntry(int value);
};

