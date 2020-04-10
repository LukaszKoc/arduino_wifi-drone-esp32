#ifndef MotorControlService_h
#define MotorControlService_h 
#include "Arduino.h"
#include "../constraints/propperties.h"

class MotorControlService {
	private:
		int input1, input2;
		void changeDirection(boolean isForward);
		void drive(boolean isForward, int speed);
		static const int freq = DC_FREQUENCY;
		static const int channel1 = 1;
		static const int channel2 = 2;
		static const int resolution = 10;
	public:
		void setup();
		void stop();
		void neutral();
		void setSpeed(int speed);
		MotorControlService(){}
		MotorControlService(int input1_arg, int input2_arg) {
			input1 = input1_arg;
			input2 = input2_arg;
		}
}; 
 
#endif
