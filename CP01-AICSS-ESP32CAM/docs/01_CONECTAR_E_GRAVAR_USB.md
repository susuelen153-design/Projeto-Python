# Passo a passo: conectar a ESP32-CAM no notebook via USB e gravar o firmware

## Atencao antes de tudo

A **ESP32-CAM AI Thinker nao tem conector USB na propria placa**. Para gravar pelo
notebook voce precisa de um destes dois caminhos:

| Caminho | O que e | Como fica |
|---|---|---|
| **A — placa MB (recomendado)** | Base "ESP32-CAM-MB" com micro-USB que encaixa por baixo da camera | Encaixa, liga o cabo USB, pronto |
| **B — adaptador FTDI/CP2102/CH340** | Conversor USB-Serial ligado por jumpers | Exige a fiacao da tabela abaixo |

Se o kit que voce comprou veio com a plaquinha preta com micro-USB, use o caminho A.

## Caminho B — ligacoes (o "mapa de pinos")

| Adaptador USB-Serial | ESP32-CAM |
|---|---|
| 5V (ou VCC em 5V) | 5V |
| GND | GND |
| TX | U0R (GPIO3, RX) |
| RX | U0T (GPIO1, TX) |
| GND | **IO0 (GPIO0)** — somente para gravar |

Pontos que mais derrubam a gravacao:

1. O jumper **IO0 → GND** e o que coloca o chip em modo de gravacao. Depois de
   gravar, **remova o jumper e pressione o botao RST**, senao o programa nao roda.
2. Alimente em **5V**, nunca em 3V3. A camera puxa picos de corrente e em 3V3 ela
   reinicia sozinha (`Brownout detector was triggered`).
3. TX vai no RX e RX vai no TX (cruzado).
4. Cabo USB precisa ser de dados, nao so de carga.

## Drivers (Windows)

1. Abra o **Gerenciador de Dispositivos**.
2. Se aparecer um dispositivo desconhecido, instale o driver do chip do seu adaptador:
   - **CH340/CH341** → driver CH341SER do site da WCH
   - **CP2102** → driver VCP da Silicon Labs
   - **FT232** → driver VCP da FTDI
3. Depois de instalado, o adaptador aparece como **COM3**, **COM4**, etc.
   Anote esse numero.

No Linux a porta e `/dev/ttyUSB0`; rode uma vez
`sudo usermod -a -G dialout $USER` e refaca o login.
No macOS a porta e `/dev/cu.usbserial-XXXX` ou `/dev/cu.SLAB_USBtoUART`.

## Gravando pelo VS Code (PlatformIO)

1. Instale a extensao **PlatformIO IDE** no VS Code.
2. Abra a pasta `firmware/platformio` (ou o arquivo de workspace
   `CP01-AICSS-ESP32CAM.code-workspace`, que ja abre as duas pastas).
3. Edite `firmware/esp32cam_dataset/esp32cam_dataset.ino` e preencha:
   ```cpp
   const char *WIFI_SSID = "SUA_REDE_2.4GHZ";
   const char *WIFI_PASS = "SUA_SENHA";
   ```
   A rede **precisa ser 2.4 GHz** — a ESP32 nao enxerga 5 GHz.
4. Com **IO0 ligado ao GND**, clique em **PlatformIO: Upload** (seta →
   na barra inferior).
5. Assim que terminar: **tire o jumper IO0–GND** e aperte **RST**.
6. Abra o **Serial Monitor** (icone da tomada, 115200 baud). Vai aparecer:
   ```
   [cam] ok
   [wifi] conectado | RSSI -54 dBm
   [web] abra no navegador: http://192.168.0.42
   ```
7. Abra esse IP no navegador do notebook (mesma rede Wi-Fi). A interface de
   coleta aparece com o video ao vivo.

## Alternativa: Arduino IDE

1. **Arquivo → Preferencias → URLs adicionais**:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. **Ferramentas → Placa → Gerenciador de placas** → instale **esp32** (Espressif).
3. Selecione **AI Thinker ESP32-CAM**, a porta COM correta e
   **Partition Scheme: Huge APP (3MB No OTA)**.
4. Abra `firmware/esp32cam_dataset/esp32cam_dataset.ino` e clique em Upload
   (com IO0 em GND).

## Se der errado

| Mensagem / sintoma | Causa provavel |
|---|---|
| `Failed to connect to ESP32: Timed out waiting for packet header` | IO0 nao esta em GND, ou TX/RX invertidos |
| `Brownout detector was triggered` | alimentacao fraca — use 5V com corrente suficiente |
| `Camera init failed with error 0x20004` | flat da camera mal encaixado ou trava do conector aberta |
| Conecta no Wi-Fi mas cai toda hora | rede 5 GHz, sinal fraco, ou roteador separando as bandas |
| Video trava no navegador | baixe a resolucao para VGA/SVGA na propria interface |

