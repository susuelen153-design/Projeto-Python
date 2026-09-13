# Checklist da entrega do CP1

## Requisitos do enunciado

### 1. ESP32-CAM funcionando — 1,5 ponto
- [ ] placa AI Thinker configurada com o firmware do projeto
- [ ] Wi-Fi 2.4 GHz conectando
- [ ] captura de imagens funcionando
- [ ] servidor web no ar
- [ ] visualizacao da camera pelo navegador
- [ ] print do Serial Monitor e da interface salvos em `evidencias/`

### 2. Coleta das imagens — 2,0 pontos
- [ ] no minimo 2 classes
- [ ] no minimo 100 imagens validas **por classe**
- [ ] variacao de angulo
- [ ] variacao de distancia
- [ ] variacao de iluminacao
- [ ] variacao de posicao do objeto
- [ ] variacao de fundo
- [ ] nenhuma sequencia de fotos praticamente identicas

### 3. Organizacao das imagens — 1,0 ponto
- [ ] nomes no padrao `classe_001.jpg`
- [ ] sem espacos, acentos ou caracteres especiais
- [ ] numeracao continua dentro de cada classe

### 4. Labeling — 3,0 pontos
- [ ] todas as imagens do treino anotadas
- [ ] bounding box envolvendo corretamente o objeto
- [ ] classe correta em cada caixa
- [ ] sem area excessiva fora do objeto
- [ ] todos os objetos relevantes da imagem identificados

### 5. Classes
- [ ] nomes exatamente iguais aos definidos pelo professor
- [ ] ordem das classes inalterada

### 6. Dataset YOLO — 1,5 ponto
- [ ] exportado pelo Roboflow no formato YOLO
- [ ] `data.yaml` presente e com as classes corretas
- [ ] `train/images` e `train/labels`
- [ ] `valid/images` e `valid/labels`
- [ ] `python tools/validar_dataset.py --dataset ../dataset/export` sem erros

### 7. Organizacao da entrega e documentacao — 1,0 ponto
- [ ] README preenchido (integrantes e RMs, classes, quantidade por classe,
      link do Roboflow, descricao do processo)
- [ ] evidencias salvas

## Montando o zip

O enunciado pede **um unico arquivo**: `CP1_NOME_GRUPO.zip`, com a pasta `CP1/`
dentro contendo `firmware/`, `evidencias/`, `dataset/` e `README.md`.

```bash
# a partir da pasta que contem CP01-AICSS-ESP32CAM/
rm -rf CP1 && mkdir -p CP1
cp -r CP01-AICSS-ESP32CAM/firmware   CP1/
cp -r CP01-AICSS-ESP32CAM/evidencias CP1/
cp -r CP01-AICSS-ESP32CAM/dataset    CP1/
cp    CP01-AICSS-ESP32CAM/README.md  CP1/
zip -r CP1_NOME_GRUPO.zip CP1
```

No Windows sem `zip`: copie as quatro pastas/arquivos para uma pasta `CP1`,
clique com o botao direito → **Enviar para → Pasta compactada** e renomeie para
`CP1_NOME_GRUPO.zip` (troque `NOME_GRUPO` pelo nome real do grupo).

Confira antes de enviar: o zip abre e mostra `CP1/` na raiz, o README esta
preenchido e o `data.yaml` tem as classes certas.
