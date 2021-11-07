#pragma once
#include <iostream>
#include <vector>
#include <map>	

using namespace std;



class Command {
private:
public:
	Command(string name, string effect);
	~Command(); // destructor

	void saveEffect(); // saves the current statee of the game as an effect of the command

	string name;
	string effect;

	
};

class CommandProcessor {
private:
	vector<Command> commands; // contains a pointer to a collection of Command objects
	vector<Command> validCommands;

public:
	CommandProcessor(); // default constructor
	~CommandProcessor(); // destructor

	Command getCommand();
	void validate(); // verifies that the command in process is a valid game command

	friend ostream& operator<<(ostream& out, const CommandProcessor& cp);

protected:
	Command readCommand();
	void saveCommand(Command command); // stores all commands and effects into a list
	Command getCommandFromString(string);
};


