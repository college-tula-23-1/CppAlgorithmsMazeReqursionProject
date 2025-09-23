#include "Maze.h"

void Maze::FindStart()
{
    int column{};
    for (auto item : maze[0])
    {
        if (item == (char)MazeChar::Space)
        {
            start.row = 0;
            start.column = column;
            return;
        }
        column++;
    }

    for(int row { 1 }; row < maze.size(); row++)
        if (maze[row][0] == (char)MazeChar::Space)
        {
            start.row = row;
            start.column = 0;
            return;
        }
}

void Maze::FindFinish()
{
    int bottom{ (int)maze.size() - 1 };

    int column{};
    for (auto item : maze[bottom])
    {
        if (item == (char)MazeChar::Space)
        {
            finish.row = bottom;
            finish.column = column;
            return;
        }
        column++;
    }

    int right{ (int)maze[0].size() - 1 };

    for (int row{}; row < bottom; row++)
        if (maze[row][right] == (char)MazeChar::Space)
        {
            finish.row = row;
            finish.column = right;
            return;
        }
}

bool Maze::IsValidWay(int row, int column)
{
    int height = maze.size();
    int width = maze[0].size();

    if (row < 0 || row >= height || column < 0 || column >= width)
        return false;
    if (maze[row][column] == (char)MazeChar::Wall)
        return false;
    if (maze[row][column] == (char)MazeChar::Way)
        return false;

    return true;
}

bool Maze::Next(int row, int column)
{
    if (row == finish.row && column == finish.column)
    {
        maze[row][column] = (char)MazeChar::Way;
        return true;
    }
        

    for (auto diff : diffs)
    {
        if (IsValidWay(row + diff[0], column + diff[1]))
        {
            maze[row][column] = (char)MazeChar::Way;
            MazeConsole();

            if (Next(row + diff[0], column + diff[1]))
                return true;

            maze[row][column] = (char)MazeChar::Space;
            MazeConsole();
        }
    }
    return false;
}

void Maze::MazeLoad()
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
        if (entry.path().extension() == ".maze" && !(--pos))
            fileName = entry.path().filename().string();

    std::cout << fileName << "\n";

    std::ifstream fileMaze(fileName, std::ios::in);
    std::string lineMaze;

    while (std::getline(fileMaze, lineMaze))
    {
        std::vector<char> line;
        for (auto symbol : lineMaze)
            switch (symbol)
            {
            case '#':
                line.push_back((char)MazeChar::Wall); break;
            case ' ':
                line.push_back((char)MazeChar::Space); break;
            }
        maze.push_back(line);
    }

    fileMaze.close();
    FindStart();
    FindFinish();
}

void Maze::MazeConsole() const
{
    for (auto line : maze)
    {
        for (auto item : line)
            std::cout << item;
        std::cout << "\n";
    }
    std::cout << "\n";
    //std::cout << "start: [" << start.row << "," << start.column << "]\n";
    //std::cout << "finish: [" << finish.row << "," << finish.column << "]\n";
}

void Maze::MazeCreateWay()
{
    Next(start.row, start.column);
}
