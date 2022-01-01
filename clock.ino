unsigned long lastMillis;
int  hours = 00;
int  minutes = 00;
uint8_t  seconds = 00;

//////////////////////////////////////////////////////////////

void PrintSeconds()
{
  if(!setMode){
    if (seconds & 1)
    {
        display.printFixedN (69, 12, ":", STYLE_NORMAL, FONT_SIZE_2X);
    }
    else
    {
        display.printFixedN (69, 12, " ", STYLE_NORMAL, FONT_SIZE_2X);
    }
  }
  else{
    display.printFixedN (69, 12, " ", STYLE_NORMAL, FONT_SIZE_2X);
  }
}

//////////////////////////////////////////////////////////////

void PrintMinutes()
{
    char minutesStr[3] = "00";
    minutesStr[0] = '0' + minutes / 10;
    minutesStr[1] = '0' + minutes % 10;
    display.printFixedN (78,  0, minutesStr, STYLE_NORMAL, FONT_SIZE_4X);
}

//////////////////////////////////////////////////////////////

void PrintHours()
{
    char hoursStr[3] = "00";
    hoursStr[0] = '0' + hours / 10;
    hoursStr[1] = '0' + hours % 10;
    display.printFixedN (20,  0, hoursStr, STYLE_NORMAL, FONT_SIZE_4X);
}

//////////////////////////////////////////////////////////////

void ClockSetup()
{
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    is_rtc_enabled = RTC_ENABLED;
    lastMillis = lcd_millis();
    PrintHours();
    PrintMinutes();
}

//////////////////////////////////////////////////////////////

void CLOCK_SET_TIME(DIRECTION direction) {
  switch(direction){
    case DIRECTION::UP: {
      if (++minutes > 59){
        minutes = 0;
        if (++hours > 23)
        {
          hours = 0;
        }
      }
      seconds = 0;
      DateTime now = rtc.now();
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), hours, minutes, seconds));
      break;
    }
    case DIRECTION::DOWN: {
      if (--minutes < 0){
        minutes = 59;
        if (--hours < 0)
        {
          hours = 23;
        }
      }
      seconds = 0;
      DateTime now = rtc.now();
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), hours, minutes, seconds));
      break;
    }
  }
}

//////////////////////////////////////////////////////////////

void ClockLoop()
{
    if ((uint32_t)(lcd_millis() - lastMillis) >= 1000)
    {
        lastMillis += 1000;
        if (++seconds > 59)
        {
            seconds = 0;
            if (++minutes > 59)
            {
                minutes = 0;
                if (++hours > 23)
                {
                    hours = 0;
                }
                PrintHours();
            }
            PrintMinutes();
        }
        PrintSeconds();
    }
}

//////////////////////////////////////////////////////////////

void RTC_Clock(){
  DateTime now = rtc.now();
  hours = now.hour();
  minutes = now.minute();
  seconds = now.second();
}