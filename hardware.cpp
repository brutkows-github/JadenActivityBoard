/** @file hardware.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>
#ifdef __AVR__
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#endif
#include "hardware.h"

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

Adafruit_NeoPixel strip(15, 38, NEO_GRB + NEO_KHZ800);

int setPixelColorCorrect(uint16_t n, uint32_t c) {
  uint8_t w = (c >> 24);
  uint8_t g = c >> 16;
  uint8_t r = c >> 8;
  uint8_t b = c;

  if (n < 5) {
    //strip.setPixelColor(n, ((uint32_t)w/2)<<24 + ((uint32_t)g/2)<<16 + ((uint32_t)r/2)<<8 + (uint32_t)b/2);
    strip.setPixelColor(n, (c >> 4) & 0x0F0F0F0F);
  } else {
    strip.setPixelColor(n, c);
  }
}

/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

void setupVS1053() {
  Serial.println("Adafruit VS1053 Library Test");
  musicPlayer.sineTest(0x24, 500);    // Make a tone to indicate VS1053 is working
  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
 
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");
  
  // list files
  printDirectory(SD.open("/"), 0);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(0,255);
  /***** Two interrupt options! *******/ 
  // This option uses timer0, this means timer1 & t2 are not required
  // (so you can use 'em for Servos, etc) BUT millis() can lose time
  // since we're hitchhiking on top of the millis() tracker
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);
  
  // This option uses a pin interrupt. No timers required! But DREQ
  // must be on an interrupt pin. For Uno/Duemilanove/Diecimilla
  // that's Digital #2 or #3
  // See http://arduino.cc/en/Reference/attachInterrupt for other pins
  // *** This method is preferred
  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));
}

void setupNeopixel() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void exitSleep() {
  sleep_disable();
}

void enterSleep(void)
{
  // There are five different sleep modes in order of power saving:
  // SLEEP_MODE_IDLE - the lowest power saving mode
  // SLEEP_MODE_ADC
  // SLEEP_MODE_PWR_SAVE
  // SLEEP_MODE_STANDBY
  // SLEEP_MODE_PWR_DOWN - the highest power saving mode
  attachInterrupt(digitalPinToInterrupt(20), exitSleep, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // Now enter sleep mode.
  sleep_mode();

  // The program will continue from here after the WDT timeout

  // First thing to do is disable sleep.
  sleep_disable();

  // Re-enable the peripherals.
  power_all_enable();
}
/*** end of file ***/
