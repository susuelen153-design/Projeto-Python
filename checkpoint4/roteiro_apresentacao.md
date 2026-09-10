# Roteiro de Apresentação, Checkpoint 4

**Tema:** Probabilidade e Distribuição Normal aplicadas à Inteligência Artificial
**Aplicação:** Logística, prever atrasos de entrega usando dados criados pelo próprio programa
**Duração:** 10 a 12 minutos. Todos precisam falar, é regra do enunciado.

| Integrante | RM | Slides |
|---|---|---|
| Giovanni Henrique Pereira Hessel | 570574 | 1, 2, 3 |
| Suellen Pereira da Silva | 573862 | 4, 5, 6 |
| Arthur Zeferino | 570858 | 7, 8, 9 |
| Israel Carneiro de Toledo | 573854 | 10, 11, 12, 13 |

---

## Antes de tudo: a ideia do trabalho em 3 frases

1. Uma transportadora promete entregar em até 60 minutos, mas chuva e trânsito atrapalham, então ninguém tem certeza se vai dar.
2. Quando não existe certeza, o jeito é calcular a **chance** de acontecer. Isso é probabilidade.
3. Um programa que aprende essas chances a partir do que já aconteceu antes consegue avisar, com antecedência, quais entregas correm risco de atrasar.

Se você entendeu essas 3 frases, você consegue apresentar o trabalho inteiro.

---

## GIOVANNI (slides 1 a 3)

### Slide 1, Capa
> "Boa noite. Nosso grupo escolheu dois temas: Probabilidade e Distribuição Normal. Para não ficar só na teoria, aplicamos os dois num problema de entregas: descobrir quais entregas correm risco de atrasar. Todos os dados foram criados pelo próprio programa, ninguém precisou de dados de empresa nenhuma."

### Slide 2, Introdução e Justificativa
> "O problema é o seguinte: a transportadora promete entregar em até 60 minutos. Só que chuva, trânsito e a distância mudam esse tempo. Ninguém consegue garantir se vai dar certo.
>
> Quando não dá para ter certeza, sobra calcular a chance. É por isso que probabilidade é a base de qualquer programa que faz previsão. Nenhum aplicativo diz 'vai chover'. Ele diz '70% de chance de chuva'. É a mesma ideia aqui.
>
> Essas cinco perguntas do quadro azul são o que a gente vai responder nos próximos slides."

**Se perguntarem o que é SLA:** é o prazo que a empresa promete ao cliente. Aqui, 60 minutos.

### Slide 3, As três fórmulas
> "Usamos três fórmulas no trabalho inteiro.
>
> A primeira é a **probabilidade** normal, que todo mundo já viu: casos que interessam dividido pelo total. Num dado, a chance de sair 6 é 1 em 6, uns 17%.
>
> A segunda é a **probabilidade condicional**. É a mesma coisa, só que quando você já sabe alguma informação. Continuando no dado: se alguém te contar que saiu número par, sobraram só 2, 4 e 6. A chance de ser 6 pulou de 1 em 6 para 1 em 3. A informação nova mudou a chance. No nosso trabalho, a informação nova é 'está chovendo'.
>
> A terceira é o **Teorema de Bayes**, que vira a pergunta do avesso. É o que o médico faz: ele vê a febre, que é o resultado, e calcula qual doença é a causa mais provável. Nós fazemos igual: vemos que a entrega atrasou e calculamos o que provavelmente causou isso.
>
> E isso está em coisas do dia a dia: o app que avisa se vai chover, o filtro de spam do e-mail, o banco avaliando empréstimo e a Netflix sugerindo o próximo vídeo."

---

## SUELLEN (slides 4 a 6)

