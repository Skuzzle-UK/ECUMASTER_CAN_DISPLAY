# ECUMASTER_CAN_DISPLAY
 
Arduino project for displaying a clock and useful engine data set via CAN-BUS.

Build with ECUMASTER EMU Black in mind, but could be repurposed for any CAN-BUS system.

All data pages are currently displaying as intended. Clock works and time can be set.

Boost pressure is adjustable as a percentage. In my case I will use a table blend method where 0% is table 1 and 100% is table 2. 50% would be an equal blend of the 2 tables.

Ignition map can be swithed from the fuel type screen.

CAN-BUS function is untested as of writing.

## Project hardware:
- Arduino nano
- MCP2515 CAN-BUS SPI module.
- 128x32 OLED display
- 3 x buttons / switches

## CAN-BUS
### 0x400
| Output | Byte pos | Type | Function |
|--------|----------|------|----------|
| CAN Analog # 1 | 0 | unsigned 8 bit | Ignition table switch |
| CAN Analog # 2 | 1 | unsigned 8 bit | Boost pressure output 0-255 |

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