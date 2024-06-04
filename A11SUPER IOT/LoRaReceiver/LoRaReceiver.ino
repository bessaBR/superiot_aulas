#include <SPI.h>
#include <LoRa.h>


const int csPin = 18;          // LoRa radio chip select
const int resetPin = 16;        // LoRa radio reset
const int irqPin = 26;          // change for your board; must be a hardware interrupt pin


void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
