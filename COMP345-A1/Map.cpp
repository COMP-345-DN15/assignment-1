//
// COMP-345 - Group DN15
// Map implementation

#include "Map.h"
#include <iostream>		// used for cin & cout
#include <fstream>		// used for file i/o
#include <string>
#include <vector>

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
    ContinentNode* cNode = new ContinentNode();
    cNode->territoryPtr = territory;
    cNode->next = this->head;
    this->head = cNode;
    this->length++;

    // necessary or is destroying the node just created?
    delete cNode;
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
Map::Map(int* territoriesArray, int territoryCount, int continentCount) 
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
    // std::map<string, int> territoryTemp;
    string continentNameTemp, countryNameTemp;
    int armyTemp = 0, continentIDTemp, countryIDTemp;
    for(int i = 0; i < territoryCount; i++) {
        this->territoriesArray[i].head = nullptr;
        this->territoriesArray[i].continentID = continentsArray[i].continentID;     // is this right??
        this->territoriesArray[i].territoryID = i;
        this->territoriesArray[i].armyCount = new int[continentsArray[i].armyCount];    // is this right??

    //     // append territories to their corresponding continent list
    //     // something is wrong below
        ContinentNode* cNode = new ContinentNode();
        cNode->territoryPtr = &this->territoriesArray[i];
        cNode->next = continentsArray[territoriesArray[i]].head;
        continentsArray[territoriesArray[i]].head = new ContinentNode();
        continentsArray[territoriesArray[i]].head->territoryPtr = &this->territoriesArray[i];
        // continentsArray[territoriesArray[i]].head;
        this->continentsArray[territoriesArray[i]].length++;
    
    }

    // for(countriesMapIterator = countriesMap.begin(); countriesMapIterator != countriesMap.end(); countriesMapIterator++) {
    //     // countryIDTemp = countriesMapIterator->first;
    //     this->territoriesArray[countriesMapIterator->first].head = nullptr;

    //     for(countriesMapItrPtr = countriesMapIterator->second.begin(); countriesMapItrPtr != countriesMapIterator->second.end(); countriesMapItrPtr++) {
    //         continentNameTemp = countriesMapItrPtr->first;
    //         this->territoriesArray[continentNameTemp].continentID = armyTemp;
    //         // continentIDTemp = countriesMapItrPtr->second;
    //     }
    // }

    // for(continentsMapIterator = continentsMap.begin(); continentsMapIterator != continentsMap.end(); continentsMapIterator++) {

    //     for(countriesMapItrPtr = countriesMapIterator->second.begin(); countriesMapItrPtr != countriesMapIterator->second.end(); countriesMapItrPtr++) {
        
    //     }
    // }
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

// Map& Map::operator= (const Map& map) {
//     // check to make sure not assigned to self
//     if(this == &map) return *this;

//     // deallocate used memory
//     for(int i = 0; i < territoryCount; i++) {
//         Edge* currentNode = territoriesArray[i].head;
//         while(currentNode != nullptr) {
//             Edge* tempNode = currentNode->next;
//             delete currentNode;
//             currentNode = tempNode;
//         }
//         delete[] territoriesArray[i].armyCount;
//     }

//     delete[] territoriesArray;
//     territoriesArray = nullptr;

//     // iterate over continents to delete their nodes
//     for(int i = 0; i < continentCount; i++) {
//         Continent* currentContinent = &continentsArray[i];
//         ContinentNode* territoryNode = currentContinent->head;
//         while(territoryNode != nullptr) {
//             ContinentNode* tempNode = territoryNode->next;
//             delete territoryNode;
//             territoryNode = tempNode;
//         }

//         delete[] continentsArray;
//         continentsArray = nullptr;
//     }

//     // reallocate new nodes
//     this->territoryCount = map.territoryCount;
//     this->continentCount = map.continentCount;
    
//     // init continent list
//     this->continentsArray = new Continent[continentCount];
//     for(int i = 0; i < territoryCount; i++) {
//         this->continentsArray[i].head = nullptr;
//         this->continentsArray->length = 0;
//     }

//     // init and copy array of territories
//     this->territoriesArray = new Territory[territoryCount];
//     for(int i = 0; i < territoryCount; i++) {
//         this->territoriesArray[i].continentID = map.territoriesArray[i].continentID;
//         this->territoriesArray[i].continentID = i;
//         // TODO:
//         // this->territoriesArray[i].armyCount = new int[insert where army count is stored]
//         this->territoriesArray[i].armyCount = 0;
//         // for(int j = 0; )

//         Edge* tempEdge = map.territoriesArray[i].head;
//         if(tempEdge != nullptr) {
//             Edge* prevNode = this->territoriesArray[i].head;
//             prevNode = new Edge();
//             // prevNode->adjTerritoryPtr = nullptr;
//             prevNode->adjTerritoryPtr = &territoriesArray[tempEdge->adjTerritoryPtr->territoryID];
//             tempEdge = tempEdge->next;

