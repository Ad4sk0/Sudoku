#include "validator/SudokuValidator.h"

inline bool SudokuValidator::isValidSize(const vector<vector<int>>& grid)
{
	if (grid.size() != GRID_SIZE)
	{
		return false;
	}

	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (grid[i].size() != GRID_SIZE)
		{
			return false;
		}
	}
	return true;
}

inline bool SudokuValidator::isValidValue(int cellValue)
{
	return cellValue >= 1 && cellValue <= 9;
}

inline bool SudokuValidator::isValidInRow(const vector<vector<int>>& grid, int testedRow, int testedCol, int cellValue) {
	for (int col = 0; col < grid.size(); col++)
	{
		if (col == testedCol) {
			continue;
		}
		if (grid[testedRow][col] == cellValue)
		{
			return false;
		}
	}
	return true;
}

inline bool SudokuValidator::isValidInCell(const vector<vector<int>>& grid, int testedRow, int testedCol, int cellValue) {
	for (int row = 0; row < grid.size(); row++)
	{
		if (row == testedRow) {
			continue;
		}
		if (grid[row][testedCol] == cellValue)
		{
			return false;
		}
	}
	return true;
}

inline bool SudokuValidator::isValidInSmallGrid(const vector<vector<int>>& grid, int testedRow, int testedCol, int cellValue) {
	int startRow = testedRow - (testedRow % 3);
	int startCol = testedCol - (testedCol % 3);

	for (int row = startRow; row < startRow + 3; row++)
	{
		for (int col = startCol; col < startCol + 3; col++)
		{
			if (row == testedRow && col == testedCol)
			{
				continue;
			}

			if (grid[row][col] == cellValue)
			{
				return false;
			}
		}
	}
	return true;
}

inline bool SudokuValidator::isValidCell(const vector<vector<int>>& grid, int row, int col) {
	int cellValue = grid[row][col];
	return isValidValue(cellValue) && isValidInRow(grid, row, col, cellValue) && isValidInCell(grid, row, col, cellValue) && isValidInSmallGrid(grid, row, col, cellValue);
}

ValidationResult SudokuValidator::isGridValid(const vector<vector<int>>& grid)
{
	if (!isValidSize(grid))
	{
		return ValidationResult(false, pair<int, int>(-1, -1));
	}

	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			if (!isValidCell(grid, row, col)) {
				return ValidationResult(false, pair<int, int>(row, col));
			}
		}
	}
	return ValidationResult(true, pair<int, int>(-1, -1));
}
