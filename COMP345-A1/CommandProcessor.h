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

	void saveEffect(string effect); // saves the current statee of the game as an effect of the command

	string name;
	string effect;
};

class CommandProcessor {
private:
	vector<Command*> commands; // contains a pointer to a collection of Command objects
	vector<Command*> validCommands;
	Command* invalidCommand;
public:
	CommandProcessor(); // default constructor
	~CommandProcessor(); // destructor

	Command* getCommand();

	friend ostream& operator<<(ostream& out, const CommandProcessor& cp);

protected:
	virtual Command* readCommand();
	void saveCommand(Command* command); // stores all commands and effects into a list
	bool validate(string);
};
