/** @file module.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Arduino.h>
#include "hardware.h"
#include "menu.h"
#include "lightpattern.h"
#include "button.h"
#include "jadengame.h"
#include "whackamole.h"
#include "ledwhenbutton.h"
#include "soundwhenbutton.h"

uint8_t (*modes[10])(void) = {
  &jadenGame,
  NULL,
  &whackAMole,
  NULL,
  //&enterSleep,
  &soundWhenButton,
  NULL,
  NULL,
  //&ledWhenButton,
  NULL,
  NULL,
  NULL, 
};
uint16_t modefade = 0b0000010101;

void menu() {
  static int mode = 0;
  while(true)jadenGame();
  if(mode == 0) {
    for(int i=0; i<10; i++) {
      if(getButton(i) == ON) {
        //mode = i;
        while(modes[i]) {
          setAllOff();
          while(getButton(i) == ON);
          delay(10);
          if((*modes[i])() == 0) break;
        }
      }
    }
    fade(modefade);
    //fade(0b11111111111111);
    delay(40);
  }
}

/*** end of file ***/
