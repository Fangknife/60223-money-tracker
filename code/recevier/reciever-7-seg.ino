#include <SPI.h>  // reciever code. Right now: 7-seg display, radio working.
#include <nRF24L01.h>
#include <RF24.h>
#include "HT16K33.h"
HT16K33 seg(0x70);  // digit display i2c address
RF24 radio(7, 8);   // CE, CSN radio pins.

const byte address[6] = "00001";  // radio address - changeable but must match other radio.
float moneyFloat;                 // name of variable being recieved from transmitter

void setup() {
  Serial.begin(9600);
  radio.begin();  // radio setup vvv
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);  // might need to be changed? don't know if this effects distance?
  radio.startListening();
  seg.begin();  // digit display setup vvv
  Wire.setClock(100000);
  seg.displayOn();
}

void loop() {
  while (!radio.available()) {}                 // if no radio: do nothing. Messing with this line even a little can break it easily
  radio.read(&moneyFloat, sizeof(moneyFloat));  // reading variable from transmitter
  Serial.println(moneyFloat);                   // just so I can see what's happening.
  seg.displayFixedPoint2(moneyFloat);           // "fixedPoint" rather than "seg.displayFloat()" to keep decimal in same place
                                                // regardless of # of digits. Looks better + easier to read in my opinion.
}
