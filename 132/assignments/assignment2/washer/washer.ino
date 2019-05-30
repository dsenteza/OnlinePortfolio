const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      if (analogRead(A0) > 680) {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      else {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      else {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      else {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      else {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      else {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
const int BUTTON_PIN = 5;

enum State {
  locked,
  econWash, 
  econDry,      
  deluxe,        
  supDeluxe, 
  dry,
  unlocked     
 };

 State counterState = unlocked;
 
void setup() {
  pinMode(2,OUTPUT);

  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);

  pinMode(5,OUTPUT);

  pinMode (13, OUTPUT);
}

void loop() {
  pinMode(A0, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  counterState = nextState(counterState);
}

State nextState(State state) {
  switch (state) {
    case unlocked:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        digitalWrite (13, LOW);
        Serial.println(digitalRead(5));
        if (digitalRead(5) == 0) { 
          state = locked;
        }
        break;
        
    case locked:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      if (analogRead(A0) < 340) {
        state = econWash;
      }
      if (340 < analogRead(A0) && analogRead(A0)<680) {
        state = deluxe;
      }
      else {
        state = supDeluxe;
      }
      break;
      
    case econWash: 
      digitalWrite (2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(5000);
      if ((340 < analogRead(A0))){
        state = dry;
      }
      else {
        state = econDry;
      }
      break;

    case econDry:
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
      digitalWrite (4, HIGH);
      digitalWrite (13, HIGH);
      delay(2000);
      state = unlocked;
      break;

     case deluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

     case supDeluxe:
      digitalWrite (2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
      digitalWrite (4, LOW);
      digitalWrite (13, HIGH);
      delay(7000);
      if (analogRead(A0)<340) {
        state = econDry;
      }
      else { 
        state = dry;
      }
      break;

      case dry:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (13, HIGH);
        delay(7000);
        state = unlocked;
        break;
    }
    return state;
}
