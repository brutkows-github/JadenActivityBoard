#include "button.h"
#include "hardware.h"
#include "menu.h"


int timer = 1000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupButtons();
  setupNeopixel();
  while (digitalRead(buttonPins[0]) == LOW);
  setupVS1053();
  testButtons();
  musicPlayer.playFullFile("notes/a3.mp3");
  //musicPlayer.playFullFile("notes/a4.mp3");
  //musicPlayer.playFullFile("notes/a5.mp3");
}

bool lastVals[14];
void loop() {
  menu();
  //jadenGame();
  //fade();
  //whackAMole();
  //rainbow2();
  //ledWhenButton();
  //soundWhenButton();
  delay(1);
}
