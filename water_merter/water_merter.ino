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
const int wSpeed = 17;


//wSpeed vars
int changevalue = 600;
bool current = false;
uint32_t lasthit;

//eeprom vars
uint16_t eepromAdres = 2;
int packageSize[] = {4,2,2};
bool live = 0;

// gets the length of an array
#define ELEMENTCOUNT(x)  (sizeof(x) / sizeof(x[0]))

//temperatur sensor stuff
OneWire LoneWire(LSensor);
OneWire WoneWire(WSensor);
DallasTemperature Lsensors(&LoneWire);
DallasTemperature Wsensors(&WoneWire);

//--------------------------------------------Setup------------------------------------------------
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
  Serial.begin(115200);
  EEPROM.begin(4096);
  Lsensors.begin();
  Wsensors.begin();
  
  pinMode(wSpeed, INPUT); 
  
  //eepromClear();
  Serial.println("OK lets Go!");
}

////--------------------------------------------loop------------------------------------------------
void loop() {
  if (live == 1){
    eepromPrint();
  }
  eepromWrite();
  SerialResponse();
  EEPROM.commit();
  delay(10000);
}

//--------------------------------------------Sensor------------------------------------------------
void w_speed(){
if (analogRead(wSpeed) < changevalue && current == true){
    Serial.println(1000/(millis() - lasthit));
    lasthit = millis();
    current = false;
  }
  if (analogRead(wSpeed) > changevalue){
    current = true;
  }
}

uint16_t Ltemp(){
  Lsensors.requestTemperatures();
  float LtemperatureC = Lsensors.getTempCByIndex(0);
  LtemperatureC = LtemperatureC*100;
  return(LtemperatureC);
}

uint16_t Wtemp(){
  Wsensors.requestTemperatures();
  float WtemperatureC = Wsensors.getTempCByIndex(0);
  WtemperatureC = WtemperatureC*100;
  return(WtemperatureC);
}

uint32_t rtcTime(){
  DateTime now = rtc.now();
  return (now.unixtime()-1665000000L);
}

//--------------------------------------------eeprom------------------------------------------------
void eepromPrint(){
  uint16_t a = 2;
  Serial.println("current adres:" + String(eepromAdres));
  while(a<eepromAdres){
    //time
    uint32_t m1;     
    EEPROM.get(a, m1);
    Serial.print("Time: "+String(m1));
    a += packageSize[0];
    //wtemp
    uint16_t m2;     
    EEPROM.get(a, m2);
    Serial.print(" Wtemp: "+String(m2));
    a += packageSize[1];
    //ltemp
    uint16_t m3;     
    EEPROM.get(a, m3);
    Serial.print(" Ltemp: "+String(m3));
    a += packageSize[2];

    
    Serial.println(" a:"+String(a)); 
  }
}

void eepromClear(){
  EEPROM.put(0,2);
  for (int i = 2; i <= 4000; i++) {
    EEPROM.put(i,0);
  }
  EEPROM.commit();
}

void eepromWrite(){
    EEPROM.get(0,eepromAdres);
  //time
  EEPROM.put(eepromAdres,rtcTime());
  eepromAdres += packageSize[0];
  //wtemp
  EEPROM.put(eepromAdres,Wtemp());
  eepromAdres += packageSize[1];
  //ltemp
  EEPROM.put(eepromAdres,Ltemp());
  eepromAdres += packageSize[2];

  EEPROM.put(0,eepromAdres);
}
//--------------------------------------------Serial------------------------------------------------
void SerialResponse(){
  String input;
  Serial.println("Serial waiting: ");
  Serial.println(Serial && input == NULL);
  while (Serial && input == NULL) {
    input = Serial.readString();
  }
  if (input == "print"){
    eepromPrint();
  }
  else if (input == "clear"){
    eepromClear();
    Serial.println("cleared!");
  }
  else if (input == "live"){
    live = 1;
    Serial.println("Going Live");
  }
  else if (input == "q"){
  Serial.println("quit");
  }
  else{
    Serial.println("syntax error");
  }
}
