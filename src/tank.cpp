 
#include "services/MotorControlService.h"
#include "services/TankDriverService.h"
#include "constraints/PinsNodeMCU.h"
#include "Arduino.h"
#include "tank.h"

Tank::Tank() {  
  tankDriverService = TankDriverService(MotorControlService(MOTOR_L_TURN_1_PIN, MOTOR_L_TURN_2_PIN), MotorControlService(MOTOR_R_TURN_1_PIN, MOTOR_R_TURN_2_PIN), BATTERY_VOLTAGE_ANALOG);
}

void Tank::begin() { 
  tankDriverService.setup();
}

void Tank::loop() {
  this->currentMillis = millis();
  if (this->isEnabled && (this->currentMillis - this->previousMillis >= DATA_CHANNELS_COUNT)) {
    this->drive();
    this->previousMillis = this->currentMillis;
  }
}
  
void Tank::drive() {
  for(int i = 0; i< DATA_CHANNELS_COUNT; i++) {
      Serial.print(String(this->controlValuesList[i]) + "\t\t");
  }
  Serial.println();
}

void Tank::enable() {
  this->isEnabled = true;
}

void Tank::disable() {
  this->isEnabled = false;
}

void Tank::setControlValuesList(int list[DATA_CHANNELS_COUNT]) {
  for(int i = 0; i < (DATA_CHANNELS_COUNT); i++) {
    this->controlValuesList[i] = list[i];
  }
}
