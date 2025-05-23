#include <LiquidCrystal.h>

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000
int count = 0;
int value;
PulseOximeter pox;
uint32_t tsLastReport = 0;

int g;
float t;
void onBeatDetected()
{
  //Serial.println("Beat!");
}
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//LiquidCrystal lcd(D7,D6,D5,D4,D3,D0);
int H, S;

#include <DHT.h>
DHT dht(2, DHT11);


#define TouchPin1 4
#define TouchPin2 5

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();

  pinMode(TouchPin1, INPUT);
  pinMode(TouchPin2, INPUT);
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  

  lcd.setCursor(0, 0);
  lcd.print("     Health     ");
  lcd.setCursor(0, 1);
  lcd.print("   Monitoring   ");
  delay(2000);
  lcd.clear();
  //Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    //Serial.println("FAILED");
    for (;;);
  }
  else
  {
    //Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
float t = dht.readTemperature();    // Use float to preserve precision
float Q=((t * 9.0) / 5.0 + 32.0);
//float Q = (t * 1.8) + 32.0;         // Celsius to Fahrenheit conversion

//(32°C × 9/5) + 32 = 89.6°F
  
  lcd.setCursor(0,1);
  lcd.print("T");
  lcd.print(Q);
  lcd.print(char(223));
  lcd.print("F");
  Serial.print('T');
  Serial.print(Q);
  delay(5);

  if (t > 98) {
    lcd.setCursor(9,1);
    lcd.print("H");
   // Serial.print('C');
    digitalWrite (7,HIGH);
  } else {
    lcd.setCursor(9,1);
    lcd.print("L");
    digitalWrite (7,LOW);
   // Serial.print('c');
  }

  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {
    S = (pox.getSpO2());
    H = (pox.getHeartRate());
    tsLastReport = millis();
  }

  digitalWrite(4, LOW);
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.setCursor(2, 0);
  lcd.print(H);
  lcd.print("  ");
  Serial.print('H');
  Serial.print(H);
  delay(5);
  
  
  lcd.setCursor(5, 0);
  lcd.print("B:");
  lcd.setCursor(7, 0);
  lcd.print(S);
  lcd.print("  ");
  Serial.print('S');
  Serial.print(S);
  delay(5);

  int Touch1 = digitalRead(TouchPin1);

  if (Touch1 == HIGH) {
    lcd.setCursor(11, 1);
    lcd.print("B1ON ");
    Serial.print('B');
  } else {
    lcd.setCursor(11, 1);
    lcd.print("B1OFF");
    Serial.print('b');
  }

  int Touch2 = digitalRead(TouchPin2);

  if (Touch2 == HIGH) {
    lcd.setCursor(11, 0);
    lcd.print("B2ON ");
    Serial.print('D');
  } else {
    lcd.setCursor(11, 0);
    lcd.print("B2OFF");
    Serial.print('d');
  }
  
}
