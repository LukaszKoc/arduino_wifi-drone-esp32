
#include "Arduino.h"
#include "controller.h"

void setup()
{
  controller.begin();
}

void loop()
{
  controller.loop();
}