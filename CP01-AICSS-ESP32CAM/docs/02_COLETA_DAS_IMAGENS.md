# Coleta das imagens (requisito de 2,0 pontos: quantidade e diversidade)

## Quanto o professor exige

- **no minimo 2 classes**
- **no minimo 100 imagens validas por classe**
- variacoes obrigatorias de **angulo, distancia, iluminacao, posicao do objeto e fundo**
- "nao serao considerados datasets compostos praticamente pela mesma imagem repetida"

Como voce vai fotografar **garfos**, as classes sugeridas neste projeto sao
`garfo` e `colher` (uma terceira, `faca`, ja esta prevista na interface).
Objetos parecidos obrigam o modelo a aprender a forma, e nao so "tem metal na foto".

> **Confirme com o professor** a lista oficial de classes antes de anotar.
> O enunciado diz que a nomenclatura e a ordem das classes nao podem mudar
> depois; trocar isso no meio do projeto quebra os proximos checkpoints.

## Jeito 1 — pelo navegador (mais simples)

1. Abra `http://IP_DA_CAMERA` no notebook.
2. Escolha a **classe** e confira o **proximo numero**.
3. Clique em **Capturar 1 foto**: o arquivo cai na pasta de downloads ja como
   `garfo_001.jpg`, `garfo_002.jpg`, ...
4. **Rajada de 10** tira 10 fotos com 1 segundo de intervalo — mexa o objeto
   entre os disparos.

## Jeito 2 — em lote pelo Python (mais rapido para 100+)

```bash
cd CP01-AICSS-ESP32CAM/tools
python coletar_imagens.py --ip 192.168.0.42 --classe garfo  --qtd 100
python coletar_imagens.py --ip 192.168.0.42 --classe colher --qtd 100
```

As imagens vao para `dataset/raw/garfo/` e `dataset/raw/colher/`, numeradas em
sequencia. O script continua de onde parou se voce rodar de novo, descarta
respostas que nao sejam JPEG valido e avisa quando ainda faltam imagens para 100.

## Roteiro pratico para 100 fotos sem repetir

Faca 10 rodadas de 10 fotos, mudando uma coisa a cada rodada:

| Rodada | O que mudar |
|---|---|
| 1 | objeto reto, de cima, fundo claro |
| 2 | girado 45°, de cima |
| 3 | girado 90° (deitado de lado) |
| 4 | camera bem perto (~15 cm) |
| 5 | camera longe (~60 cm) |
| 6 | luz do ambiente apagada, so luz de janela |
| 7 | LED de flash ligado na interface |
| 8 | fundo escuro (pano/papel escuro) |
| 9 | fundo bagunçado (mesa com outros objetos) |
| 10 | objeto parcialmente encoberto / dois objetos na mesma foto |

Fotos com **mais de um objeto** sao otimas: no Roboflow voce anota as duas
caixas e o modelo aprende a separar os itens.

## Organizando depois

Se voce baixou fotos pelo navegador e os nomes sairam bagunçados:

```bash
python organizar_dataset.py --pasta ../dataset/raw/garfo --classe garfo            # simula
python organizar_dataset.py --pasta ../dataset/raw/garfo --classe garfo --aplicar  # efetiva
```

Resultado final: nomes so com letras minusculas, numeros e `_`, sem espacos,
sem acentos e sem caracteres especiais — exatamente como o enunciado pede.
