#include "generator/SudokuGenerator.h"

pair<int, int> SudokuGenerator::findNextNonEmptyCell(vector<vector<int>> grid, unordered_set<pair<int, int>, pair_hash>& triedCells)
{
	vector<pair<int, int>> emptyCells;
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			if (grid[row][col] == 0)
			{
				continue;
			}

			if (triedCells.find(pair(row, col)) != triedCells.end())
			{
				continue;
			}
			emptyCells.emplace_back(row, col);
		}
	}
	if (emptyCells.empty()) {
		throw runtime_error("Unable to find empty cell");
	}

	std::uniform_int_distribution<> dis(0, emptyCells.size() - 1);
	int index = dis(randomGenerator);
	return emptyCells[index];
}

vector<vector<int>> SudokuGenerator::generate(int numberOfFiledCells) {
	if (numberOfFiledCells > 81) {
		throw std::invalid_argument("Number of cells cannot be greater than 81. Actual value: " + numberOfFiledCells);
	}
	int numberOfCellsToRemove = 81 - numberOfFiledCells;

	std::vector<std::vector<int>> initialGrid(9, std::vector<int>(9));
	vector<vector<int>> grid = solver.fillGrid(initialGrid);

	bool removeCells = true;
	int numberOfRemovedCells = 0;
	unordered_set<pair<int, int>, pair_hash> triedCells;
	while (numberOfRemovedCells < numberOfCellsToRemove)
	{
		int numberOfNonEmptyCells = 81 - numberOfRemovedCells;
		if (triedCells.size() >= numberOfNonEmptyCells) {
			throw logic_error("Unable to generate grid. Tried all cells.");
		}
		pair<int, int> selectedCell = findNextNonEmptyCell(grid, triedCells);
		int currentValue = grid[selectedCell.first][selectedCell.second];
		grid[selectedCell.first][selectedCell.second] = 0;

		if (solver.hasUniqueSolution(grid)) {
			numberOfRemovedCells++;
			triedCells.clear();
		}

		else {
			grid[selectedCell.first][selectedCell.second] = currentValue;
			triedCells.insert(selectedCell);
		}
	}
	return grid;
}
