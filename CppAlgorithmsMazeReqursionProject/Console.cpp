#include "Console.h"

Console::Console() :
	handleStdOutput{ GetStdHandle(STD_OUTPUT_HANDLE) }
{}

void Console::Clear()
{
	system("cls");
}

void Console::SetCursor(int row, int column)
{
	COORD position;
	position.X = column;
	position.Y = row;
	SetConsoleCursorPosition(handleStdOutput, position);
}

void Console::Write(std::string str)
{
	unsigned long count;
	WriteConsoleA(handleStdOutput, str.c_str(), str.size(), &count, nullptr);
}

int Console::GetChar()
{
	return _getch();
}

int Console::KeyPressed()
{
	return _kbhit();
}




