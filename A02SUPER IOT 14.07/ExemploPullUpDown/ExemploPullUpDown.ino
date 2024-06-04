int pushButton = 3;
int sinal;
//----------------------------------

void setup() {
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println ("bessa");
}
//----------------------------------

void loop() {
 
  sinal = digitalRead(pushButton);
  Serial.print ("A Leitura atual é : ");
  Serial.print(sinal);
  Serial.println (" ");
  delay(1);
}
