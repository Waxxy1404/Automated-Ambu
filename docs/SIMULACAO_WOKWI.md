# Simulação no Wokwi — Ambu Automatizado

## Arquivos do projeto

| Arquivo | Descrição |
|---------|-----------|
| `wokwi/diagram.json` | Diagrama de componentes e fiação |
| `wokwi/sketch.ino` | Firmware para simulação |
| `firmware/ambu_automatico.ino` | Firmware completo com comentários |

---

## Instruções de execução

### Opção A — Importar no editor Wokwi

1. Acesse [https://wokwi.com](https://wokwi.com) e faça login.
2. Clique **New Project → Import**.
3. Faça upload de `diagram.json` e `sketch.ino`, ou copie o conteúdo manualmente.
4. No painel de bibliotecas, adicione:
   - `LiquidCrystal I2C` (autor: Frank de Brabander)
5. Clique **Start Simulation** (F1).

### Opção B — VS Code + extensão Wokwi

1. Instale a extensão **Wokwi for VS Code**.
2. Abra a pasta `ambu-automatizado/wokwi/`.
3. Pressione **F1 → Wokwi: Start Simulator**.

---

## Componentes no diagram.json

```json
{
  "parts": [
    "wokwi-arduino-uno",
    "wokwi-potentiometer (10k)",
    "wokwi-lcd1602 (I2C)",
    "wokwi-servo"
  ]
}
```

## Conexões (diagram.json)

| De | Para |
|----|------|
| Pot SIG | Arduino A0 |
| Pot VCC/GND | 5V / GND |
| LCD SDA/SCL | A4 / A5 |
| LCD VCC/GND | 5V / GND |
| Servo SIG | D9 |
| Servo V+/GND | 5V / GND |

---

## Testes na simulação

1. **Potenciômetro:** clique e arraste o cursor; observe mudança de FR no LCD.
2. **Servo:** visualize oscilação entre ~30° (repouso) e ~120° (compressão).
3. **Sincronização:** em FR=8, um ciclo completo leva ~7,5 s; em FR=30, ~2 s.

---

## diagram.json (referência)

O arquivo completo está em `wokwi/diagram.json`. Estrutura principal:

- `version`: 1
- `parts`: Arduino Uno, potenciômetro, LCD I2C, servo, VCC, GND
- `connections`: fiação conforme esquemático do projeto

## Código principal

Use `wokwi/sketch.ino` para simulação rápida ou `firmware/ambu_automatico.ino` para versão documentada completa.

### Dependências Wokwi (wokwi.toml opcional)

Crie `wokwi.toml` na pasta wokwi se usar CLI:

```toml
[wokwi]
version = 1
firmware = 'sketch.ino'
elf = '.pio/build/uno/firmware.elf'
```

Para simulação direta no site, apenas `diagram.json` + `sketch.ino` são suficientes.
