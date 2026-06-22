# Simulação no Tinkercad — Ambu Automatizado

> Protótipo acadêmico. Circuito virtual equivalente ao hardware real.

## Pré-requisitos

- Conta gratuita em [Tinkercad](https://www.tinkercad.com/)
- Código `firmware/ambu_automatico.ino` (adaptar endereço LCD se necessário)

---

## Passo 1 — Inserir componentes

1. Acesse **Tinkercad → Circuits → Create new Circuit**.
2. Adicione os componentes pela barra de busca:

| Componente Tinkercad | Quantidade |
|---------------------|------------|
| Arduino Uno R3 | 1 |
| Potentiometer | 1 |
| LCD 16×2 (I2C) * | 1 |
| Micro Servo | 1 |
| Breadboard (opcional) | 1 |

\* Se o LCD I2C não estiver disponível na sua região, use **LCD 16×2** padrão com conexão paralela e adapte o código, ou use **Wokwi** (recomendado para I2C).

---

## Passo 2 — Ligações

### Potenciômetro

| Pino pot | Arduino |
|----------|---------|
| Lado esquerdo | 5V |
| Pino central (wiper) | A0 |
| Lado direito | GND |

### LCD I2C (quando disponível)

| Pino LCD | Arduino |
|----------|---------|
| VCC | 5V |
| GND | GND |
| SDA | A4 (SDA) |
| SCL | A5 (SCL) |

### Servo

| Fio servo | Arduino |
|-----------|---------|
| Sinal (laranja) | D9 |
| VCC (vermelho) | 5V |
| GND (marrom) | GND |

> **Nota Tinkercad:** A simulação alimenta o servo pelo 5V do Arduino. Em hardware real, use fonte externa.

---

## Passo 3 — Upload do código

1. Clique no Arduino → aba **Code**.
2. Selecione **Text** (não Blocks).
3. Cole o conteúdo de `firmware/ambu_automatico.ino`.
4. Instale bibliotecas equivalentes se o Tinkercad solicitar:
   - `LiquidCrystal I2C`
   - `Servo` (já incluída)

---

## Passo 4 — Executar simulação

1. Clique **Start Simulation** (botão Play).
2. Observe:
   - LCD linha 1: `AMBU AUTOMATICO`
   - LCD linha 2: `FR = XX rpm`
   - Servo alternando entre posição baixa (repouso) e alta (compressão).

---

## Passo 5 — Testes variando a FR

| Teste | Ação | Resultado esperado |
|-------|------|-------------------|
| FR mínima | Gire potenciômetro para 0% | FR = 8 rpm; ciclo ~7,5 s; servo lento |
| FR média | Potenciômetro ~50% | FR ≈ 19 rpm; ciclo ~3,2 s |
| FR máxima | Potenciômetro 100% | FR = 30 rpm; ciclo 2 s; servo rápido |
| Transição | Gire lentamente | Display atualiza; período do servo muda |

### Verificação com Serial Monitor (Tinkercad)

Ative **Serial Monitor** e confira mensagens:
```
FR = 15 rpm | T_ciclo = 4000 ms | T_insp = 1333 ms | T_exp = 2667 ms
```

---

## Limitações da simulação Tinkercad

- Servo simulado não representa carga mecânica real do Ambu.
- LCD I2C pode não estar disponível em todas as versões.
- Para simulação I2C completa, prefira **Wokwi** (`wokwi/diagram.json`).
