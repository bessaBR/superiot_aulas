#include <SPI.h>
#include <LoRa.h>

const int pinoCS = 18;          // Pino de seleção do chip LoRa
const int pinoReset = 16;       // Pino de reset do chip LoRa
const int pinoIRQ = 26;         // mude de acordo com a placa; deve ser um pino de interrupção de hardware

bool pacoteRecebido = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(pinoCS, pinoReset, pinoIRQ);
  Serial.println("LoRa Receiver (Adaptado do LoRaReceiver.ino da biblioteca LoRa.h)");

  if (!LoRa.begin(915E6)) {
    Serial.println("Falha ao iniciar o LoRa!");
    while (1);
  }
}

void loop() {
  if (!pacoteRecebido && LoRa.parsePacket()) {
    // pacote recebido
    Serial.print("Pacote recebido: '");

    // lê o pacote
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // imprime o RSSI do pacote
    Serial.print("' com RSSI ");
    Serial.println(LoRa.packetRssi());

    pacoteRecebido = true;
  } else if (pacoteRecebido && !LoRa.parsePacket()) {
    pacoteRecebido = false;
    Serial.println("Aguardando novo pacote.");
  }
}
