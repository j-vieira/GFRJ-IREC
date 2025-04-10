#include "prints.h"

void printarMedidasMPU(float aceleracaoX, float aceleracaoY, float aceleracaoZ, float giroX, float giroY, float giroZ, float temperatura)
{
    Serial.println();
    Serial.print(aceleracaoX);
    Serial.print(",");
    Serial.print(aceleracaoY);
    Serial.print(",");
    Serial.print(aceleracaoZ);
    Serial.print(",");
    Serial.print(giroX);
    Serial.print(",");
    Serial.print(giroY);
    Serial.print(",");
    Serial.print(giroZ);
    Serial.print(",");
    Serial.print(temperatura);
    Serial.println();
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