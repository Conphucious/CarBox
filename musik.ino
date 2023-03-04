#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_DFM_RX = 3;
static const uint8_t PIN_DFM_TX = 2;
static const uint8_t PIN_TOGGLE_CONSTANT = 12;
static const uint8_t PIN_TOGGLE_RANDOM = 13;

SoftwareSerial softwareSerial(PIN_DFM_RX, PIN_DFM_TX);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);

  pinMode(PIN_TOGGLE_CONSTANT, INPUT_PULLUP);
  pinMode(PIN_TOGGLE_RANDOM, INPUT_PULLUP);

  if (player.begin(softwareSerial)) {
    Serial.println("Initialized DFPlayer Mini");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play   the first MP3 file on the SD card
    player.play(1);
  } else {
    Serial.println("Connecting   to DFPlayer Mini failed!");
  }
}

void loop() {
  if (digitalRead(PIN_TOGGLE_CONSTANT) == HIGH) {
      Serial.println("CONST HIGH");
    }

    if (digitalRead(PIN_TOGGLE_RANDOM) == HIGH) {
      Serial.println("RAND HIGH");
    }

    
}
