#include <LiquidCrystal.h>
#include "HR_States.h"

LiquidCrystal LcdDriver( A5, A4, 5, 6, 7, 8 );
unsigned long Timer;
const short INTERVAL = 25;

int intervals[6] = {0, 0, 0, 0, 0, 0};
bool ignoreBeat = false;

unsigned long lastBeat = 0;

void setup() {
	Serial.begin(9600);
	Timer = millis();
	LcdDriver.begin(16,2);
	pinMode(13, OUTPUT);
	
	InitializeHR();
}

void loop()
{
	
	if (millis() - Timer >= INTERVAL) {
		switch(HR_NextState(analogRead(0))) {
			case HR_Record:
				break;
			case HR_Update:
				break;
			case HR_Wait:
				break;
		}


	Timer += INTERVAL;
	}
}

void UpdateIntervals(int ms) {
	for (int i = 0; i < 6; i++) {
		intervals[i] = intervals[i + 1];
	}
	intervals[5] = ms;
}

double GetBPM(){
	int intervalSum = 0;
	for (int i = 0; i < 6; i++){
		intervalSum += intervals[i];
	}
	return intervalSum / (double)6;
}
