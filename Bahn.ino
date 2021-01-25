#include <Watchy.h> //include the Watchy library
#include <DIN_1451_Engschrift_Regular64pt7b.h>
#include <DIN_1451_Engschrift_Regular14pt7b.h>
				

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h;
      String textstring;
      bool light = true;
      
      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.fillRoundRect(2,2,196,196,8,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(6,6,188,188,2,light ? GxEPD_WHITE : GxEPD_BLACK);
      
      display.setFont(&DIN_1451_Engschrift_Regular64pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);

      //draw hours
      textstring = currentTime.Hour;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(184-w, 100-5-h);
      display.print(textstring);
      
      //draw minutes
      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(184-w, 100+5);
      display.print(textstring);

      // draw battery
      display.fillRoundRect(16,16,34,12,4,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(49,20,3,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(17,17,32,10,3,light ? GxEPD_WHITE : GxEPD_BLACK);
      float batt = (getBatteryVoltage()-3.8)/0.45;
      if (batt > 0) {
        display.fillRoundRect(18,18,30*batt,8,2,light ? GxEPD_BLACK : GxEPD_WHITE);
												
								// draw steps
												display.setFont(&DIN_1451_Engschrift_Regular14pt7b);
							textstring = sensor.getCounter();
							textstring += " steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
							display.setTextColor(light ? GxEPD_WHITE : GxEPD_BLACK);
							display.fillRoundRect(16,16,w+4,h+4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setCursor(18, 200-18-h);
      display.print(textstring);
							lasty = 200-16-h-4;
												
								// draw year
							 display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
							textstring = currentTime.Year + 1970;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty - 6 - h);
      display.print(textstring);
							lasty += -6-h;
												
							// draw date
							textstring = monthShortStr(currentTime.Month);
							textstring += " ";
							textstring += currentTime.Day;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty - 6 - h);
      display.print(textstring);
							lasty += -6-h;
												
							// draw day
							textstring = dayStr(currentTime.Wday);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty - 6 - h);
      display.print(textstring);
							lasty += -6-h;
								
      }
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
