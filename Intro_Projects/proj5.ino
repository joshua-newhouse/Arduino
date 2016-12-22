/* Program to control a servo with a potentiometer.  Written using OOP concepts
   in order to learn about Arduino compiler.
   Uses:
	2,838 bytes of program storage space
	68 bytes of dynamic memory */
#include <Servo.h>

class MyServo : public Servo{
	private:
		int servoPin;
		int MIN_ANG;
		int MAX_ANG;

		int VoltsToAngle(int, int, int);

	public:
		MyServo() : servoPin(-1), MIN_ANG(0), MAX_ANG(0)
		{}
		MyServo(int p, int min, int max)
		: servoPin(p), MIN_ANG(min), MAX_ANG(max){
			attach(servoPin);
		}
		void Move(int v, int vMin, int vMax){
			write(VoltsToAngle(v, vMin, vMax));
			delay(15);
		}
};

int MyServo::VoltsToAngle(int in, int vmin, int vmax){
	in = in > vmax ? vmax : in < vmin ? vmin : in;
	long ret_val = 
		(long)in * (long)(MAX_ANG - MIN_ANG) / (long)(vmax - vmin);
	return (int)ret_val;
}

class Potentiometer{
	private:
		int potPin;

	public:
		int MIN_VAL;
		int MAX_VAL;

		Potentiometer() : potPin(-1), MIN_VAL(0), MAX_VAL(0)
		{}
		Potentiometer(int p, int min, int max)
		: potPin(p), MIN_VAL(min), MAX_VAL(max)
		{}
		int CurReading(){
			return analogRead(potPin);
		}
};

MyServo servo;
Potentiometer pot;

void setup(){
	servo = MyServo(9, 0, 180);
	pot = Potentiometer(A0, 0, 1024);
}

void loop(){
	servo.Move(pot.CurReading(), pot.MIN_VAL, pot.MAX_VAL);
}


