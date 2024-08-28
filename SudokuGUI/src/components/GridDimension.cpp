#include "components/GridDimensions.h"


GridDimensions::GridDimensions(int gridSize, float cellSize, float marginX, float marginY, float lineThicknessSmall, float lineThicknessBig)
	: gridSize(gridSize), cellSize(cellSize), marginX(marginX), marginY(marginY), lineThicknessSmall(lineThicknessSmall), lineThicknessBig(lineThicknessBig)
{
}

float GridDimensions::getGridPixelSize() const {
	return gridSize * cellSize + 4 * lineThicknessBig + 6 * lineThicknessSmall;
}

int GridDimensions::getGridSize() const {
	return gridSize;
}

float GridDimensions::getCellSize() const {
	return cellSize;
}

float GridDimensions::getMarginX() const {
	return marginX;
}

float GridDimensions::getMarginY() const {
	return marginY;
}

float GridDimensions::getLineThicknessSmall() const {
	return lineThicknessSmall;
}

float GridDimensions::getLineThicknessBig() const {
	return lineThicknessBig;
}

float GridDimensions:: getGridHeight() const {
	return getGridPixelSize();
}

float GridDimensions::getGridWidth() const {
	return getGridPixelSize();
}