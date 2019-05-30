const unsigned long beatPeriod = 250;
const unsigned long lightPeriod = 100;
unsigned long hertz = 0;
const int FILTER_COUNTS = 7;
float reads[FILTER_COUNTS];
unsigned long tempCount = 0;
unsigned long lightCount = 0;
unsigned long offCount = 0;
unsigned long arrayCount = 0;
double rollingAverage = 0;
int reading = 0;
double temp;
double voltage;



void setup() {
  Serial.begin (9600);
  analogReference(INTERNAL);
  pinMode (2, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  if(now >= tempCount) {
    readTemp();
    tempCount = now + beatPeriod;
      
    Serial.print (temp);
    Serial.print(",");
    Serial.println(rollingAverage);
  }

  if(now >= lightCount) {
    hertz = 60000/((7*temp) - 30);
    lightCount = now + hertz;
    digitalWrite(2, HIGH);
    offCount = now + lightPeriod;
  }

  if(now >= offCount) {
    digitalWrite(2, LOW);
  }

}

void readTemp() {
  for(int i=0; i< FILTER_COUNTS; i++) {
    reading = analogRead(A1);
    voltage = (1.1/1024) * reading;
    temp = (voltage * 100.0) - 50.0;
    reads[arrayCount % FILTER_COUNTS] = temp;
    arrayCount += 1;
   rollingAverage = 0;
    for (int i = 0; i < FILTER_COUNTS; i++) {
      rollingAverage = ((1.0/FILTER_COUNTS)* reads[i]) + rollingAverage;
    }
  }
}

