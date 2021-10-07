//
// COMP-345 - Group DN15
// Map header

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Edge;
struct Territory;
struct Continent;
struct ContinentNode;
std::map<int, map<string, int> > continentsMap;	
std::map<int, map<string, int> > countriesMap;
map<int, map<string, int> >::iterator continentsMapIterator;
map<string, int>::iterator continentsMapItrPtr;
map<int, map<string, int> >::iterator countriesMapIterator;
map<string, int>::iterator countriesMapItrPtr;
vector<string> bordersVector;
vector<string> countryNameVector;
vector<string> continentNameVector;

struct Edge { 			// Edges between nodes represent adjacency between territories
	Territory* adjTerritoryPtr;
	// int movementCost;		// we don't need this, right? Movement is always just 1, ya?	
	Edge* next;
};	

struct Territory {		// The graph’s nodes represents a territory (implemented as a Territory class)
	Edge* head;
	int continentID;
	string territoryName;
	int territoryID;
	int* armyCount;
};

struct Continent {
	int length;
	int continentID;
	int armyCount;
	ContinentNode* head;
	Continent();
	void Push(Territory* territory);
	ContinentNode* Pop();
};

struct ContinentNode {
	Territory* territoryPtr;
	ContinentNode* next;
};


class Map {

public:
	int territoryCount;
	int continentCount;
	int territoryStartIndex;
	Territory* territoriesArray;
	Continent* continentsArray;

	Map(int* territories, int territoryCount, int continentCount);		// Parameterized Constructor
	Map(Map* map);
	~Map();									// Destructor

	// addNode();

	bool validate();						// returns whether a map is valid or invalid

	int breadthFirstSearch(Continent* continentToCheck = 0);
	
	// void displayAdjacentNodes(Territory territory);

	// not working:
	// Map& operater= (const Map& map);
	// friend std::ostream& operater<< (std::ostream& out, const Map& map);

private:

};

class MapLoader {

public:

	MapLoader();			// Default constructor
	MapLoader(string fileName);		// Constructor passing file name
	void readFile();		// Read .map file
	ifstream inputFile;		// Input stream
	string userIn;			// To hold user's input for the file name
	string line;			// To hold input stream line
	int count;				// To index the arrays
	int continentCount;		// To store number of continents
	int countryCount;		// To store number of countries
	string* continentName;	// Dynamic array for continent names
	string* countryName;	// Dynamic array for country names
	int* armies;			// Dynamic array for every continent's army count
	int* countryIn;			// Dynamic array to know what continent each country belongs to
	string* borders;		// Dynamic array for borders of each country by index


private:

};

// class MapLoader
// {

// public:
// 	Map* LoadMap(ofstream textFile);	// is this the right data type for reading a file?

// 	MapLoader(string fileName);
// 	MapLoader();
// 	~MapLoader();

// 	string fileName;
// 	string fileStream;
// 	ifstream inputFile;
// 	string inputLine;

// 	// unsure of these below:
// 	int* territories;
// 	int territoryCount;
// 	int index;		
// 	int tempVar;
// 	int origin;

// private:
// 	void readContinents();
// 	void readTerritories();
// 	void readBorder();
// 	void buildMap();
// 	void readFile(string fileName);

// 	// unsure of these below:
// 	int players;
// 	int continents;

// };

// int mapLoaderTest();