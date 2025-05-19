#include <Arduino.h>
#include "HX711.h"

// HX711 load cell circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int CALIBRATION_FACTOR = -16150/819; // this value was obtained by calibrating the strain gauge with known weights (HX711 output / known book weight)

HX711 scale;

void setup() {
  Serial.begin(57600);

  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);  // intialising pin D12 as output for the light

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // initialising the scale pins

            
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();               // reset the scale to 0

}

void loop() {
  Serial.print("reading:\t");
  Serial.println(scale.get_units(5), 1); // serial printing the average of the last 5 measurements. this is to reduce noise in the cheap strain gauges.

  digitalWrite(12, scale.get_units(5) > 200 ? HIGH : LOW); // if measured book weight is larger than 200g turn the light off.
}