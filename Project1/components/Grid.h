#pragma once
#include <SFML/Graphics.hpp>
#include "GridDimensions.h"
#include "Cell.h"
#include <optional>


class Grid
{
private:
	sf::RenderWindow& window;
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
	std::vector<std::vector<sf::RectangleShape>> draw_grid_cells(std::vector<std::vector<Cell>>& grid);

public:
	Grid(sf::RenderWindow& window, const GridDimensions& gridDimensions);

	std::vector<std::vector<sf::RectangleShape>> draw(std::vector<std::vector<Cell>>& grid);
	void handleCellClick(std::pair<int, int> cell);
};

