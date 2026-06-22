# Lista de Materiais (BOM) — Ambu Automatizado

> **Aviso:** Protótipo acadêmico. Não certificado para uso clínico.

| Qtd | Componente | Especificação | Observação |
|-----|------------|---------------|------------|
| 1 | Arduino Uno | ATmega328P, 5 V | Microcontrolador principal |
| 1 | Servo motor | Alto torque, ≥ 20 kg·cm (MG996R mín.; ideal ≥ 40 kg·cm) | Sinal em D9; alimentação externa recomendada |
| 1 | Potenciômetro | 10 kΩ, linear, rotativo | Ajuste de FR (8–30 rpm) |
| 1 | LCD 16×2 | Com módulo I2C (PCF8574), endereço 0x27 ou 0x3F | SDA→A4, SCL→A5 |
| 1 | Fonte DC | 5–6 V, ≥ 3 A | Exclusiva para o servo (evita reset do Arduino) |
| 1 | Fonte USB / 5 V | ≥ 500 mA | Alimentação do Arduino |
| 1 | Protoboard | 400 ou 830 pontos | Montagem do circuito |
| — | Jumpers | Macho-macho | Ligações |
| 1 | Balão Ambu (BVM) | Adulto ou pediátrico (treino) | Apenas simulação / manequim |
| — | Peças 3D | PLA, ver `PECAS_3D.md` | Base, braço, suporte servo |
| — | Parafusos M3 | Com porcas | Fixação mecânica |
| — | Cabo USB tipo B | — | Programação Arduino |

## Consumo estimado de corrente

| Componente | Corrente típica | Corrente de pico |
|------------|-----------------|------------------|
| Arduino Uno | ~50 mA | ~100 mA |
| LCD I2C | ~20 mA | ~80 mA (backlight) |
| Servo em repouso | ~10 mA | — |
| Servo em movimento | 500 mA–2 A | até 3 A |

**Regra prática:** nunca alimentar o servo diretamente pelo regulador 5 V do Arduino.

## Custo estimado (referência 2024–2025)

| Item | Faixa (USD) |
|------|-------------|
| Arduino Uno clone | 8–15 |
| Servo alto torque | 15–35 |
| LCD I2C | 3–8 |
| Potenciômetro + protoboard | 3–5 |
| Fonte 5 V 3 A | 5–10 |
| Filamento PLA (~200 g) | 4–6 |
| **Total aproximado** | **40–80 USD** |
