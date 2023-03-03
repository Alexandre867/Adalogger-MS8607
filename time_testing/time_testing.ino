const int dtime = 3333;

void setup() {  
  Serial.begin(9600);
  while (!Serial);
  // int t = 0;
  // while (t<1000) {
  //   Serial.println(t);
  //   t = millis();
  // }
}

void loop() {
  // Do nothing
  delay((millis()/dtime+1)*dtime-millis());
  // while (millis()%dtime > 10) {delay(1);}
  Serial.println(millis()); delay(1);
}
