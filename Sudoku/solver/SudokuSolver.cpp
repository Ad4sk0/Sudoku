#include "SudokuSolver.h"

optional<pair<int, int>> SudokuSolver::findEmptyCell(const vector<vector<int>>& grid) {
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			if (grid[row][col] == 0)
			{
				return pair<int, int>(row, col);
			}
		}
	}
	return nullopt;
}

bool SudokuSolver::isRowUnique(const vector<vector<int>>& grid, int row, int value) {
	for (int col = 0; col < grid.size(); col++)
	{
		if (grid[row][col] == value)
		{
			return false;
		}
	}
	return true;
}

bool SudokuSolver::isColUnique(const vector<vector<int>>& grid, int col, int value) {
	for (int row = 0; row < grid.size(); row++)
	{
		if (grid[row][col] == value)
		{
			return false;
		}
	}
	return true;
}

bool SudokuSolver::isSmallGridUnique(const vector<vector<int>>& grid, int testedRow, int testedCol, int value) {
	int startRow = testedRow - (testedRow % 3);
	int startCol = testedCol - (testedCol % 3);

	for (int row = startRow; row < startRow + 3; row++)
	{
		for (int col = startCol; col < startCol + 3; col++)
		{
			if (grid[row][col] == value)
			{
				return false;
			}
		}
	}
	return true;
}

bool SudokuSolver::isValidValue(const vector<vector<int>>& grid, pair<int, int> cell, int value) {
	return isRowUnique(grid, cell.first, value) && isColUnique(grid, cell.second, value) && isSmallGridUnique(grid, cell.first, cell.second, value);
}

vector<vector<vector<int>>> SudokuSolver::solveInternal(vector<vector<int>>& grid, int numberOfSolutionsToFind, bool solveRandomly) {
	vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<vector<vector<int>>> solutions;
	if (solveRandomly)
	{
		std::shuffle(numbers.begin(), numbers.end(), randomGenerator);
	}

	optional<pair<int, int>> emptyCellOptional = findEmptyCell(grid);
	if (!emptyCellOptional.has_value())
	{
		solutions.push_back(grid);
		return solutions;
	}
	pair<int, int> emptyCell = emptyCellOptional.value();

	int current = -1;
	while (!numbers.empty())
	{
		current = numbers.back();
		numbers.pop_back();

		if (!isValidValue(grid, emptyCell, current)) {
			current = -1;
			continue;
		}

		grid[emptyCell.first][emptyCell.second] = current;
		auto result = solveInternal(grid, numberOfSolutionsToFind, solveRandomly);
		if (result.size() > 0) {
			for (vector<vector<int>> currentSolution : result)
			{
				solutions.push_back(currentSolution);
			}
			grid[emptyCell.first][emptyCell.second] = 0;
			if (numberOfSolutionsToFind == solutions.size()) {
				break;
			}
		}
		else {
			grid[emptyCell.first][emptyCell.second] = 0;
			current = -1;
		}
	}

	if (current == -1)
	{
		return solutions;
	}

	return solutions;
}

bool SudokuSolver::isInvalid(vector<vector<int>> grid)
{
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			int value = grid[row][col];
			if (value == 0) {
				continue;
			}
			grid[row][col] = 0;
			if (!isValidValue(grid, pair(row, col), value))
			{
				return true;
			}
			grid[row][col] = value;
		}
	}
	return false;
}

void SudokuSolver::assertIsValid(const vector<vector<int>>& grid)
{
	if (isInvalid(grid)) {
		throw invalid_argument("Invalid grid provided");
	}
}

void SudokuSolver::assertHasNoMoreThanOneSolution(vector<vector<vector<int>>>& solutions)
{
	if (solutions.size() > 1) {
		throw runtime_error("Got more than single solution. Internal error");
	}
}


bool SudokuSolver::hasUniqueSolution(vector<vector<int>> grid) {
	assertIsValid(grid);
	vector<vector<vector<int>>> solutions = solveInternal(grid, 2, false);
	if (solutions.size() == 0 || solutions.size() > 1) {
		return false;
	}
	return true;
}

vector<vector<int>> SudokuSolver::solve(vector<vector<int>> grid) {
	assertIsValid(grid);
	vector<vector<vector<int>>> solutions = solveInternal(grid, 1, false);
	assertHasNoMoreThanOneSolution(solutions);
	if (solutions.size() == 0)
	{
		throw invalid_argument("Unable to solve");
	}
	return solutions[0];
}

vector<vector<vector<int>>> SudokuSolver::findAllSolutions(vector<vector<int>> grid, int maxSolutionsToFind)
{
	assertIsValid(grid);
	return solveInternal(grid, maxSolutionsToFind, false);
}

vector<vector<int>> SudokuSolver::fillGrid(vector<vector<int>> grid)
{
	assertIsValid(grid);
	vector<vector<vector<int>>> solutions = solveInternal(grid, 1, true);
	assertHasNoMoreThanOneSolution(solutions);
	if (solutions.size() == 0)
	{
		throw invalid_argument("Unable to fill grid");
	}
	return solutions[0];
}
