#pragma once
#include <vector>

using namespace std;

struct ValidationResult
{
	bool isValid;
	pair<int, int> notValidCell;

	ValidationResult(bool isValid, const pair<int, int>& notValidCell)
		: isValid(isValid), notValidCell(notValidCell)
	{
	}
};

class SudokuValidator
{
private:

	static const int GRID_SIZE = 9;

	static bool isValidSize(const vector<vector<int>>& grid);

	static bool isValidValue(int cellValue);

	static bool isValidInRow(const vector<vector<int>>& grid, int testedRow, int testedCol, int cellValue);

	static bool isValidInCell(const vector<vector<int>>& grid, int testedRow, int testedCol, int cellValue);

	static bool isValidInSmallGrid(const vector<vector<int>>& grid, int testedRow, int testedCol, int cellValue);

public:

	static bool isValidCell(const vector<vector<int>>& grid, int row, int col);

	static ValidationResult isGridValid(const vector<vector<int>>& grid);
};

