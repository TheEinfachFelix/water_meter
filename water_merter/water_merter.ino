int changevalue = 2;
int current = 0;
char input1 = '1';
uint32_t lasthit;

void setup() {
  lasthit =  millis();

}

void loop() {
  if (analogRead(input1) < changevalue && !analogRead(input1) >= current){
    Serial.println(lasthit - millis());
    lasthit = millis();
    current = analogRead(input1);
  }
  else{
    current = analogRead(input1);
  }
   
}
