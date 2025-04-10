#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

void gpsSetup(HardwareSerial *gpsSerial, int RX, int TX);
void lerGPS(TinyGPSPlus *gps, HardwareSerial *gpsSerial);

#endif