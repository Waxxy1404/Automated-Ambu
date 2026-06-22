# Peças 3D — Referência e Impressão

> Peças listadas provêm de projetos open-source pesquisados. Baixe STLs dos repositórios originais. Este projeto acadêmico pode adaptar ou redesenhar peças simplificadas.

## Parâmetros de impressão sugeridos

| Parâmetro | Valor |
|-----------|-------|
| Material | PLA |
| Altura de camada | 0,2 mm |
| Preenchimento | 30% |
| Temperatura bico | 200 °C |
| Temperatura mesa | 60 °C |
| Perimetros | 3 |
| Suportes | Conforme orientação da peça |

---

## Projeto 1 — Open BVM Ventilator (whpthomas)

**Repositório:** https://github.com/whpthomas/open_bvm_ventilator  
**Thingiverse:** https://www.thingiverse.com/thing:4335859

| STL (pasta `3d/`) | Função |
|-------------------|--------|
| `bvm_clamp_base.stl` | Base de fixação do Ambu |
| `bvm_clamp_arm.stl` | Braço de compressão |
| `bvm_clamp_top.stl` | Tampa/superior da pinça |
| `manifold_*.stl` | Manifold de sensores (opcional) |
| Diversos suportes | ~25 peças totais |

**Motor:** NEMA 17 stepper + driver A4988/TB6560  
**Mecanismo:** Fusão de movimento rotativo→linear por fuso ou braço

---

## Projeto 2 — Automatic Resuscitator (joelfrax / Thingiverse)

**Link:** https://www.thingiverse.com/thing:4239988

| STL | Função |
|-----|--------|
| `lat1.stl`, `lat2.stl` | Laterais da estrutura |
| `Nema.stl` | Suporte motor NEMA 17 |
| `sop_bisagra.stl` | Suportes de dobradiça |
| `sop_respirador.stl` | Suporte do reanimador |
| `FV2-hinge.stl` | Dobradiça |
| `Endstop support.stl` | Suporte fim de curso |

**Motor:** NEMA 17  
**Mecanismo:** Fuso/ball screw; 15–16 rpm testados

---

## Projeto 3 — SimFeedback DIY RC Servo Ventilator

**Repositório:** https://github.com/SimFeedback/DIY-3DP-Ventilator---RC-Servo-/tree/master/STL

| STL | Função |
|-----|--------|
| Arquivos na pasta `STL/` | Estrutura para 2× servos RC |
| — | Compatível com Ambu SPUR II / MARK IV |

**Motor:** 2× servos RC alto torque (ex.: Turnigy S8166M 33 kg)  
**Mecanismo:** Braços opostos comprimindo o balão

---

## Projeto 4 — LRVent (makefastworkshop)

**Repositório:** https://github.com/makefastworkshop/LRVent

| Arquivo | Função |
|---------|--------|
| `CAD/` e STLs exportados | Estrutura modular parametrizável |
| Suportes de motor | Adaptáveis a NEMA ou BLDC |

**Motor:** Variável (NEMA, BLDC)  
**Mecanismo:** Alavanca / came configurável

---

## Projeto 5 — RepRapable BVM Ventilator (Michigan Tech)

**OSF:** https://osf.io/fjdwz  
**Publicação:** Pearce et al., 2020

| STL | Função |
|-----|--------|
| `Pressure_sensor_junction_box.stl` | Caixa de junção sensores |
| `breathing_system_*.stl` | Montagem sistema respiratório |
| `control_box_*.stl` | Caixa do controlador |
| Arquivos `.FCStd` | Modelos paramétricos FreeCAD |

**Motor:** Stepper + Arduino RTOS  
**Mecanismo:** Estrutura RepRap paramétrica

---

## Peças sugeridas para ESTE protótipo (servo único)

Para o escopo acadêmico com **1 servo + Arduino Uno**, recomenda-se imprimir:

| Peça (nome sugerido) | Função | Quantidade |
|----------------------|--------|------------|
| `base_placa.stl` | Placa base 200×150 mm | 1 |
| `suporte_servo.stl` | Fixação servo MG996R/DS3218 | 1 |
| `braco_alavanca.stl` | Braço 80–120 mm, ponta curva | 1 |
| `suporte_ambu.stl` | Cavidade para BVM + cinta | 1 |
| `dobradica_eixo.stl` | Eixo M3 para articulação | 2 |
| `tampa_protecao.stl` | Proteção lateral (opcional) | 1 |

> **Adaptação:** Use STLs do SimFeedback ou joelfrax como referência geométrica e simplifique para um único servo conforme diagrama mecânico do relatório técnico.

---

## Montagem mecânica (resumo)

```
[Servo] → [Braço alavanca] → [Platô compressor] → [Ambu BVM]
                ↑
         [Dobradiça + mola opcional de retorno]
```

1. Fixar servo na base com parafusos M3.
2. Acoplar braço ao eixo do servo (parafuso + contrapino).
3. Posicionar Ambu no suporte; platô do braço alinhado ao centro do balão.
4. Calibrar `ANGULO_REPOSO` e `ANGULO_COMPRESSAO` no firmware.
