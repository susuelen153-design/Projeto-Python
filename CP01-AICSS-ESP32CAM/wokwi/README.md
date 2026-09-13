# Simulacao no Wokwi

## O que da e o que nao da para simular

O Wokwi **nao simula o sensor de camera OV2640**. Nenhum projeto Wokwi
consegue gerar imagem real de uma ESP32-CAM — as fotos do dataset precisam
obrigatoriamente sair da placa fisica.

O que esta simulado aqui e **toda a logica de software** em volta da camera:
conexao Wi-Fi, servidor web na porta 80, rota `/capture`, rota `/status`,
nomenclatura padronizada `classe_001.jpg`, LED de flash no GPIO4 e botao de
captura no GPIO13. No lugar do quadro da camera, o firmware devolve uma
**imagem sintetica** gerada em memoria.

## Rodando no wokwi.com (mais rapido)

1. Acesse wokwi.com e crie um novo projeto **ESP32**.
2. Cole o conteudo de `src/main.cpp` na aba `sketch.ino`.
3. Cole o conteudo de `diagram.json` na aba `diagram.json`.
4. Clique em **Play**. No Serial Monitor aparece o IP simulado.
5. Clique no link do IP para abrir a interface, ou pressione o botao verde
   **CAPTURA** na protoboard — cada clique imprime o proximo nome de arquivo.

A rede do simulador e `Wokwi-GUEST` (sem senha, canal 6), ja configurada no codigo.

## Rodando dentro do VS Code

1. Instale a extensao **Wokwi for VS Code** e faca o login (licenca gratuita).
2. Abra a pasta `wokwi/` e compile: `pio run -e wokwi`.
3. Rode o comando **Wokwi: Start Simulator**.

O `wokwi.toml` ja aponta para `.pio/build/wokwi/firmware.bin` e `firmware.elf`.

## Diferencas para o firmware real

| | Simulacao (`wokwi/src/main.cpp`) | Placa real (`firmware/esp32cam_dataset/`) |
|---|---|---|
| Imagem | BMP sintetico gerado em codigo | JPEG do sensor OV2640 |
| Wi-Fi | `Wokwi-GUEST` | sua rede 2.4 GHz |
| Placa | ESP32 DevKit | AI Thinker ESP32-CAM |
| Video ao vivo | nao ha | MJPEG em `/stream` |
| Serve para | demonstrar a logica do servidor | **coletar o dataset de verdade** |
