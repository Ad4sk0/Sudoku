#pragma once
#include <SFML/Graphics.hpp>
#include "GridDimensions.h"
#include "GridStyle.h"
#include "Cell.h"
#include <optional>
#include "DirectionEnum.h"


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

	const sf::Color cellColor;
	const sf::Color cellSelectedColor;
	const sf::Color gridTextColor;
	const sf::Color gridEditableTextColor;
	const sf::Color outsideBorderColor;
	const sf::Color lineThinColor;
	const sf::Color lineThickColor;
	const sf::Text::Style gridTextStyle;
	const sf::Text::Style gridEditableTextStyle;

	std::optional<std::pair<int, int>> currentlySelectedCell;
	std::optional<std::pair<int, int>> lastCellSelection;

	void draw_grid_lines();
	std::vector<std::vector<sf::RectangleShape>> draw_grid_cells();

	void drawValueIfDefined(sf::RectangleShape& rectangle, int value, bool isConstant);

	std::optional<std::pair<int, int>> findEmptyCell(DirectionEnum direction);
	void selectCell(std::pair<int, int>& cell);

public:
	Grid(sf::RenderWindow& window, const GridDimensions& gridDimensions, const GridStyle& gridStyle, std::vector<std::vector<Cell>> initialGridCels);

	std::vector<std::vector<sf::RectangleShape>> draw();
	void handleCellClick(std::pair<int, int> cell);
	void handleNewValueEntry(int value);
	void handleNewKeyEntry(sf::Event::KeyEvent keyEvent);
	std::vector<std::vector<int>> getGridValues();
	void reset(std::vector<std::vector<Cell>> newGridCels);
};

