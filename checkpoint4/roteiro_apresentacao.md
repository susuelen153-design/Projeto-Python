# Roteiro de Apresentação, Checkpoint 4

**Tema:** Probabilidade e Distribuição Normal aplicadas à Inteligência Artificial
**Aplicação:** Logística, previsão de atrasos em entregas com dados simulados em Python
**Disciplina:** Statistical Computing with R & Python. Prof. Me. Eng. Rodolfo Magliari de Paiva
**Duração prevista:** 10 a 12 minutos. Todos os integrantes falam, conforme exige o enunciado.

| Integrante | RM | Slides | Tempo |
|---|---|---|---|
| Giovanni Henrique Pereira Hessel | 570574 | 1, 2, 3 | 3 min |
| Suellen Pereira da Silva | 573862 | 4, 5, 6 | 3 min |
| Arthur Zeferino | 570858 | 7, 8, 9 | 3 min |
| Israel Carneiro de Toledo | 573854 | 10, 11, 12, 13 | 3 min |

As mesmas falas estão nas notas do orador do arquivo `.pptx`, visíveis no modo Apresentador do PowerPoint.

---

## GIOVANNI (slides 1 a 3)

### Slide 1, Capa (30 s)
"Boa noite, professor e colegas. Nosso grupo escolheu dois dos temas propostos: Probabilidade e a Inteligência Artificial, e Distribuição Normal e a Inteligência Artificial. Para deixar o conteúdo aplicado, trabalhamos com um problema de Logística: prever o atraso de entregas de uma transportadora urbana. Os dados são simulados em Python com semente fixa, então qualquer pessoa que rode o código chega aos mesmos resultados. Apresentam comigo a Suellen, o Arthur e o Israel."

### Slide 2, Introdução e Justificativa (1 min)
"Trânsito, clima e distância mudam o tempo de cada entrega, então toda previsão de prazo carrega incerteza. E aqui está a justificativa do trabalho: um modelo preditivo não responde com certezas, ele responde com probabilidades. Quando uma rede neural classifica uma imagem, o que ela devolve é uma probabilidade de cada classe. Sem probabilidade e sem a distribuição Normal não se constrói nem se interpreta um modelo desse tipo.

O contexto é uma transportadora com prazo prometido, o SLA, de 60 minutos por entrega. O problema é descobrir quais fatores elevam o risco de atraso e qual a chance real de estourar esse prazo. A base é simulada, com semente 42. No painel à direita estão as cinco perguntas que respondemos ao longo da apresentação."

### Slide 3, Probabilidade: conceitos e fórmulas (1 min 30 s)
"Começando pelo primeiro tema. Três ferramentas sustentam o trabalho inteiro.

A probabilidade clássica, casos favoráveis sobre casos possíveis, que na prática é a frequência relativa do evento na base.

A probabilidade condicional, P de A dado B, igual à probabilidade conjunta dividida por P de B. Ela atualiza a chance de um evento quando já sabemos que outro ocorreu, e é o que separa a chance média da chance naquela situação específica.

E o Teorema de Bayes, que inverte a condicional: conhecendo P de A dado B, chegamos a P de B dado A. Esse teorema sustenta os classificadores probabilísticos que vamos mostrar adiante.

Tudo isso respeita os axiomas de Kolmogorov, no quadro azul. À direita listamos onde esses conceitos aparecem na prática: classificadores, a função softmax na saída de redes neurais, filtros de spam, sistemas de recomendação e cálculo de risco em seguros. Passo para a Suellen."

---

## SUELLEN (slides 4 a 6)

### Slide 4, A base de dados e os números pseudoaleatórios (1 min)
"Antes dos resultados, uma palavra sobre os dados. O computador não produz acaso verdadeiro. Ele usa um algoritmo determinístico que parte de uma semente e gera uma sequência com propriedades estatísticas de aleatoriedade. São os números pseudoaleatórios. Fixamos a semente em 42, então a execução é sempre a mesma.

No código, a distância vem de uma Normal com média de 12 quilômetros; chuva e horário de pico vêm de distribuições de Bernoulli, com 30% e 40% de chance; e o tempo de entrega soma o tempo fixo de coleta, 3 minutos por quilômetro, 12 minutos quando chove, 9 minutos no horário de pico e um erro Normal. A variável alvo segue a regra do SLA: atraso igual a 1 quando o tempo passa de 60 minutos. São mil entregas simuladas e cinco variáveis."

