#include "pch.h"
#include "CppUnitTest.h"
#include "sudoku/solver/SudokuSolver.h"
#include "sudoku/validator/SudokuValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SudokuSolverTests
{
	SudokuSolver solver;

	TEST_CLASS(SolveCorrectly)
	{
	public:
		TEST_METHOD(shouldSolveCorrectlyGridWith20EmptyField)
		{
			vector<vector<int>> grid = {
				{4, 6, 1, 0, 9, 5, 0, 0, 3},
				{9, 3, 2, 0, 4, 0, 7, 5, 1},
				{8, 5, 7, 3, 0, 2, 9, 6, 4},
				{0, 0, 4, 9, 5, 7, 0, 2, 6},
				{6, 0, 9, 1, 2, 0, 5, 3, 7},
				{0, 7, 5, 8, 3, 6, 1, 4, 0},
				{5, 2, 3, 0, 0, 9, 0, 1, 0},
				{1, 9, 8, 5, 6, 0, 4, 7, 2},
				{0, 4, 6, 2, 8, 0, 3, 9, 5}
			};

			vector<vector<int>> solution = solver.solve(grid);
			Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);
		}

		TEST_METHOD(shouldSolveCorrectlyGridWith40EmptyField)
		{
			vector<vector<int>> grid = {
				{0, 5, 8, 0, 0, 4, 0, 0, 2},
				{0, 0, 0, 0, 8, 0, 4, 0, 1},
				{1, 4, 9, 5, 2, 6, 3, 7, 0},
				{0, 0, 0, 2, 0, 9, 0, 0, 0},
				{0, 0, 0, 8, 4, 0, 0, 3, 6},
				{9, 8, 0, 0, 0, 0, 1, 0, 0},
				{6, 0, 2, 0, 5, 1, 0, 4, 0},
				{8, 0, 4, 0, 6, 0, 0, 1, 9},
				{0, 1, 5, 4, 9, 0, 2, 6, 3}
			};

			vector<vector<int>> solution = solver.solve(grid);
			Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);
		}

		TEST_METHOD(shouldSolveCorrectlyGridWith55EmptyField)
		{
			vector<vector<int>> grid = {
				{0, 0, 4, 0, 0, 2, 0, 0, 7},
				{9, 0, 0, 0, 4, 0, 6, 0, 2},
				{5, 0, 2, 0, 0, 7, 1, 0, 8},
				{0, 0, 0, 8, 0, 0, 0, 0, 0},
				{0, 0, 6, 0, 7, 0, 0, 5, 4},
				{0, 4, 0, 0, 0, 0, 8, 0, 0},
				{6, 0, 9, 0, 0, 0, 0, 0, 0},
				{2, 0, 1, 3, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 5, 0, 0, 6, 0}
			};

			vector<vector<int>> solution = solver.solve(grid);
			Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);
		}
	};

	TEST_CLASS(FindMultipleSolutions)
	{
	public:
		TEST_METHOD(shouldFindTwoSolutions)
		{
			std::vector<std::vector<int>> grid = {
				{9, 8, 7,   6, 5, 4,   3, 0, 0},
				{6, 5, 4,   3, 2, 1,   9, 8, 7},
				{3, 2, 1,   9, 8, 7,   6, 5, 4},

				{8, 9, 6,   7, 4, 5,   0, 0, 3},
				{7, 4, 5,   2, 1, 3,   8, 9, 6},
				{2, 1, 3,   8, 9, 6,   7, 4, 5},

				{5, 7, 9,   4, 6, 8,   0, 3, 0},
				{4, 6, 8,   1, 3, 2,   5, 7, 9},
				{1, 3, 2,   5, 7, 9,   4, 6, 8},
			};

			vector<vector<vector<int>>> solutions = solver.findAllSolutions(grid, INT_MAX);
			Assert::AreEqual(static_cast<size_t>(2), solutions.size());

			for (std::vector<std::vector<int>> solution : solutions)
			{
				Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);
			}
		}

		TEST_METHOD(shouldFindTwelveSolutions)
		{
			std::vector<std::vector<int>> grid = {
				{9, 8, 7,   6, 5, 4,   0, 0, 0},
				{6, 5, 4,   3, 2, 1,   9, 8, 7},
				{3, 2, 1,   9, 8, 7,   6, 5, 4},

				{8, 9, 6,   7, 4, 5,   0, 0, 0},
				{7, 4, 5,   2, 1, 3,   8, 9, 6},
				{2, 1, 3,   8, 9, 6,   7, 4, 5},

				{5, 7, 9,   4, 6, 8,   0, 0, 0},
				{4, 6, 8,   1, 3, 2,   5, 7, 9},
				{1, 3, 2,   5, 7, 9,   4, 6, 8},
			};

			vector<vector<vector<int>>> solutions = solver.findAllSolutions(grid, INT_MAX);
			Assert::AreEqual(static_cast<size_t>(12), solutions.size());

			for (std::vector<std::vector<int>> solution : solutions)
			{
				Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);
			}
		}
	};

	TEST_CLASS(HandleUnsolvableGridCorrectly)
	{
	public:

		TEST_METHOD(shouldDetectIfThereIsNoSolution)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 5, 4, 3, 2, 0},
				{6, 5, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 5},
				{5, 7, 9, 4, 6, 8, 0, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{0, 3, 2, 5, 7, 9, 4, 6, 0}
			};

			vector<vector<int>> solution = solver.solve(grid);
			Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);

			grid[8][8] = 1;

			Assert::ExpectException<std::invalid_argument>([&grid]()
				{
					solver.solve(grid);
				});
		}

		TEST_METHOD(shouldDetectIfTheGridIsInvalid)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 5, 4, 3, 2, 1},
				{6, 5, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 5},
				{5, 7, 9, 4, 6, 8, 1, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{1, 3, 2, 5, 7, 9, 4, 6, 0}
			};

			vector<vector<int>> solution = solver.solve(grid);
			Assert::IsTrue(SudokuValidator::isGridValid(solution).isValid);

			grid[0][0] = 1;

			Assert::ExpectException<std::invalid_argument>([&grid]()
				{
					solver.solve(grid);
				});
		}
	};

	TEST_CLASS(General)
	{
	public:
		TEST_METHOD(shouldNotModifyOriginalGrid)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 5, 4, 3, 2, 1},
				{6, 5, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 5},
				{5, 7, 9, 4, 6, 8, 1, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{1, 3, 2, 5, 7, 9, 4, 6, 0}
			};

			vector<vector<int>> solution = solver.solve(grid);
			Assert::AreEqual(8, solution[8][8]);
			Assert::AreEqual(0, grid[8][8]);
		}
	};
}