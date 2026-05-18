# Monitoramento de Vibração com ESP32 e Node-RED

Projeto de Internet das Coisas (IoT) para monitoramento de estado de máquinas utilizando um sensor de vibração SW-420, um microcontrolador ESP32-S3-WROOM-1 e um dashboard em tempo real desenvolvido com Node-RED.

O sistema detecta vibração em equipamentos e identifica se a máquina está ligada ou desligada, permitindo visualizar:

* estado atual da máquina;
* tempo no estado atual;
* histórico de eventos;
* gráfico de vibração em tempo real.

---

# Objetivo

O objetivo do projeto é demonstrar uma aplicação prática de IoT para monitoramento de máquinas domésticas ou industriais.

Exemplos de aplicação:

* identificar quando uma máquina de lavar terminou o ciclo;
* monitorar tempo de funcionamento de equipamentos;
* detectar períodos prolongados de inatividade;
* acompanhar uso operacional de máquinas.

---

# Arquitetura

```text
Sensor SW-420
↓
ESP32-S3-WROOM-1
↓ Wi-Fi
HTTP POST
↓
Node-RED
↓
Dashboard em tempo real
```

O ESP32 realiza a leitura do sensor de vibração e envia os dados pela rede Wi-Fi utilizando requisições HTTP em formato JSON.

O Node-RED recebe os dados, processa os eventos, calcula tempo de atividade e atualiza o dashboard em tempo real.

---

# Tecnologias Utilizadas

* ESP32-S3-WROOM-1
* Sensor SW-420
* Node.js
* Node-RED
* Dashboard 2
* JavaScript
* HTTP REST
* Wi-Fi

---

# Estrutura do Projeto

```text
iot-dashboard-esp32/
├─ docs/
│  ├─ arquitetura.md
│  ├─ contrato-api.md
│  └─ dashboard.md
│
├─ nodered/
│  └─ flow-monitoramento.json
│
├─ simulator/
│  └─ send-sensor.js
│
└─ README.md
```

---

# Funcionamento

O sensor SW-420 detecta vibração e gera um sinal digital:

* `true` → máquina vibrando;
* `false` → máquina parada.

O ESP32 envia os dados para o Node-RED através do endpoint:

```text
POST /sensor
```

Exemplo de mensagem enviada:

```json
{
  "deviceId": "maquina-01",
  "vibrando": true
}
```

O Node-RED adiciona o timestamp do servidor, processa o estado da máquina e atualiza o dashboard.

---

# Dashboard

O dashboard apresenta:

* status atual da máquina;
* tempo no estado atual;
* gráfico histórico de vibração;
* histórico de eventos.

Representação do gráfico:

* `1` → vibrando / ligada;
* `0` → parada / desligada.

---

# Simulador

O projeto inclui um simulador em JavaScript para testes sem hardware físico.

Execução:

```bash
node simulator/send-sensor.js
```

O simulador envia mensagens periódicas para o Node-RED simulando mudanças de estado do sensor.

---

# Executando o Projeto

## Instalar Node-RED

[Node-RED](https://nodered.org?utm_source=chatgpt.com)

## Iniciar Node-RED

```bash
node-red
```

## Abrir interface

```text
http://localhost:1880
```

## Dashboard

```text
http://localhost:1880/dashboard
```

---

# Possíveis Evoluções

* integração com MQTT;
* persistência em banco de dados;
* alertas e notificações;
* múltiplos dispositivos;
* autenticação;
* armazenamento histórico;
* deploy em Raspberry Pi;
* monitoramento industrial distribuído.

---

# Autores

Projeto acadêmico desenvolvido para estudo de Internet das Coisas (IoT), comunicação em rede e monitoramento em tempo real.
