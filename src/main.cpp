
#include "Arduino.h"
#include "controller.h" 

void setup()
{
	Serial.begin(115200);
	controller.begin();
}

void loop()
{
	controller.loop();
}