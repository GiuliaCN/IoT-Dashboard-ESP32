#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Giulia";
const char* password = "senha123";

// IP do notebook na rede do hotspot
const char* serverUrl = "http://127.0.1.1:1880/sensor";

const int sensorPin = 4;
bool ultimoEstadoEnviado = false;
unsigned long ultimoEnvio = 0;
const unsigned long intervaloEnvio = 1000;

void setup() {
  Serial.begin(115200);

  pinMode(sensorPin, INPUT);

  WiFi.begin(ssid, password);

  Serial.print("Conectando no Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  bool vibrando = lerVibracaoSuavizada();

  bool mudou = vibrando != ultimoEstadoEnviado;
  bool passouTempo = millis() - ultimoEnvio >= intervaloEnvio;

  if (mudou || passouTempo) {
    enviarEstado(vibrando);
    ultimoEstadoEnviado = vibrando;
    ultimoEnvio = millis();
  }
}

bool lerVibracaoSuavizada() {
  const int amostras = 20;
  int leiturasAtivas = 0;

  for (int i = 0; i < amostras; i++) {
    if (digitalRead(sensorPin) == HIGH) {
      leiturasAtivas++;
    }

    delay(5);
  }

  // Se pelo menos 30% das leituras detectaram vibração,
  // considera que está vibrando
  return leiturasAtivas >= 6;
}

void enviarEstado(bool vibrando) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desconectado");
    return;
  }

  HTTPClient http;

  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"deviceId\":\"maquina-01\",";
  json += "\"vibrando\":";
  json += vibrando ? "true" : "false";
  json += "}";

  int httpResponseCode = http.POST(json);

  Serial.print("Enviado: ");
  Serial.println(json);

  Serial.print("Resposta HTTP: ");
  Serial.println(httpResponseCode);

  http.end();
}
