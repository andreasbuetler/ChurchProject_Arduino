#include <MultiStepper.h>
#include <AccelStepper.h>

#define PIR_AOUT A1  
#define PIR_DOUT 1   


AccelStepper stepper(1, 5, 4); //initialise accelstepper for a two wire board, pin 5 step, pin 4 dir

const float riseSpeed = 1000;
const float sinkSpeed = -400;
const int initializingSpeed = 400;
const int highPosition = 10000;

boolean movement;
boolean detected;

void setup() {
  stepper.setCurrentPosition(0);
  Serial.begin(9600);
  stepper.setMaxSpeed(1000);
  pinMode(PIR_AOUT, INPUT);
  pinMode(PIR_DOUT, INPUT);
  Serial.println("SETUP!!!");
  
  //initializing();
}
void loop() {
  movement = readDigitalValue();
  //Serial.println(movement);
  if (movement == true) {
      Serial.println("RISE");
    while (stepper.currentPosition() != highPosition) {
      stepper.setSpeed(riseSpeed);
      stepper.runSpeed(); 
      Serial.println(stepper.currentPosition());   
    }
    stepper.stop();
    delay(3000);
  }else if(movement == false){
    
    Serial.println("SINK");
    while (stepper.currentPosition() != 0) {
      stepper.setSpeed(sinkSpeed);
      stepper.runSpeed();
      Serial.println(stepper.currentPosition());
    }
  }
  //delay(3000);
}

void initializing() { //while detected !=true
  Serial.println("INITIALIZING");
  while(detected = false){
  stepper.setSpeed(initializingSpeed);
  stepper.runSpeed();
  delay(3000);
  stepper.stop();
  stepper.setSpeed(initializingSpeed*(-1));
  stepper.runSpeed();
  }
  //if(detected == true){
  stepper.stop();
  stepper.setCurrentPosition(0);
//}
}

boolean readDigitalValue(){
  // The OpenPIR's digital output is active high
  int motionStatus = digitalRead(PIR_DOUT);

  // If motion is detected, turn the onboard LED on:
  if (motionStatus == HIGH)
    return true;
  else // Otherwise turn the LED off:
    return false;
}


