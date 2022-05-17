#include <Arduino.h>
#include <FlexCAN_T4.h>
#define PWM1 0
#define PWM2 1
#define PWM3 2
#define PWM4 3
#define PWM5 4
#define PWM6 5
#define PWM7 6
#define PWM8 7
#define CAN_ENABLE 21
uint8_t FanSpeed=64;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN;
void setup() {
  for(int i=0;i<8;i++){
    pinMode(i,OUTPUT); analogWriteFrequency(0, 375000); analogWrite(i,64);
  }
  // put your setup code here, to run once:
  delay(5000);
  FanSpeed=255;
}

void loop() {

  for(int i=0;i<8;i++){
    analogWrite(i,FanSpeed);
  }
  // delay(1000);
  // for(int i=0;i<8;i++){
  //   digitalWrite(i,HIGH);
    
  // }
  // delay(1000);
  // analogWrite(0,128);
  // delay(1000);
  // analogWrite(0,64);
  // delay(1000);
}