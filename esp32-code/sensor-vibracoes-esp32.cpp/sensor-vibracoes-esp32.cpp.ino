#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "NOME_DO_WIFI";
const char* password = "SENHA_DO_WIFI";

// IP do notebook na rede do hotspot
const char* serverUrl = "http://192.168.43.100:1880/sensor";

const int sensorPin = 4; // ajuste conforme o GPIO usado
bool ultimoEstado = false;

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
  bool vibrando = digitalRead(sensorPin) == HIGH;

  // Envia apenas quando o estado muda
  if (vibrando != ultimoEstado) {
    enviarEstado(vibrando);
    ultimoEstado = vibrando;
  }

  delay(500);
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
