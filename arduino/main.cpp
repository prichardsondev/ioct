#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

uint8_t ssRX = 2;
uint8_t ssTX = 3;
XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();
SoftwareSerial xbeeSerial(ssRX, ssTX);

int relayPin = 7;

void setup() {

  pinMode(relayPin,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  xbee.begin(xbeeSerial);
}

void loop() {
  
    xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

        xbee.getResponse().getZBRxResponse(rx);
        //ASCII 7, Hex 37, Decimal 55
        if(rx.getData(0) == 55){
          digitalWrite(relayPin,1-digitalRead(relayPin));
        }

      }

    }

    delay(500);
}