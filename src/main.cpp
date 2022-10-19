#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <Metro.h>
#define PWM1 0
#define PWM2 1
#define PWM3 2
#define PWM4 3
#define PWM5 4
#define PWM6 5
#define PWM7 6
#define PWM8 7
#define CAN_ENABLE 21
uint8_t FanSpeed=255;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN;
Metro fc=Metro(1000);
void canSniff(const CAN_message_t &msg);
void setup() {
  for(int i=0;i<8;i++){
    pinMode(i,OUTPUT); analogWriteFrequency(0, 375000); analogWrite(i,255);
  }
  pinMode(CAN_ENABLE,OUTPUT);
  digitalWrite(CAN_ENABLE,LOW);
  delay(500);
  FanSpeed=64;
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
  if(msg.id==0xC7){
    FanSpeed=msg.buf[0];
  }
}
void  fcHeartbeat();
void loop() {
  CAN.events();
  for(int i=0;i<8;i++){
    analogWrite(i,FanSpeed);
  }
     fcHeartbeat();

}
void fcHeartbeat(){ //know if FC is alive
    if(fc.check()){
    CAN_message_t ctrlMsg;
      ctrlMsg.len=8;
      ctrlMsg.id=0x22;
      uint8_t heartbeatMsg[]={0,0,0,0,1,1,0,0};
      memcpy(ctrlMsg.buf, heartbeatMsg, sizeof(ctrlMsg.buf));
      CAN.write(ctrlMsg);
    }
}