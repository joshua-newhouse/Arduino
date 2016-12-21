/* This program reads temperatures from a sensor and commands 3 LEDs to turn on
   based on the the difference in measured temp from the baseline temp which is
   obtained at start up. */

/* CONSTANTS */
const int SENSOR_PIN = A0;
const float SENSOR_TO_VOLTS = (5.0f / 1024.0f);
const float GATE = 2.0f;

/* GLOBAL VARS */
float base;

/* FUNCTION PROTOTYPES */
void Print(float);
inline float VoltsToTemp(float);

void setup(){
	for(unsigned pin = 2; pin < 5; pin++){
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
	Serial.begin(9600);
	base = (float)analogRead(SENSOR_PIN);
	Serial.println("");
	Serial.println("BASE");
	Print(base);
	Serial.println("READINGS");
}

void loop(){
	float reading = (float)analogRead(SENSOR_PIN);
	Print(reading);

	if(reading - base >= GATE && reading - base < 2.0f * GATE){
		digitalWrite(2, HIGH);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
	}
	else if(reading - base >= 2.0f * GATE && reading - base < 3.0f * GATE){
		digitalWrite(2, HIGH);
		digitalWrite(3, HIGH);
		digitalWrite(4, LOW);
	}
	else if(reading - base >= 3.0f * GATE){
		digitalWrite(2, HIGH);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
	}
	else
		for(unsigned pin = 2; pin < 5; pin++){
			pinMode(pin, OUTPUT);
			digitalWrite(pin, LOW);
		}
}

void Print(float f){
	Serial.print(f);
	Serial.print("; ");
	Serial.print(f * SENSOR_TO_VOLTS);
	Serial.print(" V; ");
	Serial.print(VoltsToTemp(f * SENSOR_TO_VOLTS));
	Serial.println(" C");
}

float VoltsToTemp(float v){
	return (v - 0.5f) * 100.0f;
}
