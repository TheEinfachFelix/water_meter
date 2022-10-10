#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <IoAbstractionWire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
RTC_DS3231 rtc;

const int input1 = 12;
const int LSensor = 2;
const int WSensor = 0;

int changevalue = 600;
bool current = false;
uint32_t lasthit;
int test = 0;

//temperatur sensor stuff
OneWire LoneWire(LSensor);
OneWire WoneWire(WSensor);
DallasTemperature Lsensors(&LoneWire);
DallasTemperature Wsensors(&WoneWire);

void setup() {
  #ifndef ESP8266 //for RTC
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) { //power loss reset 
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } // end of RTC 

  
  

  lasthit =  millis();
  Serial.begin(9600);
  EEPROM.begin(4096);
  Lsensors.begin();
  Wsensors.begin();
  
  
  //EEPROM.write(100,12);


  pinMode(17, INPUT); 
  //attachInterrupt(digitalPinToInterrupt(12),teste,FALLING);
}

void loop() {
  DateTime now = rtc.now();

  Serial.println(Ltemp());

  Serial.println(now.unixtime()-1665000000L);
  //Serial.println(EEPROM.read(100));
  //w_speed();
  //delay(5000);
}

void w_speed(){
if (analogRead(17) < changevalue && current == true){
    Serial.println(1000/(millis() - lasthit));
    lasthit = millis();
    current = false;
  }
  if (analogRead(17) > changevalue){
    current = true;
  }
}

void teste(){
  test++;
}

float Ltemp(){
  Lsensors.requestTemperatures();
  float LtemperatureC = Lsensors.getTempCByIndex(0);
  return(LtemperatureC);
}

float Wtemp(){
  Wsensors.requestTemperatures();
  float WtemperatureC = Wsensors.getTempCByIndex(0);
  return(WtemperatureC);
}
