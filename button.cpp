/** @file button.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Arduino.h>
#include "hardware.h"
#include "button.h"

uint8_t setLeds[PINCOUNT];

const int ledPins[PINCOUNT] = {
  //2,3,4,5,6,7,9,10,11,12,13,44,45,46
  44, 46, 7, 2, 3,
  45, 6, 4, 5, 13,
  12, 10, 11, 9 //pushbuttons
};

const int buttonPins[PINCOUNT] = {
  //8,14,15,18,20,53,A8,A9,A10,A11,A12,A13,A14,A15
  53, A14, A12, A10, A8,
  20, A15, A13, A11, A9,
  14, 15, 8, 18 //pushbuttons
};

const int fullOn[PINCOUNT] = {
  224, 204, 196, 0, 196,
  196, 0, 196, 224, 204,
  248, 248, 248, 248
};

void setLed(int n, bool state) {
  if(state == ON) {
    analogWrite(ledPins[n], fullOn[n]);
  } else {
    digitalWrite(ledPins[n], HIGH);
  }
}

void setLedPct(int n, uint8_t pct) {
  if(pct == 0) {
    digitalWrite(ledPins[n], HIGH);
  } else {
    analogWrite(ledPins[n], 255-((uint16_t)(255-fullOn[n]) * (uint16_t)pct / 100));
  }
}

void setLedAllMomentaryOn() {
  for(int i=0; i<10; i++){
    setLed(i, ON);
  }
}

void setAllOn() {
  for(int i=0; i<PINCOUNT; i++){
    setLed(i, ON);
  }
}

void setAllOff() {
  for (int i = 0; i < PINCOUNT; i++) {
    setLed(i, OFF);
  }
}

bool getButton(int n) {
  return digitalRead(buttonPins[n]) == LOW;
}

uint16_t getAllButton() {
  uint16_t retval = 0;
  for(int i=0; i<10; i++) {
    retval += ((uint16_t)getButton(i))<<i;
  }
  return retval;
}

void testButtons() {
  for (int i = 0; i < PINCOUNT; i++) {
    Serial.println(ledPins[i]);
    setLed(i, ON);
    delay(100);
    //digitalWrite(ledPins[i], HIGH);
  }
  for (int i = 0; i < PINCOUNT; i++) {
    Serial.println(ledPins[i]);
    setLed(i, OFF);
    delay(100);
    //digitalWrite(ledPins[i], HIGH);
  }
}

void setupButtons() {
  for (int i = 0; i < PINCOUNT; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
    digitalWrite(ledPins[i], HIGH);
  }
}

/*** end of file ***/
