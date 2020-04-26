 
#ifndef Command_h
#define Command_h

#include "CommandType.h"

class Command {
  public: 
    Command(String command, int value);
    Command(CommandType command, int value);
    Command(int command, int value);
    Command();
    CommandType getType();
    int getValue();
private: 
    CommandType command;
    int value;
    CommandType parse (String command);
};

#endif