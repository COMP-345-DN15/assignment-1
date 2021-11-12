#include <iostream>		// used for cin & cout
//#include <dirent.h>
//#include <sys/types.h>
#include "Map.h"
//#include "Map.cpp"

using namespace std;

//int main()
//{
//    cout << "starting program" << endl;
//    MapLoader* testObject = new MapLoader("WoW.map");
//    delete testObject;
//
//    return 0;
//}

void testMap() {

    cout << "starting Map test..." << endl;
    
   // WOW Map
    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/WoW.map");
    
    // TODO: ISSUE -> completes but says map is not valid
    // LOTR2 Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/LOTR2.map");
    
    // Solar Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/solar.map");
    
    // Cow Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/cow.map");
    
    // Canada Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/canada.map");
    
    // sw_baltic Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/sw_baltic.map");
    
    // bigeurope Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/bigeurope.map");
    
    // artic Map (lol)
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/artic.map");
    
    // europass Map
    //MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/europass.map");
    
    // europe Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/europe.map");
    
    // google Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/google.map");
    
    // MiddleEast-Qatar Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/MiddleEast-Qatar.map");
    
    // sudamerica Map
//    MapLoader* testObject = new MapLoader("/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/sudamerica.map");
    
    
    delete testObject;

}

void getMapNames() {
    
    // Path name -> must be set to correct local path directory containing map files
    //string path = "/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/";
    
//    struct dirent *entry;
//    DIR *dir = opendir(path);
//
//    if(dir == NULL){
//        return;
//    }
//
//    while((entry = readdir(dir)) != NULL) {
//        cout << entry->d_name << endl;
//    }
//    closedir(dir);
    
    //for(const auto & entry : std::filesystem::directory_iterator(path)) {
        //string entryPath = entry.path();
        //string mapName = entryPath.substr(95, entryPath.length());
        //cout << mapName << endl;
   // }
}

