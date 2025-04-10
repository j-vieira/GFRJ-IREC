// CÓDIGO AVIÔNICA GFRJ 2025 - FASE 3 | MPU6050, BMP280, NEO6M
#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>
#include <./mpu/mpu.h>
#include <./bmp/bmp.h>
#include <./gps/gps.h>

#define RX 16 // GPIO16 atua como RX (vai no TX do GPS)
#define TX 17 // GPIO17 atua como TX (vai no RX do GPS)
#define GPS_BAUD 9600

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);

  mpuSetup();
  gpsSetup(&gpsSerial, RX, TX);
  bmpSetup(&bmp);

  delay(100);
}

void loop() {

  mpuInit();
  medidasAcelerometro m = lerValoresMPU();
  printarMedidasMPU(m.aceleracaoX, m.aceleracaoY, m.aceleracaoZ, m.giroX, m.giroY, m.giroZ, m.temperatura);
  printarDadosBmpDescritivo(&bmp);
  lerGPS(&gps, &gpsSerial);

  delay(500);
}
