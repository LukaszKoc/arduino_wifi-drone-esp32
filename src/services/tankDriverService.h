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
		int bateryVoltagePin;
		boolean singleJoystickMode;
		float sampleSumValue = 0.0;
		int samplesToGet = SAMPLES_COUNT;
		float bateryVoltage; 
		boolean drivingStrait = false;
		unsigned long fixedSpeed;
		unsigned long dataUpdateTime;
		unsigned long dataUpdateFrequency = 100;
		double stopRuleL = 0; 
		double stopRuleR = 0;
		double lastDistanceL = 0;
		double lastDistanceR = 0;
		int speedL = 0; 
		int speedR = 0;
		void radiusColtroll();
		void drivingControl();
		void stopSontroll();
		void setSpeedL(int speed);
		void setSpeedR(int speed);
	public:
		int static const MAX_SPEED_INDICATOR = 1000;
		void setStopRules(double distanceL, double distanceR);
		float getDrivenDistance();
		float getBateryVoltage();
		void drive(int x, int y);
		void drive(int speed);
		void turn(int radius, int speed);
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