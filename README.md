# water_meter

This Project was made for an school projekt to survey rivers. This projekt is only for mesuring the water speed. Some other features might follow.

## Parts
### general
-  wmos d1 mini
-  DS3231 RTC
-  powerbank
-  watertight encloser
-  3D Printer

### Sensors
-  2x linear Hall effekt sensor
-  2x Leds
-  2x Photoresistors
-  2x temp sensors
-  1xADC
-  2x 1000K ohm resistors (for one wire Temp sensor)

## Usage
### Libs
-  RTC DS3231: https://github.com/adafruit/RTClib

### Pin out
Wemos pins:
pin | part
:--------: | :--------
0 | Water temp sensor
2 | Air temp sensor
15 | Status LED
13 | Test LED
4 | sda
2 | sca

ADC pins:
pin | part
:--------: | :--------
A0 | Photo resistor 1
A1 | Photo resistor 2
A2 | Hall Sensor 1
A3 | Hall Sensor 2

### Serial comands
input | result 
:--------: | :--------
"q" | quits the serial loop, to make a round of mesureing
"print" | prints all the data from the eeprom
"live" | will run "print" after every data messure round. To reset this reboot or repeat the comand
"clear" | DELETS the eeprom
