#include "GameEngine.h"

// Final names of other .h files TBD
// #include "Player.h"
// #include "Cards.h"
// #include "MapLoader.h"

// Game engine class


GameEngine::GameEngine()
{
    //constructor

    currentState = start;

    mapLoader = new MapLoader();
}

GameEngine::~GameEngine()
{
    //destructor

    delete mapLoader;
}

void GameEngine::sendCommand(GameEngineCommand command)
{
    //commands are only valid depending on the state I am in

    switch (currentState)
    {
    case start:
        if (command == GameEngineCommand::loadMap)
        {
            //loadMap();
            currentState = mapLoaded;
        }
        if (command == GameEngineCommand::validateMap)
        {
            //validateMap();
            currentState = mapValidated;
        }
        if (command == GameEngineCommand::addPlayer) 
        {
            //addPlayer();
            currentState = playersAdded;
        }
        break;
    default:
        //invalid command
        break;

    }
}

void GameEngine::loadMap(std::string mapName) {
    //does nothing for now
    Map* loadedMap = mapLoader->loadMap(mapName);

    //maybe add the map to my map array?
    //set the current map to this?
}

void GameEngine::validateMap() {
    // validate map selected by user
    validateMap(); // need a reference to the map loaded into loadedMap var?
}

//void GameEngine::addPlayer()
//{
//    Player* addPlayer = 
//}

