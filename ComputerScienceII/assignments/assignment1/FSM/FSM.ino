// Name(s): 

enum State {
  forward1,
  forward2,
  forward3,
  forward4,
  forward5,
  forward6,
  forward7,
  forward8,
  reverse1,
  reverse2,
  reverse3,
  reverse4,
  reverse5,
  reverse6,
  reverse7,
  reverse8
} ;State count = forward1;



bool bit1;
bool bit2;
bool bit3;
int number;

void setup() {
  Serial.begin(9600);
}

void loop() {
  nextState (count);
  delay(750);
}


State nextState(State state){
  switch (state) {
    
    case forward1:
      bit1 = 0;
      bit2 = 0;
      bit3 = 0;
      number = 0;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse8;
      }
      else{
        state = forward2;
      }
      count = state;
      break;

    case forward2:
      bit1 = 1;
      bit2 = 0;
      bit3 = 0;
      number = 1;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse1;
      }
      else{
        state = forward3;
      }
      count = state;
      break;
      
    case forward3:
      bit1 = 0;
      bit2 = 1;
      bit3 = 0;
      number = 2;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse2;
      }
      else{
        state = forward4;
      }
      count = state;
      break;
      
    case forward4:
      bit1 = 1;
      bit2 = 1;
      bit3 = 0;
      number = 3;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse3;
      }
      else{
        state = forward5;
      }
      count = state;
      break;
      
    case forward5:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      number = 4;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse4;
      }
      else{
        state = forward6;
      }
      count = state;
      break;
      
    case forward6:
      bit1 = 1;
      bit2 = 0;
      bit3 = 1;
      number = 5;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse5;
      }
      else{
        state = forward7;
      }
      count = state;
      break;
      
    case forward7:
      bit1 = 0;
      bit2 = 1;
      bit3 = 1;
      number = 6;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse6;
      }
      else{
        state = forward8;
      }
      count = state;
      break;
      
    case forward8:
      bit1 = 1;
      bit2 = 1;
      bit3 = 1;
      number = 7;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = reverse7;
      }
      else{
        state = forward1;
      }
      count = state;
      break;
      
    case reverse1:
      bit1 = 0;
      bit2 = 0;
      bit3 = 0;
      number = 0;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward2;
      }
      else{
        state = reverse8;
      }
      count = state;
      break;
      
    case reverse2:
      bit1 = 1;
      bit2 = 0;
      bit3 = 0;
      number = 1;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward3;
      }
      else{
        state = reverse1;
      }
      count = state;
      break;
      
    case reverse3:
      bit1 = 0;
      bit2 = 1;
      bit3 = 0;
      number = 2;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward4;
      }
      else{
        state = reverse2;
      }
      count = state;
      break;
      
    case reverse4:
      bit1 = 1;
      bit2 = 1;
      bit3 = 0;
      number = 3;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward5;
      }
      else{
        state = reverse3;
      }
      count = state;
      break;
      
    case reverse5:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      number = 4;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward6;
      }
      else{
        state = reverse4;
      }
      count = state;
      break;
      
    case reverse6:
      bit1 = 1;
      bit2 = 0;
      bit3 = 1;
      number = 5;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward7;
      }
      else{
        state = reverse5;
      }
      count = state;
      break;
      
    case reverse7:
      bit1 = 0;
      bit2 = 1;
      bit3 = 1;
      number = 6;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward8;
      }
      else{
        state = reverse6;
      }
      count = state;
      break;

      case reverse8:
      bit1 = 1;
      bit2 = 1;
      bit3 = 1;
      number = 7;

      print(number);
      
      if (checkReverse() == true){
        Serial.println("--Reverse--");
        state = forward1;
      }
      else{
        state = reverse7;
      }
      count = state;
      break;
  }
}


bool checkReverse(){
  if (Serial.read() != -1){
    return true;
  }
   else {
    return false;
  }
}

void print (State state) {
  Serial.print(number);
  Serial.print(" : ");
  Serial.print(bit3);
  Serial.print(bit2);
  Serial.println(bit1);
}

