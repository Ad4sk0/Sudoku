#include "pch.h"
#include "CppUnitTest.h"
#include "../Sudoku/generator/SudokuGenerator.h"
#include "../Sudoku/solver/SudokuSolver.h"
#include "../Sudoku/validator/SudokuValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SudokuGeneratorTests
{
	SudokuGenerator generator;
	SudokuSolver solver;

	static int countEmptyCells(vector<vector<int>>& grid)
	{
		int count = 0;
		for (const auto& row : grid) {
			count += std::count(row.begin(), row.end(), 0);
		}
		return count;
	}

	TEST_CLASS(ShouldGenerateCorrectGridWithUniqueSolution)
	{
	public:
		TEST_METHOD(shouldGenerateCorrectGridWithUniqueSolutionWith70FilledFields)
		{
			vector<vector<int>> grid = generator.generate(70);

			Assert::AreEqual(11, countEmptyCells(grid));

			vector<vector<vector<int>>> solutions = solver.findAllSolutions(grid, 2);

			Assert::AreEqual(static_cast<size_t>(1), solutions.size());
			Assert::IsTrue(SudokuValidator::isGridValid(solutions[0]).isValid);
		}

		TEST_METHOD(shouldGenerateCorrectGridWithUniqueSolutionWith50FilledFields)
		{
			vector<vector<int>> grid = generator.generate(50);

			Assert::AreEqual(31, countEmptyCells(grid));

			vector<vector<vector<int>>> solutions = solver.findAllSolutions(grid, 2);

			Assert::AreEqual(static_cast<size_t>(1), solutions.size());
			Assert::IsTrue(SudokuValidator::isGridValid(solutions[0]).isValid);
		}

		TEST_METHOD(shouldGenerateCorrectGridWithUniqueSolutionWith30FilledFields)
		{
			vector<vector<int>> grid = generator.generate(30);

			Assert::AreEqual(51, countEmptyCells(grid));

			vector<vector<vector<int>>> solutions = solver.findAllSolutions(grid, 2);

			Assert::AreEqual(static_cast<size_t>(1), solutions.size());
			Assert::IsTrue(SudokuValidator::isGridValid(solutions[0]).isValid);
		}

		TEST_METHOD(shouldGenerateRandomGrids)
		{
			vector<vector<int>> grid1 = generator.generate(55);
			vector<vector<int>> grid2 = generator.generate(55);

			bool areEqual = grid1 == grid2;
			Assert::IsFalse(areEqual);
		}
	};
}