---

## Erro "Surto de tensao na porta USB" (USB power surge)

> *"Dispositivo USB desconhecido precisa de mais energia do que a capacidade de
> fornecimento da porta."*

O Windows **cortou a energia da porta** porque a placa puxou mais corrente do que
os 500 mA que uma porta USB entrega, ou porque ha um **curto** na ligacao.
Nao insista: desconecte antes de continuar.

### O que fazer, na ordem

1. **Desconecte o cabo USB imediatamente.** Encoste no modulo: se algum chip
   estiver quente demais, existe curto e ele precisa ser refeito do zero.
2. Confira a fiacao antes de religar:
   - **5V do adaptador vai no pino 5V** da ESP32-CAM — nunca no 3V3;
   - nao pode haver fio ligando **5V direto no GND**;
   - TX↔U0R e RX↔U0T (cruzados), nao paralelos.
3. **Reencaixe o flat da camera.** Flat invertido ou torto e a causa mais comum
   desse surto. Abra a trava preta do conector, encaixe os contatos dourados
   virados para o lado certo e feche a trava.
4. Troque a porta: use uma **USB diretamente no notebook**, de preferencia uma
   **USB 3.0 (azul)**, nunca um hub sem fonte propria.
5. Troque o cabo por um **cabo de dados** curto e de boa qualidade.
6. Se voltar a acontecer, **alimente a placa por fora**: uma fonte 5V 2A
   (ou power bank) no pino 5V/GND da ESP32-CAM, e do adaptador USB-Serial ligue
   **somente GND, TX e RX**. O GND da fonte e o do adaptador precisam estar unidos.
   Esse e o arranjo mais confiavel para a ESP32-CAM.
7. Para a mensagem parar de aparecer e a porta voltar a energizar: feche o aviso,
   desconecte tudo e **reinicie o notebook** (o Windows so rearma a protecao da
   porta no boot, em alguns casos).

### Por que acontece justamente com a ESP32-CAM

No instante em que o Wi-Fi transmite, a placa pede picos de **300 a 500 mA**, e
a camera soma mais alguns. Isso fica no limite (ou acima) do que uma porta USB
comum fornece — por isso alimentacao externa em 5V resolve de vez, e por isso o
sintoma classico no Serial Monitor e `Brownout detector was triggered`.

---

## Se a sua placa JA TEM USB (sem adaptador FTDI)

Nesse caso nao ha fiacao nenhuma: e so o cabo USB. Mas existem modelos
diferentes com USB, e **cada um tem uma pinagem de camera diferente**. Descubra
o seu pela serigrafia do modulo:

| O que esta escrito / como e | Modelo | `#define` no .ino | env do PlatformIO |
|---|---|---|---|
| Placa preta pequena encaixada **por baixo** da ESP32-CAM, com micro-USB e botao RST | ESP32-CAM + base **MB** | `CAMERA_MODEL_AI_THINKER` | `esp32cam` |
| Placa preta com **USB-C na propria placa**, escrito `ESP32-WROVER` | Freenove ESP32-WROVER CAM | `CAMERA_MODEL_WROVER_KIT` | `freenove_wrover` |
| USB-C na placa, escrito **ESP32-S3** | Freenove ESP32-S3 CAM / S3-EYE | `CAMERA_MODEL_ESP32S3_EYE` | `esp32s3cam` |
| Placa minuscula (~2 cm), escrito **XIAO ESP32S3** | Seeed XIAO ESP32S3 Sense | `CAMERA_MODEL_XIAO_ESP32S3` | `xiao_esp32s3` |

No inicio de `esp32cam_dataset.ino`, deixe **descomentada apenas** a linha do seu
modelo. Se errar o modelo, a gravacao funciona mas aparece
`Camera init failed` no Serial Monitor.

Para gravar, escolha o env correspondente no PlatformIO (barra inferior do
VS Code → *Project Environment*) e clique em Upload.

### Base MB (ESP32-CAM-MB)

- Nao precisa de jumper IO0–GND: a base tem o botao **BOOT/IO0**.
- Se der `Failed to connect`, **segure o botao BOOT** enquanto o upload comeca
  ("Connecting....") e solte quando aparecer "Writing".
- O aviso de surto de tensao tambem acontece com a base MB — o motivo e o mesmo
  (pico de corrente do Wi-Fi + camera). A solucao continua sendo porta USB
  direta no notebook, cabo de dados bom, ou alimentacao externa em 5V.
