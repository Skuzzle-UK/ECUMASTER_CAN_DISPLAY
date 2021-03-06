# ECUMASTER_CAN_DISPLAY

Arduino project for displaying a clock and useful engine data set via CAN-BUS.

Build with ECUMASTER EMU Black in mind, but could be repurposed for any CAN-BUS system.

All data pages are currently displaying as intended. Clock works and time can be set.

Boost pressure is adjustable as a percentage. In my case I will use a table blend method where 0% is table 1 and 100% is table 2. 50% would be an equal blend of the 2 tables.

Ignition map can be swithed from the fuel type screen.

## Community input
Releases contains snapshots of the project at useful stages where the code is complete and working well. Each time a new feature is added and made stable I will create a new release.

If you intend to take this project as it is for use in your own car I would recommend taking it from the latest zip. If you intend to contribute to the project then please fork the repo.

Please feel free to look through the issues list, fork the repository and work through any of the issues that you like. You will find that most of the issues are enhancements. Add your own ideas in as issues so that others can work on them.
I intend to spend a fair amount of time myself working through the issues list that I have created but this project can only get better for everyone with input from the users.

## Project hardware
- ECUMaster EMU Black
- Arduino nano
- MCP2515 CAN-BUS SPI module - https://www.amazon.co.uk/ZkeeShop-MCP2515-Receiver-Compatible-Development/dp/B07SYH9BXS
- SSD1306 - 128x32 OLED display - https://www.amazon.co.uk/AITRIP-Display-SSD1306-3-3V-5V-Arduino/dp/B08H1LB6JZ/
- 3 x buttons / switches
- DS1307 RTC Module (if you want super accurate time keeping for the clock)

## Requires libraries
- autowp / arduino-mcp2515 - https://github.com/autowp/arduino-mcp2515/tree/master
- lexus2k / lcdgfx - https://github.com/lexus2k/lcdgfx
- adafruit / RTClib - https://github.com/adafruit/RTClib


## Function
-D6 SLEEP_PIN

Buttons assigned:
- D5 : UP
- D3 : DOWN
- D4 : SET

If SLEEP_PIN goes high then display turns off and buttons don't function to enable power down when ecu turns off.

Pressing up or down cycles through display pages as shown:
1. CLOCK
2. RPM
3. MAP
4. BARO
5. CLT
6. AIT
7. OILP
8. AFR
9. FUELTYPE
10. SPEED

Long press (2000 millis) of set button allows for values to be set on the pages shown:
1. CLOCK (set time)
3. MAP (set boost pressure)
9. FUELTYPE (swap ignition table between 95 and 99 octane)

Once in the set mode the up and down buttons function to change the values up and down. Timeout of 10000 millis if no button is pressed.

Boost percent and spark map are stored in EEPROM incase of power loss to keep last settings.

## ECU Setup
- CAN-Bus speed - 1Mbs (can be altered in the canbus.ino file on line 12 if you need to use a different speed).
- If possible send EMU stream over CAN-Bus deselected. It slows the display considerably at the moment. Maybe some work is required here to figure out how to deal with Can packets in a better way.
- Can-Bus dashboard must be set to user defined.
- From the tools menu you need to program the User defined can stream as per below or modify the code in canbus.ino to suit your own CAN-Bus stream.

## CAN-BUS Programming
### 0x400
| Output | Byte pos | Type | Function |
|--------|----------|------|----------|
| CAN Analog # 1 | 0 | unsigned 8 bit | Ignition table switch |
| CAN Analog # 2 | 1 | unsigned 8 bit | Boost table blend switch |

### 0x500
| Data | Byte pos | Type | Multiplier |
|--------|----------|------|----------|
| RPM | 0 | unsigned 16 bit little endian | 1 |
| AIT | 2 | signed 8 bit | 1 |
| MAP | 3 | unsigned 8 bit | 1 |
| SPEED | 4 | unsigned 16 bit little endian | 1 |
| BARO | 6 | unsigned 8 bit | 1 |
| OIL PRESSURE | 7 | unsigned 8 bit | 21 |

### 0x501
| Data | Byte pos | Type | Multiplier |
|--------|----------|------|----------|
| CLT | 0 | signed 8 bit | 1 |
| LAMBDA | 1 | unsigned 8 bit | 128 |
