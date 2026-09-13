# Anotacao no Roboflow e exportacao YOLO

A anotacao vale **3,0 pontos** (o maior peso do CP1) e a estrutura YOLO +
`data.yaml` vale mais **1,5**. Vale a pena caprichar nesta etapa.

## 1. Criar o projeto

1. Crie uma conta em roboflow.com.
2. **Create New Project**
   - Project Type: **Object Detection**
   - Annotation Group: `talheres` (ou o nome que o professor indicar)
   - License: a sua escolha
3. Anote o link do projeto — ele vai no README da entrega.

## 2. Subir as imagens

**Upload** → arraste as pastas `dataset/raw/garfo` e `dataset/raw/colher`.
Suba tudo de uma vez para nao bagunçar a numeracao.

## 3. Criar as classes na ordem certa

Crie primeiro `garfo`, depois `colher`. A **ordem define o id numerico**
(`garfo` = 0, `colher` = 1) e o enunciado proibe mudar ordem ou nomes depois.

## 4. Anotar

Para cada imagem, desenhe a bounding box:

- **envolva o objeto inteiro**, incluindo cabo e dentes do garfo;
- **cole a caixa no contorno** — sobra de fundo atrapalha o treino;
- **anote todos os objetos relevantes** da imagem, nao so o mais evidente;
- se o objeto estiver cortado pela borda, anote a parte visivel;
- se estiver muito desfocado ou irreconhecivel, exclua a imagem.

Atalhos que economizam tempo: `D` proxima imagem, `A` anterior, `Enter` salva a
caixa, e a numeracao das classes seleciona a classe ativa.

## 5. Gerar a versao

**Generate** → Train/Valid/Test split. Um split de **70/20/10** ou **80/20**
atende ao que o enunciado pede (`train/` e `valid/` obrigatorios).

Preprocessing util: `Auto-Orient` e `Resize 640x640 (fit)`.
**No CP1 evite augmentation** — imagem aumentada nao conta como imagem coletada
por voce, e o professor avalia a diversidade da coleta real.

## 6. Exportar

**Export Dataset** → formato **YOLOv8** (ou YOLOv5 PyTorch) → *Download zip to
computer*. Extraia dentro de `dataset/export/`, ficando assim:

```
dataset/export/
├── data.yaml
├── train/
│   ├── images/
│   └── labels/
└── valid/
    ├── images/
    └── labels/
```

## 7. Validar antes de entregar

```bash
cd CP01-AICSS-ESP32CAM/tools
python validar_dataset.py --dataset ../dataset/export
```

O script confere estrutura, `data.yaml`, pareamento imagem↔label, formato das
linhas YOLO, coordenadas normalizadas, nomes de arquivo e a contagem por classe.
Entregue so quando ele terminar com *"dataset dentro dos requisitos do CP1"*.
