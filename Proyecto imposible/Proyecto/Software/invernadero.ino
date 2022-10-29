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
#include <Ticker.h>             // incluimos libreria de temporizacion por software timer  
#include <NTPClient.h>          // incluimos libreria de NTPClient
#include <WiFiUdp.h>            // incluimos libreria de WiFiUdp

const char *ssid = "TP-LINK_B33E";                  // red de wifi a la que me conecto
const char *password = "50868155";                  // password de la red de wifi

const char *mqtt_server = "mgalarmasserver1.ddns.net"; // dns del server mosquitto (MQTT)
unsigned int mqtt_port = 1883;                      // socket port del server MQTT Mosquitto
const char *Topico = "/Grupo6/invernadero/";        // topico para publicar los datos en el server
int flotante=33;                                    // variable para flotante
int bomba= 27;                                      // variable para bomba
int detector= 4;                                    // variable para detector
String flota="";                                    // variable para flota para BD
String detec="";
String pump="";
String fecha="";
String hora="";
#define DHTPIN 26 
#define DHTTYPE DHT11                               // definimos el tipo de sensor DHT 11
DHT dht(DHTPIN, DHTTYPE);                           // definimos el tipo de ght y sus pines
LiquidCrystal_I2C lcd(0x27,20,4);                   // objeto de LCD i2c
Adafruit_BMP280 bmp;                                // creamos el objeto bmp
Ticker timer;                                       // Temporizador
WiFiClient esp32_Client;                            // creacion de objeto wifi client
PubSubClient client(esp32_Client);                  // creacion de objeto pubsunclient
WiFiUDP ntpUDP;                                     // obejto udp para la hora
NTPClient timeClient(ntpUDP, "ntp.ign.gob.ar", -10800, 8000);//objeto del server Hora



void ICACHE_RAM_ATTR controlarBomba(){
    digitalWrite(bomba, !digitalRead(bomba));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (digitalRead(bomba) == 0){
        client.publish("/grupo6/invernadero/bomba/","0");
    }else{
        client.publish("/grupo6/invernadero/bomba/","1");
    }
}

void ICACHE_RAM_ATTR bd_mysql(){
    String carga_bd = fecha+hora+temp1+temp2+hume+pres+flota+detec+pump;// Genero la carga para payload BD
    int str_len_bd = temp1.length() + 1;              // cargo el largo del carga a una variable
    char envio_bd[str_len_bd];                        // cargo el largo de la payload en el arreglo
    carga_bd.toCharArray(envio_db, str_len_bd);       // convierto la carga en arreglo y del largo delpayload
    client.publish("/grupo6/invernadero/BD/",envio_bd); // publico en el broker el topico y el arreglo 
 }

void setup(){
    pinMode(flotante,INPUT_PULLUP);                 // declaro el pin del flotante como entrada
    pinMode(bomba, OUTPUT);                         // se declara pin bomba como salida
    pinMode(detector, INPUT_PULLUP);                // se declara el pin sensor como entrada
    pinMode(LED_BUILTIN, OUTPUT);                   // el pin 2 como salida para el led azul de la placa
    Serial.begin(9600);                             // puerto serial nativo 9600
    WiFi.begin(ssid, password);                     // conecto al wifi del lugar (micasa)
    dht.begin();                                    // inicio el DHT11
    bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);   // iniciamos el objeto sensor en la direccion alterna 0x77
    lcd.init();                                     // Inicializo el LCD I2C
    bienvenido();
     while (WiFi.status() != WL_CONNECTED)          // inicio conexion
      {   
          delay(1500);                              // demora para reintentar
          digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      }
 
    /*------------------------------------------------------------------*/
    /* configurar de fabrica segun datasheet ADAFRUIT Library           */
    /*------------------------------------------------------------------*/
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,       // Operating Mode. 
                    Adafruit_BMP280::SAMPLING_X2,       // Temp. oversampling 
                    Adafruit_BMP280::SAMPLING_X16,      // Pressure oversampling
                    Adafruit_BMP280::FILTER_X16,        // Filtering.
                    Adafruit_BMP280::STANDBY_MS_500);   // Standby time.
    /*------------------------------------------------------------------*/  

    client.setServer(mqtt_server, mqtt_port);       // estableco conexion al server mwtt (ISPC)
    // client.setCallback(callback);                // inicio el callback de server mqtt y espero datos
    timer.attach(300,controlarBomba); //900         // tiempo de espera en segundos, enciende la bomba
    timer.attach(300,bd_mysql);                     // tiempo de espera en segundos, guarda bd mysql
    lcd.clear();                                    // limpiamos el lcd
}

