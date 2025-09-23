#pragma once
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <array>

#include "Console.h"

enum class MazeChar
{
	Wall = 178,
	Space = 32,
	Way = 249
};

typedef std::vector<std::vector<char>> Matrix;

struct Cell
{
	int row;
	int column;
};

class Maze
{
	Matrix maze;
	Cell start;
	Cell finish;

	void FindStart();
	void FindFinish();
	bool IsValidWay(int row, int column);
	bool Next(int row, int column);

	std::array<std::array<int, 2>, 4> diffs{ {
		{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }
	} };

public:
	void MazeLoad();
	void MazeConsole() const;
	void MazeCreateWay();
};