### Slide 4, De onde vieram os dados
> "Os dados foram criados pelo próprio programa. E aqui tem uma coisa interessante: o computador não sorteia de verdade. Ele faz uma conta que parte de um número inicial, chamado semente, e devolve valores que parecem sorteados.
>
> É como um baralho embaralhado sempre da mesma maneira: parece aleatório, mas qualquer um consegue repetir e conferir. Como deixamos a semente fixa em 42, rodar o código hoje ou daqui a um mês dá exatamente o mesmo resultado. Isso é bom porque o professor pode rodar e conferir as nossas contas.
>
> São mil entregas, com distância, se choveu, se pegou horário de pico e o tempo que levou. A última coluna é o que a gente quer prever: vale 1 quando passou dos 60 minutos."

### Slide 5, O risco por cenário
> "Rodando o código, a média deu 22,5% de atraso. Só que essa média engana.
>
> Olhem o gráfico: dia bom e fora do pico, só 8% atrasam. Com chuva, 27%. Com chuva **e** horário de pico junto, 65%, quase dois em cada três pedidos.
>
> É a mesma diferença entre dizer 'a média de idade da sala é 25 anos' e olhar aluno por aluno. A média sozinha esconde o que importa. Foi a probabilidade condicional que mostrou isso."

### Slide 6, Teorema de Bayes
> "Aqui a gente usa Bayes para virar a pergunta.
>
> A pergunta normal é: está chovendo, qual a chance de atrasar? A resposta é 41%.
>
> Bayes faz o contrário: a entrega atrasou, qual a chance de ter chovido? Jogando os números na fórmula, dá 56%.
>
> E aí a gente conferiu: contamos na base quantas entregas atrasadas tinham chuva, e deu exatamente 56%. A conta bateu com a realidade, então a fórmula está certa."

---

## ARTHUR (slides 7 a 9)

### Slide 7, A curva Normal
> "Agora o segundo tema, a Distribuição Normal, que é aquela curva em formato de sino.
>
> Ela aparece em várias coisas do dia a dia: a altura das pessoas, as notas de uma prova. A maioria fica perto da média e pouca gente fica nos extremos. Pouca gente tem 1,50 m, pouca gente tem 2,00 m, quase todo mundo está no meio.
>
> Com o tempo de entrega acontece igual: a média é 48,9 minutos e as barrinhas do gráfico ficam agrupadas em volta dela. A linha vermelha é a curva Normal encaixada nos dados, e ela cola quase perfeitamente.
>
> A parte vermelha à direita da linha pontilhada é a resposta que a empresa quer: a chance de passar dos 60 minutos, 23,7%. E na base real deu 22,5%. Ou seja, a curva acertou.
>
> E dá para usar ao contrário também: se a empresa prometesse 75 minutos em vez de 60, cumpriria o prazo em 95% das entregas."

**Se perguntarem o que é o z:** é só uma forma de medir a distância até a média usando o desvio como régua. z = 0,717 quer dizer que 60 minutos está a menos de um desvio acima da média.

### Slide 8, Por que essa curva aparece tanto
> "Olhem os três gráficos. No primeiro, os dados são bem tortos, nada de sino. Mas quando a gente pega grupos de 5 e tira a média, o desenho já melhora. Com grupos de 50, virou o sino da Normal.
>
> Ou seja: mesmo quando os dados originais são bagunçados, as médias formam a curva Normal. É por isso que ela aparece em quase tudo, e é o que se chama Teorema Central do Limite.
>
> A tabela mostra que nossos dados seguem a regra: 68% ficam a um desvio da média, 95% a dois desvios. E o teste de Shapiro-Wilk confirmou que os dados combinam com a Normal."

### Slide 9, O modelo que prevê
> "Aqui os dois temas se juntam num programa que prevê o atraso.
>
> A ideia é simples: ele aprende como é cada grupo. Nas entregas que atrasaram, a distância média era 16 km, choveu em 61% delas. Nas que não atrasaram, a distância média era 11 km, choveu em 21%. Chegando uma entrega nova, ele compara com os dois grupos e vê com qual ela mais se parece.
>
> É o mesmo raciocínio de olhar uma fruta e dizer se é laranja ou limão pelo tamanho e pela cor: a gente compara com o que já viu antes.
>
> Quem decide qual grupo é mais provável é o Teorema de Bayes. Quem mede o quanto a distância combina com cada grupo é a curva Normal. E não usamos nenhuma biblioteca pronta, o programa é só essas duas fórmulas."

