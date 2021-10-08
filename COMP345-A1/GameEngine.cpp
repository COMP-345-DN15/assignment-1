#include "GameEngine.h"

// Final names of other .h files TBD
// #include "Player.h"
// #include "Cards.h"

// Game engine class


GameEngine::GameEngine()
{
    //constructor

    currentState = start;

}

GameEngine::~GameEngine()
{
    //destructor

}

void GameEngine::sendCommand(GameEngineCommand command)
{
    //commands are only valid depending on the state I am in

    switch (currentState)
    {
    case start:
        if (command == GameEngineCommand::loadMap)
        {
            // call to loadMap transition
            // loadMap();
            // transition states and update currentState
            currentState = mapLoaded;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::loadMap] << endl;
        }
        else {
            //invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapLoaded:
        if (command == GameEngineCommand::validateMap)
        {
            // call to validateMap transition
            // validateMap();
            // transition states and update currentState
            currentState = mapValidated;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::validateMap] << endl;
        }
        else if (command == GameEngineCommand::loadMap)
        {
            // call to issueOrder transition
            // loadMap();
            // transition states and update currentState
            currentState = mapLoaded;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::loadMap] << endl;
        }
        else {
           // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapValidated:
        if (command == GameEngineCommand::addPlayer)
        {
            // call to validateMap transition
            // addPlayer();
            // transition states and update currentState
            currentState = playersAdded;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::addPlayer] << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case playersAdded:
        if (command == GameEngineCommand::assignCountries)
        {
            // call to addPlayer transition
            // addPlayer();
            // transition states and update currentState
            currentState = assignReinforcement;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::assignCountries] << endl;
        }
        else if (command == GameEngineCommand::addPlayer)
        {
            // call to issueOrder transition
            // addPlayer();
            // transition states and update currentState
            currentState = playersAdded;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::addPlayer] << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case assignReinforcement:
        if (command == GameEngineCommand::issueOrder)
        {
            // call to assignCountries transition
            // assignCountries();
            // transition states and update currentState
            currentState = issueOrders;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::issueOrder] << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case issueOrders:
        if (command == GameEngineCommand::endIssueOrders)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = executeOrders;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::endIssueOrders] << endl;
        }
        else if (command == GameEngineCommand::issueOrder)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = issueOrders;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::issueOrder] << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case executeOrders:
        if (command == GameEngineCommand::endExecOrders)
        {
            // call to endIssueOrders transition
            // endIssueOrders();
            // transition states and update currentState
            currentState = assignReinforcement;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::endExecOrders] << endl;
        }
        else if (command == GameEngineCommand::execOrder)
        {
                // call to execOrder transition
                // execOrder();
                // transition states and update currentState
                currentState = executeOrders;
                cout << "Current game state is: " << enumStateStr[GameEngineCommand::execOrder] << endl;
        }
        else if (command == GameEngineCommand::winGame)
        {
            // call to endExecOrders transition
            // endExecOrders();
            // transition states and update currentState
            currentState = win;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::winGame] << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case win:
        if (command == GameEngineCommand::endGame)
        {
            // call to exit game
            // transition states and update currentState
            cout << "You have ended the game" << endl;
        }
        else if (command == GameEngineCommand::playGame)
        {
            // call to playGame transition
            // start();
            // transition states and update currentState
            currentState = start;
            cout << "Current game state is: " << enumStateStr[GameEngineCommand::playGame] << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    //case exitGame:
        //if (command == GameEngineCommand::endGame)
        //{
            // call to endGame transition
            // endGame();
            // transition states and update currentStat
            //currentState = exitGame;
            //cout << "Current game state is: " << enumStateStr[GameEngineCommand::endGame] << endl;
        //}
        //else {
            // invalid state transition for current state
            //cout << "A state transition could not be made because the command from this state is invalid." << endl;
        //}
        //break;
     
    default:
        // The command received was not part of valid commands, print error message
        cout << "The command entered is invalid." << endl;
        break;

    }
}

void GameEngine::loadMap(std::string mapName) {
    //does nothing for now
    //Map* loadedMap = mapLoader->loadMap(mapName);

    //maybe add the map to my map array?
    //set the current map to this?
}

void GameEngine::validateMap() {
    // validate map selected by user
    validateMap(); // need a reference to the map loaded into loadedMap var?
}

//void GameEngine::addPlayer()
//{
//    Player* addPlayer  
//}

//void GameEngine::assignCountries()
//{
//    Player* assignCountries = 
//}

//void GameEngine::issueOrder()
//{
//    
//}

//void GameEngine::endIssueOrders()
//{
//    
//}

//void GameEngine::execOrder()
//{
//   
//}

//void GameEngine::endExecOrders()
//{
//    
//}

//void GameEngine::winGame()
//{
//    
//}

//void GameEngine::endGame()
//{
//    
//}

//void GameEngine::start()
//{
//    
//}