enum HRStates {
  HR_Record, HR_Update, HR_Wait};

//Current State
HRStates HRState;

// Sets the initial state
void InitializeHR() {
  HRState = HR_Wait;
}

HRStates HRNextState(int reading) {
  switch (HRState) {
  case HR_Record:
    if (beatCounter == 6) {
      HRState = HR_Update;
    }
    break;
  case HR_Update:
    HRState = HR_Wait;
    break;
  case HR_Wait:
    lastBeatMillis = 0;
    totalInterval = 0;
    beatCounter = 0;
    if (reading > BEAT_THRESHOLD) {
      HRState = HR_Record;
      lastBeatMillis = millis();
    }
    break;
  }

  return HRState;
}
