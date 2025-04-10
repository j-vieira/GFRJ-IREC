#ifndef PRINTS_H
#define PRINTS_H

#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>

void printarMedidasMPU(float aceleracaoX, float aceleracaoY, float aceleracaoZ,
                       float giroX, float giroY, float giroZ, float temperatura);

void printarDadosBmpDescritivo(Adafruit_BMP280 *bmp);

void lerGPS(TinyGPSPlus *gps, HardwareSerial *gpsSerial);

#endif
