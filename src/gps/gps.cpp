
#include <Arduino.h>
#include <TinyGPS++.h>

#define GPS_BAUD 9600

void gpsSetup(HardwareSerial *gpsSerial, int RX, int TX)
{
    gpsSerial->begin(GPS_BAUD, SERIAL_8N1, RX, TX);
}

void lerGPS(TinyGPSPlus *gps, HardwareSerial *gpsSerial)
{
    while (gpsSerial->available() > 0)
    {
        char c = gpsSerial->read();
        gps->encode(c);

        // Log completo NMEA se quiser depurar
        Serial.write(c);
    }

    if (gps->location.isUpdated())
    {
        Serial.println("\n--- DADOS FORMATADOS GPS ---");
        Serial.print("Latitude: ");
        Serial.println(gps->location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps->location.lng(), 6);

        Serial.print("Satélites em uso (GGA): ");
        Serial.println(gps->satellites.value());

        Serial.print("Altitude: ");
        Serial.print(gps->altitude.meters());
        Serial.println(" m");

        Serial.print("Velocidade: ");
        Serial.print(gps->speed.kmph());
        Serial.println(" km/h");

        Serial.print("Data: ");
        Serial.print(gps->date.day());
        Serial.print("/");
        Serial.print(gps->date.month());
        Serial.print("/");
        Serial.println(gps->date.year());

        Serial.print("Hora: ");
        Serial.print(gps->time.hour());
        Serial.print(":");
        Serial.print(gps->time.minute());
        Serial.print(":");
        Serial.println(gps->time.second());

        Serial.println("----------------------");
    }
}