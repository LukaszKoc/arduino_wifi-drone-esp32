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

#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "tank.h"
#include "wifi_module.h"
#include "model/Command.h"

class Controller {
  public:
    static const unsigned int WIFI_CHECK_INTERVAL_MS = 500;
    static const unsigned int WIFI_FAIL_TIMEOUT_MS = 2000;

    static void begin(void);
    static void loop(void);
    static void speedLoop(void);

  private:
    unsigned long currentMillis = 0;
    unsigned long logMillis = 0;
    unsigned long wifiRecievedMillis = 0;

    static int onIncomingComandCallback(int list[2]);
    static void onControlEvent(int list[Tank::DATA_CHANNELS_COUNT]);
    static void updateControlValues(int list[Tank::DATA_CHANNELS_COUNT]);
};

extern Controller controller;

#endif