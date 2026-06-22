
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int PIN_POT = A0;
const int PIN_SERVO = 9;
const int FR_MIN = 8;
const int FR_MAX = 30;
const float PROP_INSP = 1.0f / 3.0f;
const int ANG_REPOSO = 30;
const int ANG_COMP = 120;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoAmbu;

enum Fase { INSPIRACAO, EXPIRACAO };
Fase fase = INSPIRACAO;
unsigned long inicioFase = 0;
unsigned long tInsp = 0, tExp = 0;
int fr = 12, frAnt = -1;

int lerFR() {
  int v = analogRead(PIN_POT);
  return constrain(map(v, 0, 1023, FR_MIN, FR_MAX), FR_MIN, FR_MAX);
}

void calcTempos(int frVal) {
  unsigned long T = 60000UL / frVal;
  tInsp = (unsigned long)(T * PROP_INSP);
  tExp = T - tInsp;
}

void showLCD(int frVal) {
  lcd.setCursor(0, 0);
  lcd.print("AMBU AUTOMATICO ");
  lcd.setCursor(0, 1);
  lcd.print("FR = ");
  if (frVal < 10) lcd.print(' ');
  lcd.print(frVal);
  lcd.print(" rpm    ");
}

void setup() {
  lcd.init();
  lcd.backlight();
  servoAmbu.attach(PIN_SERVO);
  servoAmbu.write(ANG_REPOSO);
  calcTempos(fr);
  inicioFase = millis();
  showLCD(fr);
}

void loop() {
  fr = lerFR();
  calcTempos(fr);
  if (fr != frAnt) { showLCD(fr); frAnt = fr; }

  unsigned long dt = millis() - inicioFase;
  if (fase == INSPIRACAO) {
    servoAmbu.write(ANG_COMP);
    if (dt >= tInsp) { fase = EXPIRACAO; inicioFase = millis(); }
  } else {
    servoAmbu.write(ANG_REPOSO);
    if (dt >= tExp) { fase = INSPIRACAO; inicioFase = millis(); }
  }
}
