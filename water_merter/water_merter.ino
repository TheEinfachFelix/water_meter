#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <IoAbstractionWire.h>
 
RTC_DS3231 rtc;

int changevalue = 600;
bool current = false;
char input1 = '12';
uint32_t lasthit;
int test = 0;

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
  
  
  //EEPROM.write(100,12);


  pinMode(17, INPUT); 
  //attachInterrupt(digitalPinToInterrupt(12),teste,FALLING);
}

void loop() {
  DateTime now = rtc.now();

  Serial.println(analogRead(12));

  //Serial.println(now.unixtime()-1663400000L);
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
