#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const int RECV_PIN = D4; //Connect the signal pin of the Recever on D3
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(115200); // to listen value with serial moniteur we must are in 115200 bauds
  irrecv.enableIRIn();
}

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
}
