 
#include "services/motorControlService.h"
#include "services/tankDriverService.h" 
#include "services/DriveCommandExecutor.h" 
#include "constraints/pinsNodeMCU.h"
#include "Queue.h"
#include "Arduino.h"
#include "tank.h"
#include <LinkedList.h>
// QueueArray<&Command> commands = QueueArray<&Command>(20);

LinkedList<Command*> commands = LinkedList<Command*>();
Tank::Tank() {
    tankDriverService = TankDriverService(
    MotorControlService(MOTOR_L_TURN_1_PIN, MOTOR_L_TURN_2_PIN, 0, 1), 
    MotorControlService(MOTOR_R_TURN_1_PIN, MOTOR_R_TURN_2_PIN, 2, 3),
    BATTERY_VOLTAGE_ANALOG);

}

void Tank::begin() { 
  tankDriverService.setup();
  remoteDriver.setTankDriver(tankDriverService);
  remoteDriver.begin();
}

void Tank::loop() {
  tankDriverService.loop();
  this->currentMillis = millis();
  // if (this->isEnabled && (this->currentMillis >= this->previousMillis  + 5)) {
  //   this->drive();
  //   this->previousMillis = this->currentMillis;
  // }
  if(commands.size() > 0) {
    if(remoteDriver.actionListner(commands.get(0)->getType(), commands.get(0)->getValue())) {
      commands.remove(0);
    }
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

int Tank::putCommand(CommandType command, int value){
  
    Serial.println(String(command) + " " + value);
  commands.add(new Command(command, value));
  return commands.size();
}

void Tank::setControlValuesList(int list[DATA_CHANNELS_COUNT]) {
  for(int i = 0; i < (DATA_CHANNELS_COUNT); i++) {
    this->controlValuesList[i] = list[i] - 1500;
  }
}
 