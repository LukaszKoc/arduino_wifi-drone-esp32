#ifndef SpeedControlService_h
#define SpeedControlService_h 

double milisecPerCentimeter = 0.0;

double currentSpeedL = 0.0;
long previousMillisL = 0.0;
long milisNowL = 0.0;
int pulsesL, encoderAL, encoderBL;
int pulsesChangedL = 0;

double currentSpeedR = 0.0;
long previousMillisR = 0.0;
long milisNowR = 0.0;
const long TIMEOUT = 500;
int pulsesR, encoderAR, encoderBR;
int pulsesChangedR = 0;


//Hall sensor działa na 5V - urzyj lvl konwertera 
void IRAM_ATTR readSpeedLeft();
void IRAM_ATTR readSpeedRight();
 

const int stepsPerCentyMeter = 12;
void  redSencores(int encoderA, int encoderB, int &pulses);
double  calculateSpeed(int &pulses, long &milisNow, long &previousMillis, int &pulsesChanged);

class SpeedControlService {
  private:
    int read();
  public:
    void setup();
    SpeedControlService() { }
    SpeedControlService(int sencor1L_arg, int sencor2L_arg, int sencor1R_arg, int sencor2R_arg) {
      encoderAL = sencor1L_arg; 
      encoderBL = sencor2L_arg;
      encoderAR = sencor1R_arg; 
      encoderBR = sencor2R_arg;
    }
    double getSpeedL();  
    double getSpeedR();    
}; 

void SpeedControlService::setup( ) {
  pinMode(encoderAL, INPUT_PULLUP);
  pinMode(encoderBL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAL), readSpeedLeft, CHANGE);
  pinMode(encoderAR, INPUT_PULLUP);
  pinMode(encoderBR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAR), readSpeedRight, CHANGE);
}

double SpeedControlService::getSpeedL() {
  if( currentSpeedL != 0.0 && (millis() - previousMillisL) > TIMEOUT) {
    currentSpeedL = 0.0;
  }
  return currentSpeedL;
}

double SpeedControlService::getSpeedR() {
  if( currentSpeedR != 0.0 && (millis() - previousMillisR) > TIMEOUT) {
    currentSpeedR = 0.0;
  }
  return currentSpeedR;
}

void readSpeedLeft() {
    redSencores(encoderAL, encoderBL, pulsesL);
    double speed = calculateSpeed(pulsesL, milisNowL, previousMillisL, pulsesChangedL);
    if (speed != NULL) currentSpeedL = speed;
}

void readSpeedRight() {
    redSencores(encoderAR, encoderBR, pulsesR);
    double speed = calculateSpeed(pulsesR, milisNowR, previousMillisR, pulsesChangedR);
    if (speed != NULL) currentSpeedR = speed;
}

void redSencores(int encoderA, int encoderB, int &pulses) {
  if ( digitalRead(encoderB) == 0 ) {
    if ( digitalRead(encoderA) == 0 ) {
      // A fell, B is low
      pulses--; // Moving forward
    } else {
      // A rose, B is high
      pulses++; // Moving reverse
    }
  } else {
    if ( digitalRead(encoderA) == 0 ) {
      pulses++; // Moving reverse
    } else {
      // A rose, B is low
      pulses--; // Moving forward
    }
  }
}

double calculateSpeed(int &pulses, long &milisNow, long &previousMillis, int &speedChanged) {
  double currentSpeed = 1;
   if(pulses < 0) {
    currentSpeed = -1;
  }
  // Serial.println(String("pulses: ") + pulses);

  if( pulses == stepsPerCentyMeter || pulses == -stepsPerCentyMeter) {
    speedChanged = 1;
    milisNow = millis();
    milisecPerCentimeter = (milisNow - previousMillis);
    // Serial.println(String("milisecPerCentimeter: ") + milisecPerCentimeter);
    if(milisecPerCentimeter > TIMEOUT) {
      previousMillis =  milisNow;
      pulses = 0;
      return 0.0;
    }
    previousMillis = milisNow;

    currentSpeed = currentSpeed * (0.01 /(milisecPerCentimeter/1000));
    // Serial.println(String("currentSpeed: ") + currentSpeed);

    speedChanged = 1;
    pulses = 0;
    return currentSpeed;
  }
  return NULL;
}

#endif