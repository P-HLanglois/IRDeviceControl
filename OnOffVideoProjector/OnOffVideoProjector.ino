#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

const uint16_t kIrLed = 0;  // ESP8266 GPIO pin to use. Recommended: 0 (D3).
const int signalOnOffVideoProj = 0x00C1AA09F6;
const int signalOnOffTV = 0x4C;

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
char ssid[] = "KakarotCake";                //your network SSID (name)
char pass[] = "jesuisunelicorne";             //your network password
const IPAddress ip(192,168,43,116); //IP of your wemos

void setup() {
  WiFi.begin(ssid, pass);  
  IPAddress gateway(192,168,43,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
}

void loop() {
  //  irsend.sendNEC(signalOnOff);//Sending Nec signal : 0x00C1AA09F6 : hexadecimal value to turn off or turn on video projector
  irsend.sendRC5(signalOnOffTV);
  delay(3000);
}
