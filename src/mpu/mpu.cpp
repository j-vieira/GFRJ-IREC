#include <Arduino.h>
#include <Wire.h>

// ENDEREÇOS MPU6050
const int WHOAMI_MPU = 0x68;
const int POWER_MANAGEMENT_REGISTER = 0x6B;
const int ACCEL_XOUT = 0x3B;

const float ACCEL_SCALE = 16384.0; // LSB/g
const float GYRO_SCALE = 131.0;    // LSB/(°/s)

typedef struct medidasAcelerometro {
  float aceleracaoX, aceleracaoY, aceleracaoZ;
  float temperatura;
  float giroX, giroY, giroZ;
};

void mpuInit()
{
  Wire.beginTransmission(WHOAMI_MPU);
  Wire.write(ACCEL_XOUT);
  Wire.endTransmission(false);

  Wire.requestFrom(WHOAMI_MPU, 14, true);
}

void mpuSetup()
{
  Wire.begin();
  Wire.beginTransmission(WHOAMI_MPU);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.write(0);
  Wire.endTransmission(true);
}

void printarMedidasMPU(float aceleracaoX, float aceleracaoY, float aceleracaoZ, float giroX, float giroY, float giroZ, float temperatura)
{
  Serial.printf("\n %f, %f, %f, %f, %f, %f, %f\n", aceleracaoX, aceleracaoY, aceleracaoZ, giroX, giroY, giroZ, temperatura);
}

int16_t lerProximoValor() {
  return Wire.read() << 8 | Wire.read();
}

medidasAcelerometro lerValoresMPU() {
  struct medidasAcelerometro medidas;
  
  medidas.aceleracaoX = lerProximoValor() / ACCEL_SCALE;
  medidas.aceleracaoY = lerProximoValor() / ACCEL_SCALE;
  medidas.aceleracaoZ = lerProximoValor() / ACCEL_SCALE;
  medidas.temperatura = lerProximoValor() / 340.0 + 36.53;
  medidas.giroX = lerProximoValor() / GYRO_SCALE;
  medidas.giroY = lerProximoValor() / GYRO_SCALE;
  medidas.giroZ = lerProximoValor() / GYRO_SCALE;

  return medidas;
}


