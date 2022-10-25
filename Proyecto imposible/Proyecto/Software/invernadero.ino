/*
* Prototipo de Invernadero Hidroponico 
* ISPC Telecomunicaciones Cohorte 2022
* Grupo 6 
* Alumnos   
*/

#include <WiFi.h>               // incluimos libreria de manejo de wifi
#include <PubSubClient.h>       // incluimos libreria de publicaciones y susbcripciones
#include <Wire.h>               // incluimos libreria de comunicacion I2C nativa
#include <Adafruit_BMP280.h>    // incluimos libreria de adafruit para sensor BMP280
#include <DHT.h>                // incluimos libreria de DHT11
#include <LiquidCrystal_I2C.h>  // incluimos libreria de LCD 20x4 I2C

//const char *ssid = "TP-LINK_B33E";                // red de wifi a la que me conecto
//const char *password = "50868155";                // password de la red de wifi
const char *ssid = "MGAlarmas";                     // red de wifi a la que me conecto
const char *password = "mgalarmas3040";             // password de la red de wifi
const char *mqtt_server = "mgalarmasserver1.ddns.net"; // dns del server mosquitto (MQTT)
unsigned int mqtt_port = 1883;                      // socket port del server MQTT Mosquitto
const char *Topico = "/Grupo6/invernadero/";        // topico para publicar los datos en el server
int str_len=0;
#define DHTPIN 26 
#define DHTTYPE DHT11           // DHT 11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_BMP280 bmp;                                // creamos el objeto bmp
WiFiClient esp32_Client;                            // creacion de objeto wifi client
PubSubClient client(esp32_Client);                  // creacion de objeto pubsunclient








void setup(){
    Serial.begin(9600);                             // puerto serial nativo 9600
    WiFi.begin(ssid, password);                     // conecto al wifi del lugar (micasa)
    dht.begin();                                    // inicio el DHT11
    bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);   // iniciamos el objeto sensor en la direccion alterna 0x77
    Serial.println(F("DHTxx test!"));
    lcd.init();                                     // Inicializo el LCD I2C
    lcd.backlight();
    while (WiFi.status() != WL_CONNECTED)           // inicio conexion
    {   
        delay(1500);                                // demora para reintentar
    }
    client.setServer(mqtt_server, mqtt_port);       // estableco conexion al server mwtt (ISPC)
    client.setCallback(callback);                   // inicio el callback de server mqtt y espero datos
 
    /*----------------------------------------------------------------*/
    /* configurar de fabrica segun datasheet ADAFRUIT Library */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    /*----------------------------------------------------------------*/   

    pinMode(LED_BUILTIN, OUTPUT);                   // el pin 2 como salida para el led azul de la placa
    client.setServer(mqtt_server, mqtt_port);       // estableco conexion al server mwtt (ISPC)
    client.setCallback(callback);                   // inicio el callback de server mqtt y espero datos
 

}






void loop(){

    float t = dht.readTemperature();
    String temp1 = String(t,2);
    int str_len1 = temp1.length() + 1;
    char envio1[str_len1];
    temp1.toCharArray(envio1, str_len1);
    client.publish("/grupo6/invernadero/DHT11_T/",envio1);

    float h = dht.readHumidity();
    String hume = String(h,2);
    int str_len2 = hume.length() + 1;
    char envio2[str_len2];
    hume.toCharArray(envio2, str_len2);
    client.publish("/grupo6/invernadero/DHT11_H/",envio2);
    
    

    // Serial.print(h);
    // Serial.print(t);
    
    client.publish("/grupo6/invernadero/BMP280_P/","970");
    client.publish("/grupo6/invernadero/BMP280_T/","28.1");
    client.publish("/grupo6/invernadero/deposito/","60 %");
    //Serial.print(bmp.readTemperature());     // recupero del objeto el metodo readTemperatura
    //Serial.println(" *C");                   // imprimo C de centigrado al final del renglon y hago CR/LF
//   Serial.print("Presion = ");              // imprimo por serial la palabra Presion
//   Serial.print(bmp.readPressure() / 100);  // recupero del objeto el metodo readPressure y divido para Hectopascal
//   Serial.println(" hPa");                  // imprimo Hectopascal
//   Serial.println();               // imprimo CRyLF
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
    // client.loop();
    delay(10000);
}

void callback(char *topic, byte *payload, unsigned int length)
{
    // aca va el codigo del callback para hacer operaciones remotas
    // en este caso no se usa
}


void reconnect() {
  while (!client.connected()) {
    String clientId = "Grupo6";
    clientId += String(random(0xffff), HEX);
     if (client.connect(clientId.c_str())){
  }
  delay(5000);
}
}