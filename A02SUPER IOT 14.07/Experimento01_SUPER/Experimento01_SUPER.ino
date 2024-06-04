// Projeto: SUPER - Projeto para Educação e Pesquisa 2023
// Task: WP3-CETELI-3-IoT
// Instrutor: Andrey Bessa
// Experimento 01


// Incluindo a biblioteca para o sensor HC-SR04
#include <NewPing.h>

// Definindo os pinos para o trigger e o echo do sensor
#define TRIGGER_PIN 2
#define ECHO_PIN 3

// Criando uma instância do objeto NewPing para o sensor HC-SR04
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

void setup() {
  // Inicializando a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Realizando a medição da distância
  unsigned int distance = sonar.ping_cm();

  // Verificando se a medição foi bem-sucedida
  if (distance == 0) {
    Serial.println("Erro na medição. Distância não detectada.");
  } else {
    // Imprimindo a distância no monitor serial
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Imprimindo uma mensagem com base na distância medida
    if (distance < 10) {
      Serial.println("Cuidado! Objeto muito próximo!");
    } else if (distance < 30) {
      Serial.println("Parece que algo está se aproximando!");
    } else {
      Serial.println("Distância segura. Nenhum objeto próximo detectado.");
    }
  }

  // Aguardando um pequeno intervalo de tempo antes de realizar a próxima medição
  delay(1000);
}
