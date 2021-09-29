//
// COMP-345 - Group DN15
// Map implementation

#include "Map.h"

using namespace std;

// class Map 
// Map Constructor
Map::Map(int* territories, int territoryCount, int continentCount) 
{
    // basic member variable assignment
    this->territoryCount = territoryCount;
    this->continentCount = continentCount;
    this->territoryStartIndex = -1;     // necessary or no?

    // initialize Continent array (array of linked lists of type Continent)
    this->continentsArray = new Continent[continentCount];

    // loop to create continent linked lists within Continent array
    for(int i = 0; i < continentCount; i++) {
        this->continentsArray[i].head = nullptr;
        this->continentsArray[i].length = 0;
    }

    // initialize Territory array
    this->territoriesArray = new Territory[territoryCount];

    // loop to create Territory linked list within continent lists
    for(int i = 0; i < territoryCount; i++) {
        this->territoriesArray[i].head = nullptr;
        this->territoriesArray[i].continentID = continentsArray[i].continentID;     // is this right??
        this->territoriesArray[i].territoryID = i;
        this->territoriesArray[i].armyCount = new int[continentsArray[i].armyCount];    // is this right??

        // append territories to their corresponding continent list
        // something is wrong below
        // this->continentsArray [ territoriesArray[i] ].head = new ContinentNode{&this->territoriesArray[i], continentsArray[territoriesArray[i]].head};
        // this->continentsArray[territoriesArray[i]].length++;
    
    }

}

// Map Copy Constructor
Map::Map(Map* map)
{
    // basic member variable assignment
    this->territoryCount = territoryCount;
    this->continentCount = continentCount;
    this->territoryStartIndex = -1;     // necessary or no?

    // initialize Continent array (array of linked lists of type Continent)
    this->continentsArray = new Continent[continentCount];

    // loop to create continent linked lists within Continent array
    for(int i = 0; i < continentCount; i++) {
        this->continentsArray[i].head = nullptr;
        this->continentsArray[i].length = 0;
    }

}

// Map Destructor
Map::~Map()
{
    // iterate over territories of map to delete map edges
    for (int i = 0; i < territoryCount; i++ ) {
        Edge* current = territoriesArray[i].head;
        while(current != nullptr) {
            Edge* temp = current->next;
            delete current;
            current = temp;
        }

        delete[] territoriesArray[i].armyCount;
    }

    delete[] territoriesArray;
    territoriesArray = nullptr;

    for(int i = 0; i < continentCount; i++) {
        Continent* current = &continentsArray[i];
        ContinentNode* node = current->head;
        while(node != nullptr) {
            ContinentNode* temp = node->next;
            delete node;
            node = temp;
        }
    }

    delete[] continentsArray;
    continentsArray = nullptr;
}

bool Map::validate()
{
    // TODO:
    // check map is connected graph
    // check continents are connected subgraphs
    // check each country belongs to only one continent

    // if map is valid return true
    // else return false

};

//////////////////////////////

// class MapLoader
// MapLoader Constructor
MapLoader::MapLoader(string fileName)
{
    this->index = 0;
    this->tempVar = 0;
    this->players = 0;
    this->continents = 0;
    this->territoryCount = 0;
    
    inputFile.open(fileName);           // open file stream


    // determine number of players from file

    inputFile.close();                  // close file stream

};

MapLoader::MapLoader()
{
    this->index = 0;
    this->tempVar = 0;
    this->players = 0;
    this->continents = 0;
    this->territoryCount = 0;

    this->fileName = "";
    this->fileStream = "";
    this->inputLine = "";

    cout << "Please input file name..." << endl;
};

MapLoader::~MapLoader()
{
    delete[] territories;
};

void MapLoader::readContinents()
{

};

void MapLoader::readTerritories()
{

};

void MapLoader::readBorder()
{

};

void MapLoader::buildMap()
{

};