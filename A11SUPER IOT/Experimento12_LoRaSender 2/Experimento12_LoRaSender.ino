// Projeto: SUPER - Projeto para Educação e Pesquisa 2023
// Task: WP3-CETELI-3-IoT
// Instrutor: Andrey Bessa
// Adaptado do LoRaSender.ino da biblioteca LoRa.h

#include <SPI.h>
#include <LoRa.h>

int contador = 0;
bool pacoteRecebido = false;
const int pinoCS = 18;          // Pino de seleção do chip LoRa
const int pinoReset = 14;       // Pino de reset do chip LoRa
const int pinoIRQ = 26;         // mude de acordo com a placa; deve ser um pino de interrupção de hardware

void setup() {
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(pinoCS, pinoReset, pinoIRQ);
  Serial.println("LoRa Sender (Adaptado do LoRaSender.ino da biblioteca LoRa.h)");

  if (!LoRa.begin(915E6)) {
    Serial.println("Falha ao iniciar o LoRa!");
    while (1);
  }
}

void loop() {
  Serial.print("Enviando pacote: ");
  Serial.println(contador);

  // envia o pacote
  LoRa.beginPacket();
  LoRa.print("olá ");
  LoRa.print(contador);
  LoRa.endPacket();

  contador++;

  delay(5000);

  if (LoRa.parsePacket()) {
    pacoteRecebido = true;
    Serial.println("Pacote recebido!");
  } else {
    pacoteRecebido = false;
    Serial.println("Nenhum pacote recebido.");
  }
}
