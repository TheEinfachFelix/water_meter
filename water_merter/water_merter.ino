#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
 
RTC_DS3231 rtc;
Adafruit_ADS1115 ads;

// pin out
const uint8_t input1 = 12;
const uint8_t LSensor = 2;
const uint8_t WSensor = 0;
const uint8_t readLED = 15;
const uint8_t testLED = 13;
const uint8_t enable = 12;

//adc pin out
const uint8_t PhotoR1 = 0;
const uint8_t PhotoR2 = 1;
const uint8_t HallSenFlow = 2;
const uint8_t HallSenDepth = 3;

//eeprom vars
uint16_t eepromAdres = 2;
uint8_t packageSize[] = {4,2,2,2,2,2,2};
bool live = 0;

//deepSleep
uint32_t deepSleep = (1*60*1000000);

// gets the length of an array
#define ELEMENTCOUNT(x)  (sizeof(x) / sizeof(x[0]))

//temperatur sensor stuff
OneWire LoneWire(LSensor);
OneWire WoneWire(WSensor);
DallasTemperature Lsensors(&LoneWire);
DallasTemperature Wsensors(&WoneWire);

//--------------------------------------------Setup------------------------------------------------
void setup() {  
  Serial.begin(115200);
  EEPROM.begin(4096);
  delay(600);
  Serial.println("wake up");
  
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

  //temp sensor
  Lsensors.begin();
  Wsensors.begin();
  //adc stuff
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();

  pinMode(enable, INPUT_PULLUP); 
  pinMode(readLED, OUTPUT); 
  pinMode(testLED, OUTPUT); 
  
  //eepromClear();
  Serial.println("OK lets Go!");
    
////////////////////////////////////////////////////
  digitalWrite(readLED, 1);
  eepromWrite();
  SerialResponse();
  EEPROM.commit();
  
  digitalWrite(testLED, digitalRead(enable));
  if(digitalRead(enable)){
    sleep();
  }
}

//--------------------------------------------loop------------------------------------------------
void loop() {
  if (live == 1){
    eepromPrint();
  }

  digitalWrite(testLED, digitalRead(enable));

  SerialResponse();
  delay(500);
  if(digitalRead(enable)){
    sleep();
  }
}

//--------------------------------------------Sensor------------------------------------------------
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

uint16_t adsRead(int p){
  return(ads.readADC_SingleEnded(p));
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
    //ads
    //sen1
    uint16_t m4;     
    EEPROM.get(a, m4);
    Serial.print(" Sen1: "+String(m4));
    a += packageSize[3];
    //sen2
    uint16_t m5;     
    EEPROM.get(a, m5);
    Serial.print(" Sen2: "+String(m5));
    a += packageSize[4];
    //sen3
    uint16_t m5;     
    EEPROM.get(a, m5);
    Serial.print(" Sen3: "+String(m5));
    a += packageSize[5];
    //sen4 
        uint16_t m6;     
    EEPROM.get(a, m6);
    Serial.print(" Sen1: "+String(m6));
    a += packageSize[6];

    
    Serial.println(" a:"+String(a)); 
  }
}

void eepromClear(){
  EEPROM.put(0,2);
  for (int i = 2; i <= 4000; i++) {
    EEPROM.put(i,0);
  }
  EEPROM.commit();
  eepromAdres = 2;
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
  //adc
  EEPROM.put(eepromAdres,adsRead(PhotoR1));
  eepromAdres += packageSize[3];
  EEPROM.put(eepromAdres,adsRead(PhotoR2));
  eepromAdres += packageSize[4];
  EEPROM.put(eepromAdres,adsRead(HallSenFlow));
  eepromAdres += packageSize[5];
  EEPROM.put(eepromAdres,adsRead(HallSenDepth));
  eepromAdres += packageSize[6];


  EEPROM.put(0,eepromAdres);
}
//--------------------------------------------Serial------------------------------------------------
void SerialResponse(){
  String input;
  input = Serial.readString();
  if (input == NULL){}
  else if (input == "print"){
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
  Serial.flush();
}

//--------------------------------------------Sleep------------------------------------------------
void sleep(){
  Serial.println("deep sleep");
  digitalWrite(readLED, 0);
  ESP.deepSleep(sleepTime);
}
