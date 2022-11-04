#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>

#include "payload.hpp"

const uint32_t EEPROM_SIZE = 4096;

extern RTC_DS3231 rtc;
extern Adafruit_ADS1115 ads;

extern DallasTemperature Lsensors;
extern DallasTemperature Wsensors;

//------------pin out------------
const uint8_t input1 = 12;
const uint8_t LSensor = 2;
const uint8_t WSensor = 0;
const uint8_t readLED = 15;
const uint8_t testLED = 13;
const uint8_t enable = 12;

//------------adc pin out------------
const uint8_t PhotoR1 = 0;
const uint8_t PhotoR2 = 1;
const uint8_t HallSenFlow = 2;
const uint8_t HallSenDepth = 3;

void export_data();

void collect_data();

void eepromClear();
void eepromPrint();

void SerialResponse();
void sleep();

uint16_t adsRead(int p);
