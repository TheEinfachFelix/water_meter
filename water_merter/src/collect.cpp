#include "main.hpp"

void collect_data()
{
  uint32_t next_slot = get_next_slot();
  if (next_slot == UINT32_MAX)
  {
    Serial.println("Meep! Memory full!");
    return;
  }

  Wsensors.requestTemperatures();
  Lsensors.requestTemperatures();

  Payload payload;
  payload.time = rtc.now().unixtime();
  payload.wtemp = Wsensors.getTempCByIndex(0) * 1000; // mC°
  payload.ltemp = Lsensors.getTempCByIndex(0) * 1000; // mC°
  payload.photo_r1 = adsRead(PhotoR1);
  payload.photo_r2 = adsRead(PhotoR2);
  payload.hal_flow = adsRead(HallSenFlow);
  payload.hal_depth = adsRead(HallSenDepth);

  save_payload(next_slot, payload);
}
