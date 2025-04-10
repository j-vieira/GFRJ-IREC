#ifndef MPU_H
#define MPU_H

#include <Arduino.h>
#include <Wire.h>

typedef struct medidasAcelerometro
{
  float aceleracaoX, aceleracaoY, aceleracaoZ;
  float temperatura;
  float giroX, giroY, giroZ;
}medidasAcelerometro;


void mpuInit();
void mpuSetup();

int16_t lerProximoValor();
medidasAcelerometro lerValoresMPU();
void printarMedidasMPU(float aceleracaoX, float aceleracaoY, float aceleracaoZ,
    float giroX, float giroY, float giroZ, float temperatura);

#endif