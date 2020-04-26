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

#ifndef Wifi_module_h
#define Wifi_module_h

#include "Arduino.h"
#include "constraints/secret.h"
#include "tank.h"
#include "index_html.h"
#include <WiFi.h>
#include <WebServer.h>

class Wifi_module {
  public:
    void begin(
      void (*controlCallback)(int list[Tank::DATA_CHANNELS_COUNT] )
      );
    void loop();

  private:
    static const unsigned int WEBSERVER_PORT = 80;
    const char * REMOTE_CONTROL_PATH = "/control";
    const char * MASTER_CONTROL_FORWARD_PATH = "/command";
    const char * MDNS_DOMAIN_NAME = "quadcopter";
    WebServer * server;


    CommandType parse (String command);
    void beginWebServer(WebServer * server);
    static void wifiNodeConfig();
    static void aPConfig();
    static void onRoot();
    static void onControl();
    static void onMasterControl();
    void (*controlCallback)(int list[Tank::DATA_CHANNELS_COUNT]);
};

extern Wifi_module wifi;

#endif