#pragma once
#include <iostream>
#include "CommandProcessor.h"

using namespace std;

enum GameEngineState { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win, exitGame };
//static const char* enumStateStr[] = { "Start", "Map loaded", "Map validated", "Players added", "Assigned reinforcement", "Issue orders", "Execute orders", "Execute orders", "Assign reinforcement", "Win game", "Exit game", "Start" };

class GameEngine {

private:

	GameEngineState currentState;
	CommandProcessor commandProcessor;
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

public:

	// constructors, assignment operator, destructor
	GameEngine(); // constructor for the GameEngine
	GameEngine(const GameEngine& args);
	~GameEngine(); // destructor for the GameEngine
	GameEngine& operator= (const GameEngine& other) {
		cout << "Assignment operator called" << endl;
		return *this;
	}; // assignment operator for GameEngine
	
	void startGame();

	void receiveCommand(Command command);
	void validateMap();

	// stream operator if necessary
	friend ostream& operator<<(ostream& out, const GameEngine& ge);

};
