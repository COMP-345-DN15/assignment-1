#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "CommandProcessor.h"

using namespace std;

class FileLineReader {
private:
	string fileName;
	string line;
	ifstream fileStream;
public:
	FileLineReader(string);
	~FileLineReader();
	string readLineFromFile();
};