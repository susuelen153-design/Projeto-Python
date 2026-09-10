# Roteiro simples: explicando a apresentação para quem nunca viu estatística

Este roteiro usa linguagem de ensino médio. Serve para você entender primeiro e depois explicar para qualquer pessoa.

---

## A ideia do trabalho em 30 segundos

Uma transportadora promete entregar em até 60 minutos. Chuva e trânsito atrapalham, então ninguém sabe se vai dar certo.

Quando não dá para ter certeza, a gente calcula a **chance**. É como a previsão do tempo: ninguém diz "vai chover", diz "70% de chance de chuva".

Nós criamos mil entregas no computador, descobrimos o que aumenta a chance de atrasar e depois montamos um programa que olha uma entrega nova e diz: "essa aqui tem 70% de chance de atrasar".

Só isso. O resto da apresentação é mostrar como chegamos nesses números.

---

## Slide por slide

### Slide 1: Capa
Nome do trabalho, matéria e quem fez.

### Slide 2: Introdução
Aqui a gente conta o problema: entrega com prazo de 60 minutos e um monte de coisa que pode atrasar. E explica por que estatística resolve isso.

**Como falar:** "Escolhemos um problema de entregas porque todo mundo já esperou um pedido atrasar."

### Slide 3: As três fórmulas
As três contas que usamos no trabalho todo.

| Fórmula | O que é | Exemplo do dia a dia |
|---|---|---|
| Probabilidade | A chance de algo acontecer | Num dado, chance de sair 6 é 1 em 6 |
| Probabilidade condicional | A chance quando você já sabe alguma coisa | Se alguém disse que saiu par, sobrou 2, 4 e 6, então a chance de ser 6 virou 1 em 3 |
| Teorema de Bayes | Descobrir a causa a partir do resultado | O médico vê a febre e descobre qual doença é mais provável |

**Como falar:** "A informação nova muda a conta. É por isso que saber se está chovendo muda a chance da entrega atrasar."

### Slide 4: De onde vieram os dados
Explicamos que o computador não sorteia de verdade. Ele faz uma conta que começa num número, chamado semente, e os resultados parecem sorteados.

**Como falar:** "É como um baralho embaralhado sempre do mesmo jeito. Parece bagunçado, mas qualquer um pode repetir e conferir se a gente não inventou os números."

### Slide 5: O risco em cada situação
Um gráfico de barras mostrando a chance de atraso em cada situação.

- Dia bom, fora do pico: **8%**
- Só horário de pico: **24%**
- Só chuva: **27%**
- Chuva e pico juntos: **65%**

**Como falar:** "Na média, 22% atrasam. Mas a média engana, igual dizer que a média da sala é 7 quando tem gente com 3 e gente com 10. Olhando situação por situação, o risco pula de 8% para 65%."

### Slide 6: Teorema de Bayes
Aqui viramos a pergunta ao contrário.

- Pergunta comum: está chovendo, qual a chance de atrasar? **41%**
- Pergunta invertida: a entrega atrasou, qual a chance de ter chovido? **56%**

**Como falar:** "A gente fez a conta e deu 56%. Depois fomos contar na base de dados quantas entregas atrasadas tinham chuva, e deu 56% também. A fórmula bateu com a realidade."

### Slide 7: A curva Normal
Aquele gráfico em formato de sino.

**Como falar:** "A altura das pessoas funciona assim: quase todo mundo fica perto da média, pouca gente tem 1,50 m e pouca gente tem 2,00 m. O tempo de entrega é igual: a média é 49 minutos e a maioria fica em volta disso. Sabendo a média e o quanto os valores se espalham, a gente calcula qualquer chance de prazo."

O número principal aqui: a chance de passar dos 60 minutos é **23,7%**, e na prática deu 22,5%. Quase igual.

### Slide 8: Por que essa curva aparece tanto
Três gráficos lado a lado. No primeiro os dados são tortos. Depois a gente tira médias de grupos, e o desenho vai virando o sino.

**Como falar:** "Mesmo quando os dados são bagunçados, as médias formam essa curva. É por isso que ela aparece em quase tudo na estatística."

### Slide 9: O programa que prevê
O modelo que fizemos, sem usar nenhuma biblioteca pronta.

**Como falar:** "É o mesmo raciocínio de olhar uma fruta e dizer se é laranja ou limão pelo tamanho e pela cor. O programa aprendeu como são as entregas que atrasam e como são as que não atrasam. Aí chega uma entrega nova e ele vê com qual grupo ela se parece mais."

### Slide 10: Os resultados
O programa acertou **87 de cada 100** entregas que ele nunca tinha visto.

E na tabela: entrega curta em dia bom, risco quase zero. Entrega longa com chuva no pico, 97,7%.

**Como falar:** "Isso muda a operação, porque a empresa fica sabendo do problema antes do entregador sair, não depois do cliente reclamar."

### Slide 11: Testando mudanças no computador
Simulamos o que aconteceria se a empresa mudasse alguma coisa.

- Como está hoje: 23,7% de risco
- Melhorando as rotas: 13,6%
- Padronizando os veículos: 16,4%
- Fazendo as duas coisas: **6,8%**

**Como falar:** "Dá para testar a mudança no computador antes de gastar dinheiro mudando de verdade."

### Slide 12: Conclusão
O resumo: a média escondia o risco, a curva Normal descreveu bem o tempo, o programa acertou 87% e o risco pode cair de 23,7% para 6,8%.

### Slide 13: Bibliografia
Os livros e sites que usamos.

---

## Palavras difíceis, traduzidas

| Palavra que aparece | O que significa na prática |
|---|---|
| SLA | O prazo que a empresa promete. Aqui, 60 minutos |
| Média | Soma tudo e divide pela quantidade |
| Desvio padrão | O quanto os valores se espalham em volta da média. Pequeno significa parecidos, grande significa bagunçados |
| Distribuição | O desenho que os dados formam quando você os organiza num gráfico |
| Distribuição Normal | O desenho em formato de sino, com a maioria no meio |
| Pseudoaleatório | Parece sorteado, mas veio de uma conta, então dá para repetir igual |
| Semente (seed) | O número onde essa conta começa. Mudou a semente, mudam os sorteios |
| Bernoulli | Distribuição de coisas que só têm duas respostas: choveu ou não choveu |
| Monte Carlo | Repetir a simulação milhares de vezes para ver o que acontece na média |
| Acurácia | De cada 100 previsões, quantas o programa acertou |
| Modelo | O programa que aprendeu com os dados e faz a previsão |

---

## Se travar na hora, use estas frases

- "Probabilidade é medir a chance de algo acontecer quando não dá para ter certeza."
- "A informação nova muda a chance. Saber que está chovendo muda tudo."
- "A curva Normal é o formato de sino: a maioria fica perto da média."
- "Nosso programa não chuta, ele responde em porcentagem."
- "A gente testou no computador antes de sugerir mudança na empresa."

## As três coisas que ninguém pode esquecer

1. **22,5%** das entregas atrasam na média, mas com chuva e pico chega a **64,7%**
2. O programa acerta **87,3%** das previsões
3. Com as duas mudanças simuladas, o risco cai de **23,7% para 6,8%**
