#include <Ultrasonic.h>
 
#define pino_trigger 4
#define pino_echo 5
 
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor... ");
}
 
void loop()
{

  float cmMsec;
  cmMsec = ultrasonic.distanceRead(CM);
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.println (" ");
  delay(1000);
}
