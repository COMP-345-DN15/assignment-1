/** 
* The FileCommandProcessorAdapter class
* This is the Adapter class.
* It adapts a readCommand
*/

#include "FileCommandProcessor.h"
#include "CommandProcessor.h"

class FileCommandProcessorAdapter : public FileCommandProcessor {
private:
 CommandProcessor commandProcessor;
public:
      FileCommandProcessorAdapter(CommandProcessor cp) {
           commandProcessor = cp;
    }
     void readCommand(string str) {
          commandProcessor.readCommand(str); // something is wrong about this (maybe)
    }
}