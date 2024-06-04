#include <WiFi.h>
#include <FirebaseESP32.h>  // Certifique-se de instalar esta biblioteca

// Configurações de Wi-Fi
#define WIFI_SSID "WP3-CETELI-3-IoT"
#define WIFI_PASSWORD "uariniamazonas"

// Configurações do Firebase
#define FIREBASE_HOST " "
#define FIREBASE_AUTH " "

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Conectar-se à rede Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }

  Serial.println("Conectado ao Wi-Fi");

  // Inicializar a biblioteca Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Gerar um valor aleatório entre 0 e 100
  int randomValue = random(0, 101);
  // Escrever dados no Firebase
  if (Firebase.setInt(firebaseData, "/dados/valor", randomValue)) {
    Serial.println("Dados escritos no Firebase com sucesso!");
  } else {
    Serial.println("Erro ao escrever dados no Firebase.");
    Serial.println(firebaseData.errorReason());
  }

  delay(5000);  // Esperar 5 segundos antes de escrever novamente
}
