void setup() {
  Serial.begin (9600);
  analogReference(DEFAULT);
  pinMode(A0, INPUT_PULLUP); //Potentiometer
  pinMode (A1, INPUT_PULLUP);  //Temp Reader
}
unsigned long now = millis();
void loop() {
  if(millis() >= now + 3000) {
    //Debugger Messge
      Serial.write(0x21);
      Serial.write(0x30);
      message("Debug");
    
    //Sending timestamp of loop
      Serial.write(0x21);
      Serial.write(0x32);
      Serial.write(now>>24);
      Serial.write(now>>16);
      Serial.write(now>>8);
      Serial.write(now);
  

   //Potentiometer
      int pot = analogRead(A0);
//      Serial.println(pot);
      Serial.write(0x21);
      Serial.write(0x33);
      Serial.write(pot>>8);
      Serial.write(pot);

   //Float Code
      float raw = analogRead(A1);
      float voltage = (5.0/1024) * raw;
      float temp = (voltage * 100.0) - 50.0;
      float reads[7];
      int arrayCount = 0;
      reads[arrayCount % 7] = temp;
      arrayCount += 1;
       float filtered = 0;
        for (int i = 0; i < 7; i++) {
          filtered = ((1.0/7.0)* reads[i]) + filtered;
        }
      unsigned long rawBits;
      rawBits = *(unsigned long *) &raw;
   //Raw counts value
      Serial.write(0x21);
      Serial.write(0x34);
      Serial.write(rawBits>>24);
      Serial.write(rawBits>>16);
      Serial.write(rawBits>>8);
      Serial.write(rawBits);
      unsigned long temperature;
      temperature = *(unsigned long *) &temp;
   //Temperature value
      Serial.write(0x21);
      Serial.write(0x35);
      Serial.write(temperature>>24);
      Serial.write(temperature>>16);
      Serial.write(temperature>>8);
      Serial.write(temperature);
      unsigned long average;
      average = *(unsigned long *) &filtered;
  //Average Filtered Value
//      Serial.write(0x21);
//      Serial.write(0x36);
//      Serial.write(average>>24);
//      Serial.write(average>>16);
//      Serial.write(average>>8);
//      Serial.write(average);
      Serial.print(average);

    if(analogRead(A0)>680) {
      message("!High Alarm!");
    }
    now = now + 3000;
  }
}

void message(char word[]) {
  int one = strlen(word);
  //Serial.println(one);
  Serial.write(one>>8);
  Serial.write(one);
  Serial.write(word);
//  for (int i=0; i<one; i++){
//    Serial.write(word[i]);
//  }
}



