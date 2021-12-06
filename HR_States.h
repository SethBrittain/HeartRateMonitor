enum HRStates {HR_Record, HR_Update, HR_Wait};

// Beat Detection Threshold
const int BEAT_THRESHOLD = 650;
// How long to wait to enable beat detection
const int IGNORE_TIME = 200;

//Current State
HRStates HrState;

// Sets the initial state
void InitializeHR() {
	HrState = HR_Wait;
}

long lastBeatMs = 0;

int HRNextState(int reading) {
	switch (HrState) {
		case HR_Record:
			break;
		case HR_Update:
			HrState = HR_Wait;
		case HR_Wait:
			if (reading > BEAT_THRESHOLD) {
				HrState = HR_Record;
			}
			break;
	}

	return 0;
}
