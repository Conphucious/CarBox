#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Pins
static const uint8_t PIN_DFM_RX = 3;
static const uint8_t PIN_DFM_TX = 2;
static const uint8_t PIN_TOGGLE_CONSTANT = 12;
static const uint8_t PIN_TOGGLE_RANDOM = 13;

// Params
static const uint8_t VOLUME_LEVEL = 30;
static const uint8_t ROOT_FOLDER = 0;
static const uint8_t RANDOM_FOLDER = 1;

// States
//static uint8_t toggleStateConstant = 0;
//static uint8_t toggleStateRandom = 0;

SoftwareSerial softwareSerial(PIN_DFM_RX, PIN_DFM_TX);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);

  // Initialize the toggle switch pins and state
  pinMode(PIN_TOGGLE_CONSTANT, INPUT_PULLUP);
  pinMode(PIN_TOGGLE_RANDOM, INPUT_PULLUP);
  randomSeed(analogRead(A0));

  if (player.begin(softwareSerial)) {
    Serial.println("Initialized DFM!");
    player.setTimeOut(2000);
    player.volume(VOLUME_LEVEL);
    player.disableLoop();
    if (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) {
      Serial.println("Static clip being played");
      player.readFileCountsInFolder(ROOT_FOLDER);
      player.play(1); // First file in root will always be ALWAYS_ON.mp3 for this toggle
    } else if (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) {
      Serial.println("Random clip being played");
      int fileCountInRandom = player.readFileCountsInFolder(RANDOM_FOLDER);
      Serial.println(fileCountInRandom);
      int rngFileNumber = random(1, fileCountInRandom);
      Serial.println(rngFileNumber);
      player.playFolder(RANDOM_FOLDER, rngFileNumber);
    } else {
      Serial.println("There was an issue with the toggle switch");
    }




  } else {
    Serial.println("There was an issue initializing DFM!");
  }
}

void loop() {}
  //  Serial.println("ALL");
  //  Serial.println(hasToggleStateChanged());
  //  if (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) {
  //    toggleStateConstant = 1;
  //  } else {
  //    toggleStateConstant = 0;
  //  }
  //
  //  if (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) {
  //    toggleStateRandom = 1;
  //  } else {
  //    toggleStateRandom = 0;
  //  }
  //
  //
  //  if (hasToggleStateChanged == true) {
  //    player.pause();
  //    playClip();
  //  }
//}
//
//void playClip() {
//  if (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) {
//    toggleStateConstant = 1;
//    toggleStateRandom = 0;
//    player.readFileCountsInFolder(ROOT_FOLDER);
//    player.play(1); // First file in root will always be ALWAYS_ON.mp3 for this toggle
//  } else if (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) {
//    toggleStateRandom = 1;
//    toggleStateConstant = 0;
//    randomSeed(analogRead(A0));
//    int fileCountInRandom = player.readFileCountsInFolder(RANDOM_FOLDER);
//    int rngFileNumber = random(1, fileCountInRandom);
//    player.play(rngFileNumber);
//  } else {
//    Serial.println("There was an issue with the toggle switch!");
//  }
//}
//
//
//bool hasToggleStateChanged() {
//  if (((digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) && toggleStateConstant == 0)) {
//    toggleStateConstant = 1;
//    return true;
//  } else if (((digitalRead(PIN_TOGGLE_CONSTANT) == LOW) && toggleStateConstant == 1)) {
//    toggleStateRandom = 0;
//    return true;
//  } else if (((digitalRead(PIN_TOGGLE_RANDOM) == HIGH) && toggleStateRandom == 0)) {
//    toggleStateRandom = 1;
//    return true;
//  } else if (((digitalRead(PIN_TOGGLE_RANDOM) == LOW) && toggleStateRandom == 1)) {
//    toggleStateRandom = 0;
//    return true;
//  }
//  return false;
//}
