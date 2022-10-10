const int LightSensor = 16;
const int WLightSensor = 13;
int d = A0;

void setup() {
  // put your setup code here, to run once:
  //pinMode(d, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(d));

}
