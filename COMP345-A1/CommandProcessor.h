#pragma once
#include <iostream>

using namespace std;

class CommandProcessor {
private:
	list<Command*> commandsList; // contains a pointer to a collection of Command objects

public:
	CommandProcessor(); // default constructor
	~CommandProcessor(); // destructor

	void readCommand(Command commandToRead) {
		string commandstr;
		cin >> commandstr;
	};
	void getCommand() {
		readCommand();
		saveCommand(); // stores all commands and effects into a list
	};
	void validate(); // verifies that the command in process is a valid game command

	friend ostream& operator<<(ostream& out, const CommandProcessor& ge);

};

class Command {
private:
public:
	Command(); // default constructor
	~Command(); // destructor
	void saveEffect(); // saves the current statee of the game as an effect of the command
	string command;
	string effect;

};