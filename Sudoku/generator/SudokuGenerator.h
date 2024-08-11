#pragma once
#include <vector>
#include <unordered_set>
#include "../solver/SudokuSolver.h"

using namespace std;

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const {
		auto hash1 = std::hash<T1>{}(pair.first);
		auto hash2 = std::hash<T2>{}(pair.second);
		return hash1 ^ hash2;
	}
};

class SudokuGenerator
{
private:

	SudokuSolver solver;

	pair<int, int> findNextNonEmptyCell(vector<vector<int>> grid, unordered_set<pair<int, int>, pair_hash>& triedCells);

public:

	vector<vector<int>> generate(int numberOfFiledCells);
};