//             while(tempEdge != nullptr) {
//                 prevNode->next = new Edge();
//                 prevNode->adjTerritoryPtr = &territoriesArray[tempEdge->adjTerritoryPtr->territoryID];
//                 tempEdge = tempEdge->next;
//                 prevNode = prevNode->next;
//             }
//             prevNode->next = nullptr;
//         }

//         // append created territory to continent list
//         this->continentsArray[map.territoriesArray[i].continentID].head = new ContinentNode();
//         this->continentsArray[map.territoriesArray[i].continentID].head->territoryPtr = &this->territoriesArray[i];
//         this->continentsArray[map.territoriesArray[i].continentID].head->next =  continentsArray[map.territoriesArray[i].continentID].head;

//     }

//     return *this;
// }

// void Map::displayAdjacentNodes(Territory territory)
// {
//     Edge* nodePtr = territoriesArray[territory.territoryID].head;

//     while(nodePtr != nullptr) {
        
//     }
// }

//////////////////////////////

// class MapLoader

MapLoader::MapLoader() {
    line = "";
    userIn = "";
    continentCount = 0;
    countryCount = 0;
    count = 0;
}

MapLoader::MapLoader(string fileName) {
    line = "";
    userIn = fileName;
    continentCount = 0;
    countryCount = 0;
    count = 0;
}

