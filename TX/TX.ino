/*
 * using https://github.com/xreef/LoRa_E32_Series_Library
 * 
 * tx side is arduino mega
  *
 * E32-TTL-100----- Arduino UNO
 * M0         ----- GND
 * M1         ----- GND
 * RX         ----- PIN 18 (PullUP & Voltage divider)
 * TX         ----- PIN 19 (PullUP)
 * AUX        ----- Not connected
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
*/
#include "Arduino.h"
#include "LoRa_E32.h"

#define txPin 18
#define rxPin 19
// ---------- Arduino pins --------------
LoRa_E32 e32ttl100(txPin, rxPin); // Config without connect AUX and M0 M1

String gps_lat ="";
String gps_long="";

void setup() {
  Serial.begin(9600);
  Serial.println("starting ...");
  delay(500);
  
  e32ttl100.begin();

  getGpsData();
  sendWithLora();
}

void loop() {
  delay(1000);
  sendWithLora();

}
void getGpsData(){
  gps_lat ="112211221122";
  gps_long="998899889988";
}
void sendWithLora(){
  String msg="lat="+gps_lat+", long="+gps_long;
  ResponseStatus rs = e32ttl100.sendMessage(msg);
  // Check If there is some problem of succesfully send
  Serial.println(rs.getResponseDescription());
  
}
