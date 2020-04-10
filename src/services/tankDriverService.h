#ifndef TankDriverService_h
#define TankDriverService_h 

#include "Arduino.h"
#include "MotorControlService.h"

class TankDriverService {
	private:
		MotorControlService motorLeft, motorRight;
		int speedL, speedR, bateryVoltagePin;
		boolean singleJoystickMode;
		float sampleSumValue = 0.0;
		int samplesToGet = SAMPLES_COUNT;
		float bateryVoltage; 
		unsigned long dataUpdateTime;
	public:
		float getBateryVoltage();
		void drive(int x, int y);
		void stop();
		void setup();
		void loopAction();
		void neutral();
		int mapSpeed(int speed);
		TankDriverService(){};
		TankDriverService(
					MotorControlService _motorLeft, 
					MotorControlService _motorRight, 
					int _bateryVoltagePin, 
					boolean _singleJoystickMode = true) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
			bateryVoltagePin = _bateryVoltagePin;
			singleJoystickMode = _singleJoystickMode;
		}
};
 
#endif