void MapLoader::readFile()
{
    // Scan the whole file once to record number of continents and countries
    inputFile.open("./map-files/" + userIn);        // Open stream file

    if (!inputFile) std::cerr << "Could not open the file!" << std::endl;

    if (inputFile.is_open())
    {
        cout << "input file succesfully opened!" << endl;
        while (getline(inputFile, line)) {
            if (line[0] == '[') {
                // to identify continents tag
                if (line[3] == 'n') {
                    getline(inputFile, line); // to skip tag
                    while (!line.empty()) {
                        continentCount++;
                        getline(inputFile, line);
                    }
                }
                // to identify countries tag
                else if(line[3] == 'u') {
                    getline(inputFile, line); // to skip tag
                    while (!line.empty()) {
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

    cout << "countryName array size: " << countryName->capacity() << endl;
    
    // Scan the whole file once to record number of continents and countries
    inputFile.open("./map-files/" + userIn);        // Open stream file

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            if (line[0] == '[') {
                // to identify [file] label
                if (line[1] == 'f') {

                    cout << "found the [files] line" << endl;
                    // to skip label line
                    cout << "SKIPPED: " << line << "\n";
                    getline(inputFile, line); // pic

                    // to skip [file] lines
                    while (line.length() > 2) {
                        // cout << "skip [file] while !line.empty" << endl;
                        cout << "SKIPPED: " << line << "\n";
                        getline(inputFile, line);
                    }
                    cout << "empty line length = " << line.length() << endl;
                }
                // to store [continents]
                else if (line[3] == 'n') {
                    cout << "found a continent line!" << endl;

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
                                // continentName[count] = line.substr(0, i);
                                string var = line.substr(0, i);
                                continentNameVector.push_back(var);
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

                    cout << "found the [countries] line" << endl;

                    // to skip label line
                    cout << endl;
                    cout << "SKIPPED: " << line << "\n";
                    getline(inputFile, line);
                    count = 0; // reset counter

                    // to store countries
                    while (line.length() > 2) {
                        cout << "COUNTRY: " << line << "\n";
                        for (size_t i = 0; i < line.length(); i++) {
                            // cout << "outer loop" << endl;
                            if (line[i] == ' ') {
                                i++;
                                for (size_t j = i; j < line.length(); j++) {
                                    // cout << "inner loop" << endl;
                                    if (line[j] == ' ') {
                                        // assign name of countries
                                        // something about the next line makes me do "j-3", but why?
                                        // cout << "seg fault here" << endl;
                                        cout << "count: " << count << endl;

                                        // countryName[count] = line.substr(i, j-3);
                                        countryNameVector.push_back(line.substr(i, j-3));
                                        // cout << "This is what I get for countryName: \"" << countryName[count] << "\"" << endl;
                                        cout << "This is what I get for countryName: \"" << countryNameVector[count] << "\"" << endl;

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

                    cout << "found the [borders] line" << endl;

                    // to skip label line
                    cout << endl;
                    cout << "seg fault here?" << endl;
                    cout << "SKIPPED: " << line << "\n";
                    
                    getline(inputFile, line);
                    count = 0; // reset counter
                    string lineVar;
                    
                    // to store borders
                    while (line.length() > 2) {
                        cout << "BORDERS: " << line << "\n";

                        for (size_t i = 0; i < line.length(); i++) {
                            if (line[i] == ' ') {
                                // assign name of continent
                                i++;
                                
                                // borders[count] = line.substr(i, line.length());
                                cout << "check error: " << line.substr(1, i) << endl;
                                
                                cout << "vector size: " << bordersVector.size() << endl;
                                cout << "error here?" << endl;
                                cout << "i = " << i << endl;
                                // bordersVector.resize(100);
                                cout << "vector size: " << bordersVector.size() << endl;
                                
                                // lineVar = line.substr(i, line.length());
                                // lineVar = "hi";
                                cout << "before hi!" << endl;
                                // cout << lineVar << endl;

                                bordersVector.push_back(line);

                                cout << "heyaaa" << endl;
                                
                                cout << "This is what I get for borders: \"" << bordersVector.at(i ) << "\"" << endl;
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
}

// To establish connection between countries
//for (size_t i = 0; i < array.length(); i++) {
//    for (size_t j = 0; j < line.length(); j++) {
//        if (line[j] != ' ') {
//            establishConnection(from(i), to(j));
//        }
//    }
//}




// MapLoader Constructor
// MapLoader::MapLoader(string fileName)
// {
//     this->index = 0;
//     this->tempVar = 0;
//     this->players = 0;
//     this->continents = 0;
//     this->territoryCount = 0;
    
//     inputFile.open(fileName);           // open file stream


//     // determine number of players from file

//     // inputFile.close();                  // close file stream

// };

// MapLoader::MapLoader()
// {
//     this->index = 0;
//     this->tempVar = 0;
//     this->players = 0;
//     this->continents = 0;
//     this->territoryCount = 0;

//     this->fileName = "";
//     this->fileStream = "";
//     this->inputLine = "";

//     cout << "Please input file name..." << endl;
// };

// MapLoader::~MapLoader()
// {
//     delete[] territories;
// };

// void MapLoader::readContinents()
// {

// };

// void MapLoader::readTerritories()
// {

// };

// void MapLoader::readBorder()
// {

// };

// void MapLoader::buildMap()
// {

// };

// void MapLoader::readFile(string fileName)
// {
//     inputFile.open(fileName); 
//     // inputFile.open(".\\Maps\\" + userIn);        // Open stream file
//     if (inputFile.is_open())
//     {
//         int data, armies, countryNumber, continentNumber, continentCount = 0, countryCount = 0;
//         string line, continentName, countryName;
//         while(inputFile >> data)
//         {
//             // read line
//             getline(inputFile, line);
//             // check if first character is ';' -> if so, skip line
//             if(line[0] == ';') {
//                 // should skip this whole line
//                 inputFile.ignore(1, '\n');

//             // check if first character is '[' - > if so, indicates a new section
//             } else if(line[0] == '[') {

//                 // check if second character is 'f' -> if so, ignore line
//                 if(line[1] == 'f') {
//                     // should skip this whole line
//                     inputFile.ignore(1, '\n');

//                 // else -> marks the start of important section
//                 } else {
//                     // check if fourth character is 'n' -> if so, indicates beginning of Continents section
//                     if(line[3] == 'n') {
//                         // go to next line
//                         inputFile.ignore(1, '\n');
//                         // begin looping to read continents
//                         while(line[0] != ' ') {
//                             // loop line looking for space
//                             for(int i = 0; i < line.length(); i++) {
//                                 if(line[i] == ' ') {
//                                     // assign name of continent
//                                     continentName = line.substr(0, i-1);
//                                     // assign army count
//                                     armies = line[i+1];
//                                     break;
//                                 }
//                             }

//                             cout << "continent obtained! name = " << continentName << " and army count = " << armies;

//                             // add continent info to map
//                             // should we just call constructor on it and add the object instead?
//                             continentCount++;
//                             continentsMap.insert(make_pair(continentCount, map<string, int>()));
//                             continentsMap[continentCount].insert(make_pair(continentName, armies));
//                             inputFile.ignore(1, '\n');

//                             // read new line
//                             getline(inputFile, line);
//                         }
//                     // else -> indicates beginning of Countries section
//                     } else {
//                         // go to next line
//                         inputFile.ignore(1, '\n');
//                         // begin looping to read countries
//                         while(line[0] != ' ') {
//                             // get countryID
//                             countryNumber = line[0];

//                             // loop line looking for space
//                             for(int i = 2; i < line.length(); i++) {
//                                 if(line[i] == ' ') {
//                                     // assign name of country
//                                     countryName = line.substr(2, i-1);
//                                     // assign army count
//                                     continentNumber = line[i+1];
//                                     break;
//                                 }
//                             }

//                             cout << "country obtained! name = " << countryName << " and it belongs to continent " << continentNumber;

//                             // add continent to map
//                             // should we just call constructor on it and add the object instead?
//                             countryCount++;
//                             countriesMap.insert(make_pair(countryCount, map<string, int>()));
//                             countriesMap[countryCount].insert(make_pair(countryName, continentNumber));
//                             inputFile.ignore(1, '\n');

//                             // read new line
//                             getline(inputFile, line);
//                         }
//                     }
//                 }
//             }
//         }
//         inputFile.close();
//     }
// }