---

## ISRAEL (slides 10 a 13)

### Slide 10, Os resultados
> "Treinamos com 700 entregas e testamos em 300 que o programa nunca tinha visto, para ver se ele realmente aprendeu.
>
> Acertou 87,3% delas. E, das vezes que ele avisou 'essa vai atrasar', acertou 89%. Na tabela do meio: 221 entregas no prazo classificadas certo, 41 atrasos detectados e só 5 alarmes falsos. O ponto fraco são 33 atrasos que escaparam, aqueles que estouraram o prazo por pouco.
>
> À direita, o programa aplicado a entregas novas: 5 km em dia bom, risco praticamente zero. 20 km com chuva no horário de pico, 97,7%. É isso que muda a operação, porque a empresa fica sabendo antes do entregador sair."

### Slide 11, Testando mudanças no computador
> "Por último, usamos o computador para testar mudanças antes de aplicar de verdade. São 20 mil simulações para cada situação.
>
> Como está hoje: 23,7% de risco. Se a empresa melhorar as rotas e economizar 6 minutos: cai para 13,6%. Se padronizar a frota, deixando os tempos mais parecidos: 16,4%. Fazendo as duas coisas: 6,8%.
>
> A vantagem é essa: dá para saber o resultado no computador antes de gastar dinheiro mudando a operação de verdade."

### Slide 12, Conclusão
> "Resumindo o que aprendemos.
>
> A média escondia o risco: parecia 22,5%, mas em certos dias chegava a 64,7%.
>
> A curva Normal descreveu bem o tempo de entrega e calculou o risco quase igual ao que aconteceu de verdade.
>
> Com essas duas fórmulas, sem biblioteca nenhuma, montamos um programa que acerta 87% das previsões.
>
> E o ganho é concreto: o risco pode cair de 23,7% para 6,8%, o que significa menos multa por atraso e cliente mais satisfeito."

### Slide 13, Bibliografia
> "Essas são as referências que usamos, nas normas da ABNT. O código completo está no arquivo que entregamos junto com o PDF. Obrigado, e ficamos à disposição para perguntas."

---

## Perguntas que o professor pode fazer

| Pergunta | Resposta simples |
|---|---|
| Por que dados inventados e não reais? | Porque a semente fixa deixa qualquer pessoa rodar o código e chegar no mesmo resultado. E como fomos nós que definimos as regras dos dados, dá para conferir se o método realmente descobre essas regras. |
| O que é probabilidade condicional? | É a chance de algo acontecer quando você já tem uma informação. No dado: 1 em 6 de sair 6; mas sabendo que saiu par, vira 1 em 3. |
| O que é o Teorema de Bayes? | É calcular a causa a partir do resultado, como o médico que vê a febre e descobre a doença mais provável. |
| Por que o modelo deixou passar 33 atrasos? | Porque ele é conservador e a maior parte da base é de entregas no prazo. Dá para deixá-lo mais sensível baixando o limite de decisão, mas aí aumentam os alarmes falsos. |
| A curva Normal serve para tudo? | Não. Serve para coisas contínuas e equilibradas em volta da média, como altura e tempo. Por isso aplicamos um teste antes para confirmar. |
| Por que 23,7% na conta e 22,5% na base? | Diferença normal de amostra, porque são mil entregas. Com mais dados os dois números ficam iguais. |

## Antes de postar no Teams

- [x] `apresentacao_cp4.pdf`, a apresentação em PDF
- [x] `codigo_cp4.py`, o código em Python
- [ ] Só um integrante posta, dentro do horário
- [ ] Conferir nome completo e RM de todos na capa
