#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

MMA8452Q accel;

enum State {
    pedometer,
    sleepTracker,
};

const char magicNumber = 0x32;
const char debug = 0x50;
const char error = 0x51;
const char temp = 0x52;
const char sleepTrackerCode = 0x54;
const char pedometerCode = 0x55;
const char stepRateCode = 0x56;

const unsigned long restPeriod = 1000;
unsigned long nextReadTime = 0;
unsigned long holdTime = 0;
unsigned long beatTime = restPeriod;
int rawReading = 0;

unsigned long lastReset = 0;
unsigned long timeSinceReset = millis() - lastReset;

unsigned long timeAsleep = 0;
unsigned long now = 0;

int stepCount = 0;
double values[11];
float tempVal;
float calculated = 0;

State counterState = sleepTracker;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT_PULLUP); //Temp Reader
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(13, OUTPUT);
    accel.init();
}

void loop() {
    counterState = nextState(counterState);

    if (millis() - holdTime >= restPeriod) {
        holdTime = holdTime + beatTime;
//        debugMessage(debugString);
//        errorMessage(errorString);
        tempReading();
//        totalRunTime();

        if (counterState == pedometer) {
            stepSender();
        }
        else if (counterState == sleepTracker) {
            sleepSender();
        }
    }
}

void stepRateSender() {
    Serial.write(magicNumber);
    Serial.write(stepRateCode);
    unsigned long timeTracked;
    timeTracked = *(unsigned long*) &timeSinceReset;
    Serial.write(timeTracked >> 24);
    Serial.write(timeTracked >> 16);
    Serial.write(timeTracked >> 8);
    Serial.write(timeTracked);
    
}

void tempReading() {
    rawReading = analogRead(A0);
    calculated = 25 + ((rawReading - 750) * 0.1);
    Serial.write(magicNumber);
    Serial.write(temp);
    unsigned long rawBits;
    rawBits = *(unsigned long*) &calculated;
    Serial.write(rawBits >> 24);
    Serial.write(rawBits >> 16);
    Serial.write(rawBits >> 8);
    Serial.write(rawBits);
}

void sleepSender() {
    Serial.write(magicNumber);
    Serial.write(sleepTrackerCode);
    unsigned long rawBits;
    rawBits = *(unsigned long*) &timeAsleep;
    Serial.write(rawBits >> 24);

    Serial.write(rawBits >> 16);
    Serial.write(rawBits >> 8);
    Serial.write(rawBits);
}

void stepSender() {
    Serial.write(magicNumber);
    Serial.write(pedometerCode);
    int totalSteps = stepCount;
    Serial.write(totalSteps >> 8);
    Serial.write(totalSteps);
    
}

State nextState(State state) {
    switch (state) {
        case sleepTracker:
            digitalWrite(13, HIGH); // light on
                now = millis();
                if ( (now >= nextReadTime) ) {
                    if (analogRead(A1) == LOW) {
                        delay(100);
                        if (analogRead(A1) == LOW) {
                            state = pedometer;
                            break;
                        }
                    }
                    if (analogRead(A2) == LOW) {
                    delay(100);
                        if (analogRead(A2) == LOW) {
                            timeAsleep = 0;
                        }
                    }
                    if (accel.available()) {
                        accel.read();
                        if (accel.cx > 0.1 || accel.cy > 0.1 || accel.cz > 1.1) {
//                            delay(1000);
                              timeAsleep = timeAsleep + 0;
                        }
                        else {
                            timeAsleep = timeAsleep + 1;
                        }
                    }
                    nextReadTime = now + restPeriod;
                }
                break;
         case pedometer:
              
              digitalWrite(13, LOW); // light off
              if (analogRead(A1) == LOW) {
                    delay(100);
                    if (analogRead(A1) == LOW) {
                        state = sleepTracker;
                        break;
                    }
              }

              if (analogRead(A2) == LOW) {
                    delay(100);
                    if (analogRead(A2) == LOW) {
                        stepCount = 0;
                        lastReset = millis();
                    }
              }
              
              if (accel.available()) {
                  accel.read();
                  for (int i = 0; i < 11; i++) {
                      values[i] = values[i+1];
                  }
                  values[11] = accel.cz;

                  if ((values[1] >= values[0]) && (values[2] >= values[1]) && (values[3] >= values[2])
                      && (values[4] >= values[3]) && (values[5] >= values[4]) && (values[5] >= values[6])
                      && (values[6] >= values[7]) && (values[7] >= values[8]) && (values[8] >= values[9])
                      && (values[9] >= values[10]) && (values[5] >= 1.5)) 
                      {
                          stepCount++;
                          if (values[0] >= 1.8 && values[11] <= 1,8 && !stepcount++) {
                            stepcount++;
                          }
//                          Serial.print("Number of Steps: ");
                      }
              }
              break;
    }
    return state;
}

// Original Peak Detection
//                      (values[5] >= values[0]) && (values[5] >= values[1]) && (values[5] >= values[2])
//                      && (values[5] >= values[3]) && (values[5] >= values[4]) && (values[5] >= values[6])
//                      && (values[5] >= values[7]) && (values[5] >= values[8]) && (values[5] >= values[9])
//                      && (values[5] >= values[10]) && (values[5] >= 1.5)

