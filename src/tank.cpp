 
#include "services/motorControlService.h"
#include "services/tankDriverService.h" 
#include "constraints/pinsNodeMCU.h"
#include "Arduino.h"
#include "tank.h"

Tank::Tank() {  
      
  tankDriverService = TankDriverService(
    MotorControlService(MOTOR_L_TURN_1_PIN, MOTOR_L_TURN_2_PIN, 0, 1), 
    MotorControlService(MOTOR_R_TURN_1_PIN, MOTOR_R_TURN_2_PIN, 2, 3),
    BATTERY_VOLTAGE_ANALOG);
}

void Tank::begin() { 
  tankDriverService.setup();
}

void Tank::loop() {
  this->currentMillis = millis();
  if (this->isEnabled && (this->currentMillis >= this->previousMillis  + 5)) {
    this->drive();
    this->previousMillis = this->currentMillis;
  }
}
  
void Tank::drive() {
  tankDriverService.drive(controlValuesList[1]/5, controlValuesList[0]/5);
}

// double Tank::readSpeedRight() {
//   double speed = speedController.getSpeedR();
//   Serial.println(speed);
//   return speed;
// }

// double Tank::readSpeedLeft() {
//   double speed = speedController.getSpeedL();
//   Serial.println(speed);
//   return speed;
// }

void Tank::enable() {
  this->isEnabled = true;
}

void Tank::disable() {
  this->isEnabled = false;
}

void Tank::setControlValuesList(int list[DATA_CHANNELS_COUNT]) {
  for(int i = 0; i < (DATA_CHANNELS_COUNT); i++) {
    this->controlValuesList[i] = list[i] - 1500;
  }
}
 