#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>
#include <prints.h>

// CÓDIGO AVIÔNICA GFRJ 2025 - FASE 3 | MPU6050, BMP280, NEO6M

#define RX 16 // GPIO16 atua como RX (vai no TX do GPS)
#define TX 17 // GPIO17 atua como TX (vai no RX do GPS)
#define GPS_BAUD 9600

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// ENDEREÇOS MPU6050
const int WHOAMI_MPU = 0x68;
const int POWER_MANAGEMENT_REGISTER = 0x6B;
const int ACCEL_XOUT = 0x3B;

const float ACCEL_SCALE = 16384.0; // LSB/g
const float GYRO_SCALE = 131.0;    // LSB/(°/s)

float aceleracaoX, aceleracaoY, aceleracaoZ;
float temperatura;
float giroX, giroY, giroZ;

const int BMP_DEVICE_I2C_ADDRESS = 0x76;
Adafruit_BMP280 bmp;

int16_t lerProximoValor() {
  return Wire.read() << 8 | Wire.read();
}

void lerValoresMPU() {
  aceleracaoX = lerProximoValor() / ACCEL_SCALE;
  aceleracaoY = lerProximoValor() / ACCEL_SCALE;
  aceleracaoZ = lerProximoValor() / ACCEL_SCALE;
  temperatura  = lerProximoValor() / 340.0 + 36.53;
  giroX = lerProximoValor() / GYRO_SCALE;
  giroY = lerProximoValor() / GYRO_SCALE;
  giroZ = lerProximoValor() / GYRO_SCALE;
}

void bmpSetup() {
  Serial.println(F("BMP280 teste."));

  if(!bmp.begin(BMP_DEVICE_I2C_ADDRESS)) {
    Serial.println("Nao foi possivel encontrar um BMP280 valido.");
    while(1) delay(10);
  }
}

void gpsSetup() {
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RX, TX);
}

void setup() {
  Serial.begin(115200);

  Wire.begin();
  Wire.beginTransmission(WHOAMI_MPU);
  Wire.write(POWER_MANAGEMENT_REGISTER);
  Wire.write(0);
  Wire.endTransmission(true);

  gpsSetup();
  bmpSetup();

  delay(100);
}

void loop() {
  Wire.beginTransmission(WHOAMI_MPU);
  Wire.write(ACCEL_XOUT);
  Wire.endTransmission(false);

  Wire.requestFrom(WHOAMI_MPU, 14, true);
  lerValoresMPU();

  printarMedidasMPU(aceleracaoX, aceleracaoY, aceleracaoZ, giroX, giroY, giroZ, temperatura);
  printarDadosBmpDescritivo(&bmp);
  lerGPS(&gps, &gpsSerial);

  delay(500);
}
