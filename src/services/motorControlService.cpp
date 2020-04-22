 
#include "Arduino.h"
#include "../constraints/propperties.h"
#include "motorControlService.h"

void MotorControlService::setup() {
	ledcAttachPin(input1, channel1);
	ledcAttachPin(input2,channel2);
	ledcSetup(channel1, freq, resolution);
	ledcSetup(channel2, freq, resolution);
	// stop();
}

void MotorControlService::setSpeed(int speed) {
	bool direction = speed > 0;
	speed = abs(speed);
	drive(direction, speed); //max speed Arduino: 255 ESP:1024
}

void MotorControlService::stop() {
	digitalWrite(input1, LOW);
	digitalWrite(input2, LOW);
}

void MotorControlService::neutral() {
	drive(true, 0);
}

void MotorControlService::drive(boolean isForward, int speed = 1024) {
	stop();
	if(isForward) {
		// Serial.print("+");
	    ledcWrite(channel2, 0);
	    ledcWrite(channel1, speed);
	} else {
		// Serial.print("-");
	    ledcWrite(channel1, 0);
	    ledcWrite(channel2, speed);
	}
	// Serial.println(speed);
}
 
