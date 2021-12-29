#include <arduino.h>
#include "ECM.h"
#include <lcdgfx.h>
#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(10);
DisplaySSD1306_128x32_I2C display(-1);
SCREENS screen = SCREENS::CLOCK;
ECM ecm = ECM();

void setup() {
  Serial.begin(9600); // Used for debugging only
  SetupCANBUS();
  SetupButtons();
  SetupOLED();
}

void loop() {
  CheckButtonPressed();
  CheckSetTimeout();
  ReadCANBUS();
  WriteCANBUS();
  UpdateOLED();
}