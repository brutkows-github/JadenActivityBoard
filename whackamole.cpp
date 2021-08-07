/** @file whackamole.c
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
#include "whackamole.h"

char *moleSounds[] = {
	"notes/c3.mp3",
	"notes/d3.mp3",
	"notes/e3.mp3",
	"notes/f3.mp3",
	"notes/g3.mp3",
	"notes/c4.mp3",
	"notes/d4.mp3",
	"notes/e4.mp3",
	"notes/g4.mp3",
	"notes/a5.mp3"
};

uint8_t whackAMole() {
	uint32_t colors[4] = {
	  0x000000FF,
    0x0000FF00,
    0x00FF0000,
    0x00FFFFFF
	};
	setAllOff();
	for(int i=0; i<21; ) {
		static int mole = random(10);
    setLed(mole, ON);
		if (getButton(mole) == ON) {
			int led = i%5;
			uint32_t color = 0xFFFFFFFF / (20-i);
			setLed(mole, OFF);
			setPixelColorCorrect(led, colors[i/5]);
			musicPlayer.stopPlaying();
			musicPlayer.startPlayingFile(moleSounds[mole]);
      strip.show();
      while(getButton(mole) == ON);
      delay(10);
			mole = random(10);
			i = i+1;
		}
	}
	winner();
	return 0;
}
