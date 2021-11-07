#include <iostream>
#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "CommandProcessor.h"

using namespace std;

// GameEngine Driver



void testGameEngine()
{
	cout << "===================" << endl;
	cout << "Welcome to Warzone" << endl;
	cout << "===================\n" << endl;
	cout << "Testing game engine\n" << endl;

	GameEngine* gameEngine = new GameEngine();

	gameEngine->startGame();

	delete gameEngine;
}


