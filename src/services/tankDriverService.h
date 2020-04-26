#ifndef TankDriverService_h
#define TankDriverService_h 

#include "Arduino.h"
#include "MotorControlService.h"
// #include "constraints/pinsNodeMCU.h"
// #include "services/speedControlService.h"

class TankDriverService {
	private:
		MotorControlService motorLeft, motorRight; 
		// SpeedControlService speedController;
		int speedL, speedR, bateryVoltagePin;
		boolean singleJoystickMode;
		float sampleSumValue = 0.0;
		int samplesToGet = SAMPLES_COUNT;
		float bateryVoltage; 
		boolean stedyDriving = false;
		unsigned long fixedSpeed;
		unsigned long dataUpdateTime;
		unsigned long dataUpdateFrequency = 50;
		void radiusColtroll();
		void stedyDrive(int speedLeft, int speedRight);
	public:
		float getDrivenDistance();
		float getBateryVoltage();
		void drive(int x, int y);
		void driveStrait(int speed);
		void stop();
		void setup();
		void loop();
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
			// speedController = SpeedControlService(MOTOR_L_SPEED_SENSOR_1, MOTOR_L_SPEED_SENSOR_2, MOTOR_R_SPEED_SENSOR_1, MOTOR_R_SPEED_SENSOR_2);
		}
};
 
#endif