#include "Arduino.h"
#include "DriveCommandExecutor.h"
#include "tankDriverService.h" 
#include "./model/Command.h" 
 
void DriveCommandExecutor::begin() {
}

boolean DriveCommandExecutor::actionListner(CommandType type, int value) {
 
	Serial.println(String("comand type: ") + type);
	Serial.println();
	switch(type) {
		case STOP: { 
	     	stop();
			 return true; 
		}
		break;
		case FORWARD: {  
			forward(value); 
			 return true;
			}
	 	break;
	  	case BACKWARD: {   
	  		backward(value);
			 return true;
			  }
		break;
		case RIGHT: {  
			right(value); 
			 return true;
			}
		break;
		case LEFT: { 
			left(value);   
			 return true; 
			}
		break;       
	  }
	  return false;
}

void DriveCommandExecutor::stop(){
	tankDriver->neutral();
	Serial.println("Stop\n"); 
}

void DriveCommandExecutor::right(int radius){
	tankDriver->turn(radius, maxSpeed);
	Serial.println(String("Rotate Right ") + radius);
}

void DriveCommandExecutor::left(int radius){
	tankDriver->turn(-radius, maxSpeed);
	Serial.println(String("Rotate Left ") + radius);
}

void DriveCommandExecutor::forward(int distance) {
	Serial.println(String("Forward") + distance);
	tankDriver->setStopRules(distance, distance);
	tankDriver->driveStrait(maxSpeed);
	Serial.println(String("distance: ") + tankDriver->getDrivenDistance());
}

void DriveCommandExecutor::backward(int distance) {
	Serial.println(String("Backward") + distance);
}

void DriveCommandExecutor::setTankDriver(TankDriverService& _tankDriver) {
	this->tankDriver = &_tankDriver;
}
