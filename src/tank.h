 
#ifndef Tank_h
#define Tank_h

#include "services/motorControlService.h"
#include "services/tankDriverService.h"
#include "services/DriveCommandExecutor.h"
#include "model/Command.h"
#include "Arduino.h"
#include <Queue.h>
#include <LinkedList.h>

class Tank {
  public: 
    Tank();
    void begin();
    void loop();
    void enable();
    void disable();
    // double readSpeedLeft();
    // double readSpeedRight();

    static const unsigned int DATA_CHANNELS_COUNT = 6;
    static const unsigned int DEFAULT_CONTROL_VALUE = 0;
    void setControlValuesList(int list[DATA_CHANNELS_COUNT]);
    static int putCommand(CommandType command, int value);
  private:
    // Queue commands;
    // static DataQueue<Command *> commands;
    DriveCommandExecutor remoteDriver;
    TankDriverService tankDriverService;
    static const uint16_t size = 20;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = 0;
    static const unsigned int MIN_CONTROL_VALUE = 1000;
    static const unsigned int MAX_CONTROL_VALUE = 2000;
    int controlValuesList[DATA_CHANNELS_COUNT];
    boolean isEnabled = false;
    void drive();
};

extern Tank tank;

#endif