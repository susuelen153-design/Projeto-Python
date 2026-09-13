# COMECE AQUI — ESP32-CAM + base MB

## 1. Abra o projeto no VS Code

Abra o arquivo `CP01-AICSS-ESP32CAM.code-workspace` (janela nova, ja com o
nome "CP01 - AICSS - ESP32CAM"). Instale a extensao **PlatformIO IDE** se o
VS Code sugerir.

## 2. Coloque o seu Wi-Fi

Abra **um unico arquivo**:

```
firmware/esp32cam_dataset/config.h
```

E preencha as duas linhas:

```cpp
#define MEU_WIFI_NOME  "NOME_DA_SUA_REDE"
#define MEU_WIFI_SENHA "SUA_SENHA"
```

Salve com Ctrl+S. **Pronto, so isso.** A rede precisa ser de **2,4 GHz**.

> Nao sabe o nome exato ou nao quer mexer em arquivo? Deixe as aspas vazias.
> A placa vai criar a propria rede **ESP32CAM-CP01** (senha `12345678`).
> Conecte o celular nela, abra `http://192.168.4.1`, escolha a sua rede numa
> lista e digite a senha. Fica salvo na memoria da placa.

## 3. Grave a placa

1. Conecte o cabo USB na base MB.
2. Na barra inferior do VS Code, confirme o ambiente **esp32cam**.
3. Clique na seta **→** (Upload).
4. Se aparecer `Connecting.....`, **segure o botao BOOT** da base ate comecar
   a escrever.
5. Terminou: aperte **RST**.

## 4. Abra a camera

Clique no icone da **tomada** (Serial Monitor). Vai aparecer:

```
[cam] ok
=====================================================
 ABRA NO NAVEGADOR:  http://192.168.0.42
=====================================================
```

Abra esse endereco no navegador do notebook. A tela de coleta aparece com o
video ao vivo, o seletor de classe e o botao de captura.

## 5. Colete as fotos

Pela tela: escolha a classe, clique em **Capturar 1 foto** (ou **Rajada de 10**).
Cada foto ja baixa com o nome certo: `garfo_001.jpg`, `garfo_002.jpg`...

Em lote, pelo terminal:

```bash
cd tools
python coletar_imagens.py --ip 192.168.0.42 --classe garfo  --qtd 100
python coletar_imagens.py --ip 192.168.0.42 --classe colher --qtd 100
```

Depois: anotacao no Roboflow (`docs/03_ROBOFLOW_ANOTACAO.md`) e conferencia
final com `docs/04_CHECKLIST_ENTREGA.md`.
