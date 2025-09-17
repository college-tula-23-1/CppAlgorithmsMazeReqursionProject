#pragma once
#include <Windows.h>
#include <conio.h>
#include <string>

class Console
{
	HANDLE handleStdOutput;

public:
	Console();

	void Clear();
	void SetCursor(int row, int column);
	void Write(std::string str);

	int GetChar();
	int KeyPressed();
};