### Slide 5, Probabilidade condicional na prática (1 min)
"Rodando o código, chegamos a este quadro. Na média, 22,5% das entregas atrasam. Só que essa média esconde a realidade da operação. Sem chuva e fora do pico, o risco é de 8%. Só com chuva, sobe para 41%. Com chuva e horário de pico ao mesmo tempo, chega a 64,7%, quase dois em cada três pedidos.

O risco relativo da chuva é de 2,87 vezes. É exatamente esse tipo de padrão condicional que um modelo preditivo aprende a partir dos dados."

### Slide 6, Teorema de Bayes (1 min)
"Agora invertemos a pergunta. Em vez de perguntar qual a chance de atrasar quando está chovendo, perguntamos: esta entrega atrasou, o que provavelmente aconteceu?

Aplicando Bayes, P de chuva dado atraso é igual a P de atraso dado chuva, vezes P de chuva, dividido por P de atraso. Substituindo os valores: 0,410 vezes 0,307, dividido por 0,225, resulta em 0,560.

Nos quatro cartões estão os nomes de cada termo: verossimilhança, priori, evidência e posteriori, que é o vocabulário usado em qualquer modelo bayesiano. E o código confirma o cálculo: a frequência observada na base também é 0,560. Arthur segue com o segundo tema."

---

## ARTHUR (slides 7 a 9)

### Slide 7, Distribuição Normal (1 min 30 s)
"Segundo tema, a Distribuição Normal. A fórmula da densidade está no quadro azul e depende de apenas dois parâmetros, a média mu e o desvio padrão sigma. No nosso caso, 48,9 minutos de média e 15,4 minutos de desvio.

No gráfico, as barras são os dados observados e a curva vermelha é a Normal ajustada. A aderência é quase perfeita, e há uma razão: o tempo de entrega é uma soma de vários efeitos, e somas de efeitos independentes tendem à Normal.

A área sombreada à direita da linha tracejada é a resposta que a empresa procura, a probabilidade de estourar o SLA. Calculamos pela padronização, o escore z: 60 menos 48,94, dividido por 15,42, dá 0,717. Consultando a Normal padrão, o risco é de 23,7%, contra 22,5% observados na base. E há um uso gerencial direto: pelo percentil 95, prometer 75 minutos cumpriria o prazo em 95% das entregas."

### Slide 8, Por que a Normal aparece tanto (1 min)
"A explicação está no Teorema Central do Limite. À esquerda, uma população fortemente assimétrica, uma exponencial. No meio, médias de amostras de tamanho 5, já mais simétricas. À direita, com n igual a 50, a distribuição das médias é praticamente Normal. Independentemente da forma original dos dados, a média amostral converge para a Normal.

Validamos a normalidade de duas formas. Pela regra empírica, 68, 95 e 99,7% dentro de um, dois e três desvios, que bate com o observado. E pelo teste de Shapiro-Wilk, com p-valor de 0,093, acima de 0,05, o que significa que não rejeitamos a hipótese de normalidade.

À direita listamos onde essa curva é usada: inicialização de pesos de redes neurais, padronização de variáveis, verossimilhança gaussiana, detecção de anomalias acima de três sigma e o ruído gaussiano dos modelos de difusão."

### Slide 9, Classificador Naive Bayes Gaussiano (1 min 30 s)
"Neste slide os dois temas se encontram. Construímos um classificador Naive Bayes Gaussiano sem usar nenhuma biblioteca de machine learning, apenas probabilidade e a fórmula da Normal.

A ideia é a seguinte: a probabilidade de uma classe dado os dados é proporcional à probabilidade a priori dessa classe multiplicada pelas verossimilhanças de cada variável. É o Teorema de Bayes aplicado. O termo naive, ingênuo, vem da suposição de que as variáveis são independentes entre si dada a classe.

No código à direita, a função `densidade_normal` é a mesma fórmula da Normal do slide anterior. E a função `prever` calcula priori vezes verossimilhança para cada classe, normaliza e devolve a classe mais provável junto com a probabilidade. Treinamos com 70% da base. O Israel apresenta os resultados."

---

## ISRAEL (slides 10 a 13)

### Slide 10, Resultados e simulação de cenários (1 min 30 s)
"Avaliamos o modelo em 300 entregas que ele nunca tinha visto. A acurácia ficou em 87,3%, a precisão em 89,1%, o recall em 55,4% e o F1 em 0,683.

