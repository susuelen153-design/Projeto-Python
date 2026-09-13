/*
 * CP1 - Visao Computacional com ESP32-CAM e YOLO
 * Firmware de coleta de imagens para construcao do dataset.
 *
 * Placa..: AI Thinker ESP32-CAM (OV2640)
 * Rede...: Wi-Fi 2.4 GHz
 * Funcoes: servidor web, visualizacao ao vivo (MJPEG) e captura de fotos
 *          com nome padronizado (ex: garfo_001.jpg)
 *
 * Endpoints:
 *   GET /          -> interface de coleta
 *   GET /stream    -> video ao vivo (multipart/x-mixed-replace)
 *   GET /capture   -> uma foto JPEG
 *   GET /status    -> JSON com estado da camera
 *   GET /config?...-> ajustes rapidos (resolucao, qualidade, brilho, flash)
 */

#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// ---------------------------------------------------------------------------
// 1) CONFIGURE AQUI A SUA REDE (obrigatoriamente 2.4 GHz)
// ---------------------------------------------------------------------------
const char *WIFI_SSID = "COLOQUE_SUA_REDE_2.4GHZ";
const char *WIFI_PASS = "COLOQUE_SUA_SENHA";
// ---------------------------------------------------------------------------
// 2) ESCOLHA A SUA PLACA
//    Deixe descomentada APENAS a linha do modelo que voce comprou.
//    Na duvida, leia a etiqueta/serigrafia do modulo (docs/01_...md).
// ---------------------------------------------------------------------------
#define CAMERA_MODEL_AI_THINKER      // ESP32-CAM classica (com ou sem base MB)
// #define CAMERA_MODEL_WROVER_KIT   // Freenove ESP32-WROVER CAM (USB-C na placa)
// #define CAMERA_MODEL_ESP32S3_EYE  // Freenove ESP32-S3 WROOM CAM / ESP32-S3-EYE
// #define CAMERA_MODEL_XIAO_ESP32S3 // Seeed XIAO ESP32S3 Sense (placa pequenina)

// ---------------------------------------------------------------------------
// 3) PINAGEM DA CAMERA - definida automaticamente pelo modelo acima
// ---------------------------------------------------------------------------
#if defined(CAMERA_MODEL_AI_THINKER)
  #define PWDN_GPIO_NUM 32
  #define RESET_GPIO_NUM -1
  #define XCLK_GPIO_NUM 0
  #define SIOD_GPIO_NUM 26
  #define SIOC_GPIO_NUM 27
  #define Y9_GPIO_NUM 35
  #define Y8_GPIO_NUM 34
  #define Y7_GPIO_NUM 39
  #define Y6_GPIO_NUM 36
  #define Y5_GPIO_NUM 21
  #define Y4_GPIO_NUM 19
  #define Y3_GPIO_NUM 18
  #define Y2_GPIO_NUM 5
  #define VSYNC_GPIO_NUM 25
  #define HREF_GPIO_NUM 23
  #define PCLK_GPIO_NUM 22
  #define LED_FLASH_GPIO 4

#elif defined(CAMERA_MODEL_WROVER_KIT)
  #define PWDN_GPIO_NUM -1
  #define RESET_GPIO_NUM -1
  #define XCLK_GPIO_NUM 21
  #define SIOD_GPIO_NUM 26
  #define SIOC_GPIO_NUM 27
  #define Y9_GPIO_NUM 35
  #define Y8_GPIO_NUM 34
  #define Y7_GPIO_NUM 39
  #define Y6_GPIO_NUM 36
  #define Y5_GPIO_NUM 19
  #define Y4_GPIO_NUM 18
  #define Y3_GPIO_NUM 5
  #define Y2_GPIO_NUM 4
  #define VSYNC_GPIO_NUM 25
  #define HREF_GPIO_NUM 23
  #define PCLK_GPIO_NUM 22
  #define LED_FLASH_GPIO 2

#elif defined(CAMERA_MODEL_ESP32S3_EYE)
  #define PWDN_GPIO_NUM -1
  #define RESET_GPIO_NUM -1
  #define XCLK_GPIO_NUM 15
  #define SIOD_GPIO_NUM 4
  #define SIOC_GPIO_NUM 5
  #define Y9_GPIO_NUM 16
  #define Y8_GPIO_NUM 17
  #define Y7_GPIO_NUM 18
  #define Y6_GPIO_NUM 12
  #define Y5_GPIO_NUM 10
  #define Y4_GPIO_NUM 8
  #define Y3_GPIO_NUM 9
  #define Y2_GPIO_NUM 11
  #define VSYNC_GPIO_NUM 6
  #define HREF_GPIO_NUM 7
  #define PCLK_GPIO_NUM 13
  #define LED_FLASH_GPIO 2

