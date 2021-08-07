/** @file lightpattern.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Arduino.h>
#include "hardware.h"
#include "lightpattern.h"
#include "button.h"

// buttons is a bitmask of the buttons to fade.
void fade(uint16_t buttons) {
  static uint8_t pct = 1;
  for(uint16_t i = 0; i < PINCOUNT; i++) {
      static bool updn = 1;
      if(buttons & (1<<i)) {
        setLedPct(i, pct);
        // change the brightness for next time through the loop:
        if(updn) ++pct; else --pct;
        // reverse the direction of the fading at the ends of the fade:
        if (pct <= 1 || pct >= 100) {
          updn = !updn;
        }
      }
  }
};

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow() {
  static long firstPixelHue = 0;
  static int i = 0;
  int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
  pixelHue = strip.gamma32(strip.ColorHSV(pixelHue));
  setPixelColorCorrect(i, pixelHue);
  strip.show();
  i += 1;
  if (i >= strip.numPixels()) {
    i = 0;
    firstPixelHue += 256;
  }
  if (firstPixelHue >= 5 * 65536) firstPixelHue = 0;
}

void rainbow2() {
  uint32_t c = 0;
  c+= getButton(10) ? 0x00FF0000 : 0;
  c+= getButton(11) ? 0x0000FF00 : 0;
  c+= getButton(12) ? 0x000000FF : 0;
  //c+= getButton(13) ? (uint32_t)0xFF : 0;
  for(int i=0; i<strip.numPixels(); i++) {
    setPixelColorCorrect(i, c);
  }
  strip.show();
}

void lightWhenPushed() {
    for (int i = 0; i < PINCOUNT; i++) {
      setLed(i, getButton(i));
    }
}

void allLedColor(uint32_t c) {
  for(int i=0; i<strip.numPixels(); i++) {
    setPixelColorCorrect(i, c);
  }
}

void allLedOff() {
  for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
  }
  strip.show();
}


void winner() {
	for (int time=0; time<6000; time++) {
		rainbow();
		delay(1);
	}
  allLedOff();
}

/*** end of file ***/
