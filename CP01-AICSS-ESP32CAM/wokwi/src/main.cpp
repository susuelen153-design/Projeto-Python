/*
 * CP01 - AICSS - ESP32CAM  |  Simulacao no Wokwi
 *
 * IMPORTANTE: o Wokwi nao simula o sensor OV2640. Esta versao reproduz
 * TODA a logica do firmware real (Wi-Fi, servidor web, rota /capture,
 * nomenclatura padronizada classe_001.jpg, flash no GPIO4 e botao de
 * captura no GPIO13) e devolve uma imagem SINTETICA gerada em memoria
 * no lugar do quadro da camera. Serve para validar o servidor web e a
 * interface de coleta antes de gravar na placa fisica.
 *
 * Wi-Fi do simulador: SSID "Wokwi-GUEST", sem senha, canal 6.
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define LED_FLASH_GPIO 4
#define BOTAO_GPIO 13

WebServer server(80);

// Estado da coleta (espelha o que o firmware real faz no navegador)
String classeAtual = "garfo";
uint16_t proximoNumero = 1;
uint32_t totalCapturas = 0;

// ---------------------------------------------------------------------------
// Imagem sintetica: BMP 24 bits 160x120 com um padrao que muda a cada captura.
// (BMP porque pode ser montado byte a byte, sem depender do encoder JPEG.)
// ---------------------------------------------------------------------------
static const int IMG_W = 160, IMG_H = 120;

size_t montarBMP(uint8_t *saida, uint8_t semente) {
  const int rowSize = ((IMG_W * 3 + 3) / 4) * 4;
  const uint32_t pixels = rowSize * IMG_H;
  const uint32_t total = 54 + pixels;

  memset(saida, 0, 54);
  saida[0] = 'B'; saida[1] = 'M';
  saida[2] = total & 0xFF;  saida[3] = (total >> 8) & 0xFF;
  saida[4] = (total >> 16) & 0xFF; saida[5] = (total >> 24) & 0xFF;
  saida[10] = 54;                    // offset dos dados
  saida[14] = 40;                    // tamanho do header DIB
  saida[18] = IMG_W & 0xFF; saida[19] = (IMG_W >> 8) & 0xFF;
  saida[22] = IMG_H & 0xFF; saida[23] = (IMG_H >> 8) & 0xFF;
  saida[26] = 1;                     // planos
  saida[28] = 24;                    // bits por pixel

  uint8_t *p = saida + 54;
  for (int y = 0; y < IMG_H; y++) {
    for (int x = 0; x < IMG_W; x++) {
      bool objeto = (x > 40 + semente % 20) && (x < 120 + semente % 20) &&
                    (y > 30) && (y < 90) && ((x / 6 + y / 6) % 2 == 0);
      uint8_t v = objeto ? 230 : (uint8_t)(40 + ((x + y + semente) % 60));
      *p++ = v;                       // B
      *p++ = objeto ? 200 : v;        // G
      *p++ = objeto ? 120 : v;        // R
    }
    p += rowSize - IMG_W * 3;
  }
  return total;
}

// ---------------------------------------------------------------------------
// Interface
// ---------------------------------------------------------------------------
void handleRoot() {
  String html =
      F("<!DOCTYPE html><html lang='pt-br'><head><meta charset='utf-8'>"
        "<meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>CP01 - simulacao ESP32-CAM</title><style>"
        "body{background:#12141a;color:#e9ecf1;font:15px system-ui,sans-serif;"
        "margin:0;padding:16px}img{width:320px;image-rendering:pixelated;"
        "border-radius:8px;background:#000}button{background:#3b82f6;color:#fff;"
        "border:0;border-radius:8px;padding:10px 15px;font-weight:600;margin-top:12px}"
        "code{background:#1c1f27;padding:2px 6px;border-radius:4px}"
        ".aviso{background:#3a2a12;border:1px solid #6b4a17;border-radius:8px;"
        "padding:10px;font-size:13px;margin-bottom:14px}</style></head><body>"
        "<div class='aviso'>Simulacao Wokwi: a imagem abaixo e sintetica, pois o "
        "sensor OV2640 nao existe no simulador. Na placa real esta mesma rota "
        "<code>/capture</code> devolve o JPEG da camera.</div>"
        "<img src='/capture?t=0' id='im'><br>"
        "<button onclick=\"fetch('/capture').then(r=>r.blob()).then(b=>{"
        "const a=document.createElement('a');a.href=URL.createObjectURL(b);"
        "a.download='");
  html += classeAtual;
  html += F("_'+String(");
  html += String(proximoNumero);
  html += F(").padStart(3,'0')+'.bmp';a.click();location.reload()})\">"
            "Capturar imagem</button><p>Classe atual: <code>");
  html += classeAtual;
  html += F("</code> &nbsp; proximo arquivo: <code>");
  char nome[40];
  snprintf(nome, sizeof(nome), "%s_%03u.jpg", classeAtual.c_str(), proximoNumero);
  html += nome;
  html += F("</code></p></body></html>");
  server.send(200, "text/html; charset=utf-8", html);
}

void handleCapture() {
  static uint8_t buffer[54 + 160 * 120 * 3 + 120 * 3];
  digitalWrite(LED_FLASH_GPIO, HIGH);
  size_t n = montarBMP(buffer, (uint8_t)(totalCapturas * 7));
  delay(60);
  digitalWrite(LED_FLASH_GPIO, LOW);

  char nome[40];
  snprintf(nome, sizeof(nome), "%s_%03u.jpg", classeAtual.c_str(), proximoNumero);
  Serial.printf("[captura] %s (%u bytes, imagem simulada)\n", nome, (unsigned)n);
  proximoNumero++;
  totalCapturas++;

  server.setContentLength(n);
  server.send(200, "image/bmp", "");
  server.client().write(buffer, n);
}

void handleStatus() {
  char json[160];
  snprintf(json, sizeof(json),
           "{\"modo\":\"simulacao\",\"ip\":\"%s\",\"classe\":\"%s\","
           "\"proximo\":%u,\"total\":%u}",
           WiFi.localIP().toString().c_str(), classeAtual.c_str(),
           proximoNumero, (unsigned)totalCapturas);
  server.send(200, "application/json", json);
}

void handleConfig() {
  if (server.hasArg("classe")) { classeAtual = server.arg("classe"); proximoNumero = 1; }
  if (server.hasArg("n")) proximoNumero = server.arg("n").toInt();
  if (server.hasArg("flash"))
    digitalWrite(LED_FLASH_GPIO, server.arg("flash").toInt() ? HIGH : LOW);
  server.send(200, "text/plain", "ok");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_FLASH_GPIO, OUTPUT);
  pinMode(BOTAO_GPIO, INPUT_PULLUP);
  Serial.println("\n== CP01 - AICSS - ESP32CAM | simulacao Wokwi ==");

  WiFi.begin("Wokwi-GUEST", "", 6);
  Serial.print("[wifi] conectando");
  while (WiFi.status() != WL_CONNECTED) { delay(200); Serial.print("."); }
  Serial.printf("\n[web] abra: http://%s\n", WiFi.localIP().toString().c_str());

  server.on("/", handleRoot);
  server.on("/capture", handleCapture);
  server.on("/status", handleStatus);
  server.on("/config", handleConfig);
  server.begin();
  Serial.println("[web] servidor iniciado (porta 80)");
  Serial.println("Pressione o botao CAPTURA no simulador para gerar um arquivo.");
}

void loop() {
  server.handleClient();

  static uint32_t ultimoToque = 0;
  if (digitalRead(BOTAO_GPIO) == LOW && millis() - ultimoToque > 400) {
    ultimoToque = millis();
    char nome[40];
    snprintf(nome, sizeof(nome), "%s_%03u.jpg", classeAtual.c_str(), proximoNumero);
    digitalWrite(LED_FLASH_GPIO, HIGH); delay(80); digitalWrite(LED_FLASH_GPIO, LOW);
    Serial.printf("[botao] captura -> %s\n", nome);
    proximoNumero++; totalCapturas++;
  }
}
