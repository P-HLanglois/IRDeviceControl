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

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void signalOnOffVideoProj() {
  irsend.sendNEC(signalOnOff);
  delay(2000);
  irsend.sendNEC(signalOnOff); //Sending Nec signal : 0x00C1AA09F6 : hexadecimal value to turn off or turn on video projector
}

void signalOnOffTV() {
  irsend.sendRC5(signalOnOffTV);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

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

  server.on("/", handleRoot);

  server.on("/signalOnOffVideoProj", []() {
    signalOnOffVideoProj();
    delay(2000);
    server.send(200, "text/plain", "Signal sent to Video Projector");
  });
  
  server.on("/startTV", []() {
    signalOnOffTV();
    server.send(200, "text/plain", "Signal sent to TV");
    delay(500);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  
}
