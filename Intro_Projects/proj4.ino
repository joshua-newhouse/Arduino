/* Uses 3 photoresisters to measure amount of red, blue, and green light present
   Sends PWM signal to red, blue, and green LEDs with a duty cycle, (DC),
   proportional to the measured amount of light in that respective wavelength.*/

/* CONSTANTS */
const unsigned TYPES = 2;
const unsigned COLORS = 3;

enum types{
	SENSOR, LED
};

enum colors{
	R, G, B
};

enum sensorPin{
	RD_SNSR = A0, GRN_SNSR = A1, BLU_SNSR = A2
};

enum ledPin{
	RD_PIN = 9, GRN_PIN = 10, BLU_PIN = 11
};

/* VARIABLES */
unsigned vals[TYPES][COLORS] = {0};	//Holds sensor readings of each color
					//as well as DC for each LED

/* FUNCTIONS */
void setup(){
	Serial.begin(9600);
	for(int p = RD_PIN; p <= BLU_PIN; p++)
		pinMode(p, OUTPUT);
}

void loop(){
	int c, s;
	for(c = R, s = RD_SNSR; c <= B; c++, s++){
		vals[SENSOR][c] = analogRead(s);	//Reads sensor
		vals[LED][c] = vals[SENSOR][c] / 4;	//Calculates DC
		Serial.print(vals[SENSOR][c]);
		Serial.print(' ');
		Serial.print(vals[LED][c]);
		Serial.print('\t');
		delay(5);
	}
	Serial.println("");

	for(c = R, s = RD_PIN; c <= B; c++, s++)
		analogWrite(s, vals[LED][c]);	//Turns on LED, PWM for DC
}
