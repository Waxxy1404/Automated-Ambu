# Ambu Automatizado — Protótipo Acadêmico

Automatização educacional de reanimador manual tipo Ambu (BVM) com **Arduino Uno**, **servo de alto torque**, **potenciômetro**, **LCD I2C** e **peças 3D**.

> **AVISO:** Protótipo exclusivamente educacional. **Não usar em pacientes reais.** Não substitui ventilador certificado.

---

## Estrutura do repositório

```
ambu-automatizado/
├── firmware/
│   └── ambu_automatico.ino      # Código Arduino completo e comentado
├── wokwi/
│   ├── diagram.json               # Simulação Wokwi — diagrama
│   └── sketch.ino                 # Firmware para Wokwi
├── schematic/
│   └── ESQUEMA_CIRCUITO.md        # Esquemático e ligações
├── docs/
│   ├── RELATORIO_TECNICO.md       # Relatório completo (9 etapas)
│   ├── BOM.md                     # Lista de materiais
│   ├── PECAS_3D.md                # STLs e parâmetros de impressão
│   ├── SIMULACAO_TINKERCAD.md     # Guia Tinkercad
│   ├── SIMULACAO_WOKWI.md         # Guia Wokwi
│   ├── TESTES.md                  # Protocolo de testes
│   └── ROTEIRO_VIDEO.md           # Roteiro do vídeo
└── referencias/
    └── REFERENCIAS.md             # Bibliografia e links
```

---

## Início rápido

### 1. Hardware
Monte o circuito conforme [`schematic/ESQUEMA_CIRCUITO.md`](schematic/ESQUEMA_CIRCUITO.md).

### 2. Firmware
1. Abra `firmware/ambu_automatico.ino` no Arduino IDE.
2. Instale bibliotecas: **LiquidCrystal I2C**, **Servo**.
3. Ajuste `ENDERECO_LCD` (0x27 ou 0x3F) se necessário.
4. Faça upload para o Arduino Uno.

### 3. Simulação (Wokwi)
1. Importe `wokwi/diagram.json` e `wokwi/sketch.ino` em [wokwi.com](https://wokwi.com).
2. Inicie a simulação e gire o potenciômetro virtual.

---

## Especificações

| Parâmetro | Valor |
|-----------|-------|
| FR ajustável | 8 – 30 rpm |
| Relação I:E | 1:2 (simplificada) |
| Display | `AMBU AUTOMATICO` / `FR = XX rpm` |
| Servo | D9 — 30° (repouso) ↔ 120° (compressão) |
| Potenciômetro | A0 — 10 kΩ |

---

## Documentação principal

- **Relatório técnico completo:** [`docs/RELATORIO_TECNICO.md`](docs/RELATORIO_TECNICO.md)
- **Testes:** [`docs/TESTES.md`](docs/TESTES.md)
- **Vídeo:** [`docs/ROTEIRO_VIDEO.md`](docs/ROTEIRO_VIDEO.md)

---

## Licença e uso

Projeto acadêmico. Referências open-source citadas em [`referencias/REFERENCIAS.md`](referencias/REFERENCIAS.md). Uso livre para fins educacionais, com atribuição aos projetos originais quando aplicável.

**Não possui certificação médica.**
