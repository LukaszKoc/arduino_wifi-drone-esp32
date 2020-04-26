
#include "Arduino.h"
#include "constraints/pinsNodeMCU.h"
#include "services/speedControlService.h"
#include "tankDriverService.h"


SpeedControlService speedController = SpeedControlService(MOTOR_L_SPEED_SENSOR_1, MOTOR_L_SPEED_SENSOR_2, MOTOR_R_SPEED_SENSOR_1, MOTOR_R_SPEED_SENSOR_2);

void TankDriverService::setup() {
	// pinMode(bateryVoltagePin, INPUT);
	speedController.setup();
	motorLeft.setup();
	motorRight.setup();
	dataUpdateTime = millis();
}

void TankDriverService::loop() {
	if((millis() - dataUpdateTime ) > dataUpdateFrequency) {
		if(drivingStrait && (speedL != 0 && speedR != 0)) {
			radiusColtroll();
		}
		drivingControl();
		dataUpdateTime = millis();
	}	
}
 
float TankDriverService::getBateryVoltage() {
	return bateryVoltage;
}

float TankDriverService::getDrivenDistance() {
	return speedController.getTotalDistance();
}

void TankDriverService::driveStrait(int speed) {
	speedController.clearDistance();
	drivingStrait = true;
	setSpeedL(speed);
	setSpeedR(speed);
}

void TankDriverService::turn(int radius, int speed ) {
	speedController.clearDistance();
	drivingStrait = true;
	setStopRules((double)radius, (double)radius);
	setSpeedL(-speed);
	setSpeedR(speed);
}
void TankDriverService::drive(int y, int x) {
	int speedRight, speedLeft;
	speedLeft = y;
	speedRight = y;
	
	if(x > 30) {
		speedLeft = -25;
		speedRight = 25;
	} else if(x < -30) {
		speedLeft = 25;
		speedRight = -25;
	}
	if(x > 50) {
		speedLeft = -50;
		speedRight = 50;
	} else if(x < -50) {
		speedLeft = 50;
		speedRight = -50;
	}
	if(x > 70) {
		speedLeft = -100;
		speedRight = 100;
	} else if(x < -70) {
		speedLeft = 100;
		speedRight = -100;
	}

	setSpeedL(speedLeft);
	setSpeedR(speedRight);
}
void TankDriverService::setStopRules(double distanceL, double distanceR){
	stopRuleL = abs(speedController.getDistanceL() + distanceL);
	stopRuleR = abs(speedController.getDistanceR() + distanceR);
}
void TankDriverService::drivingControl() {
	stopSontroll();
	motorLeft.setSpeed(mapSpeed(speedL));
	motorRight.setSpeed(mapSpeed(speedR));
}

void TankDriverService::stopSontroll() {
	if(speedL != 0 && abs(speedController.getDistanceL()) >= stopRuleL ) {
		setSpeedL(0);
		drivingStrait = false;
		// Serial.println(String("stop rule activated L: "));
		// Serial.println(String("disctanceL: ") + speedController.getDistanceL());
		// Serial.println(String("disctanceR: ") + speedController.getDistanceR());
	}
	if(speedR != 0 && abs(speedController.getDistanceR()) >= stopRuleR ) {
		setSpeedR(0);
		drivingStrait = false;
		// Serial.println(String("stop rule activated R: "));
	}
}

void TankDriverService::radiusColtroll() {
	double distanceL = speedController.getDistanceL();
	double distanceR = speedController.getDistanceR();
	Serial.println(String("disctanceL: ") + speedController.getDistanceL());
	Serial.println(String("disctanceR: ") + speedController.getDistanceR());

	double distanceDifference = abs(distanceL) - abs(distanceR);
	if(abs(distanceDifference) >= 0.1 ) {
		Serial.println(String("distanceDifference:  ") + distanceDifference);
		Serial.println(String("setSpeed L: ") + speedL);
		Serial.println(String("setSpeed R: ") + speedR);
		
		if(abs(distanceL) > abs(distanceR)) { //lekko w prawo
			setSpeedL(speedL + (speedL/abs(speedL)*1));
			setSpeedR(speedR - (speedR/abs(speedR)*1));
		} else {  //lekko w lewo 
			setSpeedL(speedL - (speedL/abs(speedL)*1));
			setSpeedR(speedR + (speedR/abs(speedR)*1));
		}
	}
}

void TankDriverService::setSpeedL(int speed) {
	if(speed > MAX_SPEED_INDICATOR ) speed = MAX_SPEED_INDICATOR;
	if(speed < -MAX_SPEED_INDICATOR ) speed = -MAX_SPEED_INDICATOR;
	if(abs(speed)< 80) speed = 0;
	speedL = speed;
}

void TankDriverService::setSpeedR(int speed) {
	if(speed > MAX_SPEED_INDICATOR ) speed = MAX_SPEED_INDICATOR;
	if(speed < -MAX_SPEED_INDICATOR ) speed = -MAX_SPEED_INDICATOR;
	if(abs(speed)< 80) speed = 0;
	speedR = speed;
}

int TankDriverService::mapSpeed(int speed) {
	if(speed < 0) {
		return - map(-speed, 0, MAX_SPEED_INDICATOR, 0, DC_PWM_RANGE);
	} else {
		return  map(speed, 0, MAX_SPEED_INDICATOR, 0, DC_PWM_RANGE);	
	}	
}

void TankDriverService::stop() {
	drivingStrait = false;
	motorLeft.stop();
	motorRight.stop();
}
void TankDriverService::neutral() {
	drivingStrait = false;
	motorLeft.neutral();
	motorRight.neutral();
}
  