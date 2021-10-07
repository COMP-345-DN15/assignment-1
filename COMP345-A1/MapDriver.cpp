//
// COMP-345 - Group DN15
// MapDriver

// #include "Map.h"

// using namespace std;

// int main()
// {
//     cout << "testing testing 1 2 3" << endl;
//     cout << "testing testing 4 5 6";
    
//     return 0;
// }

// #pragma once
#include <iostream>		// used for cin & cout
#include "Map.h"
#include "Map.cpp"

using namespace std;

int main()
{
    string fileName = "WoW.map";
	MapLoader* testObject = new MapLoader(fileName);
	testObject->readFile();

	delete testObject;
	return 0;
}