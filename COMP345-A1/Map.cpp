//@see: http://domination.sourceforge.net/makemaps.shtml
#include "Map.h"
#include <iostream>		// used for cin & cout
#include <fstream>		// used for file i/o
#include <string>
//#include <vector>

using namespace std;

Continent::Continent()
{
    head = nullptr;
    length = 0;
}

void Continent::Push(Territory* territory)
{
//    ContinentNode* continentNode = new ContinentNode();
//    continentNode->territoryPtr = territory;
//
//    continentNode->next = this->head;
//    this->head = continentNode;
//    this->length++;
//    if(continentNode->next == nullptr) cout << "cont next == nullptr" << endl;
//    // necessary or is destroying the node just created?
////    delete continentNode;
    
    this->head = new ContinentNode{territory, this->head};
    this->length++;
}

ContinentNode* Continent::Pop()
{
    
    this->length--;
    ContinentNode* tempNode = this->head;
    head = tempNode->next;
    return tempNode;
}

// class Map 
// Map Constructor
Map::Map(MapLoader* mapLoaderObject)
{
    // basic member variable assignment
    this->territoryCount = mapLoaderObject->countryCount;
    this->continentCount = mapLoaderObject->continentCount;
    this->territoryStartIndex = -1;     // necessary or no?

    // initialize Continent array (array of linked lists of type Continent)
    this->continentsArray = new Continent[continentCount];

    // loop to create continent linked lists within Continent array
    for (int i = 0; i < continentCount; i++) {
        this->continentsArray[i].head = nullptr;
        this->continentsArray[i].length = 0;
        this->continentsArray[i].armyCount = mapLoaderObject->armies[i];
        this->continentsArray[i].continentID = i;

    }

    // initialize Territory array
    this->territoriesArray = new Territory[territoryCount];
    
    transferTerritories(territoriesArray, mapLoaderObject->getContinentIDArray(), mapLoaderObject->getCountryArray());

    // loop to create Territory linked list within continent lists
    for (int i = 0; i < territoryCount; i++) {
        this->territoriesArray[i].head = nullptr;
        this->territoriesArray[i].continentID = continentsArray[i].continentID;     // is this right??
        this->territoriesArray[i].territoryID = i;
    //     // append territories to their corresponding continent list
    //     // something is wrong below
        ContinentNode* cNode = new ContinentNode();
        cNode->territoryPtr = &this->territoriesArray[i];
        cNode->next = continentsArray[territoriesArray[i].continentID].head;
        continentsArray[territoriesArray[i].continentID].head = new ContinentNode();
        continentsArray[territoriesArray[i].continentID].head->territoryPtr = &this->territoriesArray[i];
        // continentsArray[territoriesArray[i]].head;
        this->continentsArray[territoriesArray[i].continentID].length++;

        
        Edge* edge = this->territoriesArray[i].head;
        if(edge != nullptr) {
            Edge* prev = this->territoriesArray[i].head = new Edge{&territoriesArray[edge->adjTerritoryPtr->territoryID], nullptr};
            edge = edge->next;
            
            while(edge != nullptr) {
                prev->next = new Edge{&territoriesArray[edge->adjTerritoryPtr->territoryID]};
                edge = edge->next;
                prev = prev->next;
            }
            prev->next = nullptr;
        }
        this->continentsArray[this->territoriesArray[i].continentID].head = new ContinentNode {&this->territoriesArray[i], continentsArray[this->territoriesArray[i].continentID].head};
        this->continentsArray[this->territoriesArray[i].continentID].length++;
    }
}

// Map Copy Constructor
Map::Map(Map* map)
{
    // basic member variable assignment
    this->territoryCount = map->territoryCount;
    this->continentCount = map->continentCount;
    this->territoryStartIndex = -1;     // necessary or no?

    // initialize Continent array (array of linked lists of type Continent)
    this->continentsArray = new Continent[continentCount];

    // loop to create continent linked lists within Continent array
    for (int i = 0; i < continentCount; i++) {
        this->continentsArray[i].head = nullptr;
        this->continentsArray[i].length = 0;
    }
}

