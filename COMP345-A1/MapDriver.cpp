#include <iostream>		// used for cin & cout
#include "Map.h"
//#include "Map.cpp"

using namespace std;

//int main()
//{
//    cout << "starting program" << endl;
//    MapLoader* testObject = new MapLoader("WoW.map");
//    testObject->readFile();
//
//    cout << testObject->countryCount << " " << testObject->continentCount << endl;
//    cout << testObject->continentName[0] << " " << testObject->continentName[1] << " " << endl;
//    cout << testObject->armies[0] << " " << testObject->armies[1] << " " << endl;
//
//    Map* mapTest = new Map(testObject, testObject->countryIn);
//    
//    mapTest->transferTerritories(testObject->getContinentIDArray(), testObject->getCountryArray());
//
//    testObject->makeConnections(mapTest);
//    
//    if(mapTest->validate() == true) {
//        cout << "valid map detected!" << endl;
//    }
//
//    cout << "This is a valid map: " << mapTest->validate() << endl;
//
//    delete mapTest;
//    delete testObject;
//
//    return 0;
//}


void testMap() {

    cout << "starting program" << endl;
    MapLoader* testObject = new MapLoader("WoW.map");
    testObject->readFile();

    cout << testObject->countryCount << " " << testObject->continentCount << endl;
    cout << testObject->continentName[0] << " " << testObject->continentName[1] << " " << endl;
    cout << testObject->armies[0] << " " << testObject->armies[1] << " " << endl;

    Map* mapTest = new Map(testObject, testObject->countryIn);

    mapTest->transferTerritories(testObject->getContinentIDArray(), testObject->getCountryArray());

    testObject->makeConnections(mapTest);

    if (mapTest->validate() == true) {
        cout << "valid map detected!" << endl;
    }

    cout << "This is a valid map: " << mapTest->validate() << endl;

    delete mapTest;
    delete testObject;

}