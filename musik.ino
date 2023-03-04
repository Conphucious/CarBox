#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_DFM_RX = 3;
static const uint8_t PIN_DFM_TX = 2;
static const uint8_t PIN_TOGGLE_CONSTANT = 12;
static const uint8_t PIN_TOGGLE_RANDOM = 13;
static const uint8_t VOLUME_LEVEL = 30;

SoftwareSerial softwareSerial(PIN_DFM_RX, PIN_DFM_TX);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);

  // Initialize the toggle switch pins
  pinMode(PIN_TOGGLE_CONSTANT, INPUT_PULLUP);
  pinMode(PIN_TOGGLE_RANDOM, INPUT_PULLUP);

  if (player.begin(softwareSerial)) {
    Serial.println("Initialized DFM!");
    player.volume(VOLUME_LEVEL);
    if (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) {
      player.play(1); // First file will always be static ON file
    } else if (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) {
      player.randomAll();
    } else {
      Serial.println("There was an issue wit the toggle switch!");
    }
  } else {
    Serial.println("There was an issue initializing DFM!");
  }
}

void loop() {}
