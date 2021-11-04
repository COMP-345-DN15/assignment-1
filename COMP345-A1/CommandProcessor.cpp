#include <list>
#include "CommandProcessor.h"

using namespace std;

CommandProcessor::CommandProcessor()
{
    // default constructor

}

CommandProcessor::CommandProcessor(const CommandProcessor& commandProcessor)
{
    // copy constructor


}

CommandProcessor::~CommandProcessor()
{
    // something here will be a nullptr
    //destructor

}

CommandProcessor& CommandProcessor::operator = (const CommandProcessor& commandProcessor) {
    // stuff to put here
    return *this;
}

ostream& operator << (ostream& out, const CommandProcessor& commandProcessor) {

    // stream insertion operator
    // out << all things  

}

class CommandProcessor {
    
};



Command::Command()
{
    // default constructor
                    
}

Command::Command(const Command& gameEngine)
{
    // copy constructor

}

Command::~Command()
{
    // something here will be a nullptr
    //destructor

}

Command& Command::operator = (const Command& command) {
    // stuff to put here
    return *this;
}

ostream& operator << (ostream& out, const Command& command) {

    // stream insertion operator
    // out << all things  

}

class Command {

};