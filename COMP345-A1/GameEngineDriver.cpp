#include <iostream>
#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "CommandProcessor.h"

using namespace std;

// GameEngine Driver

void printErrorArgumentsMsg()
{
	cout << "You must specify commands come from console or file exactly like this." << endl;
	cout << "-console or -file <filename>" << endl;
}

void testGameEngine(int argc, char* argv[])
{
	cout << "===================" << endl;
	cout << "Welcome to Warzone" << endl;
	cout << "===================\n" << endl;

	/* Parse the command line arguments to know if we are reading game commands from the console or a file. */

	
	if (argc < 2) {
		printErrorArgumentsMsg();
		return;
	}

	string firstArgument = argv[1];
	GameEngine* gameEngine;

	if (firstArgument.compare("-console") == 0) {
		//we are running the app with cmds from console

		//create GameEngine with no file.

		gameEngine = new GameEngine();
	}
	else if (firstArgument.compare("-file") == 0) {

		if (argc < 3) {
			printErrorArgumentsMsg();
			return;
		}

		string commandsFileName = argv[2];

		//we should check that this file exists...

		//create gameEngine with file
		gameEngine = new GameEngine(commandsFileName);
	}
	else {
		printErrorArgumentsMsg();
		return;
	}

	//game engine created, continue

	gameEngine->startGame();

	delete gameEngine;
}


