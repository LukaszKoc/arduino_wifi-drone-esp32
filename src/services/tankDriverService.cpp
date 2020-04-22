
#include "Arduino.h"
#include "tankDriverService.h"

void TankDriverService::setup() {
	pinMode(bateryVoltagePin, INPUT);
	dataUpdateTime = millis();
	motorLeft.setup();
	motorRight.setup();
}

void TankDriverService::loopAction() {

  if(millis() > dataUpdateTime + 5) {
    dataUpdateTime = millis();
		if(samplesToGet  == 0) {
		    bateryVoltage =  (sampleSumValue / SAMPLES_COUNT) * 
		    		(REFERENCE_VCC / 4095.0) * CALIBRATION_INDICATOR;
			samplesToGet = SAMPLES_COUNT;
			sampleSumValue = 0;
		} else {
			sampleSumValue += analogRead(bateryVoltagePin);
			samplesToGet --;
		}
	}
}
 
float TankDriverService::getBateryVoltage() {
	return bateryVoltage;
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
  