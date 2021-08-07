/** @file button.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski.  All rights reserved.
 */ 

#ifndef HARDWARE_H
#define HARDWARE_H

#define pinCount 14
#define ON 1
#define OFF 0

// These are the pins used for the music maker shield
#define SHIELD_RESET  42      // VS1053 reset pin (unused!)
#define SHIELD_CS     47      // VS1053 chip select pin (output)
#define SHIELD_DCS    48      // VS1053 Data/command select pin (output)
#define VS1053_RX  16 // This is the pin that connects to the RX pin on VS1053

// These are common pins between breakout and shield
#define CARDCS 49     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 21       // VS1053 Data request, ideally an Interrupt pin
#include <Adafruit_VS1053.h>
#include <Adafruit_NeoPixel.h>

extern Adafruit_VS1053_FilePlayer musicPlayer;
extern Adafruit_NeoPixel strip;

int setPixelColorCorrect(uint16_t n, uint32_t c);
void printDirectory(File dir, int numTabs);
void setupVS1053();
void setupNeopixel();
void setupButtons();
void enterSleep();

#endif /* HARDWARE_H */

/*** end of file ***/
