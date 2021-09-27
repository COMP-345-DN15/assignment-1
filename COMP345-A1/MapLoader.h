#pragma once
#include <iostream>
#include "Map.h"

using namespace std;

class MapLoader {

public:

	MapLoader();
	Map* loadMap(std::string mapName);


private:

	void readContinents();
	void readTerritories();
	void readBorders();
	void buildMap();

};
