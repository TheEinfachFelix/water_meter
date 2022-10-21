## Sensors
-  flow meter
-  water level
-  conductivity
-  [x] light level
-  [x] temp (water + Air)
-  water clearaty
-  

## Code 
-  sd card
-  nb iot?
-  [x] Serial interface to print data
-  [x] smart Serial read
-  [x] data logging to eprom
-  [x] power smater data logging
-  [x] low power / deepsleep
-  [x] using interupts to messure speed of water and so on
-  [x] rtc module
-  [x] deep sleep
-  [x] add all readings to eeprom

## Notes
Interupts: The pins D5, D6, D7 work without restrictions; D3 and D4 work, but can not be low on boot, otherwise the WEMOS freezes

eepron: 4 mb size 100.000 writes 
        #include <EEPROM.h> //Einbinden der EEPROM Bibliothekbyte 
        Wert = EEPROM.read(0);
        byte wert = 255;            // übergabe dees Wertes 255 an die neue Vriable wert
        int adresse = 0;            // Festelegen der Adresse
        EEPROM.write(adresse,wert)  // Schreiben der Variable wert in die Adresse adresse

power: normal 70mA sleep 0,15ma
messured: 33mA normal and 2mA sleep


## pcb
-  [x] gnd and vcc pin header
-  [x] deep sleep stuff

## 3d print
-  water hight and flow
-  case

## other
-  power consumtion messuren