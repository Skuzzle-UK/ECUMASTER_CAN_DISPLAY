SCREENS lastscreen = SCREENS::CLOCK;

//////////////////////////////////////////////////////////////

void SetupOLED() {
  ClockSetup();
}

//////////////////////////////////////////////////////////////

void ScreenUp() {
  screen = static_cast<SCREENS>(static_cast<int>(screen) + 1); //How to move through an enum
  if (screen == SCREENS::END) {
    screen = SCREENS::BEGIN;
    screen = static_cast<SCREENS>(static_cast<int>(screen) + 1);
  }
}

//////////////////////////////////////////////////////////////

void ScreenDown() {
  screen = static_cast<SCREENS>(static_cast<int>(screen) - 1);
  if (screen == SCREENS::BEGIN) {
    screen = SCREENS::END;
    screen = static_cast<SCREENS>(static_cast<int>(screen) - 1);
  }
}

//////////////////////////////////////////////////////////////

void UpdateOLED() {
    switch(screen){
      case SCREENS::CLOCK: {
        CLOCKScreen();
        break;
      }
      case SCREENS::RPM: {
        RPMScreen();
        break;
      }
      case SCREENS::MAP: {
        MAPScreen();
        break;
      }
      case SCREENS::BARO: {
        BAROScreen();
        break;
      }
      case SCREENS::CLT: {
        CLTScreen();
        break;
      }
      case SCREENS::AIT: {
        AITScreen();
        break;
      }
      case SCREENS::OILP: {
        OILPScreen();
        break;
      }
      case SCREENS::AFR: {
        AFRScreen();
        break;
      }
      case SCREENS::FUELTYPE: {
        FUELTYPEScreen();
        break;
      }
      case SCREENS::SPEED: {
        SPEEDScreen();
        break;
      }
  }
}

//////////////////////////////////////////////////////////////

void CLOCKScreen(){
  PrintHours();
  PrintMinutes();
  PrintSeconds();
  ClockLoop();
}

//////////////////////////////////////////////////////////////

void RPMScreen(){
  char displaystr[4];
  sprintf(displaystr, "%4d", ecm.RPM());    
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "rpm", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void MAPScreen(){
  if (!setMode){
    char displaystr[4];
    sprintf(displaystr, "%4d", (short)ecm.MAP());
    display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
    display.printFixed (110,  20, "kpa", STYLE_NORMAL);
  }
  else {
    char buffer[3];
    display.printFixedN (10,  0, itoa(ecm.BOOST_PERCENT(), buffer, 10), STYLE_NORMAL, FONT_SIZE_4X);
    display.printFixed (110,  20, "  %", STYLE_NORMAL);
  }
}

//////////////////////////////////////////////////////////////

void BAROScreen(){
  char displaystr[4];
  sprintf(displaystr, "%4d", (short)ecm.BARO());
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "kpa", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void CLTScreen(){
  char displaystr[4];
  sprintf(displaystr, "%4d", (short)ecm.CLT());
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "oC", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void AITScreen(){
  char displaystr[4];
  sprintf(displaystr, "%4d", (short)ecm.AIT());
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "oC", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void OILPScreen(){
  char displaystr[4];
  sprintf(displaystr, "%4d", (short)ecm.OIL_PRESSURE());
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "psi", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void AFRScreen(){
  char displaystr[4];
  dtostrf(ecm.AFR(), 4, 1, displaystr);
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "afr", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void FUELTYPEScreen(){  
  if (!setMode){
    if (ecm.SPARK_MAP()){
      display.printFixedN (10,  0, "  99", STYLE_NORMAL, FONT_SIZE_4X);
    }
    else{
      display.printFixedN (10,  0, "  95", STYLE_NORMAL, FONT_SIZE_4X);
    }
  }
  else{
    if (ecm.SPARK_MAP()){
      display.printFixedN (10,  0, "= 99", STYLE_NORMAL, FONT_SIZE_4X);
    }
    else{
      display.printFixedN (10,  0, "= 95", STYLE_NORMAL, FONT_SIZE_4X);
    }
  }
  display.printFixed (110,  20, "oct", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////

void SPEEDScreen(){
  char displaystr[4];
    sprintf(displaystr, "%4d", (short)ecm.SPEED());
  display.printFixedN (10,  0, displaystr, STYLE_NORMAL, FONT_SIZE_4X);
  display.printFixed (110,  20, "mph", STYLE_NORMAL);
}

//////////////////////////////////////////////////////////////
