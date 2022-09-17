int changevalue = 600;
bool current = false;
char input1 = '17';
uint32_t lasthit;

void setup() {
  lasthit =  millis();
  Serial.begin(9600);
}

void loop() {
  w_speed();
}

void w_speed(){
if (analogRead(17) < changevalue && current == true){
    Serial.println(1000/(millis() - lasthit));
    lasthit = millis();
    current = false;
  }
  if (analogRead(17) > changevalue){
    current = true;
  }
  
}
