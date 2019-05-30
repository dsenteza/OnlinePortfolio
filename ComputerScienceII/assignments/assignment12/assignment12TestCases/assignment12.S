.global hasAOne
hasAOne:
  cpse r24, r1 //compare r24 to r1 (which is set to zero by default) skips next line if true
  ldi r24, 1 //sets r24 to 1
  ret

.global byteToAscii
byteToAscii:
  ldi r23, 48 //load 48 into r23 because 0 is 48 in ascii
  add r24, r23 //add r23 to r24 
  ret

.global int8ToInt
int8ToInt:
  clr r25
  sbrc r24, 7 //skip next line if bit 8 in r24 is zero
  ldi r25, 255 //set r25 to 255
  ret

.global addInt8ToInt
addInt8ToInt:
  call int8ToInt
  add r22, r24 // add r22 to r24
  adc r23, r1 //add the carryover to r23
  add r23, r25 //add r23 to r25
  mov r24, r22 // move what is in r22 to r24
  mov r25, r23 // move what is in r23 to 25
  ret

.global add4Int8
add4Int8:
  call int8ToInt // change r24 to a 2 byte value in r24 and r25
  mov r26, r22 // move values around to the same format as addInt8ToInt
  mov r22, r24 // need 2 byte in r22 and r23 and one byte in r24
  mov r23, r25
  mov r24, r26
  call addInt8ToInt // call add method
  mov r26, r20 // move values around to addInt8ToInt format
  mov r22, r24
  mov r23, r25
  mov r24, r26
  call addInt8ToInt // call add method
  mov r26, r18 // move values around to addInt8ToInt format
  mov r22, r24
  mov r23, r25
  mov r24, r26
  call addInt8ToInt //call add method
  ret

.global average    //***USE ROTATION**
average:
  add r24, r22 // add two unsigned bytes together
  adc r25, r1 //add the carryover to r25
//  sbrc r25, 7
//  adiw r24, 1
  lsr r25 //divide r25:r24 by 2
  ror r24 //r25:r24 is an unsigned two-byte integer
  ret
