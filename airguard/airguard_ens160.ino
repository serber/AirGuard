#include <Wire.h>

#include "ScioSense_ENS160.h"  // ENS160 library

ScioSense_ENS160 ens160(ENS160_I2CADDR_0);  //0x53..ENS160+AHT21

int humidity;

void setup() {
  Serial.begin(9600);

  while (!Serial) {}

  Serial.println("------------------------------------------------------------");
  Serial.println("ENS160 - Digital air quality sensor");
  Serial.println();
  Serial.println("Sensor readout in standard mode");
  Serial.println();
  Serial.println("------------------------------------------------------------");

  delay(1000);

  Serial.print("ENS160...");

  ens160.begin();

  Serial.println(ens160.available() ? "done." : "failed!");

  if (ens160.available()) {
    // Print ENS160 versions
    Serial.print("\tRev: ");
    Serial.print(ens160.getMajorRev());

    Serial.print(".");
    Serial.print(ens160.getMinorRev());

    Serial.print(".");
    Serial.println(ens160.getBuild());

    Serial.print("\tStandard mode ");

    Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
  }
}

void loop() {
  if (ens160.available()) {
    // Give values to Air Quality Sensor.
    ens160.set_envdata(25.0, 50.0);

    ens160.measure(true);

    ens160.measureRaw(true);

    Serial.print("AQI: ");
    Serial.print(ens160.getAQI());
    Serial.print("\t");

    Serial.print("TVOC: ");
    Serial.print(ens160.getTVOC());
    Serial.print("ppb\t");

    Serial.print("eCO2: ");
    Serial.print(ens160.geteCO2());
    Serial.println("ppm\t");
  }

  delay(1000);
}