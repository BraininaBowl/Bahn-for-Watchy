#include <Watchy.h> //include the Watchy library
#include "DIN_1451_Engschrift_Regular64pt7b.h"
#include "DIN_1451_Engschrift_Regular12pt7b.h"
				

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h;
      String textstring;
      bool light = false;

      // ** UPDATE **
      //resets step counter at midnight everyday
      if(currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
      }

      // ** DRAW **
      
      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.fillRoundRect(2,2,196,196,8,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(6,6,188,188,5,light ? GxEPD_WHITE : GxEPD_BLACK);
      
      display.setFont(&DIN_1451_Engschrift_Regular64pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);

      //draw hours
      textstring = currentTime.Hour;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(183-w, 100-5);
      display.print(textstring);
      
      //draw minutes
      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(183-w, 100+3+h);
      display.print(textstring);

      // draw battery
      display.fillRoundRect(16,16,34,12,4,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(49,20,3,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(18,18,30,8,3,light ? GxEPD_WHITE : GxEPD_BLACK);
      float batt = (getBatteryVoltage()-3.3)/0.9;
      if (batt > 0) {
       display.fillRoundRect(20,20,26*batt,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      }									

      display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
      lasty = 200 - 16;

      //draw steps
      textstring = sensor.getCounter();
      textstring += " steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.fillRoundRect(16,lasty-h-2,w + 7,h+4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setCursor(19, lasty-3);
      display.setTextColor(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.print(textstring);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      lasty += -8-h;

      // draw year
      textstring = currentTime.Year + 2000;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;

      // draw date
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;
      
      // draw day
      textstring = dayStr(currentTime.Wday);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -40;

      // weather things
      weatherData currentWeather = getWeatherData();
      int8_t temperature = currentWeather.temperature;
      int16_t weatherConditionCode = currentWeather.weatherConditionCode;

      // draw weather state
      if (weatherConditionCode >= 801) {
        textstring = "Cloudy";
      } else if (weatherConditionCode == 800) {
        textstring = "Clear";
      } else if (weatherConditionCode == 781) {
        textstring = "Tornado";
      } else if (weatherConditionCode == 771) {
        textstring = "Squall";
      } else if (weatherConditionCode == 762) {
        textstring = "Ash";
      } else if (weatherConditionCode == 761 || weatherConditionCode == 731) {
        textstring = "Dust";
      } else if (weatherConditionCode == 751) {
        textstring = "Sand";
      } else if (weatherConditionCode == 741) {
        textstring = "Fog";
      } else if (weatherConditionCode == 721) {
        textstring = "Haze";
      } else if (weatherConditionCode == 711) {
        textstring = "Smoke";
      } else if (weatherConditionCode == 701) {
        textstring = "Mist";
      } else if (weatherConditionCode >= 600) {
        textstring = "Snow";
      } else if (weatherConditionCode >= 500) {
        textstring = "Rain";
      } else if (weatherConditionCode >= 300) {
        textstring = "Drizzle";
      } else if (weatherConditionCode >= 200) {
        textstring = "Thunderstorm";
      } else {
        textstring = "";
      }
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;

      // draw temperature
      textstring = temperature;
      textstring += strcmp(TEMP_UNIT, "metric") == 0 ? "C" : "F";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
