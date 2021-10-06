#pragma once
#include <iostream>

using namespace std;

enum GameEngineCommand { invalidCommand, loadMap, validateMap, addPlayer, assignCountries, issueOrder, endIssueOrders, execOrder, endExecOrders, winGame, endGame, playGame };

enum GameEngineState { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win, exitGame };
static const char* enumStateStr[] = { "Start", "Map loaded", "Map validated", "Players added", "Assigned reinforcement", "Issue orders", "Execute orders", "Execute orders", "Assign reinforcement", "Win game", "Exit game", "Start" };

class GameEngine {

// private members
private:

	GameEngineState currentState;
	void loadMap(std::string mapName);
	// void addPlayer;
	// void assignCountries;
	// void issueOrder;
	// void endIssueOrders;
	// void execOrder;
	// void endExecOrders;
	// void winGame;
	// void endGame;
	// void playGame;

// public members
public:

	GameEngine(); // constructor for the GameEngine
	~GameEngine(); // destructor for the GameEngine
	void sendCommand(GameEngineCommand command);
	void validateMap();

	// stream operator if necessary
	friend ostream& operator<<(ostream& out, const GameEngine& ge);

};
