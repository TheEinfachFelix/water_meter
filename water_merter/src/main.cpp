#include "main.hpp"

RTC_DS3231 rtc;
Adafruit_ADS1115 ads;

//------------eeprom vars------------
uint16_t eepromAdres = 2;
bool live = 0;
String packageGet[] = {};
String packagePrint[] = {};
uint8_t packageSize[] = {4, 2, 2, 2, 2, 2, 2}; // 16 byte in total
// storage for 4.194.304/16= 262.144 data points
// but the eeprom can only be writen to ca 100.000 times
// at an interval of 30 minuts you can write data for
// 2.083 days till the eeprom dies or
// 5.461 days thil the eeprom is full
//  so you can write ca 32 byte per intervall and have no problem with eeprom size

//------------deepSleep------------
uint32_t sleepTime = (1 * 60 * 1000000);

//------------gets the length of an array------------
#define ELEMENTCOUNT(x) (sizeof(x) / sizeof(x[0]))

//------------temperatur sensor stuff------------
OneWire LoneWire(LSensor);
OneWire WoneWire(WSensor);
DallasTemperature Lsensors(&LoneWire);
DallasTemperature Wsensors(&WoneWire);

//--------------------------------------------Setup------------------------------------------------
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  delay(800);
  Serial.println("wake up");

  //------------for RTC------------

  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }
  if (rtc.lostPower())
  { // power loss reset
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  //------------end of RTC------------

  //------------temp sensor------------
  Lsensors.begin();
  Wsensors.begin();

  //------------adc stuff------------
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();

  //------------pin things------------
  pinMode(enable, INPUT_PULLUP);
  pinMode(readLED, OUTPUT);
  pinMode(testLED, OUTPUT);

  // eepromClear();
  Serial.println("OK lets Go!");

  //------------loops stuff for deepSleep------------
  digitalWrite(readLED, 1);
  collect_data(); // save stuff to eeprom
  SerialResponse();
  EEPROM.commit();

  digitalWrite(testLED, digitalRead(enable));
  if (digitalRead(enable))
    sleep();
}

//--------------------------------------------loop------------------------------------------------
void loop()
{
  if (live == 1)
  {
    eepromPrint();
  }

  digitalWrite(testLED, digitalRead(enable));

  SerialResponse();
  delay(500);
  if (digitalRead(enable))
  {
    sleep();
  }
}

uint16_t adsRead(int p)
{
  return (ads.readADC_SingleEnded(p));
}

//--------------------------------------------eeprom------------------------------------------------
void eepromPrint()
{
  uint32_t next_slot = get_next_slot();
  if (next_slot == UINT32_MAX)
    next_slot = max_slot_count;

  Serial.println("current slot:" + String(next_slot));

  Payload payload;

  for (uint32_t i = 0; i < next_slot; i++)
  {
    read_payload(i, payload);

    // time
    Serial.print("Time: " + String(payload.time));

    // wtemp
    Serial.print(" Wtemp: " + String(payload.wtemp));
    // ltemp
    Serial.print(" Ltemp: " + String(payload.ltemp));

    // ads

    // PhotoR1
    Serial.print(" PhotoR1: " + String(payload.photo_r1));
    // PhotoR2
    Serial.print(" PhotoR2: " + String(payload.photo_r2));

    // HallSenFlow
    Serial.print(" HallSenFlow: " + String(payload.hal_flow));
    // HallSenDepth
    Serial.print(" HallSenDepth: " + String(payload.hal_depth));

    Serial.println(" a: " + String(i));
  }
}

void eepromClear()
{
  for (int i = 0; i < EEPROM_SIZE; i++)
    EEPROM.write(i, 255);

  EEPROM.commit();
}

//--------------------------------------------Serial------------------------------------------------
void SerialResponse()
{
  String input;
  input = Serial.readString();
  if (input == NULL)
    return;

  else if (input == "print")
  {
    eepromPrint();
  }
  else if (input == "save")
  {
    export_data();
  }
  else if (input == "clear")
  {
    eepromClear();
    Serial.println("cleared!");
  }
  else if (input == "live")
  {
    if (live)
    {
      live = 0;
      Serial.println("Live off");
    }
    else
    {
      live = 1;
      Serial.println("Going Live");
    }
  }
  else if (input == "q")
  {
    Serial.println("quit");
  }
  else
  {
    Serial.println("syntax error");
  }
  Serial.flush();
}

//--------------------------------------------Sleep------------------------------------------------
void sleep()
{
  Serial.println("deep sleep");
  digitalWrite(readLED, 0);
  ESP.deepSleep(sleepTime);
}
