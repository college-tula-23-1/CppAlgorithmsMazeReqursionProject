#pragma once
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

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

public:
	void MazeLoad();
	void MazeConsole() const;
	
};

