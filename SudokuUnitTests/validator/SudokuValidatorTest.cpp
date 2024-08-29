#include "pch.h"
#include "CppUnitTest.h"
#include "sudoku/validator/SudokuValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SudokuValidatorTests
{
	TEST_CLASS(GridIsValid)
	{
	public:
		TEST_METHOD(shouldDetectValidNotRandomGrid)
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
				{1, 3, 2, 5, 7, 9, 4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsTrue(result.isValid);
		}

		TEST_METHOD(shouldDetectValidRandomGrid)
		{
			vector<vector<int>> grid = {
				{6, 8, 2, 7, 3, 5, 4, 1, 9},
				{4, 9, 3, 6, 8, 1, 5, 7, 2},
				{1, 7, 5, 4, 2, 9, 6, 3, 8},
				{2, 5, 6, 9, 4, 7, 3, 8, 1},
				{3, 1, 8, 5, 6, 2, 7, 9, 4},
				{7, 4, 9, 3, 1, 8, 2, 5, 6},
				{5, 6, 7, 1, 9, 4, 8, 2, 3},
				{9, 2, 4, 8, 7, 3, 1, 6, 5},
				{8, 3, 1, 2, 5, 6, 9, 4, 7}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsTrue(result.isValid);
		}
	};

	TEST_CLASS(GridIsNotValidInRow)
	{
	public:
		TEST_METHOD(shouldDetectInvalidRowInNotRandomGrid)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 5, 4, 3, 2, 7},
				{6, 5, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 5},
				{5, 7, 9, 4, 6, 8, 1, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{1, 3, 2, 5, 7, 9, 4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(0, result.notValidCell.first);
			Assert::AreEqual(2, result.notValidCell.second);
		}

		TEST_METHOD(shouldDetectInvalidRowInRandomGrid)
		{
			vector<vector<int>> grid = {
				{5, 3, 4, 6, 7, 8, 9, 1, 1},
				{6, 7, 2, 1, 9, 5, 3, 4, 8},
				{1, 9, 8, 3, 4, 2, 5, 6, 7},
				{8, 5, 9, 7, 6, 1, 4, 2, 3},
				{4, 2, 6, 8, 5, 3, 7, 9, 1},
				{7, 1, 3, 9, 2, 4, 8, 5, 6},
				{9, 6, 1, 5, 3, 7, 2, 8, 4},
				{2, 8, 7, 4, 1, 9, 6, 3, 5},
				{3, 4, 5, 2, 8, 6, 1, 7, 9}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(0, result.notValidCell.first);
			Assert::AreEqual(7, result.notValidCell.second);
		}
	};

	TEST_CLASS(GridIsNotValidInColumn)
	{
	public:
		TEST_METHOD(notRandomGrid)
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
				{1, 3, 2, 5, 4, 9, 4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(3, result.notValidCell.first);
			Assert::AreEqual(4, result.notValidCell.second);
		}

		TEST_METHOD(shouldDetectInvalidColumnInRandomGrid)
		{
			vector<vector<int>> grid = {
				{5, 3, 4, 6, 7, 8, 9, 1, 2},
				{6, 7, 2, 1, 9, 5, 3, 4, 8},
				{1, 9, 8, 3, 4, 2, 5, 6, 7},
				{8, 5, 9, 7, 6, 1, 4, 2, 3},
				{4, 2, 6, 8, 5, 3, 7, 9, 1},
				{7, 1, 3, 9, 2, 4, 8, 5, 6},
				{9, 6, 1, 5, 3, 7, 2, 8, 4},
				{2, 8, 7, 4, 1, 9, 6, 3, 5},
				{3, 4, 5, 2, 8, 6, 1, 7, 6}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(5, result.notValidCell.first);
			Assert::AreEqual(8, result.notValidCell.second);
		}
	};

	TEST_CLASS(GridIsNotValidInSmallGrid)
	{
	public:
		TEST_METHOD(shouldDetectInvalidSmallGridInNotRandomGrid)
		{
			vector<vector<int>> grid = {
				{9, 8, 7,   6, 5, 4,   3, 2, 1},
				{6, 5, 4,   3, 2, 1,   9, 8, 7},
				{3, 2, 1,   9, 8, 7,   6, 5, 4},

				{8, 9, 6,   7, 4, 5,   2, 1, 3},
				{7, 4, 5,   2, 1, 3,   8, 9, 6},
				{2, 1, 3,   8, 9, 6,   7, 4, 9},

				{5, 7, 9,   4, 6, 8,   1, 3, 2},
				{4, 6, 8,   1, 3, 2,   5, 7, 9},
				{1, 3, 2,   5, 7, 9,   4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(4, result.notValidCell.first);
			Assert::AreEqual(7, result.notValidCell.second);
		}

		TEST_METHOD(shouldDetectInvalidSmallGridInRandomGrid)
		{
			vector<vector<int>> grid = {
				{1, 6, 2,   4, 8, 3,   9, 7, 5},
				{3, 7, 4,   6, 9, 5,   2, 1, 8},
				{8, 9, 5,   7, 2, 6,   1, 3, 4},

				{9, 8, 6,   3, 4, 7,   5, 2, 1},
				{4, 5, 1,   2, 6, 8,   3, 9, 7},
				{7, 2, 3,   9, 5, 1,   4, 8, 6},

				{5, 1, 9,   8, 7, 2,   6, 4, 3},
				{6, 4, 7,   5, 3, 9,   8, 1, 2},
				{2, 3, 8,   6, 1, 4,   7, 5, 9}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(1, result.notValidCell.first);
			Assert::AreEqual(3, result.notValidCell.second);
		}
	};


	TEST_CLASS(GridHasInvalidCharacters)
	{
	public:
		TEST_METHOD(shouldDetect0Value)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 0, 4, 3, 2, 1},
				{6, 5, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 9},
				{5, 7, 9, 4, 6, 8, 1, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{1, 3, 2, 5, 7, 9, 4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(0, result.notValidCell.first);
			Assert::AreEqual(4, result.notValidCell.second);
		}

		TEST_METHOD(shouldDetectToBigValue)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 5, 4, 3, 2, 1},
				{6, 10, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 9},
				{5, 7, 9, 4, 6, 8, 1, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{1, 3, 2, 5, 7, 9, 4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(1, result.notValidCell.first);
			Assert::AreEqual(1, result.notValidCell.second);
		}

		TEST_METHOD(shouldDetectNegativeValue)
		{
			vector<vector<int>> grid = {
				{9, 8, 7, 6, 5, 4, 3, 2, -1},
				{6, 10, 4, 3, 2, 1, 9, 8, 7},
				{3, 2, 1, 9, 8, 7, 6, 5, 4},
				{8, 9, 6, 7, 4, 5, 2, 1, 3},
				{7, 4, 5, 2, 1, 3, 8, 9, 6},
				{2, 1, 3, 8, 9, 6, 7, 4, 9},
				{5, 7, 9, 4, 6, 8, 1, 3, 2},
				{4, 6, 8, 1, 3, 2, 5, 7, 9},
				{1, 3, 2, 5, 7, 9, 4, 6, 8}
			};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(0, result.notValidCell.first);
			Assert::AreEqual(8, result.notValidCell.second);
		}
	};

	TEST_CLASS(GridHasInvalidSize)
	{
	public:
		TEST_METHOD(shouldDetectEmptyGrid)
		{
			vector<vector<int>> grid = {};

			ValidationResult result = SudokuValidator::isGridValid(grid);
			Assert::IsFalse(result.isValid);
			Assert::AreEqual(-1, result.notValidCell.first);
			Assert::AreEqual(-1, result.notValidCell.second);
		}

		TEST_METHOD(shouldDetectInvalidRowsSize)
		{
			{
				vector<vector<int>> grid = {
								{9, 8, 7, 6, 0, 4, 3, 2, 1},
								{6, 5, 4, 3, 2, 1, 9, 8, 7},
								{3, 2, 1, 9, 8, 7, 6, 5, 4},
								{8, 9, 6, 7, 4, 5, 2, 1, 3},
								{7, 4, 5, 2, 1, 3, 8, 9, 6},
								{2, 1, 3, 8, 9, 6, 7, 4, 9},
								{5, 7, 9, 4, 6, 8, 1, 3, 2},
								{4, 6, 8, 1, 3, 2, 5, 7, 9},
								{1, 3, 2, 5, 7, 9, 4, 6, 8},
								{1, 3, 2, 5, 7, 9, 4, 6, 8}
				};

				ValidationResult result = SudokuValidator::isGridValid(grid);
				Assert::IsFalse(result.isValid);
				Assert::AreEqual(-1, result.notValidCell.first);
				Assert::AreEqual(-1, result.notValidCell.second);
			}

			{
				vector<vector<int>> grid = {
								{9, 8, 7, 6, 0, 4, 3, 2, 1},
								{6, 5, 4, 3, 2, 1, 9, 8, 7},
								{3, 2, 1, 9, 8, 7, 6, 5, 4},
								{8, 9, 6, 7, 4, 5, 2, 1, 3},
								{7, 4, 5, 2, 1, 3, 8, 9, 6},
								{2, 1, 3, 8, 9, 6, 7, 4, 9},
								{5, 7, 9, 4, 6, 8, 1, 3, 2},
								{4, 6, 8, 1, 3, 2, 5, 7, 9},
				};

				ValidationResult result = SudokuValidator::isGridValid(grid);
				Assert::IsFalse(result.isValid);
				Assert::AreEqual(-1, result.notValidCell.first);
				Assert::AreEqual(-1, result.notValidCell.second);
			}
		}

		TEST_METHOD(shouldDetectInvalidColumnsSize)
		{
			{

				vector<vector<int>> grid = {
					{9, 8, 7, 6, 0, 4, 3, 2, 1},
					{6, 5, 4, 3, 2, 1, 9, 8, 7},
					{3, 2, 1, 9, 8, 7, 6, 5, 4},
					{8, 9, 6, 7, 4, 5, 2, 1, 3},
					{7, 4, 5, 2, 1, 3, 8, 9},
					{2, 1, 3, 8, 9, 6, 7, 4, 9},
					{5, 7, 9, 4, 6, 8, 1, 3, 2},
					{4, 6, 8, 1, 3, 2, 5, 7, 9},
					{1, 3, 2, 5, 7, 9, 4, 6, 8}
				};

				ValidationResult result = SudokuValidator::isGridValid(grid);
				Assert::IsFalse(result.isValid);
				Assert::AreEqual(-1, result.notValidCell.first);
				Assert::AreEqual(-1, result.notValidCell.second);
			}

			{

				vector<vector<int>> grid = {
				   {9, 8, 7, 6, 0, 4, 3, 2, 1},
				   {6, 5, 4, 3, 2, 1, 9, 8, 7},
				   {3, 2, 1, 9, 8, 7, 6, 5, 4},
				   {8, 9, 6, 7, 4, 5, 2, 1, 3},
				   {7, 4, 5, 2, 1, 3, 8, 9, 6},
				   {2, 1, 3, 8, 9, 6, 7, 4, 9},
				   {5, 7, 9, 4, 6, 8, 1, 3, 2},
				   {4, 6, 8, 1, 3, 2, 5, 7, 9},
				   {1, 3, 2, 5, 7, 9, 4, 6, 8, 1}
				};

				ValidationResult result = SudokuValidator::isGridValid(grid);
				Assert::IsFalse(result.isValid);
				Assert::AreEqual(-1, result.notValidCell.first);
				Assert::AreEqual(-1, result.notValidCell.second);
			}
		}
	};













}
