// Projeto: SUPER - Projeto para Educação e Pesquisa 2023
// Task: WP3-CETELI-3-IoT
// Instrutor: Andrey Bessa

#include <Servo.h>

// Definindo o pino para o servo motor
#define SERVO_PIN 9

// Criando uma instância do objeto Servo para controlar o servo motor
Servo servoMotor;

void setup() {
  // Anexando o servo motor ao pino correspondente
  servoMotor.attach(SERVO_PIN);
}

void loop() {
  // Movendo o servo motor para a posição inicial (0 graus)
  servoMotor.write(0);
  delay(1000); // Aguarda 1 segundo

  // Movendo o servo motor para uma posição intermediária (90 graus)
  servoMotor.write(90);
  delay(1000); // Aguarda 1 segundo

  // Movendo o servo motor para a posição final (180 graus)
  servoMotor.write(180);
  delay(1000); // Aguarda 1 segundo
}
