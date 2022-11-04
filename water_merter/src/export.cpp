
#include "main.hpp"

void print_payload(const Payload &p)
{
  // line format: time,wtemp,ltemp,photo_r1,photo_r2,hal_flow_hal_depth
  String line;
  line += String(p.time) + ",";
  line += String(p.wtemp) + ",";
  line += String(p.ltemp) + ",";
  line += String(p.photo_r1) + ",";
  line += String(p.photo_r2) + ",";
  line += String(p.hal_flow) + ",";
  line += String(p.hal_depth);
  Serial.println(line);
}

void export_data()
{
  uint32_t next_slot = get_next_slot();
  if (next_slot == UINT32_MAX)
    next_slot = max_slot_count;

  Payload payload;

  for (uint32_t i = 0; i < next_slot; i++)
  {
    read_payload(i, payload);
    print_payload(payload);
  }
}
