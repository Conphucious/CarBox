#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_DFM_TX   = 2;
static const uint8_t PIN_DFM_RX = 3;
static const uint8_t PIN_ = 3;
static const uint8_t PIN_MP3_RX = 3;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

//   Create the Player object
DFRobotDFPlayerMini player;

void setup() {

  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial   port for DFPlayer Mini
  softwareSerial.begin(9600);

  if
  // Start communication   with DFPlayer Mini
  if (player.begin(softwareSerial)) {
      Serial.println("OK");

      // Set volume to maximum (0 to 30).
      player.volume(30);
      // Play   the first MP3 file on the SD card
      player.play(1);
    } else {
      Serial.println("Connecting   to DFPlayer Mini failed!");
    }
}

void loop() {
}
