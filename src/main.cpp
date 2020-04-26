
#include "Arduino.h"
#include "controller.h" 

void setup()
{
	Serial.begin(115200);
	controller.begin();
  	delay(10);
}

void loop()
{
	controller.loop();
	delay(5);
}