#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

const int RECV_PIN = D4;
decode_results results;

const uint16_t kIrLed = D6;  // ESP8266 GPIO pin to use. Recommended: 0 (D3).
const int signalOnOffVideoProj = 0x00C1AA09F6;
const int signalOnOffTV = 0x4C;

IRrecv irrecv(RECV_PIN); // Set the GPIO to be used to listen the message.
IRsend irsend(D6);  // Set the GPIO to be used to sending the message.

void setup(){
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  irrecv.enableIRIn();
}

// This code permit to listen the value which we throw, it s usefull to verify if the value is good.
void loop(){
  if (irrecv.decode(&results)){
        serialPrintUint64(results.value, HEX);
        switch (results.decode_type){
            case NEC: Serial.println(" NEC"); break ;
            case SONY: Serial.println(" SONY"); break ;
            case RC5: Serial.println(" RC5"); break ;
            case RC6: Serial.println(" RC6"); break ;
            case DISH: Serial.println(" DISH"); break ;
            case SHARP: Serial.println(" SHARP"); break ;
            case JVC: Serial.println(" JVC"); break ;
            case SANYO: Serial.println(" SANYO"); break ;
            case MITSUBISHI: Serial.println(" MITSUBISHI"); break ;
            case SAMSUNG: Serial.println(" SAMSUNG"); break ;
            case LG: Serial.println(" LG"); break ;
            case WHYNTER: Serial.println(" WHYNTER"); break ;
            case AIWA_RC_T501: Serial.println(" AIWA_RC_T501"); break ;
            case PANASONIC: Serial.println(" PANASONIC"); break ;
            case DENON: Serial.println(" DENON"); break ;
          default:
            case UNKNOWN: Serial.println(" UNKNOWN"); break ;
          }
        irrecv.resume();
 }
 irsend.sendNEC(signalOnOffVideoProj);
 //irsend.sendRC5(signalOnOffTV);
 delay(3000);
}
