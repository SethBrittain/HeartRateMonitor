#include <LiquidCrystal.h>

// LCD screen
LiquidCrystal LcdDriver( A5, A4, 5, 6, 7, 8 );

// Tick rate
unsigned long Timer;
const short INTERVAL = 25;

// Beat Detection Threshold
const int BEAT_THRESHOLD = 650;
// How long to wait to enable beat detection
const int IGNORE_TIME = 200;

// Beat interval tracking
unsigned long lastBeatMillis = 0;
unsigned int totalInterval = 0;
unsigned short beatCounter = 0;

// State machine
#include "HR_States.h"

void setup() {
	// Sets up serial port for debug
	Serial.begin(9600);

	// Timer for heartrate monitor polling
	Timer = millis();

	// Sets up LCD for outputting BPM to screen
	LcdDriver.begin(16,2);
	
	// Sets up the state machine
	InitializeHR();
}

void loop()
{
	if (millis() - Timer >= INTERVAL) {
		unsigned int reading = analogRead(0);
		switch(HRNextState(reading)) {
			case HR_Record:
				if (millis() - lastBeatMillis > IGNORE_TIME && reading > BEAT_THRESHOLD) {
					beatCounter++;
					totalInterval += millis() - lastBeatMillis;
					lastBeatMillis = millis();
				}
				break;
			case HR_Update:
				LcdDriver.clear();
				LcdDriver.print(CalculateBPM() + " BPM");
				break;
			case HR_Wait:
				break;
		}


	Timer += INTERVAL;
	}
}

double CalculateBPM() {
	return 60000 / ((double)totalInterval / 6);
}