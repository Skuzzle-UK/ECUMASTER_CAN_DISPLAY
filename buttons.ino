#define UP_BUTTON 5
#define DOWN_BUTTON 3
#define SET_BUTTON 4
#define LONG_PRESS 2000
byte DEBOUNCE_TIME = 250;
#define SET_TIMEOUT 10000

int set_button_state = HIGH;
unsigned long time_set_button_SETd;
bool setMode = false;
unsigned long setModeEntered = 0;

void SetupButtons() {
  time_set_button_SETd = millis();
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(SET_BUTTON, INPUT_PULLUP);
}

void CheckButtonPressed() {
  //Check up
  if (digitalRead(UP_BUTTON) == LOW)
  {
    Up();
  }
  //Check down
  else if (digitalRead(DOWN_BUTTON) == LOW)
  {
    Down();
  }
  //Check set
  else if (digitalRead(SET_BUTTON) == LOW) {
    switch(screen){
      case SCREENS::CLOCK: {
        Set();
        break;
      }
      case SCREENS::MAP: {
        Set();
        break;
      }
      case SCREENS::FUELTYPE: {
        Set();
        break;
      }
    }
  }
  else {
    set_button_state = HIGH;
    time_set_button_SETd = millis();
  }
}

/*Button pressed methods*/
void Set() {
if (set_button_state != LOW) {
    DeactivateSetMode();
  }
  else if (millis() - time_set_button_SETd > LONG_PRESS && !setMode) {
    ActivateSetMode();
  }
}

void ActivateSetMode(){
    DEBOUNCE_TIME = 80;
    display.clear();
    setModeEntered = millis();
    setMode = true;
    ecm.LOCK();
}

void DeactivateSetMode(){
    DEBOUNCE_TIME = 200;
    setMode = false;
    ecm.UNLOCK();
    set_button_state = LOW;
    time_set_button_SETd = millis();
}

void CheckSetTimeout() {
  if (millis() - setModeEntered > SET_TIMEOUT && setMode) {
    DeactivateSetMode();
  }
}

double lastpressed = 0;

void Up() {
  if (millis() - lastpressed > DEBOUNCE_TIME) {
    display.clear();
    if (setMode){
      switch(screen){
        case SCREENS::CLOCK: {
          CLOCK_SET_TIME(DIRECTION::UP);
          break;
        }
        case SCREENS::MAP: {
          ecm.SET_BOOST_PRESSURE(DIRECTION::UP);
          break;
        }
        case SCREENS::FUELTYPE: {
          ecm.SET_SPARK_MAP();
          break;
        }
      }
      setModeEntered = millis(); //Resets timeout
    }
    else{
      ScreenUp();
    }
    lastpressed = millis();
  }
}

void Down() {
  if (millis() - lastpressed > DEBOUNCE_TIME) {
    display.clear();
    if (setMode){
      switch(screen){
        case SCREENS::CLOCK: {
          CLOCK_SET_TIME(DIRECTION::DOWN);
          break;
        }
        case SCREENS::MAP: {
          ecm.SET_BOOST_PRESSURE(DIRECTION::DOWN);
          break;
        }
        case SCREENS::FUELTYPE: {
          ecm.SET_SPARK_MAP();
          break;
        }
      }
      setModeEntered = millis(); //Resets timeout
    }
    else{
      ScreenDown();
    }
    lastpressed = millis();
  }
}