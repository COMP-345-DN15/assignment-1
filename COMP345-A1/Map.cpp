//@see: http://domination.sourceforge.net/makemaps.shtml
#include "Map.h"

using namespace std;

Continent::Continent()
{
    head = nullptr;
    length = 0;
}

void Continent::Push(Territory* territory)
{
    this->head = new ContinentNode{territory, this->head};
    this->length++;
}

ContinentNode* Continent::Pop()
{
    if (this->head == nullptr) return nullptr;
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
    contVector.resize(continentCount);
    
    // loop to create continent linked lists within Continent array
    for (int i = 0; i < continentCount; i++) {
        contVector.at(i).head = nullptr;
        contVector.at(i).length = 0;
        contVector.at(i).armyCount = mapLoaderObject->armies[i];
        contVector.at(i).continentID = i;
    }

    terrVector.resize(territoryCount);
    
    // loop to create Territory linked list within continent lists
    for (int i = 0; i < territoryCount; i++) {
        terrVector.at(i).head = nullptr;
        terrVector.at(i).continentID = mapLoaderObject->countryContinentIdVector.at(i);
        terrVector.at(i).territoryID = i;
        terrVector.at(i).territoryName = mapLoaderObject->countryNameVector.at(i);
        contVector.at(mapLoaderObject->countryContinentIdVector.at(i)).head = new ContinentNode{&terrVector.at(i), contVector.at(mapLoaderObject->countryContinentIdVector.at(i)).head};
        contVector.at(mapLoaderObject->countryContinentIdVector.at(i)).length++;
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
    // what needs to be deleted still?
    // TODO: Check for memory leaks
}

Map& Map::operator=(const Map &map) {
    if (this == &map) {
        return *this;
    }
    
    //reallocate new values:
    this->territoryCount = map.territoryCount;
    this->continentCount = map.continentCount;
    this->territoryStartIndex = map.territoryStartIndex;

    //Initialize continent Linked Lists
    contVector.resize(continentCount);
    for (int i = 0; i < continentCount; i++) {
        this->contVector.at(i).head = nullptr;
        this->contVector.at(i).length = 0;
    }

    //Initialize territories array and copy
    terrVector.resize(territoryCount);
    for (int i = 0; i < territoryCount; i++) {
        this->terrVector.at(i).continentID = map.terrVector.at(i).continentID;
        this->terrVector.at(i).territoryID = i;
        Edge* temp_edge = map.territoriesArray[i].head;
        
        if (temp_edge != nullptr) {
            Edge* prev = this->terrVector.at(i).head = new Edge{ &terrVector.at(temp_edge->adjTerritoryPtr->territoryID), nullptr };
            temp_edge = temp_edge->next;

            while (temp_edge != nullptr) {
                prev->next = new Edge{ &terrVector.at(temp_edge->adjTerritoryPtr->territoryID) };
                temp_edge = temp_edge->next;
                prev = prev->next;
            }
            prev->next = nullptr;
        }
        //Append territory to its corresponding continent list
        this->contVector.at(map.terrVector.at(i).continentID).head = new ContinentNode{ &this->terrVector.at(i), contVector.at(map.terrVector.at(i).continentID).head };
        this->contVector.at(map.terrVector.at(i).continentID).length++;
    }

    return *this;
}

bool Map::validate()
{

    ////// STEP 1 //////
    // Check ALL Nodes are Connected -> Connected Graph Check

    // if number of connected nodes does not match expected amount, print statement and return false
    int territoryCheck = this->territoryNodeCount();
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
    int successfulContinents = 0;
    int totalTerritoriesCheck = 0;
    for (int i = 0; i < continentCount; i++) {
        Continent* continent = &contVector.at(i);
            
        // if number of connected nodes does not match expected amount, print statement and return false
        continentCheck = continentNodeCount(continent);
        totalTerritoriesCheck += continentCheck;
        
        if (contVector.at(i).length != continentCheck) {
            cout << "Continents not connected properly!\n" << "Expected to have " << continent->length << " nodes connected, but instead detected " << continentCheck << " nodes connected." << endl;
            return false;
        } else {
//            cout << "Continent " << i << " is correctly connected!" << endl;
            successfulContinents++;
        }
    }
    
    if(successfulContinents == continentCount) cout << "Continents are correctly connected!" << endl;

    // compare total counted Territories in each Continent vs global number of Territories
    if (totalTerritoriesCheck != territoryCount) {
        cout << "Invalid Map Detected!\nSome Territories belong to more than one Continent!\n" << "Expected to have " << territoryCount << " nodes connected, but instead detected " << totalTerritoriesCheck << " nodes connected." << endl;
        return false;
    }

    ////// STEP 3 //////
    // Check Edges for any issues with graph -> ALL Nodes should have at least one incoming and outgoing Edge
    bool incomingEdgeCheck;
    for (int i = 0; i < territoryCount; i++) {
        Edge* outerEdge = terrVector.at(i).head;
        while (outerEdge != nullptr) {
            incomingEdgeCheck = false;
            Edge* incomingEdge = outerEdge->adjTerritoryPtr->head;
            while (incomingEdge != nullptr) {
                if (incomingEdge->adjTerritoryPtr->territoryID == terrVector.at(i).territoryID) {
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
    cout << endl << "MAP IS VALID!" << endl;
    return true;
};

void Map::AddEdge(int origin, int destination)
{
    origin--;
    destination--;
    
    if(destination < 0) return;
    
    //Check for valid indexes
    if (origin < 0 || origin > territoryCount) {
        cout << "WARNING: Error on adding edge (" << origin << "," << destination << "): origin territory index " << origin << " out of range. Edge not added.\n";
        return;
    }
    else if (destination < 0 || destination > territoryCount) {
        cout << "WARNING: Error on adding edge(" << origin << ", " << destination << ") : destination territory index " << destination << " out of range. Edge not added.\n";
        return;
    }
    //Check if self-loop
    else if (origin == destination) {
        cout << "WARNING: Error on adding edge(" << origin << ", " << destination << ") : self-looping is forbidden. Edge not added.\n";
        return;
    }
    //Check if edge is already defined, if yes then do not add the edge
    Edge* temp = terrVector.at(origin).head;
    while (temp != nullptr) {
        if (temp->adjTerritoryPtr->territoryID == destination) {
//            cout << "Skipped creation of edge (" << origin << "," << destination << "), edge already exists." << endl;
            return;
        }
        temp = temp->next;
    }
    terrVector.at(origin).head = new Edge{ getTerritory(destination), terrVector.at(origin).head };
    terrVector.at(destination).head = new Edge{ getTerritory(origin), terrVector.at(destination).head };
}

Territory* Map::getTerritoriesArray()
{
    return territoriesArray;
}

Territory* Map::getTerritory(int territoryIndex)
{
    if (territoryIndex < 0 || territoryIndex >= territoryCount) {
        cout << "ERROR: Failure to fetch territory at index " << territoryIndex << ", index is out of range." << endl;
        return nullptr;
    }
    return &terrVector.at(territoryIndex);
}

int Map::territoryNodeCount()
{
    bool* checkedNodes = new bool[territoryCount];
    for(int i = 0; i < territoryCount; i++) {
        checkedNodes[i] = false;
    }
    
    int checkedCount{0};
    Continent nodesQueue;
    nodesQueue.Push(&terrVector.at(0));
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

vector<int> MapLoader::getCountryArray()
{
    return this->countryContinentIdVector;
}

//string* MapLoader::getContinentIDArray()
//{
//    return this->countryName;
//}

MapLoader::MapLoader()
{
    line = "";
    fileName = "";
    continentCount = 0;
    countryCount = 0;
    arrayIndex = 0;
}

MapLoader::MapLoader(string filename)
{
    line = "";
    fileName = filename;
    continentCount = 0;
    countryCount = 0;
    arrayIndex = 0;
        
    
    // Scan the whole file once to record number of continents and countries
    inputFile.open(fileName);        // Open stream file

    cout << "Now reading file..." << endl;
    
    if (!inputFile) cerr << "Could not open the file!" << endl;
//    else cout << "File opened successfully!" << endl;
    
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
    
    continentName = new string[continentCount];
//    countryName = new string[countryCount];
    armies = new int[continentCount];
//    countryContinentIdArray = new int[countryCount];
    countryContinentIdVector.resize(countryCount);
    
    // TODO: Fix this mem alloc
    borders.resize(countryCount);
    for(int i = 0; i < countryCount; i++) {
        borders[i].resize(countryCount, 0);
    }
    
    // Scan file and record data
    inputFile.open(fileName);        // Open stream file

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            if (line[0] == '[') {
                // to identify [file] label
                if (line[1] == 'f') {
                    // to skip label line
                    getline(inputFile, line);

                    // to skip [file] lines
                    while (line.length() > 2) {
                        getline(inputFile, line);
                    }
                }
                // to store [continents]
                else if (line[3] == 'n') {
                    continentCount = 0;
                    getline(inputFile, line);
                    // to store continents
                    while (line.length() > 2) {
                        for (size_t i = 0; i < line.length(); i++) {
                            if (line[i] == ' ') {
                                // assign name of continent
                                continentName[continentCount] = line.substr(0, i);
                                // assign army count
                                armies[arrayIndex] = line[i + 1] - 48; // -48 to convert from ASCII to (int)
                                continentCount++;
                                break;
                            }
                        }
                        getline(inputFile, line);
                    }
                }

                // to store [countries]
                else if (line[3] == 'u') {
//                    countryCount = 0;
                    int countryIndex = 0;
                    getline(inputFile, line);
                    int contIdDigits = 0;
                    int contIdInt = 0;
                    string contIDString = "";
                    countryNameVector.resize(countryCount);
                    // to store countries
                    while (line.length() > 2) {
                        if(std::isdigit(line[0]) == 0) getline(inputFile, line);
                        for (size_t i = 0; i < line.length(); i++) {
                            if (line[i] == ' ') {
                                i++;
                                for (size_t j = i; j < line.length(); j++) {
                                    if(line[j] == ' ') {
                                        int d = j + 1;
                                        while(line[d] != ' ') {
                                            contIdDigits++;
                                            d++;
                                        }
                                        
                                        for(int k = 0; k < contIdDigits; k++) {
                                            contIDString += std::to_string(line[j + k + 1] - 48);
                                        }
                                        for(char const &c : contIDString) {
                                            if (std::isdigit(c) == 0) break;
                                            else {
                                                contIdInt = std::stoi(contIDString) - 1;
                                            }
                                        }
                                        
                                        // assign name of countries
//                                        countryName[countryCount] = line.substr(i, j-3);
                                        countryNameVector.at(countryIndex) = line.substr(i, j - 3);
                                        // assign cotinent each country belongs to
                                        countryContinentIdVector.at(countryIndex) = contIdInt;
                                        countryIndex++;
                                        contIDString.clear();
                                        contIdDigits = 0;
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
                    getline(inputFile, line);
                    arrayIndex = 0; // reset counter
                    int borderToAdd = 0;
                    string borderString = "";
                    // to store borders
                    for(int i = 0; i < countryCount; i++) {
                        borders[i].reserve(line.length());
                        borderString.clear();
                        for (int j = 0; j < line.length(); j++) {
                            if (line[j] == ' ' || j == line.length() - 1) {
                                if(j == line.length() - 1) {
                                    borderString += line[j];
                                }
                                
                                if(!borderString.empty()) {
                                    for(char const &c : borderString) {
                                        if (std::isdigit(c) == 0) {
                                            break;
                                        } else {
                                            borderToAdd = std::stoi(borderString);
                                        }
                                    }
                                }
                                if(borderToAdd != i+1) {
                                    borders[i].push_back(borderToAdd);
                                }
                                borderString.clear();
                            } else {
                                borderString += line[j];
                            }
                        }
                        getline(inputFile, line);
                    }
                }
            }
        }
    }
    inputFile.close();
    
    cout << "Now constructing Map object..." << endl;
    
    mapObject = new Map(this);
    
    cout << "Now making Map connections..." <<endl;
    // add edges to map
    for(int i = 0; i < countryCount; i++) {
        for(int j = 0; j < borders[i].size(); j++) {
            if(i+1 != borders[i][j]) {
                mapObject->AddEdge(i+1, borders[i][j]);
            }
        }
    }
    
//    cout << "Now validating input Map..." << endl;
//    mapObject->validate();
}

MapLoader::~MapLoader()
{
    delete[] continentName;
//    delete[] countryName;
    delete[] armies;
    
    // where to delete mapObject?
//    delete mapObject;
}
