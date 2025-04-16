#include <Adafruit_NeoPixel.h>

// Shake Sensor + LED Flower
// Breakbeam Sensor + Neopixel Bridge Lighting

// Shake Sensor Code
const int shakeSensorPin = 2;     // Shake sensor connected to pin 2
const int flowerLedPin = 13;       // Flower LED connected to pin 13

// NeoPixel LED Code
#define BRIDGE_SENSORPIN 4 // Bridge breakbeam sensors
#define PIN_NEO_PIXEL  8   // Arduino pin that connects to bridge light
#define NUM_PIXELS     21  // Number of LEDs

Adafruit_NeoPixel bridgeLights(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

// Variables to track bridge lighting timing
int beamSensorState = 0, lastBeamState = 1;
unsigned long bridgeTriggerTime = 0;
bool bridgeIsLit = false;

void setup() {
  // Set up for Hole & Flower
  pinMode(shakeSensorPin, INPUT_PULLUP);  // Enable internal pull-up resistor
  pinMode(flowerLedPin, OUTPUT);           // Set LED pin as output

  // Set up Bridge & Breakbeam
  pinMode(BRIDGE_SENSORPIN, INPUT_PULLUP);
  Serial.begin(115200);

  bridgeLights.begin();  // Initialize bridge light
  bridgeLights.clear();  // Turn off light at the start
  bridgeLights.show();
}

void loop() {
  // Shake Sensor Logic
  int shakeSensorState = digitalRead(shakeSensorPin);
  Serial.println(shakeSensorState); // <-- This prints 1 (not shaking) or 0 (shaking)

  if (shakeSensorState == LOW) {           // Shake detected from marble (connected to GND)
    digitalWrite(flowerLedPin, HIGH);       // Light up flower
    delay(5000);                           // Stay lit for 5 seconds
    digitalWrite(flowerLedPin, LOW);        // Turn flower off
  }

  // Beam Sensor Logic (Bridge lights up when sensor is triggered)
  beamSensorState = digitalRead(BRIDGE_SENSORPIN);

  if (beamSensorState == LOW && lastBeamState == HIGH) {
    Serial.println("Bridge Beam Broken - Lights On");
    bridgeIsLit = true;
    bridgeTriggerTime = millis();
    lightUpBridge();
  }

  // If 5 seconds have passed, turn off bridge lights
  if (bridgeIsLit && ((millis() - bridgeTriggerTime) >= 5000)) {
    Serial.println("Turning Bridge Lights Off");
    turnOffBridge();
    bridgeIsLit = false;
  }

  lastBeamState = beamSensorState; // Update last sensor state
}

// Bridg