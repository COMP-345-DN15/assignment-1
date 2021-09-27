#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Territory {



private:

	string territoryName;

	// vector that contains a list of Territory objects
	vector<Territory*> territoryNeighbours;

};