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

void Command::saveEffect(string effect) {
	this->effect = effect;
}

CommandProcessor::CommandProcessor()
{
	/* Create a list of all valid commands that can be played. */

	validCommands.push_back(new Command("loadMap", ""));
	validCommands.push_back(new Command("validateMap", ""));
	validCommands.push_back(new Command("addPlayer", ""));
	validCommands.push_back(new Command("gameStart", ""));
	validCommands.push_back(new Command("issueOrder", ""));
	validCommands.push_back(new Command("endIssueOrders", ""));
	validCommands.push_back(new Command("execOrder", ""));
	validCommands.push_back(new Command("endExecOrders", ""));
	validCommands.push_back(new Command("winGame", ""));
	validCommands.push_back(new Command("endGame", ""));
	validCommands.push_back(new Command("playGame", ""));

	invalidCommand = new Command("invalid", "invalid");
}

CommandProcessor::~CommandProcessor()
{
	for (int i = 0; i < commands.size(); i++) {
		delete commands[i];
	}

	for (int i = 0; i < validCommands.size(); i++) {
		delete validCommands[i];
	}

	delete invalidCommand;
}

/*
* The GameEngine calls this function to get the next commands to act on.
*/
Command* CommandProcessor::getCommand() {

    /* Get a command from the console or a file. */

    Command* nextCommand = readCommand();

    /* Save the command to the list of commands. */

    saveCommand(nextCommand);

    return nextCommand;
}

/*
* Save the command to the commands list.
*/
void CommandProcessor::saveCommand(Command* command)
{
    commands.push_back(command);
}

bool CommandProcessor::validate(string commandInput)
{
	for (int i = 0; i < validCommands.size(); i++) {
		if (commandInput.compare(validCommands[i]->name) == 0)
			return true;
	}

	return false;
}

/*
* Return the next command, either from a text from or from the keyboard.
*/
Command* CommandProcessor::readCommand() {

	/* Read command from keyboard. */

	string userInput = "invalid";

	do {

		cout << "Enter the next command: " << endl;
		cin >> userInput;

	} while (!validate(userInput));


	return new Command(userInput, "");
}
