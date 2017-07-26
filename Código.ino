// Frank, the living dead, made this code. 
// Chapecó, Brazil
// 2017


// Partes deste código foram produzidos através de exemplos dados por:
// Adafruit
// Intel
// Filipeflop
// Keyes

#include <DHT.h>
#include <DHT_U.h>                    
#include <LiquidCrystal.h>
#include "CurieIMU.h"
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 8
#define DHTTYPE DHT11  

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int state=LOW;
int lastState=LOW;
const int ledPin = 13;
boolean stepEventsEnabeled = true;
long lastStepCount = 0; // Último passo detectado
boolean blinkState = false;    
float comprimento_do_passo;
float calories = 0;
float peso = 57;
float altura = 168;
float calories_lost_per_km;
float calories_burned; 
float distance;
float passos_por_milha;
float velocidade;
char option;
float t;

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  comprimento_do_passo=0.30*altura; // Altura em centímetros
  calories_lost_per_km=(0.57*peso*1.6)/0.453; // Peso em kilogramas
  passos_por_milha = 160000.0/comprimento_do_passo; // 16000.0 CM = 16 KM

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Proj. Bem-estar");
  lcd.setCursor(0, 1);
  lcd.print("07/2017");
  delay(3000);
  
  // pinMode(13, OUTPUT);
  // Iniciar o sensor: 
  CurieIMU.begin();
  // Modo de detecção de passos:
  CurieIMU.setStepDetectionMode(CURIE_IMU_STEP_MODE_NORMAL);
  // Ativar contagem de passos:
  CurieIMU.setStepCountEnabled(true);

  if (stepEventsEnabeled) {
    // attach the eventCallback function as the
    // step event handler:
    CurieIMU.attachInterrupt(eventCallback);
    CurieIMU.interrupts(CURIE_IMU_STEP);  // Detecção de passos
  }

  
}

static void updateStepCount() {
  // get the step count:
  int stepCount = CurieIMU.getStepCount();

  // if the step count has changed, print it:
  if (stepCount != lastStepCount) {
    // save the current count for comparison next check:
    lastStepCount = stepCount;
  }
}

static void eventCallback(void) {
  if (CurieIMU.stepsDetected())
    updateStepCount();
}

void loop() {
  

  if (!stepEventsEnabeled) { // Detecção periódica
    updateStepCount();
  }
  
//__________________________________//

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Passos: ");
  lcd.setCursor(0, 1);
  lcd.print(lastStepCount);
  delay(4000);

//__________________________________//

calories_burned = lastStepCount*(lastStepCount/passos_por_milha);

if (option=='c') {  
  
}

 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Calorias Q.: "); 
 lcd.setCursor(0, 1);
 lcd.print(calories_burned); 
 lcd.print(" Kcal");
 delay(4000);

//__________________________________//

distance = (comprimento_do_passo*lastStepCount)/100; // Distância em metros.

if (option=='d') {
  
}

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Distancia P.: ");
lcd.setCursor(0, 1);
lcd.print(distance);
lcd.print(" Metros");
delay(4000);

//__________________________________//
// CONEXÃO NO PINO 8

  delay(delayMS);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    //Serial.println("Erro - Temp");
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print(event.temperature);
    lcd.print(" C*");
    delay(3000);
  }
  
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    //Serial.println("Erro - Humi");
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidade: ");
    lcd.setCursor(0, 1);
    lcd.print(event.relative_humidity);
    lcd.print("%");
    delay(3000);
  }
  
//__________________________________//

  lastState=state;
  digitalWrite(13, blinkState);
  blinkState = !blinkState;
  delay(300);
  
}
