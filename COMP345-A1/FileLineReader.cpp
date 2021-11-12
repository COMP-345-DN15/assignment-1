#pragma once

#include "FileLineReader.h"

#include <iostream>
#include <fstream>

using namespace std;

FileLineReader::FileLineReader(string fileName)
{
    this->fileName = fileName;

    fileStream.open(fileName);

    if (!fileStream.is_open()) { // if file name is bad
        cout << "Could not open Gameplay file successfully" << endl;
    }
}

FileLineReader::~FileLineReader()
{
    fileStream.close();
}

string FileLineReader::readLineFromFile()
{
    getline(fileStream, line);

    if (fileStream.eof()) {
        return "endGame"; //?
    }

    return line;
}