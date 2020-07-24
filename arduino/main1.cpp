//use this version for neopixels
#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

uint8_t ssRX = 2;
uint8_t ssTX = 3;
uint8_t neoPixelsPin = 7;
uint8_t neoPixelCount = 1;
uint32_t color;

Adafruit_NeoPixel strip(neoPixelCount, neoPixelsPin, NEO_GRB + NEO_KHZ800);
SoftwareSerial xbeeSerial(ssRX, ssTX);

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();

void setup() {
  color = strip.Color(0, 0, 0);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(dataLed,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  xbee.begin(xbeeSerial);
}

void setColor(){
    for(int i=0;i<neoPixelCount;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i,color); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(500); // Delay for a period of time (in milliseconds).
  }
}

//c code from internet... forget from who
// #define DEBUG false   // change me!
// void add_cksum(byte p[], int pktsize)
// {
//   int cksum = 0;  // start with a zero checksum
//   for (byte i = 3; i < pktsize-1; i++) {  // skip the Start and len, start with byte 4.
//     // (remembering that C arrays start at 0, not 1.)
//     cksum += p[i];    // Add in this byte.
//   }  // next byte
//   cksum &= 0xFF;        // low order 8 bits
//   cksum = 0xFF - cksum; // subtract from 0xFF
//   p[pktsize-1] = cksum;
//   if (DEBUG) {
//     Serial.print("add_cksum got ");
//     Serial.println(cksum, HEX);
//   }
// }
// continuously reads packets, looking for ZB Receive or Modem Status

void loop() {
    uint8_t r,g,b;
  
    xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      Serial.println("Data available...");
      
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        Serial.println("got a zb rx packet");
        
        xbee.getResponse().getZBRxResponse(rx);

        r = rx.getData(0);
        g = rx.getData(1);
        b = rx.getData(2);
        color = strip.Color(r,g,b);


        //uncomment below to send color set back to coordinator
        // byte data[] = {0x7E,0x00,0x11,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x8B,0x2D,0x4C,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00};

        // data[17] = r;
        // data[18] = g;
        // data[19]=  b;

        //if you want write frame back to server to report color status
        //on front end
        // add_cksum(data,sizeof(data));
        // xbeeSerial.write(data,sizeof(data));
      
      }
      
    }
      
    setColor();
    delay(500);
}