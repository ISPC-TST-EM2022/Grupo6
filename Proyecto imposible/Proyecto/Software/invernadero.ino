#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>            // incluimos libreria de comunicacion I2C nativa
#include <Adafruit_BMP280.h> // incluimos libreria de adafruit para sensor BMP280
#include "DHT.h"
#define DHTPIN 2 

//const char *ssid = "TP-LINK_B33E";                     // red de wifi a la que me conecto
//const char *password = "50868155";                     // password de la red de wifi
const char *ssid = "MGAlarmas";                     // red de wifi a la que me conecto
const char *password = "mgalarmas3040";                     // password de la red de wifi
const char *mqtt_server = "mgalarmasserver1.ddns.net"; // dns del server mosquitto (MQTT)
unsigned int mqtt_port = 1883;                         // socket port del server MQTT Mosquitto
const char *Topico = "/invernadero/grupo6/";           // topico para publicar los datos en el server

Adafruit_BMP280 bmp;                            // creamos el objeto bmp
WiFiClient esp32_Client;                        // creacion de objeto wifi client
PubSubClient client(esp32_Client);              // creacion de objeto pubsunclient

void setup()
{
    Serial.begin(9600);                         // puerto serial nativo 9600
    WiFi.begin(ssid, password);                 // conecto al wifi del lugar (micasa)
    while (WiFi.status() != WL_CONNECTED)       // inicio conexion
    {   
        delay(1500);                            // demora para reintentar
    }
    client.setServer(mqtt_server, mqtt_port);   // estableco conexion al server mwtt (ISPC)
    client.setCallback(callback);               // inicio el callback de server mqtt y espero datos
    bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);// iniciamos el objeto sensor en la direccion alterna 0x77
    /* configurar de fabrica segun datasheet ADAFRUIT Library */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    pinMode(LED_BUILTIN, OUTPUT);                     // el pin 2 como salida para el led azul de la placa

}

void loop()
{
  Serial.print("Temperatura = ");          // imprimo por serial la palabra temperatura
  Serial.print(bmp.readTemperature());     // recupero del objeto el metodo readTemperatura
  Serial.println(" *C");                   // imprimo C de centigrado al final del renglon y hago CR/LF
  Serial.print("Presion = ");              // imprimo por serial la palabra Presion
  Serial.print(bmp.readPressure() / 100);  // recupero del objeto el metodo readPressure y divido para Hectopascal
  Serial.println(" hPa");                  // imprimo Hectopascal
  Serial.println();               // imprimo CRyLF
  digitalWrite(LED_BUILTIN, HIGH);// Enciendo led azul
  delay(100);
  digitalWrite(LED_BUILTIN, LOW); // apago led azul
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);// Enciendo led azul
  delay(100);
  digitalWrite(LED_BUILTIN, LOW); // apago led azul
  delay(3000);
      if (!client.connected()) // si la conexion esta negada reconecto
        reconnect();
    client.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    // aca va el codigo del callback para hacer operaciones remotas
    // en este caso no se usa
}

void reconnect()
{
    while (!client.connected())
    {
        delay(5000); // demora para reintentar conectarse
    }
}