#pragma once

#include <cinttypes>

const uint32_t EEPROM_SIZE = 4096;

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
