#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

const int BMP_DEVICE_I2C_ADDRESS = 0x76;

void bmpSetup(Adafruit_BMP280 *bmp) {
    Serial.println(F("BMP280 teste."));
  
    if(!bmp->begin(BMP_DEVICE_I2C_ADDRESS)) {
      Serial.println("Nao foi possivel encontrar um BMP280 valido.");
      while(1) delay(10);
    }
  }

  void printarDadosBmpDescritivo(Adafruit_BMP280 *bmp)
{
    Serial.print(F("Temperatura = "));
    Serial.print(bmp->readTemperature());
    Serial.println(" °C");

    Serial.print(F("Pressao = "));
    Serial.print(bmp->readPressure());
    Serial.println(" Pa");

    Serial.print(F("Altitude aproximada = "));
    Serial.print(bmp->readAltitude(1013.25));
    Serial.println(" m");

    Serial.println();
}