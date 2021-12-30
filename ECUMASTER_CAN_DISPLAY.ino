#include <arduino.h>
#include "ECM.h"
#include <lcdgfx.h>
#include <SPI.h>
#include <mcp2515.h>

//////////////////////////////////////////////////////////////

#define SLEEP_PIN 6 //Allows for the screen to turn off if pin is not grounded

//////////////////////////////////////////////////////////////

MCP2515 mcp2515(10);
DisplaySSD1306_128x32_I2C display(-1);
SCREENS screen = SCREENS::CLOCK;
ECM ecm = ECM();

//////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); // Used for debugging only
  pinMode(SLEEP_PIN, INPUT_PULLUP);
  SetupCANBUS();
  SetupButtons();
  SetupOLED();
  ClockSetup();
}

//////////////////////////////////////////////////////////////

void loop() {
if(digitalRead(SLEEP_PIN) == LOW){
  CheckButtonPressed();
  CheckSetTimeout();
  ReadCANBUS();
  WriteCANBUS();
  UpdateOLED();
}
else{ OLED_OFF(); }
}

//////////////////////////////////////////////////////////////