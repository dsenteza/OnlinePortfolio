#include"MorseCodes.h"
#include<WString.h>

const int light = 13;
unsigned long accumulator = 0;
boolean on = false;
int pause = 500;
// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
  // TODO
  if(c > 96 && c < 123){
    c = c-32;
  }
  return c;
}

void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
}

int MCpointer = 0;
String currentMC;
boolean isOn = false;

void convertIncomingCharsToMorseCode() {
  if(millis() > accumulator){
    if(isOn == false && Serial.available()>0){
      if(MCpointer < currentMC.length()){
        char next = currentMC[MCpointer];
        if (next == '.'){
          digitalWrite(light, HIGH);
          accumulator = accumulator + pause;
          isOn = true;
        }
        else if (next == '-'){
          digitalWrite(light, HIGH);
          accumulator += pause * 3;
          isOn = true;
        }
        else if (next == ' '){
          digitalWrite(light, LOW);
          accumulator += pause * 7;
          isOn = false;
        }
        MCpointer++;
      }
      else{
        digitalWrite(light, LOW);
        accumulator += pause * 3;
        currentMC = morseEncode(Serial.read());
        Serial.println(currentMC);
        MCpointer = 0;
      }
    }
    else{
      digitalWrite(light, LOW);
      accumulator += pause * 1;
      isOn = false;
    }
  }
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();  
}
