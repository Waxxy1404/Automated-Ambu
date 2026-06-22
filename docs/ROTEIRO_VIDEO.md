# Roteiro do Vídeo — Ambu Automatizado (Protótipo Acadêmico)

**Duração total sugerida:** 8–12 minutos  
**Público:** Professores, colegas de curso, comunidade maker  
**Aviso legal (obrigatório no início e fim):** Este dispositivo é exclusivamente educacional e não substitui equipamento médico certificado.

---

## Introdução (0:00 – 1:30)

**Visual:** Título + imagem de Ambu manual + protótipo montado.

**Narração:**
> "Olá! Neste vídeo apresentamos o projeto Ambu Automatizado, desenvolvido como protótipo acadêmico de sistemas embarcados aplicados à engenharia biomédica. O objetivo é demonstrar como um reanimador manual tipo Ambu pode receber uma etapa de automação usando Arduino, servo motor e peças impressas em 3D — **sem qualquer finalidade clínica ou uso em pacientes reais**."

**Pontos-chave:**
- Contexto: ventilação manual vs. automatizada
- Componentes principais do projeto
- Aviso de segurança

---

## Parte 1 — Modelos 3D encontrados (1:30 – 3:30)

**Visual:** Slides ou capturas de tela dos repositórios (Open BVM, joelfrax, SimFeedback, LRVent, Michigan Tech).

**Narração:**
> "Na etapa de pesquisa, analisamos projetos open-source como o Open BVM Ventilator, o Automatic Resuscitator do Thingiverse, o SimFeedback com servos RC, o LRVent e o ventilador RepRapable da Michigan Tech. Cada um utiliza mecanismos diferentes: fusos NEMA 17, braços articulados ou servos de alto torque."

**Demonstrar:**
- Imagens dos conjuntos montados (GitHub/Thingiverse)
- Comparação: stepper vs. servo vs. rack-and-pinion
- Peças STL selecionadas para inspiração do nosso protótipo

---

## Parte 2 — Montagem eletrônica (3:30 – 5:30)

**Visual:** Protoboard, Arduino, fiação passo a passo.

**Narração:**
> "O circuito utiliza Arduino Uno, potenciômetro de 10 kΩ na entrada A0, LCD 16×2 com I2C nos pinos A4 e A5, e servo de alto torque no pino D9. A alimentação do servo é feita por fonte externa de 5 volts e 3 amperes, com GND comum ao Arduino."

**Demonstrar:**
- Conexão do potenciômetro (5V, GND, A0)
- Conexão I2C do LCD
- Servo no D9 + fonte externa
- Esquemático na tela (figura do relatório)

---

## Parte 3 — Simulação (5:30 – 7:00)

**Visual:** Tela do Wokwi ou Tinkercad em execução.

**Narração:**
> "Antes da montagem física, validamos o firmware no simulador Wokwi. O potenciômetro virtual ajusta a frequência respiratória de 8 a 30 rpm, o display mostra o valor em tempo real, e o servo simula o movimento de compressão do balão."

**Demonstrar:**
- Start simulation
- Variação do potenciômetro
- LCD atualizando
- Servo oscilando

---

## Parte 4 — Demonstração do potenciômetro e FR (7:00 – 9:30)

**Visual:** Protótipo físico completo (eletrônica + mecânica + Ambu de treino).

**Narração:**
> "Com o protótipo montado, giramos o potenciômetro e observamos a mudança da frequência respiratória no display. A 8 rpm, cada ciclo dura 7,5 segundos; a 30 rpm, 2 segundos. O braço mecânico comprime o Ambu na inspiração e retorna na expiração, com relação I:E simplificada de 1 para 2."

**Demonstrar:**
- FR = 8 rpm (movimento lento, cronômetro)
- FR = 20 rpm (intermediário)
- FR = 30 rpm (rápido)
- Serial Monitor com tempos calculados (opcional)

---

## Parte 5 — Conclusão (9:30 – 11:00)

**Visual:** Protótipo + lista de aprendizados + referências.

**Narração:**
> "Concluímos que é possível automatizar pedagogicamente um Ambu com baixo custo e componentes acessíveis. As limitações incluem ausência de sensores de pressão, alarmes clínicos e certificação regulatória. Este trabalho contribui para o aprendizado de embarcados, mecatrônica e engenharia biomédica — **nunca substituindo equipamentos hospitalares certificados**. Agradecemos a audiência e disponibilizamos código, esquemático e documentação nos links abaixo."

**Pontos finais:**
- Aprendizados técnicos
- Limitações do protótipo
- Trabalhos futuros (sensor de pressão, interface serial, peça 3D customizada)
- Referências open-source

---

## Checklist de gravação

- [ ] Aviso legal no início e fim
- [ ] Áudio claro (microfone externo se possível)
- [ ] Close nos componentes e no display
- [ ] Legenda com valores de FR durante demo
- [ ] Créditos aos projetos open-source citados
- [ ] Links na descrição do vídeo (GitHub, Wokwi, relatório)

## Sugestão de título

**"Ambu Automatizado com Arduino — Protótipo Acadêmico (NÃO USAR CLINICAMENTE)"**
