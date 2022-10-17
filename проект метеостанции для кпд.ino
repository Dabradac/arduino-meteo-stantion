#include <Wire.h>
#include <GyverBME280.h>
GyverBME280 bme;
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
#include "cgAnem.h"
CG_Anem cgAnem(ANEM_I2C_ADDR);
float firmWareVer;

void setup() {

  //Serial.begin(9600); // запуск порта
  //Serial.println("Start"); // инициализация датчика
  oled.init();        // инициализация дисплея
  cgAnem.init();   // инициализация анемоментра
  bme.begin(0x76) ;  // инициализация датчика температуры

  // v = cgAnem.airflowRate();
 // float v10 = 1.5 * v;
 // float twc := 13.12 + 0.6215 * t - 11.37 * v10 + + 0.3965 * t * v10;
  // запуск датчика и проверка на работоспособность
  //if (!bme.begin(0x76)) Serial.println("Error!"); //если порты а4 а5
}
// доделать конвертацию serial в string или float а зачем сложить по формуле twc = 13.12 + 0.6215*ta - 11.37*v100.16 + 0.3965*ta*v100.16

void loop() {
  // переменные для расчета ощущамой температуры
  float Temperature = bme.readTemperature(); // переменная температуры окружающей среды
  float AirflowRate = cgAnem.getAirflowRate(); // переменная скорости воздуха
//float AirTemperature= cgAnem.getTemperature(); // переменная температуры воздуха, в формуле не используется.
  float AirflowRate10 = 1.5 * AirflowRate; // переменная скорости ветра на уровне 10 метров от земли в м/с;
  // блок измерения температуры 
  oled.setScale(3); // размер текста
     oled.setCursor(0, 1);
  // температура
  oled.print("Температура: ");
  oled.print(bme.readTemperature());
  oled.setCursor(0, 2);
  // влажность
  oled.print("Влажность: ");
  oled.print(bme.readHumidity());
  oled.setCursor(0, 3);
 //давление
  oled.print("Давление: ");
  oled.print(bme.readPressure());
  delay(5000); 
  oled.clear();
  //блок измерения скорости и температуры ветра
  //скорость ветра
  oled.setCursor(0, 1);
  oled.println("Скорость ветра: ");
  oled.print(cgAnem.getAirflowRate());
  // температура воздуха
  oled.setCursor(0, 2);
  oled.println("Температура воздуха: ");
  oled.print(cgAnem.getTemperature());
  delay(5000);
  // Расход воздуха
   /*
  oled.setCursor(0, 3);
  oled.println("Air flow consumption: ");
  oled.print(cgAnem.airConsumption());*/
  // расчет ощущаемой температуры
  oled.clear();
  oled.setCursor(0, 1);
  oled.print("Ощущаемая температура :");
  float twc = 13.12 + 0.6215*Temperature - 11.37*AirflowRate10 + 0.3965*Temperature*AirflowRate10;
  oled.print (twc);
  oled.print("C");
  delay(5000);
}