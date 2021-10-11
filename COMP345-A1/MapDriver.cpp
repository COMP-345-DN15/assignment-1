#include <iostream>		// used for cin & cout
#include "Map.h"
//#include "Map.cpp"

using namespace std;

int main()
{
    cout << "starting program" << endl;
    MapLoader* testObject = new MapLoader("WoW.map");
    delete testObject;

    return 0;
}
