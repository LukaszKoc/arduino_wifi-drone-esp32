#ifndef DriveCommandExecutor_h
#define DriveCommandExecutor_h 

#include "Arduino.h"
#include "MotorControlService.h"
#include "tankDriverService.h" 
#include "./model/Command.h"

class DriveCommandExecutor {
	private:
		int maxSpeed = 25;
		TankDriverService *tankDriver;
		void right(int radius);
		void left(int radius);
		void forward(int distance);
		void backward(int distance);
		void stop();
	public:
		void begin();
		void setTankDriver(TankDriverService& _tankDriver);
		boolean actionListner(CommandType type, int value);
}; 
#endif 