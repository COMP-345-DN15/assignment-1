#pragma once
#include <iostream>

using namespace std;

class FileLineReader {
private:
	void readCommand();
	void readLinesFromFile();
public:
	string command;
	FileLineReader();
};