#include "payload.hpp"

#include <EEPROM.h>

void save_payload(uint32_t slot, const Payload &payload)
{
  uint32_t offset = (slot * slot_size);
  EEPROM.put(offset, payload);
}

Payload read_payload(uint32_t slot)
{
  uint32_t offset = (slot * slot_size);
  Payload payload;
  EEPROM.get(offset, payload);
  return payload;
}

void read_payload(uint32_t slot, Payload &payload)
{
  uint32_t offset = (slot * slot_size);
  EEPROM.get(offset, payload);
}

uint32_t get_next_slot()
{
  for (uint32_t i = 0; i < max_slot_count; i++)
  {
    Payload p = read_payload(i);
    if (p.time == 0xFFFFFFFF)
      return i;
  }
  return UINT32_MAX;
}
