#include <arduino.h>
#include "ECM.h"
#include <lcdgfx.h>
#include <SPI.h>
#include <mcp2515.h>

//////////////////////////////////////////////////////////////

#define SLEEP_PIN A1 //Allows for the screen to turn off if pin does not recieve value
#define SLEEP_PIN_MIN_VAL 511 //Should be somewhere around 2.5v

//////////////////////////////////////////////////////////////

//Instantiates required objects
MCP2515 mcp2515(10);
DisplaySSD1306_128x32_I2C display(-1);
SCREENS screen = SCREENS::CLOCK;
ECM ecm = ECM();

//////////////////////////////////////////////////////////////

void setup() {
  SetupCANBUS();
  SetupButtons();
  SetupOLED();
  ClockSetup();
}

//////////////////////////////////////////////////////////////

void loop() {
if(analogRead(SLEEP_PIN) > SLEEP_PIN_MIN_VAL){
  CheckButtonPressed();
  CheckSetTimeout();
  ReadCANBUS();
  WriteCANBUS();
  UpdateOLED();
}
else{ OLED_OFF(); }
}

//////////////////////////////////////////////////////////////