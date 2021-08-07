/** @file soundwhenbutton.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Arduino.h>
#include "hardware.h"
#include "button.h"
#include "lightpattern.h"
#include "soundwhenbutton.h"

char *buttonSounds[] = {
  "jadenl~1/j.mp3",
  "jadenl~1/a.mp3",
  "jadenl~1/d.mp3",
  "jadenl~1/e.mp3",
  "jadenl~1/n.mp3",
  "jadenl~1/grandma.mp3",
  "jadenl~1/grandpa.mp3",
  "notes/e3.mp3",
  "notes/g3.mp3",
  "notes/a4.mp3"
};

uint8_t soundWhenButton() {
  bool vals[14];
  static bool lastVals[14];
  setAllOn();
  setLedPct(9, 10);
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
            musicPlayer.startPlayingFile(buttonSounds[i]);
            delay(100);
          }
        }
        lastVals[i] = vals[i];
      }
      if(musicPlayer.playingMusic) {
        rainbow();
        delay(10);
      }
  }
}
/*** end of file ***/
