/*
 * ============================================================================
 * PROJETO: AMBU AUTOMATIZADO (PROTÓTIPO ACADÊMICO)
 * ============================================================================
 * AVISO: Este firmware é exclusivamente para fins educacionais e de
 * prototipagem. NÃO deve ser utilizado em pacientes reais ou ambientes
 * clínicos. Não substitui um ventilador mecânico certificado.
 * ============================================================================
 *
 * Hardware:
 *   - Arduino Uno
 *   - Servo motor de alto torque (sinal em D9)
 *   - Potenciômetro 10 kΩ (A0)
 *   - LCD 16x2 com módulo I2C (endereço 0x27)
 *
 * Bibliotecas necessárias (Arduino IDE > Gerenciador de Bibliotecas):
 *   - LiquidCrystal I2C (Frank de Brabander)
 *   - Servo (incluída no core Arduino)
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- Configuração de pinos ---
const int PIN_POTENCIOMETRO = A0;   // Entrada analógica do potenciômetro
const int PIN_SERVO         = 9;    // Sinal PWM do servo motor

// --- Limites de frequência respiratória (rpm = respirações por minuto) ---
const int FR_MIN = 8;               // Mínimo: 8 rpm  → ciclo de 7,5 s
const int FR_MAX = 30;              // Máximo: 30 rpm → ciclo de 2,0 s

// --- Relação inspiração:expiração simplificada (I:E = 1:2) ---
const float PROPORCAO_INSPIRACAO = 1.0f / 3.0f;  // 33% do ciclo = inspiração
const float PROPORCAO_EXPIRACAO  = 2.0f / 3.0f;  // 67% do ciclo = expiração

// --- Posições angulares do servo (graus) ---
const int ANGULO_REPOSO       = 30;   // Expiração: braço afastado do Ambu
const int ANGULO_COMPRESSAO   = 120;  // Inspiração: braço comprime o Ambu

// --- Endereço I2C padrão do módulo LCD (0x27 ou 0x3F) ---
const uint8_t ENDERECO_LCD = 0x27;

// --- Objetos globais ---
LiquidCrystal_I2C lcd(ENDERECO_LCD, 16, 2);  // LCD 16 colunas x 2 linhas
Servo servoAmbu;                              // Objeto de controle do servo

// --- Variáveis de estado do ciclo respiratório ---
enum FaseRespiratoria {
  FASE_INSPIRACAO,
  FASE_EXPIRACAO
};

FaseRespiratoria faseAtual       = FASE_INSPIRACAO;
unsigned long    inicioFaseMs    = 0;       // Timestamp de início da fase atual
unsigned long    duracaoInspMs   = 0;       // Duração da inspiração em ms
unsigned long    duracaoExpMs    = 0;       // Duração da expiração em ms
int              frAtual         = 12;      // Frequência respiratória atual (rpm)
int              frAnterior      = -1;      // FR anterior (para atualizar LCD)

// --- Protótipos das funções auxiliares ---
int  lerFrequenciaRespiratoria();
void calcularTemposCiclo(int fr, unsigned long &tInsp, unsigned long &tExp);
void atualizarDisplay(int fr);
void executarCicloRespiratorio();
void moverServoSuave(int anguloDestino, int passos, int atrasoMs);

// ============================================================================
// SETUP — Executado uma vez na inicialização
// ============================================================================
void setup() {
  // Inicializa comunicação serial para depuração (9600 baud)
  Serial.begin(9600);
  Serial.println(F("AMBU AUTOMATICO - Prototipo Academico"));
  Serial.println(F("NAO USAR EM PACIENTES REAIS"));

  // Inicializa barramento I2C e display LCD
  lcd.init();
  lcd.backlight();

  // Mensagem de boas-vindas no display (2 segundos)
  lcd.setCursor(0, 0);
  lcd.print("AMBU AUTOMATICO");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...    ");
  delay(2000);

  // Conecta o servo ao pino D9 e posiciona em repouso (expiração)
  servoAmbu.attach(PIN_SERVO);
  servoAmbu.write(ANGULO_REPOSO);

  // Calcula tempos iniciais com FR padrão de 12 rpm
  calcularTemposCiclo(frAtual, duracaoInspMs, duracaoExpMs);
  inicioFaseMs = millis();

  // Exibe FR inicial no display
  atualizarDisplay(frAtual);
}

// ============================================================================
// LOOP — Executado continuamente
// ============================================================================
void loop() {
  // 1. Lê potenciômetro e converte para FR (8–30 rpm)
  frAtual = lerFrequenciaRespiratoria();

  // 2. Recalcula tempos de inspiração/expiração se FR mudou
  calcularTemposCiclo(frAtual, duracaoInspMs, duracaoExpMs);

  // 3. Atualiza display somente quando FR muda (evita flicker)
  if (frAtual != frAnterior) {
    atualizarDisplay(frAtual);
    frAnterior = frAtual;

    // Log serial para acompanhamento durante testes
    Serial.print(F("FR = "));
    Serial.print(frAtual);
    Serial.print(F(" rpm | T_ciclo = "));
    Serial.print(60000UL / frAtual);
    Serial.print(F(" ms | T_insp = "));
    Serial.print(duracaoInspMs);
    Serial.print(F(" ms | T_exp = "));
    Serial.println(duracaoExpMs);
  }

  // 4. Executa máquina de estados do ciclo respiratório
  executarCicloRespiratorio();
}

// ============================================================================
// FUNÇÃO: lerFrequenciaRespiratoria
// Lê o potenciômetro (0–1023) e mapeia linearmente para 8–30 rpm.
// ============================================================================
int lerFrequenciaRespiratoria() {
  // Leitura analógica com média de 5 amostras para reduzir ruído
  long soma = 0;
  for (int i = 0; i < 5; i++) {
    soma += analogRead(PIN_POTENCIOMETRO);
    delay(2);
  }
  int leituraMedia = soma / 5;

  // Mapeia faixa ADC (0–1023) para FR clínica simplificada (8–30 rpm)
  int fr = map(leituraMedia, 0, 1023, FR_MIN, FR_MAX);

  // Garante limites mesmo com ruído nas extremidades
  fr = constrain(fr, FR_MIN, FR_MAX);
  return fr;
}

// ============================================================================
// FUNÇÃO: calcularTemposCiclo
// Converte FR (rpm) em tempos de inspiração e expiração.
//
// Matemática:
//   T_ciclo [s] = 60 / FR
//   T_insp  [s] = T_ciclo × (I / (I + E))   com I:E = 1:2 → T_insp = T/3
//   T_exp   [s] = T_ciclo × (E / (I + E))   com I:E = 1:2 → T_exp  = 2T/3
//
// Exemplos:
//   FR =  8 rpm → T = 7,5 s → T_insp = 2,5 s | T_exp = 5,0 s
//   FR = 10 rpm → T = 6,0 s → T_insp = 2,0 s | T_exp = 4,0 s
//   FR = 15 rpm → T = 4,0 s → T_insp = 1,33 s | T_exp = 2,67 s
//   FR = 20 rpm → T = 3,0 s → T_insp = 1,0 s | T_exp = 2,0 s
//   FR = 30 rpm → T = 2,0 s → T_insp = 0,67 s | T_exp = 1,33 s
// ============================================================================
void calcularTemposCiclo(int fr, unsigned long &tInsp, unsigned long &tExp) {
  // Período total do ciclo em milissegundos
  unsigned long periodoCicloMs = 60000UL / fr;

  // Divide o ciclo conforme relação I:E = 1:2
  tInsp = (unsigned long)(periodoCicloMs * PROPORCAO_INSPIRACAO);
  tExp  = (unsigned long)(periodoCicloMs * PROPORCAO_EXPIRACAO);
}

// ============================================================================
// FUNÇÃO: atualizarDisplay
// Exibe no LCD:
//   Linha 1: "AMBU AUTOMATICO"
//   Linha 2: "FR = XX rpm"
// ============================================================================
void atualizarDisplay(int fr) {
  lcd.setCursor(0, 0);
  lcd.print("AMBU AUTOMATICO ");

  lcd.setCursor(0, 1);
  lcd.print("FR = ");
  if (fr < 10) {
    lcd.print(' ');  // Alinha visualmente valores de 1 dígito
  }
  lcd.print(fr);
  lcd.print(" rpm    ");
}

// ============================================================================
// FUNÇÃO: executarCicloRespiratorio
// Máquina de estados não bloqueante que alterna inspiração/expiração.
// ============================================================================
void executarCicloRespiratorio() {
  unsigned long agora = millis();
  unsigned long tempoDecorrido = agora - inicioFaseMs;

  switch (faseAtual) {

    case FASE_INSPIRACAO:
      // Servo avança para comprimir o Ambu
      servoAmbu.write(ANGULO_COMPRESSAO);

      // Quando tempo de inspiração esgotou, muda para expiração
      if (tempoDecorrido >= duracaoInspMs) {
        faseAtual    = FASE_EXPIRACAO;
        inicioFaseMs = agora;
      }
      break;

    case FASE_EXPIRACAO:
      // Servo retorna à posição de repouso (balão reexpande)
      servoAmbu.write(ANGULO_REPOSO);

      // Quando tempo de expiração esgotou, reinicia ciclo
      if (tempoDecorrido >= duracaoExpMs) {
        faseAtual    = FASE_INSPIRACAO;
        inicioFaseMs = agora;
      }
      break;
  }
}

// ============================================================================
// FUNÇÃO: moverServoSuave (auxiliar opcional)
// Move o servo gradualmente entre posições para reduzir picos de corrente.
// Útil em protótipos com fonte compartilhada.
// ============================================================================
void moverServoSuave(int anguloDestino, int passos, int atrasoMs) {
  int anguloAtual = servoAmbu.read();
  int incremento  = (anguloDestino - anguloAtual) / passos;

  for (int i = 0; i < passos; i++) {
    anguloAtual += incremento;
    servoAmbu.write(anguloAtual);
    delay(atrasoMs);
  }
  servoAmbu.write(anguloDestino);
}
