#include <SPI.h>
#include <LoRa.h>

int counter = 0;

const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;        // LoRa radio reset
const int irqPin = 26;          // change for your board; must be a hardware interrupt pin

void setup() {
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(csPin, resetPin, irqPin);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
