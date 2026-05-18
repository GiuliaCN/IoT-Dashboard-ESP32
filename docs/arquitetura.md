# Arquitetura

```text
Sensor SW-420
↓
ESP32-S3-WROOM-1
↓ Wi-Fi
HTTP POST /sensor
↓
Node-RED
↓
Dashboard local
```

**Observações**

O timestamp é gerado pelo servidor Node-RED no momento do recebimento da mensagem.