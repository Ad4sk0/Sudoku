#pragma once
class Cell
{
public:
	int value;
	const bool isConstant;

	Cell(int value, bool isConstant) : value(value), isConstant(isConstant) {}
};

