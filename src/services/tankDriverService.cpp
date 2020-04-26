
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
	if(stedyDriving && (dataUpdateTime  + dataUpdateFrequency) > millis()) {
		radiusColtroll();
		dataUpdateTime = millis();
	}	
}
 
float TankDriverService::getBateryVoltage() {
	return bateryVoltage;
}

float TankDriverService::getDrivenDistance() {
	Serial.println(String("Distance  : ") + speedController.getDistance());
	Serial.println(String("Distance L: ") + speedController.getDistanceL());
	Serial.println(String("Distance R: ") + speedController.getDistanceR());
	return speedController.getDistance();
}

void TankDriverService::driveStrait(int speed) {
	fixedSpeed = speed;
	stedyDriving = true;
	speed = mapSpeed(speed);
	motorLeft.setSpeed(speed);
	motorRight.setSpeed(speed);
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

	speedLeft = mapSpeed(speedLeft);
	speedRight = mapSpeed(speedRight);
	motorLeft.setSpeed(speedLeft);
	motorRight.setSpeed(speedRight);
}


void TankDriverService::radiusColtroll() {
	double distanceL = speedController.getDistanceL();
	double distanceR = speedController.getDistanceR();
	double speedDiference = distanceL - distanceR;
	if(abs(speedDiference) >= 0.5 ) {
		double speedUpdate = fixedSpeed / 200 * 5 * speedDiference;
		Serial.println(String("speed correction about") + speedUpdate);
		if(speedDiference > 0) //lekko w lewo 
			stedyDrive(fixedSpeed - speedUpdate, fixedSpeed + speedUpdate);
		else  //lekko w prawe 
			stedyDrive(fixedSpeed + speedUpdate, fixedSpeed - speedUpdate);
	}
}

void TankDriverService::stedyDrive(int speedLeft, int speedRight) {
	stedyDriving = true;
	speedLeft = mapSpeed(speedLeft);
	speedRight = mapSpeed(speedRight);
	motorLeft.setSpeed(speedLeft);
	motorRight.setSpeed(speedRight);
}

int TankDriverService::mapSpeed(int speed) {
	if(speed < 0) {
		return - map(-speed, 0, 100, 0, DC_PWM_RANGE);
	} else {
		return  map(speed, 0, 100, 0, DC_PWM_RANGE);	
	}	
}

void TankDriverService::stop() {
	motorLeft.stop();
	motorRight.stop();
}
void TankDriverService::neutral() {
	motorLeft.neutral();
	motorRight.neutral();
}
  