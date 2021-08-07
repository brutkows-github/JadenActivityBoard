/** @file button.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski.  All rights reserved.
 */ 

#ifndef BUTTON_H
#define BUTTON_H
#define PINCOUNT 14

extern const int ledPins[PINCOUNT];
extern uint8_t setLeds[PINCOUNT];
extern const int buttonPins[PINCOUNT];//pushbuttons
extern const int fullOn[PINCOUNT];

void setLed(int n, bool state);
void setLedAllMomentaryOn();
void setLedPct(int n, uint8_t pct);
void setAllOff();
void setAllOn();
bool getButton(int n);
uint16_t getAllButton();
void testButtons();
void setupButtons();

#endif /* BUTTON_H */

/*** end of file ***/
