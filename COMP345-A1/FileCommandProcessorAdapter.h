#pragma once

#include "FileLineReader.h"
#include "CommandProcessor.h"

class FileCommandProcessorAdapter : public CommandProcessor {
private:
	FileLineReader fileLineReader;
	CommandProcessor commandProcessor;
public:
	FileCommandProcessorAdapter();
	void readCommand(string);
};