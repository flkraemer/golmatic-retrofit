// Golmatic MD24 stepper based Z-axis autofeed. 
// This code uses an Arduino Nano to control a stepper driver such as DM542T and a large stepper motor such as Nema 34, 4-6 Nm.
// Upon button press (up or down) the spindle head of the machine can be moved vertically.
// If no button is pressed, the driver is set to disable to allow for manually cranking. 
// 2022 by Felix Kraemer - mail@flkraemer.com - www.flkraemer.com

#include <Arduino.h>
#include <AccelStepper.h>
 
#define stepper_pin_step 8
#define stepper_pin_dir  9
#define disable_pin 13

const int buttonupPin = 2; 
const int buttondownPin = 3;
int buttonupState = 0;
int buttondownState = 0;
int targetSpeed = 3500;

AccelStepper stepper(AccelStepper::DRIVER, stepper_pin_step, stepper_pin_dir);
 
void setup() {
stepper.setMaxSpeed(1000.0);
stepper.setAcceleration(50.0);
digitalWrite(disable_pin, HIGH);
pinMode(buttonupPin, INPUT);
pinMode(buttondownPin, INPUT);
}
 
void loop() {
  buttonupState = digitalRead(buttonupPin);
  buttondownState = digitalRead(buttondownPin);
  
  if (((buttonupState == HIGH) && !(buttondownState == HIGH)))  {
    digitalWrite(disable_pin, LOW);
    stepper.move(targetSpeed);
    stepper.run();
    }
  else if (((buttondownState == HIGH) && !(buttonupState == HIGH)))  {
    digitalWrite(disable_pin, LOW);
    stepper.move(-targetSpeed);
    stepper.run();
    }
  else{
    stepper.setCurrentPosition(0);
    digitalWrite(disable_pin, HIGH);
  }
 
}
