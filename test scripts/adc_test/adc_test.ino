#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

void setup() {
Serial.begin(9600); //gain
ads.setGain(GAIN_TWOTHIRDS);
ads.begin();
}

void loop() {
Serial.print("A0: ");
Serial.print(2*ads.readADC_SingleEnded(0));
Serial.print("  A1: ");
Serial.print(2*ads.readADC_SingleEnded(1));
Serial.print("  A2: ");
Serial.print(2*ads.readADC_SingleEnded(2));
Serial.print("  A3: ");
Serial.println(2*ads.readADC_SingleEnded(3));
delay(1000);
}
