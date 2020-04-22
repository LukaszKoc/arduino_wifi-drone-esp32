#ifndef MotorControlService_h
#define MotorControlService_h 
#include "Arduino.h"
#include "../constraints/propperties.h"

class MotorControlService {
	private:
		int input1, input2;
		void changeDirection(boolean isForward);
		void drive(boolean isForward, int speed);
		static const int freq = DC_PWM_FREQUENCY;
		int channel1;
		int channel2;
		static const int resolution = DC_PWM_RESOLUTION;
	public:
		void setup();
		void stop();
		void neutral();
		void setSpeed(int speed);
		MotorControlService(){}
		MotorControlService(int input1_arg, int input2_arg, int channel1_arg, int channel2_arg) {
			input1 = input1_arg;
			input2 = input2_arg;
			channel1 = channel1_arg;
			channel2 = channel2_arg;
		}
}; 
 
#endif
