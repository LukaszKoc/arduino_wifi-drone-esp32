 
#ifndef Tank_h
#define Tank_h

#include "services/MotorControlService.h"
#include "services/TankDriverService.h"
#include "Arduino.h"

class Tank {
  public: 
    Tank();
    void begin();
    void loop();
    void enable();
    void disable();
    static const unsigned int DATA_CHANNELS_COUNT = 6;
    static const unsigned int DEFAULT_CONTROL_VALUE = 0;
    void setControlValuesList(int list[DATA_CHANNELS_COUNT]);

  private:
    void drive();
    TankDriverService tankDriverService;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = 0;
    static const unsigned int MIN_CONTROL_VALUE = 1000;
    static const unsigned int MAX_CONTROL_VALUE = 2000;
    int controlValuesList[DATA_CHANNELS_COUNT];
    boolean isEnabled = false;

};

extern Tank tank;

#endif