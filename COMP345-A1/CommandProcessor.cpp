#include "CommandProcessor.h"
#include <vector>

using namespace std;

Command::Command(string name, string effect)
{
	this->name = name;
	this->effect = effect;
}

Command::~Command()
{

}

CommandProcessor::CommandProcessor()
{
     
	/* Create a list of all valid commands that can be played. */

	//validCommands = new vector<Command>();

	validCommands.push_back(Command("loadMap", "TODO"));
	validCommands.push_back(Command("validateMap", "TODO"));
	validCommands.push_back(Command("addPlayer", "TODO"));
	validCommands.push_back(Command("assignCountries", "TODO"));
	validCommands.push_back(Command("issueOrder", "TODO"));
	validCommands.push_back(Command("endIssueOrders", "TODO"));
	validCommands.push_back(Command("execOrder", "TODO"));
	validCommands.push_back(Command("endExecOrders", "TODO"));
	validCommands.push_back(Command("winGame", "TODO"));
	validCommands.push_back(Command("endGame", "TODO"));
	validCommands.push_back(Command("playGame", "TODO"));

}

CommandProcessor::~CommandProcessor()
{
	//delete validCommands;
	//free each command in the validCommands vector
}

/*
* The GameEngine calls this function to get the next commands to act on.
*/
Command CommandProcessor::getCommand() {

    /* Get a command from the console or a file. */

    Command nextCommand = readCommand();

    /* Save the command to the list of commands. */

    saveCommand(nextCommand);

    return nextCommand;
}

/*
* Save the command to the commands list.
*/
void CommandProcessor::saveCommand(Command command)
{
    commands.push_back(command);
}

Command CommandProcessor::getCommandFromString(string commandInput)
{
	for (int i = 0; i < validCommands.size(); i++) {
		if (commandInput.compare(validCommands[i].name) == 0)
			return validCommands[i];
	}

	return Command("invalid", "invalid");
}

/*
* Return the next command, either from a text from or from the keyboard.
*/
Command CommandProcessor::readCommand() {

	//for now we are only reading the commands from the keyboard.
	//this function needs to be adapted to read the commands from the file with the FLR.

	/* Read command from keyboard. */

	Command nextCommand = Command("invalid", "invalid");

	do {
		cout << "Enter the next command: " << endl;
		string userInput;
		cin >> userInput;
		nextCommand = getCommandFromString(userInput);
	} while (nextCommand.name.compare("invalid") == 0);

	return nextCommand;
}
