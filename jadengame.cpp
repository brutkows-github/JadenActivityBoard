/** @file jadengame.c
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Brian Rutkowski. All rights reserved.
 */
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include "hardware.h"
#include "button.h"
#include "jadengame.h"
#include "lightpattern.h"

uint8_t jadenGame() {
  static int state = 0;
  const char *soundFiles[] = {
    "jadenl~1/j.mp3",
    "jadenl~1/a.mp3",
    "jadenl~1/d.mp3",
    "jadenl~1/e.mp3",
    "jadenl~1/n.mp3",
    "jadenl~1/jaden.mp3"
  };
  const char *buttonSounds[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "jadenl~1/grandma.mp3",
    "jadenl~1/grandpa.mp3",
    "jadenl~1/brian.mp3",
    "jadenl~1/amanda.mp3",
    "jadenl~1/tesla.mp3",
  };
  while(true) {
    if (state >= 4005) {
      state = 0;
      for (int i = 0; i < 10; i++) {
        //digitalWrite(ledPins[i], HIGH);
        setLed(i, OFF);
        setPixelColorCorrect(i + 5, 0);
        setPixelColorCorrect(i/2, 0);
      }
      setAllOff();
      allLedOff();
      return 0;
    }
    else if (state >= 5) {
      if (state == 5) {
        while (musicPlayer.playingMusic);
        musicPlayer.startPlayingFile(soundFiles[5]);
      }
      if ((state / 200) % 2) {
        for (int i = 0; i < 10; i++) {
          setLed(i, ON);
        }
      } else {
        for (int i = 0; i < 10; i++) {
          setLed(i, OFF);
        }
      }
      state = state + 1;
      rainbow();
      delay(.58);
    }
    else {
      if (digitalRead(buttonPins[state]) == LOW) {
        musicPlayer.stopPlaying();
        musicPlayer.startPlayingFile(soundFiles[state]);
        setPixelColorCorrect((4 - state) + 5, 0xFFFFFFFF);
        setPixelColorCorrect(state + 10, 0xFFFFFFFF);
        setLed(state, OFF);
        state = state + 1;
      } else {
        setLed(state, ON);
      }
      //sound on lower buttons
      for (int i = 5; i < 10; i++) {
        if (digitalRead(buttonPins[i]) == LOW) {
          setLed(i, ON);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(buttonSounds[i]);
          while(musicPlayer.playingMusic) {
            delay(10);
          }
        }
        setLedPct(i, 25);
      }
    }
    //lights on middle buttons
    for (int i = 10; i < 14; i++) {
      setLed(i, !digitalRead(buttonPins[i]));
    }
    strip.show();
    //return 1;
  }
}

/*** end of file ***/