void loop(){

    float t1 = dht.readTemperature();               // adquirimos temperatura del DHT11
    String temp1 = String(t1,2);                    // Convierto el float a string
    int str_len1 = temp1.length() + 1;              // cargo el largo del float a una variable
    char envio1[str_len1];                          // cargo el largo de la temperatura en al arreglo
    temp1.toCharArray(envio1, str_len1);            // convierto el envio1 en arreglo y del largo de temp1
    client.publish("/grupo6/invernadero/DHT11_T/",envio1); // publico en el broker el topico y el arreglo 
    Serial.print(envio1);                           // publico en el serial
    lcd.setCursor(0,0);                             // posicionamos el cursor    
    lcd.print("T:");
    lcd.print(envio1);                              // imprimimos

    float t2 = bmp.readTemperature();               // adquirimos temperatura del BMP280
    String temp2 = String(t2,2);                    // Convierto el float a string
    int str_len3 = temp2.length() + 1;              // cargo el largo del float a una variable
    char envio3[str_len3];                          // cargo el largo de la temperatura en al arreglo
    temp2.toCharArray(envio3, str_len3);            // convierto el envio3 en arreglo y del largo de temp1
    client.publish("/grupo6/invernadero/BMP280_T/", envio3); // publico en el broker el topico y el arreglo 
    Serial.print(envio3);                           // publico en el serial
    lcd.setCursor(8,0);                             // posicionamos el cursor    
    lcd.print("T:");
    lcd.print(envio3);                              // imprimimos

    float h = dht.readHumidity();                   // adquirimos humedad del DHT11
    String hume = String(h,2);                      // Convierto el float a string
    int str_len2 = hume.length() + 1;               // cargo el largo de la humedad en una variable
    char envio2[str_len2];                          // cargo el largo de la humedad en el arreglo
    hume.toCharArray(envio2, str_len2);             // convierto el envio2 en arreglo y del largo de hume
    client.publish("/grupo6/invernadero/DHT11_H/",envio2);// publico en el broker el topico y el arreglo
    Serial.print(envio2);                           // publico en el serial
    lcd.setCursor(1,1);                             // posicionamos el cursor    
    lcd.print("Hr: ");
    lcd.print(envio2);  
    lcd.print("%");

    float p = (bmp.readPressure() / 100);           // adquirimos temperatura del BMP280
    String pres = String(p,2);                      // Convierto el float a string
    int str_len4 = pres.length() + 1;               // cargo el largo del float a una variable
    char envio4[str_len4];                          // cargo el largo de la temperatura en al arreglo
    pres.toCharArray(envio4, str_len4);             // convierto el envio3 en arreglo y del largo de temp1
    client.publish("/grupo6/invernadero/BMP280_P/", envio4); // publico en el broker el topico y el arreglo 
    Serial.print(envio4); 
    lcd.setCursor(0,2);                             // publico en el serial
    lcd.print("hPa: ");
    lcd.print(envio4);

    if (digitalRead(flotante)==1){
        client.publish("/grupo6/invernadero/deposito/","1");
        flota="SI";
    }else{
        client.publish("/grupo6/invernadero/deposito/","0");
        flota="NO";
    }

    if (digitalRead(detector)==0){
        client.publish("/grupo6/invernadero/detectorA/","0");  
        Serial.println("Agua NO"); 
        lcd.setCursor(12,2);                          // publico en el serial
        lcd.println("Agua: NO");
        detec = "NO";

    }else{
        client.publish("/grupo6/invernadero/detectorA/","1");
        Serial.println("Agua SI");                               
        lcd.setCursor(12,2);                          // publico en el serial
        lcd.println("Agua: SI"); 
        detec = "SI";            
    }

    if (digitalRead(bomba) == 0){
        client.publish("/grupo6/invernadero/bomba/","0");
        Serial.println("Bomba NO"); 
        lcd.setCursor(0,3);                          // publico en el serial
        lcd.println("Bomba: APAGADA");
        pump = "NO";
    }else{
        client.publish("/grupo6/invernadero/bomba/","1");
        Serial.println("Bomba SI"); 
        lcd.setCursor(0,3);                          // publico en el serial
        lcd.println("Bomba: ENCENDIDA");
        pump="SI";
    }

        if (!client.connected())                     // si la conexion esta negada reconecto
        reconnect();
        delay(5000);
}

void callback(char *topic, byte *payload, unsigned int length)
{
    // aca va el codigo del callback para hacer operaciones remotas
    // en este caso no se usa
}

void reconnect()
{
    while (!client.connected()){                    // si la conexion esta negada reconecto
        String clientId = "Grupo6";                 // genero el usuario
        clientId += String(random(0xffff), HEX);    // genero parte del usuario random
        if (client.connect(clientId.c_str())){}     
        delay(5000);                                // demora de la conexion
    }
}

void bienvenido(){
    lcd.backlight();                            // Encendemos el backlight
    lcd.clear();                                // limpiamos el lcd
    lcd.setCursor(0,0);                         // posicionamos el cursor    
    lcd.print("Grupo 6");                       // imprimimos
    lcd.setCursor(0,1);                         // posicionamos el cursor 
    lcd.print("Proyecto Imposible");            // imprimimos
    lcd.setCursor(0,2);                         // posicionamos el cursor
    lcd.print("Invernadero");                   // imprimimos
    lcd.setCursor(0,3);                         // posicionamos el cursor
    lcd.print("Hidroponico");                   // imprimimos

}
