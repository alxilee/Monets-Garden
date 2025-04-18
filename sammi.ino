#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

// Motor
// Breakbeam Sensor + MP3 Player

// Define your pins
#define LEDPIN 13           // Pin 13 is for the onboard LED
#define SENSORPIN 4         // Pin 4 for the IR Breakbeam sensor

// Tell Arduino which pins are wired to MP3 player (remember RX on Arduino is TX on MP3 player)
SoftwareSerial DF1201SSerial(2, 3);  // Arduino RX (2), Arduino TX (3)

// Object to handle all communication with the MP3 player
DFRobot_DF1201S DF1201S;

// Variables for the breakbeam sensor
int sensorState = 0, lastState = 0;  // Variable to store the sensor states

void setup() {
  // Initialize the LED pin as an output
  pinMode(LEDPIN, OUTPUT);
  // Initialize the sensor pin as an input
  pinMode(SENSORPIN, INPUT);
  digitalWrite(SENSORPIN, HIGH);  // Enable the internal pull-up resistor
  
  // Initialize MP3 player communication
  DF1201SSerial.begin(115200);
  while (!DF1201S.begin(DF1201SSerial)) {
    Serial.println("MP3 Init failed, please check the wire connection!");
    delay(1000);
  }
  
  DF1201S.setVol(6);  // Set volume
  delay(500);
  DF1201S.switchFunction(DF1201S.