// Projeto: SUPER - Projeto para Educação e Pesquisa 2023
// Task: WP3-CETELI-3-IoT
// Instrutor: Andrey Bessa


#include <NewPing.h>  // Incluindo as bibliotecas necessárias
#include <Servo.h>
#define TRIGGER_PIN 2 // Definindo os pinos para o trigger e o echo do sensor
#define ECHO_PIN 3
#define BUTTON_PIN 4 // Definindo o pino para o botão
#define SERVO_PIN 5  // Definindo os pinos para o servo motor

NewPing sonar(TRIGGER_PIN, ECHO_PIN); // Criando uma instância do objeto NewPing para o sensor HC-SR04
Servo servoMotor; // Criando uma instância do objeto Servo para controlar o servo motor

bool sistemaLigado = false; // Variável para controlar o estado do sistema
int ultimoEstadoBotao = HIGH; // Variável para controlar o último estado do botão

unsigned long ultimaMedicao = 0; // Variáveis para controlar a temporização
unsigned long ultimaAcaoServo = 0;
const unsigned long intervaloMedicao = 1000;
const unsigned long intervaloAcaoServo = 5000;

void setup() {
  Serial.begin(9600);                // Inicializando a comunicação serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configurando o pino do botão como entrada
  servoMotor.attach(SERVO_PIN);      // Anexando o servo motor ao pino correspondente
  servoMotor.write(0);               // Movendo o servo motor para a posição inicial (desligado)
}

void loop() {
  int estadoBotao = digitalRead(BUTTON_PIN);   // Verificando o estado do botão
  if (ultimoEstadoBotao == HIGH && estadoBotao == LOW) {   // Verificar se o botão foi pressionado
    sistemaLigado = !sistemaLigado;
    if (sistemaLigado) {
      Serial.println("Sistema ligado!");
    } else {
      servoMotor.write(0);
      Serial.println("Sistema desligado!");
    }
  }
  ultimoEstadoBotao = estadoBotao;   // Atualizar o último estado do botão
  unsigned long agora = millis();   // Verificar se é hora de fazer uma nova medição
  if (sistemaLigado && agora - ultimaMedicao >= intervaloMedicao) {
    ultimaMedicao = agora;
    unsigned int distance = sonar.ping_cm();     // Realizando a medição da distância

    if (distance == 0) {     // Verificando se a medição foi bem-sucedida
      Serial.println("Erro na medição. Distância não detectada.");
    } else {
      Serial.print("Distância: ");       // Imprimindo a distância no monitor serial
      Serial.print(distance);
      Serial.println(" cm");

      if (distance < 10) {    // Verificando se a distância é menor que 10 cm
        servoMotor.write(90); // Angulo para acionar o servo motor
      }
    }
  }

  if (sistemaLigado && agora - ultimaAcaoServo >= intervaloAcaoServo) {// Verificar se é hora de agir sobre o servo motor
    ultimaAcaoServo = agora;
    servoMotor.write(0); // Desliga o servo motor
  }
}
