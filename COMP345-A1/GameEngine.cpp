#include "GameEngine.h"
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"

// Final names of other .h files TBD
// #include "Player.h"
// #include "Cards.h"

// Game engine class



GameEngine::GameEngine()
{
    // default constructor

    this->currentState = start;


    this->commandProcessor = new CommandProcessor();
}

GameEngine::GameEngine(string commandsFileName)
{
    // commands filename constructor
    this->currentState = start;

    this->commandProcessor = new FileCommandProcessorAdapter(commandsFileName);
}


GameEngine::GameEngine(const GameEngine& other) {
    cout << "Copy constructor called" << endl;
    currentState = other.currentState;
} // copy constructor for GameEngine

//GameEngine::GameEngine(const GameEngine& gameEngine) {
    // copy constructor
   // currentState = start;
  //  cout << "Game engine copied" << endl;
//}

GameEngine::~GameEngine()
{
    // something here will be a nullptr
    //destructor
    delete this->commandProcessor;
}

//GameEngine& GameEngine::operator = (const GameEngine& gameEngine) {
    // stuff to put here
  //  return *this;
//}

/*ostream& operator << (ostream& out, const GameEngine& gameEngine) {

     stream insertion operator
     out << all things

}*/

void GameEngine::startGame()
{
    do
    {
        /* Get the next command to act on. */
        Command* nextCommand = commandProcessor->getCommand();

        /* Acts on the command. */
        receiveCommand(nextCommand);
    } while (currentState != exitGame);
}

void GameEngine::receiveCommand(Command* command)
{
    //commands are only valid depending on the state I am in

    switch (currentState)
    {
    case start:
        if (command->name.compare("loadMap") == 0)
        {
            // call to loadMap transition
            // loadMap();
            // transition states and update currentState
            currentState = mapLoaded;
            cout << "Current game state is: Map Loaded" << endl;
            command->saveEffect("The map was loaded.");
        }
        else {
            //invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapLoaded:
        if (command->name.compare("validateMap") == 0)
        {
            // call to validateMap transition
            // validateMap();
            // transition states and update currentState
            currentState = mapValidated;
            cout << "Current game state is: Map Validated" << endl;
        }
        else if (command->name.compare("loadMap") == 0)
        {
            // call to issueOrder transition
            // loadMap();
            // transition states and update currentState
            currentState = mapLoaded;
            cout << "Current game state is: Map Loaded" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapValidated:
        if (command->name.compare("addPlayer") == 0)
        {
            // call to validateMap transition
            // addPlayer();
            // transition states and update currentState
            currentState = playersAdded;
            cout << "Current game state is: Players Added" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case playersAdded:
        if (command->name.compare("gameStart") == 0)
        {
            // call to addPlayer transition
            // addPlayer();
            // transition states and update currentState
            currentState = assignReinforcement;
            cout << "Current game state is: Assign Reinforcements" << endl;
        }
        else if (command->name.compare("addPlayer") == 0)
        {
            // call to issueOrder transition
            // addPlayer();
            // transition states and update currentState
            currentState = playersAdded;
            cout << "Current game state is: Players Added " << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case assignReinforcement:
        if (command->name.compare("issueOrder") == 0)
        {
            // call to assignCountries transition
            // assignCountries();
            // transition states and update currentState
            currentState = issueOrders;
            cout << "Current game state is: Issue Orders" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case issueOrders:
        if (command->name.compare("endIssueOrders") == 0)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = executeOrders;
            cout << "Current game state is: Execute Orders" << endl;
        }
        else if (command->name.compare("issueOrder") == 0)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = issueOrders;
            cout << "Current game state is: Issue Orders" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case executeOrders:
        if (command->name.compare("endExecOrders") == 0)
        {
            // call to endIssueOrders transition
            // endIssueOrders();
            // transition states and update currentState
            currentState = assignReinforcement;
            cout << "Current game state is: Assign Reinforcements" << endl;
        }
        else if (command->name.compare("execOrder") == 0)
        {
            // call to execOrder transition
            // execOrder();
            // transition states and update currentState
            currentState = executeOrders;
            cout << "Current game state is: Execute Orders" << endl;
        }
        else if (command->name.compare("winGame") == 0)
        {
            // call to endExecOrders transition
            // endExecOrders();
            // transition states and update currentState
            currentState = win;
            cout << "Current game state is: Win" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case win:
        if (command->name.compare("endGame") == 0)
        {
            // call to exit game
            // transition states and update currentState
            cout << "You have ended the game" << endl;
            currentState = exitGame;
        }
        else if (command->name.compare("playGame") == 0)
        {
            // call to playGame transition
            // start();
            // transition states and update currentState
            currentState = start;
            cout << "Current game state is: Start " << endl;
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
    //validateMap(); // need a reference to the map loaded into loadedMap var?
}
