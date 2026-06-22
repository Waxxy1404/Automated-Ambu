# Testes de Funcionamento — Ambu Automatizado

> Protótipo acadêmico. Testes em manequim ou simulador — nunca em pacientes.

---

## Teste 1 — Mudança da frequência pelo potenciômetro

**Objetivo:** Verificar mapeamento correto da leitura analógica para FR (8–30 rpm).

| Passo | Ação | Resultado esperado |
|-------|------|-------------------|
| 1 | Energizar circuito | Sistema inicia; LCD exibe FR inicial |
| 2 | Potenciômetro no mínimo (sentido horário ou anti-horário conforme ligação) | FR = 8 rpm no display |
| 3 | Potenciômetro no máximo | FR = 30 rpm |
| 4 | Posição intermediária (~50%) | FR ≈ 19 rpm (±2) |
| 5 | Girar lentamente de min a max | FR aumenta monotonicamente, sem saltos |

**Critério de aprovação:** FR sempre dentro de [8, 30]; resposta suave ao giro do potenciômetro.

---

## Teste 2 — Atualização do display

**Objetivo:** Confirmar formatação e refresh do LCD I2C.

| Passo | Ação | Resultado esperado |
|-------|------|-------------------|
| 1 | Observar linha 1 | Texto fixo: `AMBU AUTOMATICO` |
| 2 | Observar linha 2 | Formato: `FR = XX rpm` (XX com 1–2 dígitos) |
| 3 | Alterar FR | Linha 2 atualiza em < 1 s após mudança |
| 4 | Backlight | Display legível com iluminação ativa |

**Critério de aprovação:** Sem caracteres corrompidos; endereço I2C correto (0x27 ou 0x3F).

---

## Teste 3 — Resposta do servo

**Objetivo:** Validar movimento de compressão e retorno.

| Passo | Ação | Resultado esperado |
|-------|------|-------------------|
| 1 | FR = 8 rpm | Servo move para ~120° (compressão), retorna ~30° (repouso) |
| 2 | FR = 30 rpm | Mesma amplitude angular, ciclo mais rápido |
| 3 | Observar transições | Sem travamento; retorno completo à posição de repouso |
| 4 | Medir corrente (multímetro) | Picos < 3 A com fonte adequada |

**Critério de aprovação:** Amplitude consistente; sem aquecimento excessivo do servo em 10 min de operação.

---

## Teste 4 — Sincronização FR × movimento mecânico

**Objetivo:** Confirmar que o período do ciclo corresponde à fórmula T = 60/FR.

| FR (rpm) | T_ciclo esperado | T_insp (1:2) | T_exp (1:2) | Verificação |
|----------|------------------|--------------|-------------|-------------|
| 8 | 7,5 s | 2,5 s | 5,0 s | Cronômetro no ciclo completo |
| 10 | 6,0 s | 2,0 s | 4,0 s | Idem |
| 15 | 4,0 s | 1,33 s | 2,67 s | Idem |
| 20 | 3,0 s | 1,0 s | 2,0 s | Idem |
| 30 | 2,0 s | 0,67 s | 1,33 s | Idem |

**Procedimento:**
1. Configure FR desejada no potenciômetro.
2. Use cronômetro do celular: conte 5 ciclos completos.
3. Divida tempo total por 5 → T_ciclo medido.
4. Compare com T_ciclo esperado (tolerância ±10%).

**Critério de aprovação:** Erro de timing ≤ 10% em todas as faixas testadas.

---

## Teste 5 — Estabilidade prolongada (opcional)

| Duração | FR | Resultado esperado |
|---------|-----|-------------------|
| 30 min | 12 rpm | Sem reset do Arduino; servo operacional |
| 30 min | 30 rpm | Fonte estável; sem queda de tensão |

---

## Registro de resultados (modelo)

| Data | Teste | FR | T_medido | Pass/Fail | Observações |
|------|-------|-----|----------|-----------|-------------|
| ____ | 1 | 8 | — | | |
| ____ | 4 | 15 | 4,1 s | | |
| ____ | 3 | 30 | — | | |
