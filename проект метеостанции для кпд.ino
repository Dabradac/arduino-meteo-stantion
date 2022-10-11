#include <GyverBME280.h>
GyverBME280 bme;
#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
#include "cgAnem.h"
CG_Anem cgAnem(ANEM_I2C_ADDR);
float firmWareVer;

void setup() {

  //Serial.begin(9600); // запуск порта
  //Serial.println("Start"); // инициализация датчика
  lcd.begin(16, 2); // поменять если дисплей не 16х2
  cgAnem.init()     // инициализация анемоментра
  bme.begin(0x76)   // инициализация датчика температуры
  // запуск датчика и проверка на работоспособность
  //if (!bme.begin(0x76)) Serial.println("Error!"); //если порты а4 а5
}
// доделать конвертацию serial в string или float а зачем сложить по формуле twc = 13.12 + 0.6215*ta - 11.37*v100.16 + 0.3965*ta*v100.16

void loop() {
  // температура
  lcd.print("Temperature: " + string(bme.readTemperature()) + " C");
  // влажность
  lcd.print("Humidity: " + string(bme.readHumidity()) + "//");
  // давление
  lcd.print("Pressure: " + string(bme.readPressure()) + "Pa");
  //скорость ветра
  lcd.println("Air flow rate: " + String(cgAnem.airflowRate) + " m/s");
  // температура воздуха
  lcd.println("Current temperature: " + String(cgAnem.temperature) + " C");
  // хз, тож чет с воздухом
  lcd.println("Air flow consumption:" + String(cgAnem.airConsumption) + " m^3/hour");
   // float twc = 13.12 + 0.6215*temp - 11.37*v100.16 + 0.3965*temp*v100.16
  delay(10000);
}