#elif defined(CAMERA_MODEL_XIAO_ESP32S3)
  #define PWDN_GPIO_NUM -1
  #define RESET_GPIO_NUM -1
  #define XCLK_GPIO_NUM 10
  #define SIOD_GPIO_NUM 40
  #define SIOC_GPIO_NUM 39
  #define Y9_GPIO_NUM 48
  #define Y8_GPIO_NUM 11
  #define Y7_GPIO_NUM 12
  #define Y6_GPIO_NUM 14
  #define Y5_GPIO_NUM 16
  #define Y4_GPIO_NUM 18
  #define Y3_GPIO_NUM 17
  #define Y2_GPIO_NUM 15
  #define VSYNC_GPIO_NUM 38
  #define HREF_GPIO_NUM 47
  #define PCLK_GPIO_NUM 13
  #define LED_FLASH_GPIO 21

#else
  #error "Escolha um modelo de placa no bloco 2) acima."
#endif

WebServer server(80);

// ---------------------------------------------------------------------------
// Pagina de coleta
// ---------------------------------------------------------------------------
static const char PAGE_INDEX[] PROGMEM = R"HTML(
<!DOCTYPE html><html lang="pt-br"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>ESP32-CAM | Coleta do dataset</title>
<style>
 :root{color-scheme:dark}
 body{margin:0;background:#12141a;color:#e9ecf1;font:15px/1.5 system-ui,sans-serif}
 .wrap{max-width:900px;margin:0 auto;padding:16px}
 h1{font-size:19px;margin:0 0 4px}
 p.sub{margin:0 0 16px;color:#9aa3b2;font-size:13px}
 img{width:100%;max-width:100%;border-radius:10px;background:#000;display:block}
 .row{display:flex;flex-wrap:wrap;gap:10px;margin:14px 0;align-items:flex-end}
 label{display:block;font-size:12px;color:#9aa3b2;margin-bottom:4px}
 input,select{background:#1c1f27;color:#e9ecf1;border:1px solid #333a47;
   border-radius:8px;padding:9px 10px;font-size:14px}
 input[type=number]{width:90px}
 button{background:#3b82f6;color:#fff;border:0;border-radius:8px;
   padding:11px 16px;font-size:14px;font-weight:600;cursor:pointer}
 button.alt{background:#2b3140}
 button:disabled{opacity:.5;cursor:not-allowed}
 #log{background:#0d0f14;border:1px solid #232937;border-radius:8px;
   padding:10px;height:150px;overflow:auto;font:12px/1.5 ui-monospace,monospace;
   white-space:pre-wrap}
 .tag{display:inline-block;background:#1c1f27;border:1px solid #333a47;
   border-radius:999px;padding:3px 10px;font-size:12px;color:#9aa3b2}
</style></head><body><div class="wrap">
<h1>ESP32-CAM &mdash; coleta de imagens do dataset</h1>
<p class="sub">As fotos sao salvas na pasta de downloads com nome padronizado
 (<code>classe_001.jpg</code>), sem espacos, acentos ou caracteres especiais.</p>

<img id="live" src="/stream" alt="video ao vivo">

<div class="row">
  <div><label>Classe</label>
    <select id="classe">
      <option value="garfo">garfo</option>
      <option value="colher">colher</option>
      <option value="faca">faca</option>
    </select></div>
  <div><label>Proximo numero</label>
    <input id="n" type="number" min="1" value="1"></div>
  <div><label>Resolucao</label>
    <select id="res" onchange="cfg('framesize',this.value)">
      <option value="8">VGA 640x480</option>
      <option value="9">SVGA 800x600</option>
      <option value="10" selected>XGA 1024x768</option>
      <option value="13">UXGA 1600x1200</option>
    </select></div>
  <div><label>Flash</label>
    <select id="flash" onchange="cfg('flash',this.value)">
      <option value="0" selected>desligado</option>
      <option value="1">ligado</option>
    </select></div>
</div>

<div class="row">
  <button id="btn1" onclick="foto()">Capturar 1 foto</button>
  <button class="alt" onclick="rajada()">Rajada de 10 (1/s)</button>
  <button class="alt" onclick="document.getElementById('log').textContent=''">Limpar log</button>
  <span class="tag" id="cont">0 fotos nesta sessao</span>
</div>

<div id="log"></div>
</div><script>
let total=0, ocupado=false;
const log=m=>{const l=document.getElementById('log');
  l.textContent+=m+"\n"; l.scrollTop=l.scrollHeight;};
const pad=n=>String(n).padStart(3,'0');

async function cfg(k,v){ await fetch(`/config?${k}=${v}`); log(`ajuste ${k}=${v}`); }

async function foto(){
  if(ocupado) return; ocupado=true;
  const classe=document.getElementById('classe').value;
  const campo=document.getElementById('n');
  const nome=`${classe}_${pad(+campo.value)}.jpg`;
  try{
    const r=await fetch('/capture?t='+Date.now());
    if(!r.ok) throw new Error('HTTP '+r.status);
    const b=await r.blob();
    const a=document.createElement('a');
    a.href=URL.createObjectURL(b); a.download=nome;
    document.body.appendChild(a); a.click(); a.remove();
    setTimeout(()=>URL.revokeObjectURL(a.href),4000);
    campo.value=(+campo.value)+1; total++;
    document.getElementById('cont').textContent=total+' fotos nesta sessao';
    log(`ok  ${nome}  (${(b.size/1024).toFixed(0)} kB)`);
  }catch(e){ log('ERRO '+e.message); }
  ocupado=false;
}

async function rajada(){
  for(let i=0;i<10;i++){ await foto(); await new Promise(r=>setTimeout(r,1000)); }
  log('-- rajada concluida: varie angulo, distancia, luz e fundo --');
}
</script></body></html>
)HTML";

// ---------------------------------------------------------------------------
// Handlers
// ---------------------------------------------------------------------------
void handleRoot() {
  server.sendHeader("Cache-Control", "no-store");
  server.send_P(200, "text/html; charset=utf-8", PAGE_INDEX);
}

void handleCapture() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    server.send(500, "text/plain", "falha ao capturar imagem");
    return;
  }
  server.sendHeader("Cache-Control", "no-store");
  server.sendHeader("Content-Disposition", "inline; filename=captura.jpg");
  server.setContentLength(fb->len);
  server.send(200, "image/jpeg", "");
  server.client().write(fb->buf, fb->len);
  esp_camera_fb_return(fb);
}

void handleStream() {
  WiFiClient client = server.client();
  client.print(F("HTTP/1.1 200 OK\r\n"
                 "Content-Type: multipart/x-mixed-replace; boundary=quadro\r\n"
                 "Cache-Control: no-store\r\n\r\n"));

  while (client.connected()) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) break;
    client.printf("--quadro\r\nContent-Type: image/jpeg\r\n"
                  "Content-Length: %u\r\n\r\n", fb->len);
    client.write(fb->buf, fb->len);
    client.print(F("\r\n"));
    esp_camera_fb_return(fb);
    delay(40);  // ~20 fps maximo, evita travar o Wi-Fi
  }
}

