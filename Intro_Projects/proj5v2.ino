/* Program to control a servo with a potentiometer.  Performs exactly the same
   as proj5 but does not use OOP concepts.
   Uses:
	2452 bytes of program storage space
	56 bytes of dynamic memory */
#include <Servo.h>

Servo servo;
const int potPin = A0;

void setup(){
	servo.attach(9);
}

void loop(){
	servo.write(map(analogRead(potPin), 0, 1024, 0, 180));
}


