# Contrato da API do Sensor

## Endpoint

POST /sensor

## Content-Type

application/json

## Corpo da requisição

```json
{
  "deviceId": "maquina-01",
  "vibrando": true
}
```

### Campos

| Campo | Tipo | Obrigatório | Descrição |
| :---: | :---: | :---: | :---: |
| deviceId | string | sim | Identificador do dispositivo |
| vibrando | boolean | sim | Indica se o sensor SW-420 detectou vibração |

### Resposta
```json
{
  "ok": true,
  "status": "LIGADA",
  "tempoEstadoAtualSegundos": 15
}
```