void handleStatus() {
  sensor_t *s = esp_camera_sensor_get();
  char json[200];
  snprintf(json, sizeof(json),
           "{\"ip\":\"%s\",\"rssi\":%d,\"framesize\":%d,\"quality\":%d,"
           "\"heap\":%u,\"psram\":%s}",
           WiFi.localIP().toString().c_str(), WiFi.RSSI(),
           s ? s->status.framesize : -1, s ? s->status.quality : -1,
           (unsigned)ESP.getFreeHeap(), psramFound() ? "true" : "false");
  server.send(200, "application/json", json);
}

void handleConfig() {
  sensor_t *s = esp_camera_sensor_get();
  if (!s) {
    server.send(500, "text/plain", "sensor indisponivel");
    return;
  }
  if (server.hasArg("framesize"))
    s->set_framesize(s, (framesize_t)server.arg("framesize").toInt());
  if (server.hasArg("quality"))
    s->set_quality(s, server.arg("quality").toInt());
  if (server.hasArg("brightness"))
    s->set_brightness(s, server.arg("brightness").toInt());
  if (server.hasArg("flash"))
    digitalWrite(LED_FLASH_GPIO, server.arg("flash").toInt() ? HIGH : LOW);
  server.send(200, "text/plain", "ok");
}

// ---------------------------------------------------------------------------
// Setup / loop
// ---------------------------------------------------------------------------
bool iniciarCamera() {
  camera_config_t config = {};
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_XGA;  // 1024x768: bom para dataset
    config.jpeg_quality = 10;           // menor = melhor qualidade
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  config.fb_location = psramFound() ? CAMERA_FB_IN_PSRAM : CAMERA_FB_IN_DRAM;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("[cam] falha na inicializacao: 0x%x\n", err);
    return false;
  }
  sensor_t *s = esp_camera_sensor_get();
  if (s) {
    s->set_vflip(s, 0);
    s->set_hmirror(s, 0);
    s->set_brightness(s, 1);
    s->set_saturation(s, 0);
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println("\n== CP1 | ESP32-CAM coleta de dataset ==");

  pinMode(LED_FLASH_GPIO, OUTPUT);
  digitalWrite(LED_FLASH_GPIO, LOW);

  if (!iniciarCamera()) {
    Serial.println("Verifique o flat da camera e a alimentacao 5V.");
    while (true) delay(1000);
  }
  Serial.println("[cam] ok");

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.printf("[wifi] conectando em \"%s\"", WIFI_SSID);
  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 30000) {
    delay(400);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[wifi] nao conectou. A rede precisa ser 2.4 GHz.");
    ESP.restart();
  }
  Serial.printf("[wifi] conectado | RSSI %d dBm\n", WiFi.RSSI());
  Serial.print  ("[web] abra no navegador: http://");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/capture", HTTP_GET, handleCapture);
  server.on("/stream", HTTP_GET, handleStream);
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/config", HTTP_GET, handleConfig);
  server.begin();
  Serial.println("[web] servidor iniciado na porta 80");
}

void loop() {
  server.handleClient();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[wifi] queda de conexao, reconectando...");
    WiFi.reconnect();
    delay(2000);
  }
}
