# CP01 - AICSS - ESP32CAM

**Checkpoint 1 — Construcao do dataset**
Projeto: Visao Computacional com ESP32-CAM e YOLO.

> Comecando agora? Leia **[COMECE_AQUI.md](COMECE_AQUI.md)** — sao 5 passos.
>
> Este README e o arquivo exigido na entrega. **Preencha os campos marcados com
> `PREENCHER` antes de gerar o zip.**

## Integrantes

| Nome | RM |
|---|---|
| PREENCHER | PREENCHER |
| PREENCHER | PREENCHER |

## Classes utilizadas

| id | classe |
|---|---|
| 0 | `garfo` |
| 1 | `colher` |

A nomenclatura e a ordem seguem as classes oficiais definidas pelo professor e
**nao serao alteradas** durante o desenvolvimento do projeto.

## Quantidade de imagens por classe

| Classe | Imagens coletadas | Imagens anotadas |
|---|---|---|
| garfo | PREENCHER | PREENCHER |
| colher | PREENCHER | PREENCHER |

## Link do projeto Roboflow

PREENCHER

## Descricao do processo realizado

1. **Firmware.** A ESP32-CAM AI Thinker foi programada com o firmware em
   `firmware/esp32cam_dataset/`, que inicializa o sensor OV2640, conecta na rede
   Wi-Fi 2.4 GHz e sobe um servidor web na porta 80 com visualizacao ao vivo
   (`/stream`) e captura de fotos (`/capture`).
2. **Captura.** As imagens foram coletadas pela interface do navegador e em lote
   pelo script `tools/coletar_imagens.py`, sempre com nome padronizado
   `classe_NNN.jpg`.
3. **Diversidade.** Foram feitas rodadas variando angulo, distancia, iluminacao,
   posicao do objeto e fundo, conforme `docs/02_COLETA_DAS_IMAGENS.md`.
4. **Organizacao.** Os nomes foram padronizados com `tools/organizar_dataset.py`
   — apenas minusculas, numeros e `_`, sem espacos, acentos ou caracteres especiais.
5. **Anotacao.** Todas as imagens foram anotadas no Roboflow, com bounding boxes
   envolvendo o objeto inteiro, sem area excessiva de fundo e cobrindo todos os
   objetos relevantes de cada imagem.
6. **Exportacao.** O dataset foi exportado no formato YOLO, gerando `data.yaml`,
   `train/{images,labels}` e `valid/{images,labels}`.
7. **Validacao.** A estrutura foi conferida com `tools/validar_dataset.py`.

## Estrutura do projeto

```
CP01-AICSS-ESP32CAM/
├── firmware/
│   ├── esp32cam_dataset/        codigo gravado na ESP32-CAM
│   │   └── config.h             <- UNICO arquivo que voce precisa editar (Wi-Fi)
│   └── platformio/              projeto PlatformIO para o VS Code
├── wokwi/                       simulacao no Wokwi da logica do servidor web
├── tools/
│   ├── coletar_imagens.py       baixa fotos da camera ja com nome padronizado
│   ├── organizar_dataset.py     padroniza nomes de arquivos existentes
│   └── validar_dataset.py       valida o dataset YOLO antes da entrega
├── dataset/
│   ├── data.yaml                modelo de referencia
│   ├── raw/                     fotos cruas por classe
│   └── export/                  dataset exportado do Roboflow
├── evidencias/                  prints do funcionamento
└── docs/
    ├── 01_CONECTAR_E_GRAVAR_USB.md
    ├── 02_COLETA_DAS_IMAGENS.md
    ├── 03_ROBOFLOW_ANOTACAO.md
    └── 04_CHECKLIST_ENTREGA.md
```

## Como reproduzir

```bash
# 1. gravar a placa (VS Code + PlatformIO)
#    edite WIFI_SSID / WIFI_PASS em firmware/esp32cam_dataset/esp32cam_dataset.ino
#    com IO0 ligado ao GND: PlatformIO -> Upload; depois retire o jumper e aperte RST

# 2. abrir o IP mostrado no Serial Monitor no navegador

# 3. coletar as imagens
cd tools
python coletar_imagens.py --ip 192.168.0.42 --classe garfo  --qtd 100
python coletar_imagens.py --ip 192.168.0.42 --classe colher --qtd 100

# 4. validar o dataset exportado do Roboflow
python validar_dataset.py --dataset ../dataset/export
```

Detalhes de hardware, drivers e solucao de problemas: `docs/01_CONECTAR_E_GRAVAR_USB.md`.
