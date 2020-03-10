/*
 * using https://github.com/xreef/LoRa_E32_Series_Library
 * 
 * Rx side is wemos D1 mini
  *
 * E32-TTL-100----- wemos D1 mini
 * M0         ----- GND
 * M1         ----- GND
 * RX         ----- PIN D2 (PullUP & Voltage divider)
 * TX         ----- PIN D3 (PullUP)
 * AUX        ----- PIN D5
 * VCC        ----- 3.3v
 * GND        ----- GND
 *
*/
#include "Arduino.h"
#include "LoRa_E32.h"

#define txPin D2
#define rxPin D3
// ---------- Arduino pins --------------
LoRa_E32 e32ttl100(txPin, rxPin,A0); // Config without connect AUX and M0 M1

String gps_lat ="";
String gps_long="";

void setup() {
  Serial.begin(9600);
  Serial.println("starting ...");
  delay(500);
  
  e32ttl100.begin();
  delay(500);
//  ResponseStructContainer c;
//  c = e32ttl100.getConfiguration();
//  Configuration configuration = *(Configuration*) c.data;
//  printParameters(configuration);
}

void loop() {
  getFromLora();
  checkAux();
  delay(5000);
}
void checkAux(){
  int aux=analogRead(A0);
  Serial.print("aux=");
  Serial.println(aux);
}
void getGpsData(){
  gps_lat ="112211221122";
  gps_long="998899889988";
}
void getFromLora(){
  String msg;
  int avl=e32ttl100.available();
  Serial.print("avl=");
  Serial.println(avl);
  if (avl>1) {
    // read the String message
    ResponseContainer rc = e32ttl100.receiveMessage();
    // Is something goes wrong print error
    if (rc.status.code!=1){
      rc.status.getResponseDescription();
    }else{
      msg=rc.data;
      // Print the data received
      Serial.println(msg);
    }
  }
  else {
    Serial.println("no e32");
  }
  
}

//void printConfParameters(struct Configuration configuration) {
//  Serial.println("----------------------------------------");
//
//  Serial.print("HEAD : ");  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
//  Serial.println(" ");
//  Serial.print("AddH : ");  Serial.println(configuration.ADDH, DEC);
//  Serial.print("AddL : ");  Serial.println(configuration.ADDL, DEC);
//  Serial.print("Chan : ");  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
//  Serial.println(" ");
//  Serial.print("SpeedParityBit     : ");  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
//  Serial.print("SpeedUARTDatte  : ");  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
//  Serial.print("SpeedAirDataRate   : ");  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());
//
//  Serial.print("OptionTrans        : ");  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
//  Serial.print("OptionPullup       : ");  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
//  Serial.print("OptionWakeup       : ");  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
//  Serial.print("OptionFEC          : ");  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
//  Serial.print("OptionPower        : ");  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());
//
//  Serial.println("----------------------------------------");
//
//}
