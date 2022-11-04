#pragma once

#include "const.hpp"

#include <cinttypes>

struct Payload
{
  uint32_t time;
  uint16_t wtemp;
  uint16_t ltemp;
  uint16_t photo_r1;
  uint16_t photo_r2;
  uint16_t hal_flow;
  uint16_t hal_depth;
};

void save_payload(uint32_t slot, const Payload &payload);
Payload read_payload(uint32_t slot);
void read_payload(uint32_t slot, Payload &payload);
uint32_t get_next_slot();

const uint32_t slot_size = sizeof(Payload);
const uint32_t max_slot_count = EEPROM_SIZE / slot_size;
