#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>

#include "payload.hpp"
#include "const.hpp"

extern RTC_DS3231 rtc;
extern Adafruit_ADS1115 ads;

extern DallasTemperature Lsensors;
extern DallasTemperature Wsensors;

void export_data();
void print_payload(const Payload &p);
void collect_data();

void eepromClear();
void eepromPrint();

void SerialResponse();
void sleep();

uint16_t adsRead(int p);
