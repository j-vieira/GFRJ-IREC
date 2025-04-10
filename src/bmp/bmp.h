#ifndef BMP_H
#define BMP_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>


void bmpSetup(Adafruit_BMP280 *bmp);
void printarDadosBmpDescritivo(Adafruit_BMP280 *bmp);

#endif
