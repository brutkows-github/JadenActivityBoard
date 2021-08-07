/** @file ledwhenbutton.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Arduino.h>
#include "button.h"
#include "hardware.h"
#include "lightpattern.h"
#include "ledwhenbutton.h"

char *ledSounds[] = {
  "notes/c3.mp3",
  "notes/d3.mp3",
  "notes/e3.mp3",
  "notes/f3.mp3",
  "notes/g3.mp3",
  "notes/a4.mp3",
  "notes/b4.mp3",
  "notes/c4.mp3",
  "notes/d4.mp3",
  "notes/e4.mp3"
};

uint8_t ledWhenButton() {
  bool vals[14];
  static bool lastVals[14];
  setAllOn();
  setLedPct(9, 1);
  while(true) {
      for (int i = 0; i < 10; i++) {
        vals[i] = getButton(i);
        if (vals[i] != lastVals[i]) {
          if(vals[i] == ON) {
            if(i==9){
              setAllOff();
              allLedOff();
              return 0;
            }
            //Serial.println(buttonPins[i]);
            musicPlayer.stopPlaying();
            musicPlayer.startPlayingFile(ledSounds[i]);
            delay(100);
          }
        }
        lastVals[i] = vals[i];
      }
      //display pattern
  }
}

/*** end of file ***/
