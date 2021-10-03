//
// COMP-345 - Group DN15
// Map implementation

#include "Map.h"

using namespace std;

// struct definitions
// Continent
Continent::Continent()
{
    head = nullptr;
    length = 0;
}

void Continent::Push(Territory* territory)
{
    this->head = new ContinentNode{ territory, this->head};
    this->length++;
}

ContinentNode* Continent::Pop()
{
    if(this->head == nullptr) {
        return nullptr;
    }

    this->length--;
    ContinentNode* tempNode = this->head;
    head = tempNode->next;
    return tempNode;
}

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
        this->continentsArray[this->territoriesArray[i]].head = new ContinentNode{&this->territoriesArray[i], continentsArray[territoriesArray[i]].head};
        this->continentsArray[territoriesArray[i]].length++;
    
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

    ////// STEP 1 //////
    // Check ALL Nodes are Connected -> Connected Graph Check

    // if number of connected nodes does not match expected amount, print statement and return false
    int territoryCheck = breadthFirstSearch();
    if(territoryCount != territoryCheck) {
        cout << "Invalid Map Detected!\n Territorities not connected!\n" << "Expected to have " << territoryCount << " nodes connected, but instead detected " << territoryCheck << " nodes connected.";
        return false;
    }

    ////// STEP 2 //////
    // Check Continents are Conncted -> Continents Connected Subgraph
    // Check that each Territory belongs to ONLY one Continent 
    // -> combined number of Territories contained in each Continent should match total number of Territories

    // loop to check each continent
    int continentCheck;
    int totalTerritoriesCheck = 0;
    for(int i = 0; i < continentCount; i++) {
        Continent* continent = &continentsArray[i];

        // if number of connected nodes does not match expected amount, print statement and return false
        continentCheck = breadthFirstSearch(continent);
        totalTerritoriesCheck += continentCheck;
        if(continent->length != continentCheck) {
            cout << "Invalid Map Detected!\n Continents not connected!\n" << "Expected to have " << continentCount << " nodes connected, but instead detected " << continentCheck << " nodes connected.";
            return false;
        }
    }

    // compare total counted Territories in each Continent vs global number of Territories
    if(totalTerritoriesCheck != territoryCount) {
        cout << "Invalid Map Detected!\n Some Territories belong to more than one Continent!/n" << "Expected to have " << territoryCount << " nodes connected, but instead detected " << totalTerritoriesCheck << " nodes connected.";
        return false;
    }

    ////// STEP 3 //////
    // Check Edges for any issues with graph -> ALL Nodes should have at least one incoming and outgoing Edge
    bool incomingEdgeCheck;
    for(int i = 0; i < territoryCount; i++) {
        Edge* outerEdge = territoriesArray[i].head;
        while(outerEdge != nullptr) {
            incomingEdgeCheck = false;
            Edge* incomingEdge = outerEdge->adjTerritoryPtr->head;
            while(incomingEdge != nullptr) {
                if(incomingEdge->adjTerritoryPtr->territoryID == territoriesArray[i].territoryID) {
                    incomingEdgeCheck = true;
                    break;
                }
                incomingEdge = incomingEdge->next;
            }
            if(incomingEdgeCheck == false) {
                cout << "Invalid Map Detected!/n Territory " << i << " has outgoing edge to Territory " 
                << outerEdge->adjTerritoryPtr->territoryID << " but no incoming edge.\n";
                return false;
            }
            outerEdge = outerEdge->next;
        }
    }

    ////// STEP 4 //////
    // if Map has passed all checks until this point -> Map is VALID
    return true;
};

int Map::breadthFirstSearch(Continent* continentToCheck) 
{

    bool continentCheck = false;
    Continent *visitedNodesQueue = new Continent();
    // Continent visitedNodesQueue;
    // check if passed continentToCheck = 0
    // if continentToCheck != 0 -> will check for connected subgraph
    // else will check for connected graph of all nodes
    // -> create appropriate type of queue
    if(continentToCheck != 0) {
        continentCheck = true;
        if(continentToCheck->head == nullptr) {
            return 0;
        } else {
            visitedNodesQueue->Push(continentToCheck->head->territoryPtr);
        }
    } else {
        visitedNodesQueue->Push(&territoriesArray[0]);
    }

    // create array of bools to check territories one by one
    bool* visitedNodes = new bool[territoryCount];
    visitedNodes[0] = true;
    // loop to init each bool in array to false
    for(int i = 1; i < territoryCount; i++) {
        visitedNodes[i] = false;
    }

    int visitedNodesCount = 1;
    bool accepted = false;

    while(visitedNodesQueue->length > 0) {
        visitedNodesCount++;
        ContinentNode* currentNode = visitedNodesQueue->Pop();
        Edge* outerEdge = currentNode->territoryPtr->head;

        while(outerEdge != nullptr) {
            if(visitedNodes[outerEdge->adjTerritoryPtr->territoryID == false]) {
                accepted = true;
                if(continentCheck) {
                    if(outerEdge->adjTerritoryPtr->continentID != currentNode->territoryPtr->continentID) {
                        accepted = false;
                    }
                }
            }

            if(accepted) {
                visitedNodesQueue->Push(outerEdge->adjTerritoryPtr);
                visitedNodes[outerEdge->adjTerritoryPtr->territoryID] = true;
            }

            outerEdge = outerEdge->next;
        }
        delete currentNode;
    }
    delete visitedNodesQueue;
    delete[] visitedNodes;
    return visitedNodesCount;
}

// void Map::displayAdjacentNodes(Territory territory)
// {
//     Edge* nodePtr = territoriesArray[territory.territoryID].head;

//     while(nodePtr != nullptr) {
        
//     }
// }

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