#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const uint16_t kIrLed = 0;  // ESP8266 GPIO pin to use. Recommended: 0 (D3).
const int signalOnOffVideoProj = 0x00C1AA09F6;
const int signalOnOffTV = 0x4C;

ESP8266WebServer server(80);
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
char ssid[] = "KakarotCake";                //your network SSID (name)
char pass[] = "jesuisunelicorne";             //your network password
const IPAddress ip(192,168,43,116); //IP of your wemos


void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void throwSignalOnOffVideoProj() {
  irsend.sendNEC(signalOnOffVideoProj);
  delay(2000);
  irsend.sendNEC(signalOnOffVideoProj); //Sending Nec signal : 0x00C1AA09F6 : hexadecimal value to turn off or turn on video projector
}

void throwSignalOnOffTV() {
  irsend.sendRC5(signalOnOffTV);
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, 1);
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
  digitalWrite(LED_BUILTIN, 0);
}

void setup() {
  WiFi.begin(ssid, pass);  
  IPAddress gateway(192,168,43,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

  server.on("/", handleRoot);

  server.on("/signalOnOffVideoProj", []() {
    throwSignalOnOffVideoProj();
    delay(500);
    server.send(200, "text/plain", "Signal sent to Video Projector");
  });
  
  server.on("/startTV", []() {
    throwSignalOnOffTV();
    delay(500);
    server.send(200, "text/plain", "Signal sent to TV");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  MDNS.update();
}
