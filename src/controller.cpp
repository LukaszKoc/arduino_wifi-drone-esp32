/*
 * This file is part of the  distribution (https://github.com/wifi-drone-esp32 or http://wifi-drone-esp32.github.io).
 * Copyright (c) 2019 Michal Schwarz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Arduino.h"
#include "controller.h"
#include <StackArray.h>
#include "constraints/pinsNodeMCU.h"
#include "constraints/propperties.h"

Controller controller;
Tank tank;
    
void Controller::begin(void)
{
  // ibus.begin(Serial2);
  tank.begin();
  wifi.begin(onControlEvent);
  delay(10);
}

void Controller::loop(void) {
  controller.currentMillis = millis();
  if (controller.currentMillis - controller.wifiRecievedMillis >= WIFI_FAIL_TIMEOUT_MS) {
    tank.disable();
  } else {
    tank.enable();
  }
  wifi.loop();
  tank.loop();
}

void Controller::updateControlValues(int list[Tank::DATA_CHANNELS_COUNT]) {
  controller.wifiRecievedMillis = millis();
  tank.setControlValuesList(list);
}

void Controller::onControlEvent(int list[Tank::DATA_CHANNELS_COUNT]) {
  // if(list[3] = NULL_VAL) {
  //   tank.putCommand(Command(list[0], list[1]).getType(), list[1]);
  // } else {
      updateControlValues(list);
  // }
}
