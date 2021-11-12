/** 
* The FileCommandProcessorAdapter class
* This is the Adapter class.
* It adapts a readCommand
*/

#include "FileLineReader.h"
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string commandsFileName)
{
    this->fileLineReader = new FileLineReader(commandsFileName);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete this->fileLineReader;
}

Command* FileCommandProcessorAdapter::readCommand()  {

    string nextLine = "invalid";

    do {

        nextLine = fileLineReader->readLineFromFile();

    } while (!validate(nextLine));
    

    return new Command(nextLine, "");
}