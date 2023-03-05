#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Pins
static const uint8_t PIN_DFM_RX = 3;
static const uint8_t PIN_DFM_TX = 2;
static const uint8_t PIN_TOGGLE_CONSTANT = 12;
static const uint8_t PIN_TOGGLE_RANDOM = 13;

// Params
static const uint8_t VOLUME_LEVEL = 20;
static const uint8_t MP3_FOLDER = 1;

// States
static uint8_t toggleState = 0;
static const uint8_t TOGGLE_STATE_CONSTANT_ACTIVE = 1;
static const uint8_t TOGGLE_STATE_RANDOM_ACTIVE = 2;

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
    playClip();
  } else {
    Serial.println("There was an issue initializing DFM!");
  }
}

void loop() {
  if (hasConstantToggleStateChanged() || hasRandomToggleStateChanged()) {
    Serial.println("Toggle setting changed");
    player.pause();
    playClip();
  }
  delay(250);
}


void playClip() {
  if (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) {
    Serial.println("Static clip is being played");
    toggleState = TOGGLE_STATE_CONSTANT_ACTIVE;
    player.readFileCountsInFolder(MP3_FOLDER);
    player.playFolder(MP3_FOLDER, 1);
  } else if (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) {
    Serial.println("Random clip is being played");
    toggleState = TOGGLE_STATE_RANDOM_ACTIVE;
    int fileCountInRandom = player.readFileCountsInFolder(MP3_FOLDER);
    int rngFileNumber = random(1, fileCountInRandom);
    player.playFolder(MP3_FOLDER, rngFileNumber);
  } else {
    Serial.println("There was an issue with the toggle switch");
  }

}

boolean hasConstantToggleStateChanged() {
  return (digitalRead(PIN_TOGGLE_CONSTANT) == LOW) && (toggleState == TOGGLE_STATE_CONSTANT_ACTIVE) || (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) && (toggleState != TOGGLE_STATE_CONSTANT_ACTIVE);
}

boolean hasRandomToggleStateChanged() {
  return (digitalRead(PIN_TOGGLE_RANDOM) == LOW) && (toggleState == TOGGLE_STATE_RANDOM_ACTIVE) || (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) && (toggleState != TOGGLE_STATE_RANDOM_ACTIVE);
}
