console.log("SIMULADOR INICIOU");

const url = "http://localhost:1880/sensor";

let vibrando = false;

async function enviar() {
  try {
    // Simula mudança ocasional de estado
    if (Math.random() < 0.1) {
      vibrando = !vibrando;
    }

    const data = {
      deviceId: "maquina-01",
      vibrando
    };

    const response = await fetch(url, {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(data)
    });

    console.log("Enviado:", data, "Status:", response.status);
  } catch (err) {
    console.error("Erro ao enviar:", err.message);
  }
}

setInterval(enviar, 2000);