// Map Destructor
Map::~Map()
{
    // iterate over territories of map to delete map edges
    for (int i = 0; i < territoryCount; i++) {
        Edge* current = territoriesArray[i].head;
        while (current != nullptr) {
            Edge* temp = current->next;
            delete current;
            current = temp;
        }
    }

    delete[] territoriesArray;
    territoriesArray = nullptr;

    for (int i = 0; i < continentCount; i++) {
        Continent* current = &continentsArray[i];
        ContinentNode* node = current->head;
        while (node != nullptr) {
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
//    int territoryCheck = new int();
//    Continent* cont = new Continent;
    int bfsVar = 0;
    int territoryCheck = this->breadthFirstSearch(bfsVar);
//    int territoryCheck = this->territoryNodeCount();
    if (territoryCount != territoryCheck) {
        cout << "Invalid Map Detected!\nTerritorities not connected!\n" << "Expected to have " << territoryCount << " nodes connected, but instead detected " << territoryCheck << " nodes connected." << endl;
        return false;
    } else {
        cout << "Territories are correctly connected!" << endl;
    }

    ////// STEP 2 //////
    // Check Continents are Conncted -> Continents Connected Subgraph
    // Check that each Territory belongs to ONLY one Continent 
    // -> combined number of Territories contained in each Continent should match total number of Territories

    // loop to check each continent
    int continentCheck;
    int totalTerritoriesCheck = 0;
    for (int i = 0; i < continentCount; i++) {
        Continent* continent = &continentsArray[i];

        // if number of connected nodes does not match expected amount, print statement and return false
//        continentCheck = breadthFirstSearch(bfsVar, continent);
        continentCheck = continentNodeCount(continent);
        totalTerritoriesCheck += continentCheck;
        if (continent->length != continentCheck) {
            cout << "Invalid Map Detected!\n Continents not connected!\n" << "Expected to have " << continent->length << " nodes connected, but instead detected " << continentCheck << " nodes connected." << endl;
            return false;
        } else {
            cout << "Continents are correctly connected!" << endl;
        }
    }

    // compare total counted Territories in each Continent vs global number of Territories
    if (totalTerritoriesCheck != territoryCount) {
        cout << "Invalid Map Detected!\n Some Territories belong to more than one Continent!/n" << "Expected to have " << territoryCount << " nodes connected, but instead detected " << totalTerritoriesCheck << " nodes connected." << endl;
        return false;
    }

    ////// STEP 3 //////
    // Check Edges for any issues with graph -> ALL Nodes should have at least one incoming and outgoing Edge
    bool incomingEdgeCheck;
    for (int i = 0; i < territoryCount; i++) {
        Edge* outerEdge = territoriesArray[i].head;
        while (outerEdge != nullptr) {
            incomingEdgeCheck = false;
            Edge* incomingEdge = outerEdge->adjTerritoryPtr->head;
            while (incomingEdge != nullptr) {
                if (incomingEdge->adjTerritoryPtr->territoryID == territoriesArray[i].territoryID) {
                    incomingEdgeCheck = true;
                    break;
                }
                incomingEdge = incomingEdge->next;
            }
            if (incomingEdgeCheck == false) {
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

void Map::AddEdge(int origin, int destination) {
    //Check for valid indexes
    if (origin < 0 || origin >= territoryCount) {
        cout << "WARNING: Error on adding edge (" << origin << "," << destination << "): origin territory index " << origin << " out of range. Edge not added.\n";
        return;
    }
    else if (destination < 0 || destination >= territoryCount) {
        cout << "WARNING: Error on adding edge(" << origin << ", " << destination << ") : destination territory index " << destination << " out of range. Edge not added.\n";
        return;
    }
    //Check if self-loop
    else if (origin == destination) {
        cout << "WARNING: Error on adding edge(" << origin << ", " << destination << ") : self-looping is forbidden. Edge not added.\n";
        return;
    }
    //Check if edge is already defined, if yes then do not add the edge
    Edge* temp = territoriesArray[origin].head;
    while (temp != nullptr) {
        if (temp->adjTerritoryPtr->territoryID == destination) {
            cout << "Skipped creation of edge (" << origin << "," << destination << "), edge already exists." << endl;
            return;
        }
        temp = temp->next;
    }

    territoriesArray[origin].head = new Edge{ getTerritory(destination), territoriesArray[origin].head };
    territoriesArray[destination].head = new Edge{ getTerritory(origin), territoriesArray[destination].head };
}

Territory* Map::getTerritoriesArray()
{
    return territoriesArray;
}

Territory* Map::getTerritory(int territoryIndex) {
    if (territoryIndex < 0 || territoryIndex >= territoryCount) {
        cout << "ERROR: Failure to fetch territory at index " << territoryIndex << ", index is out of range." << endl;
        return nullptr;
    }
    return &territoriesArray[territoryIndex];
}

int Map::breadthFirstSearch(int bfs, Continent* continentToCheck)
{
        
    bool continentCheck = false;
    Continent* visitedNodesQueue = new Continent();
    // Continent visitedNodesQueue;
    // check if passed continentToCheck = 0
    // if continentToCheck != 0 -> will check for connected subgraph
    // else will check for connected graph of all nodes
    // -> create appropriate type of queue
    if (continentToCheck != 0) {
        continentCheck = true;
        if (continentToCheck->head == nullptr) {
            int retVal{0};
            return retVal;
        }
        else {
            visitedNodesQueue->Push(continentToCheck->head->territoryPtr);
        }
    }
    else {
        Territory *terr = new Territory;
        terr = &territoriesArray[0];

        visitedNodesQueue->Push(terr);
    }
    
    // create array of bools to check territories one by one
    bool* visitedNodes = new bool[territoryCount];
    visitedNodes[0] = true;
    int nodeCount = 1;
    Territory *terr = new Territory;
    Continent *cont = new Continent;
    if (!continentCheck) {
    
    // loop to init each bool in array to false
        for (int i = 1; i < territoryCount; i++) {
            terr = &territoriesArray[i];
            visitedNodes[i] = false;
            nodeCount++;
            visitedNodesQueue->Push(terr);
        }
    }
    else {
        for (int i = 1; i < continentCount; i++) {
            cont = &continentsArray[i];
            visitedNodes[i] = false;
            nodeCount++;
        }
    }
    bool accepted = false;

    int visitedNodesLoop = 0;

    for(int i = 0; i < nodeCount; i++) {
        this->visitedNodesCount++;
        ContinentNode* currentNode = visitedNodesQueue->Pop();

        Edge* outerEdge = currentNode->territoryPtr->head;

        while (outerEdge != nullptr) {
            visitedNodesLoop++;
            if (visitedNodes[outerEdge->adjTerritoryPtr->territoryID == false]) {
                accepted = true;
                if (continentCheck) {
                    if(outerEdge->adjTerritoryPtr->continentID != currentNode->territoryPtr->continentID) {
                        accepted = false;
                    }
                }
            }

            if (accepted) {
                visitedNodesQueue->Push(outerEdge->adjTerritoryPtr);
                visitedNodes[outerEdge->adjTerritoryPtr->territoryID] = true;
            }
            outerEdge = outerEdge->next;
        }
    }

    bfs = visitedNodesCount;
    delete visitedNodesQueue;
    delete[] visitedNodes;
    return bfs;
}

int Map::territoryNodeCount()
{
    bool* checkedNodes = new bool[territoryCount];
    for(int i = 0; i < territoryCount; i++) {
        checkedNodes[i] = false;
    }
    
    int checkedCount{0};
    Continent nodesQueue;
    nodesQueue.Push(&territoriesArray[0]);
    checkedNodes[0] = true;
    
    while(nodesQueue.length > 0) {
        checkedCount++;
        ContinentNode* currentNode = nodesQueue.Pop();
        Edge* outerEdge = currentNode->territoryPtr->head;
        while(outerEdge != nullptr) {
            if(!checkedNodes[outerEdge->adjTerritoryPtr->territoryID]) {
                nodesQueue.Push(outerEdge->adjTerritoryPtr);
                checkedNodes[outerEdge->adjTerritoryPtr->territoryID] = true;
            }
            outerEdge = outerEdge->next;
        }
        delete currentNode;
    }
    delete[] checkedNodes;
    return checkedCount;
}

int Map::continentNodeCount(Continent *cont)
{
    if(cont->head == nullptr) {
        return 0;
    }
    
    bool* checkedNodes = new bool[territoryCount];
    for(int i = 0; i < territoryCount; i++) {
        checkedNodes[i] = false;
    }
    
    int checkedCount{0};
    Continent* nodesQueue = new Continent();
    nodesQueue->Push(cont->head->territoryPtr);
    checkedNodes[cont->head->territoryPtr->territoryID] = true;
    
    while(nodesQueue->length > 0) {
        checkedCount++;
        ContinentNode* currentNode = nodesQueue->Pop();
        Edge* outerEdge = currentNode->territoryPtr->head;
        
        while(outerEdge != nullptr) {
            if(!checkedNodes[outerEdge->adjTerritoryPtr->territoryID] and outerEdge->adjTerritoryPtr->continentID == currentNode->territoryPtr->continentID) {
                nodesQueue->Push(outerEdge->adjTerritoryPtr);
                checkedNodes[outerEdge->adjTerritoryPtr->territoryID] = true;
            }
            outerEdge = outerEdge->next;
        }
        delete currentNode;
    }
    delete nodesQueue;
    delete[] checkedNodes;
    return checkedCount;
}

int* MapLoader::getCountryArray()
{
    return this->countryIn;
}

string* MapLoader::getContinentIDArray()
{
    return this->countryName;
}

void Map::transferTerritories(Territory* territories, string* territoryNames, int* continentIDs)
{
//    this->territoriesArray = new Territory[this->territoryCount];
    
    for(int i = 0; i < territoryCount; i++) {
        this->territoriesArray[i].continentID = continentIDs[i];
        this->territoriesArray[i].territoryID = i;
        this->territoriesArray[i].territoryName = territoryNames[i];
    
    
        Edge* edge = this->territoriesArray[i].head;
        
        if(edge != nullptr) {
            Edge* previous = this->territoriesArray[i].head = new Edge{&territoriesArray[edge->adjTerritoryPtr->territoryID], nullptr};
            
            edge = edge->next;
            
            while(edge != nullptr) {
                previous->next = new Edge{&territoriesArray[edge->adjTerritoryPtr->territoryID]};
                edge = edge->next;
                previous = previous->next;
            }
            previous->next = nullptr;
        }
        
        this->continentsArray[this->territoriesArray[i].continentID].head = new ContinentNode{&this->territoriesArray[i], continentsArray[this->territoriesArray[i].continentID].head};
        this->continentsArray[this->territoriesArray[i].continentID].length++;
    }
}

MapLoader::MapLoader() {
    line = "";
    userIn = "";
    continentCount = 0;
    countryCount = 0;
    count = 0;
}

MapLoader::MapLoader(string filename) {
    line = "";
    userIn = filename;
    continentCount = 0;
    countryCount = 0;
    count = 0;
    
    cout << "Now reading input file" << endl;
    
    this->readFile();
    
    cout << "Now constructing Map object" << endl;
    
    Map* inputMap = new Map(this);
    
    cout << "Now validating Map" << endl;
    
    inputMap->validate();
}

MapLoader::~MapLoader()
{
    delete[] continentName;
    delete[] countryName;
    delete[] armies;
    delete[] borders;
}

void MapLoader::readFile()
{
    // Scan the whole file once to record number of continents and countries
    inputFile.open(userIn);        // Open stream file

    cout << "begin reading file" << endl;
    
    if (!inputFile) cerr << "Could not open the file!" << endl;
    else cout << "file opened successfully" << endl;
    
    if (inputFile.is_open())
    {
        while (getline(inputFile, line)) {
            if (line[0] == '[') {
                // to identify continents tag
                if (line[3] == 'n') {
                    getline(inputFile, line); // to skip tag
                    while (line.length() > 2) {
                        continentCount++;
                        getline(inputFile, line);
                    }
                }
                // to identify countries tag
                else if(line[3] == 'u') {
                    getline(inputFile, line); // to skip tag
                    while (line.length() > 2) {
                        countryCount++;
                        getline(inputFile, line);
                    }
                }
            }
        }
    }
    inputFile.close();

    // Initialize all arrays to start storing map details
    continentName = new string[continentCount];
    countryName = new string[countryCount];
    armies = new int[continentCount];
    countryIn = new int[countryCount];
    borders = new string[countryCount];
    
    // Scan file and record data
    inputFile.open(userIn);        // Open stream file

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            if (line[0] == '[') {
                // to identify [file] label
                if (line[1] == 'f') {

                    // to skip label line
                    cout << "SKIPPED: " << line << "\n";
                    getline(inputFile, line);

                    // to skip [file] lines
                    while (line.length() > 2) {
                        cout << "SKIPPED: " << line << "\n";
                        getline(inputFile, line);
                    }
                }

                // to store [continents]
                else if (line[3] == 'n') {

                    // to skip label line
                    cout << endl;
                    cout << "SKIPPED: " << line << "\n";
                    getline(inputFile, line);

                    // to store continents
                    while (line.length() > 2) {
                        cout << "CONTINENT: " << line << "\n";
                        for (size_t i = 0; i < line.length(); i++) {
                            if (line[i] == ' ') {
                                // assign name of continent
                                continentName[count] = line.substr(0, i);
                                cout << "This is what I get for continentName: \"" << continentName[count] << "\"" << endl;
                                // assign army count
                                armies[count] = line[i + 1] - 48; // -48 to convert from ASCII to (int)
                                cout << "This is what I get for armies: \"" << armies[count] << "\"" << endl;
                                count++;
                                break;
                            }
                        }
                        getline(inputFile, line);
                    }
                }

                // to store [countries]
                else if (line[3] == 'u') {

                    // to skip label line
                    cout << endl;
                    cout << "SKIPPED: " << line << "\n";
                    getline(inputFile, line);
                    count = 0; // reset counter

                    // to store countries
                    while (line.length() > 2) {
                        cout << "COUNTRY: " << line << "\n";
                        for (size_t i = 0; i < line.length(); i++) {
                            if (line[i] == ' ') {
                                i++;
                                for (size_t j = i; j < line.length(); j++) {
                                    if (line[j] == ' ') {
                                        // assign name of countries
                                        // something about the next line makes me do "j-3", but why?
                                        countryName[count] = line.substr(i, j-3);
                                        cout << "This is what I get for countryName: \"" << countryName[count] << "\"" << endl;
                                        // assign cotinent each country belongs to
                                        // at some point the the number will be a double digit, what do?
                                        countryIn[count] = line[j + 1] - 48; // -48 to convert from ASCII to (int)
                                        cout << "This is what I get for countryIn: \"" << countryIn[count] << "\"" << endl;
                                        count++;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        getline(inputFile, line);
                    }
                }

                // to store [borders]
                else if (line[1] == 'b') {

                    // to skip label line
                    cout << endl;
                    cout << "SKIPPED: " << line << "\n";
                    getline(inputFile, line);
                    count = 0; // reset counter

                    // to store borders
                    while (line.length() > 2) {
                        cout << "BORDERS: " << line << "\n";

                        for (size_t i = 0; i < line.length(); i++) {
                            if (line[i] == ' ') {
                                // assign name of continent
                                i++;
                                borders[count] = line.substr(i, line.length());
                                cout << "This is what I get for borders: \"" << borders[count] << "\"" << endl;
                                count++;
                                break;
                            }
                        }
                        getline(inputFile, line);
                    }
                }
            }
        }
    }
    inputFile.close();

    //delete[] continentName;
    //delete[] countryName;
    //delete[] armies;
    //delete[] countryIn;
    //delete[] borders;
}

void MapLoader::makeConnections(Map* userMap) {
    string line;
    string subLine;
    int origin;
    int dest ;
    int count = 0;
    int h;
    // To establish connection between countries
    for (size_t i = 0; i < borders->length(); i++) {
        line = borders[i];
        for (size_t j = 0; j < borders[i].length(); j++) {
            h = j;
            while (line[h] != ' ') {
                count++;
                h++;
                if (count == 2) break;
            }
            origin = i + 1;
            subLine = line.substr(j, count);
            dest = stoi(subLine);
            userMap->AddEdge(origin, dest);
            j += count;
            count = 0;
            if (j - 1 == borders->length()) break;
        }
    }
    
    for(int i = 0; i < continentCount; i++) {
        
    }
}
