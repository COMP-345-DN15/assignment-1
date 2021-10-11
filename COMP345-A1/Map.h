#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Edge;
struct Territory;
struct Continent;
struct ContinentNode;
class MapLoader;

struct Edge {             // Edges between nodes represent adjacency between territories
    Territory* adjTerritoryPtr;
    Edge* next;
};

struct Territory {        // The graph’s nodes represents a territory (implemented as a Territory class)
    Edge* head;
    int continentID;
    string territoryName;
    int territoryID;
};

struct Continent {
    ContinentNode* head;
    int length;
    int continentID;
    int armyCount;
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

    Territory* getTerritory(int index);
    
//    Map(MapLoader mapLoaderObject, Territory* territoriesArray);   // Parameterized Constructor
//    Map(MapLoader mapLoaderObj, string* continentNames, string* countryNames, int* continentIDs, int* armies);
    Map(MapLoader* mapLoaderObject);
    Map(Map* map);
    ~Map();                                    // Destructor

    void AddEdge(int origin, int destination);		// Adds a bi-directional edge from territories[origin] to territories[destination]


    bool validate();                        // returns whether a map is valid or invalid
    int visitedNodesCount;
    
    int breadthFirstSearch(int bfs, Continent* continentToCheck = 0);

    int territoryNodeCount();
    int continentNodeCount(Continent *cont);
//    void transferElements(int* integerArray = 0, string* stringArray = 0);
    void transferTerritories(Territory* territories, string* territoryNames, int* continentIDs);
    
    Territory* getTerritoriesArray();

private:

};


class MapLoader {

public:

    MapLoader();            // Default constructor
    MapLoader(string);        // Constructor passing file name
    ~MapLoader();
    void readFile();        // Read .map file
    void makeConnections(Map* userMap); // Reads details and creates edges
    ifstream inputFile;        // Input stream
    string userIn;            // To hold user's input for the file name
    string line;            // To hold input stream line
    int count;                // To index the arrays
    int continentCount;        // To store number of continents
    int countryCount;        // To store number of countries
    string* continentName;    // Dynamic array for continent names
    string* countryName;    // Dynamic array for country names
    int* countryIn;            // Dynamic array to know what continent each country belongs to
    int* armies;            // Dynamic array for every continent's army count
    string* borders;        // Dynamic array for borders of each country by index
    
    int* getCountryArray();
    string* getContinentIDArray();
    
private:

};
