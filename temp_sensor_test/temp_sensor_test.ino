#include <OneWire.h>
#include <DallasTemperature.h>

const int LSensor = 2;
const int WSensor = 0;
OneWire LoneWire(LSensor);
OneWire WoneWire(WSensor);
DallasTemperature Lsensors(&LoneWire);
DallasTemperature Wsensors(&WoneWire);

void setup() {
  Serial.begin(115200);
  Lsensors.begin();
  Wsensors.begin();
}

void loop() {
  Lsensors.requestTemperatures(); 
  Wsensors.requestTemperatures(); 
  float LtemperatureC = Lsensors.getTempCByIndex(0);    
  float WtemperatureC = Wsensors.getTempCByIndex(0); 
  Serial.print("Lt: ")
  Serial.println(LtemperatureC);
  Serial.print("Wt: ");
  Serial.println(WtemperatureC);
  delay(1000);
}
