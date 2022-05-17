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
  CAN.begin();
  CAN.setBaudRate(500000);
  CAN.enableFIFO();
  CAN.enableFIFOInterrupt();
  CAN.onReceive(canSniff);
  CAN.mailboxStatus();
}

void canSniff(const CAN_message_t &msg) {
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();
}

void loop() {
  CAN.events();

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