Na matriz de confusão temos 221 entregas no prazo classificadas corretamente, 41 atrasos detectados, apenas 5 alarmes falsos e 33 atrasos que passaram despercebidos. A leitura honesta é essa: quando o modelo aponta atraso, ele quase sempre acerta, mas deixa escapar parte dos atrasos limítrofes, aqueles bem próximos dos 60 minutos.

À direita, o modelo aplicado a entregas novas. Cinco quilômetros com tempo bom, risco praticamente zero. Vinte quilômetros com chuva e no pico, 97,7%. É isso que muda a operação, porque com o risco calculado pedido a pedido dá para reforçar frota, reroteirizar ou avisar o cliente antes que o prazo estoure."

### Slide 11, Simulação de Monte Carlo (1 min)
"Por fim, voltamos aos números pseudoaleatórios, agora para simular decisões. São 20 mil sorteios de uma Normal para cada cenário, o que caracteriza a Simulação de Monte Carlo.

No cenário atual, 23,7% de risco. Com roteirização automática, reduzindo 6 minutos da média, cai para 13,6%. Padronizando a frota, o que reduz 25% do desvio, fica em 16,4%. Combinando as duas ações, 6,8%.

Duas leituras: neste caso reduzir a média pesou mais do que reduzir a variabilidade, e simular a decisão antes de aplicá-la evita testar hipóteses direto na operação real."

### Slide 12, Conclusão (1 min)
"Concluindo. A taxa geral de 22,5% de atrasos convivia com cenários de 64,7%, e foram a probabilidade condicional e o Teorema de Bayes que mostraram onde o risco se concentra. A Normal descreveu bem o tempo de entrega: com dois parâmetros estimamos o risco de SLA com erro de pouco mais de um ponto percentual e definimos um prazo realista de 75 minutos. Sobre esses dois conceitos construímos um classificador que atingiu 87,3% de acurácia usando só Bayes e a densidade normal. E o ganho é mensurável, com o risco caindo de 23,7% para 6,8% na simulação, o que se reflete em multas de SLA, retrabalho logístico e satisfação do cliente.

Como continuidade, o mesmo modelo poderia ser treinado com dados reais de telemetria e comparado com regressão logística e gradient boosting."

### Slide 13, Bibliografia (20 s)
"Estas são as referências que fundamentaram o trabalho, nas normas da ABNT. O código-fonte completo está no arquivo `codigo_cp4.py`, entregue junto com o PDF. Obrigado, ficamos à disposição para perguntas."

---

## Perguntas prováveis e respostas preparadas

| Pergunta | Resposta curta |
|---|---|
| Por que usar dados simulados? | Garantem reprodutibilidade pela semente fixa e permitem controlar os parâmetros. Como sabemos exatamente como os dados foram gerados, dá para verificar se o método recupera essa estrutura. |
| Por que o recall ficou baixo? | A classe atraso é minoritária, 21,6% da base, e o modelo é conservador. Para elevá-lo, baixaríamos o limiar de decisão de 0,50 para algo como 0,35, trocando alguns falsos positivos por mais atrasos detectados. |
| Por que o nome naive? | Porque assume independência entre as variáveis dada a classe. É uma simplificação irrealista, mas que funciona bem na prática e reduz muito o número de parâmetros a estimar. |
| A Normal serve para qualquer variável? | Não. Serve para variáveis contínuas e aproximadamente simétricas. Contagens pedem Poisson, eventos binários pedem Bernoulli, tempos de espera pedem exponencial. Por isso aplicamos o teste de Shapiro-Wilk antes. |
| Qual a diferença entre aleatório e pseudoaleatório? | O pseudoaleatório vem de um algoritmo determinístico com uma semente: é estatisticamente parecido com o acaso, mas reprodutível. Aleatoriedade verdadeira exige fonte física, como ruído térmico. |
| Por que a probabilidade teórica difere da empírica? | Por erro amostral, já que são mil observações. Com amostras maiores os dois valores convergem, que é o próprio Teorema Central do Limite. |

## Checklist de entrega no Microsoft Teams

- [x] `apresentacao_cp4.pdf`, parte escrita em PDF com 13 slides: capa, introdução, nove de desenvolvimento, conclusão e bibliografia
- [x] `codigo_cp4.py`, código-fonte em Python
- [ ] Postagem feita por um único representante do grupo, dentro do horário
- [ ] Conferir nome completo e RM de todos os integrantes na capa
