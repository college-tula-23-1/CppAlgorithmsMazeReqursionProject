#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>

#include "Console.h"

const char WALL{ 178 };
const char SPACE{ 32 };
const char WAY{ 249 };

typedef std::vector<std::vector<char>> Maze;

void MazeLoad(Maze& maze);

int main()
{
    Maze maze;

    Console console;
    console.Clear();

    MazeLoad(maze);
    
    
    console.KeyPressed();
}

void MazeLoad(Maze& maze)
{
    auto currentPath = std::filesystem::current_path();

    int pos{ 0 };
    std::ranges::for_each(
        std::filesystem::directory_iterator(currentPath),
        [&pos](auto& entry) {
            if (!entry.is_directory()
                && entry.path().extension() == ".maze")
                std::cout << ++pos << ": "
                << entry.path().filename().string() << "\n";
        }
    );

    std::cout << "\nInput number of maze: ";
    std::cin >> pos;

    std::string fileName;

    for (auto entry : std::filesystem::directory_iterator(currentPath))
    {
        if (entry.path().extension() == ".maze" && !(--pos))
        {
            fileName = entry.path().filename().string();
        }
    }

    std::cout << fileName << "\n";
}