#include <iostream>

#include "Maze.h"

int main()
{
    Maze maze;
    maze.MazeLoad();
    maze.MazeConsole();
    maze.MazeCreateWay();
    
    std::cout << "\n";
    maze.MazeConsole();
}

