 
#include "Arduino.h"
#include "CommandType.h"
#include "Command.h"
 
Command::Command(CommandType _command, int _value) {  
    command = _command;
    value = _value;
}
Command::Command(int _command, int _value) {  
    command = CommandType(_command);
    value = _value;
}

CommandType Command::getType(){
        return command;
}
int Command::getValue(){
        return value;
}

