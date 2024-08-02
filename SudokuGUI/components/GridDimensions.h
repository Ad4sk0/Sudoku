#pragma once
class GridDimensions
{
public:
    GridDimensions(int gridSize, float cellSize, float marginX, float marginY, float lineThicknessSmall, float lineThicknessBig);

    int getGridSize() const;
    float getCellSize() const;
    float getMarginX() const;
    float getMarginY() const;
    float getLineThicknessSmall() const;
    float getLineThicknessBig() const;
    float getGridHeight() const;
    float getGridWidth() const;

private:
    int gridSize;
    float cellSize;
    float marginX;
    float marginY;
    float lineThicknessSmall;
    float lineThicknessBig;

    float getGridPixelSize() const;
};


