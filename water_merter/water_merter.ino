int changevalue = 600;
bool current = false;
char input1 = '17';
uint32_t lasthit;

void setup() {
  lasthit =  millis();
  Serial.begin(9600);
}

void loop() {
  if (analogRead(17) < changevalue && current == true){
    Serial.println((millis() - lasthit)*100);
    lasthit = millis();
    current = false;
  }
  if (analogRead(17) > changevalue){
    current = true;
  }
}
