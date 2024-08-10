#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <optional>


using namespace std;

class SudokuSolver
{
private:
	std::mt19937 randomGenerator;

	optional<pair<int, int>> findEmptyCell(const vector<vector<int>>& grid);

	bool isRowUnique(const vector<vector<int>>& grid, int row, int value);

	bool isColUnique(const vector<vector<int>>& grid, int col, int value);

	bool isSmallGridUnique(const vector<vector<int>>& grid, int testedRow, int testedCol, int value);

	bool isValidValue(const vector<vector<int>>& grid, pair<int,int> cell, int value);

	vector<vector<vector<int>>> solveInternal(vector<vector<int>>& grid, int numberOfSolutionsToFind, bool solveRandomly);

	bool isInvalid(vector<vector<int>> grid);

	void assertIsValid(const vector<vector<int>>& grid);

	void assertHasNoMoreThanOneSolution(vector<vector<vector<int>>>& solutions);

public:

	SudokuSolver() : randomGenerator(std::random_device{}()) {
	}

	bool hasUniqueSolution(vector<vector<int>> grid);

	vector<vector<int>> solve(vector<vector<int>> grid);

	vector<vector<vector<int>>> findAllSolutions(vector<vector<int>> grid, int maxSolutionsToFind);

	vector<vector<int>> fillGrid(vector<vector<int>> grid);
};