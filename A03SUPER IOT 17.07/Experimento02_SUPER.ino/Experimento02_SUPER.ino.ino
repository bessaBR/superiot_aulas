// Projeto: SUPER - Projeto para Educação e Pesquisa 2023
// Task: WP3-CETELI-3-IoT
// Instrutor: Andrey Bessa

// Incluindo as bibliotecas necessárias
#include <NewPing.h>
#include <Servo.h>

// Definindo os pinos para o trigger e o echo do sensor
#define TRIGGER_PIN 2
#define ECHO_PIN 3

// Definindo o pino para o botão
#define BUTTON_PIN 4

// Definindo os pinos para o servo motor
#define SERVO_PIN 5

// Criando uma instância do objeto NewPing para o sensor HC-SR04
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

// Criando uma instância do objeto Servo para controlar o servo motor
Servo servoMotor;

// Variável para controlar o estado do sistema
bool sistemaLigado = false;

void setup() {
  // Inicializando a comunicação serial
  Serial.begin(9600);

  // Configurando o pino do botão como entrada
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Anexando o servo motor ao pino correspondente
  servoMotor.attach(SERVO_PIN);

  // Movendo o servo motor para a posição inicial (desligado)
  servoMotor.write(0);
}

// Variável para controlar o último estado do botão
int ultimoEstadoBotao = HIGH;

void loop() {
  // Verificando o estado do botão
  int estadoBotao = digitalRead(BUTTON_PIN);

  // Verificar se o botão foi pressionado
  if (ultimoEstadoBotao == HIGH && estadoBotao == LOW) {
    sistemaLigado = !sistemaLigado;
    if (sistemaLigado) {
      Serial.println("Sistema ligado!");
    } else {
      servoMotor.write(0);
      Serial.println("Sistema desligado!");
    }
  }

  // Atualizar o último estado do botão
  ultimoEstadoBotao = estadoBotao;

  if (sistemaLigado) {
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

      // Verificando se a distância é menor que 10 cm
      if (distance < 10) {
        // Ligar o servo motor
        servoMotor.write(90); // Angulo para acionar o servo motor
        delay(5000); // Aguarda 5 segundos
        servoMotor.write(0); // Desliga o servo motor
      }
    }
  }

  // Aguardando um pequeno intervalo de tempo antes de realizar a próxima medição
delay(1000);
}
