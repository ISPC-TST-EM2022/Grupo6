#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

int Dire1 =12; // pin de puente H manejo de direccion Mecanica 
int Dire2 =11; // pin de puente H manejo de direccion Mecanica 
int Velocidad = 10; // manejo de velocidad por PWM al puente H
int Led= 2;
const char* ssid = "MGAlarmas"; //nombre de la red a donde me conecto
const char* password = "mgalarmas3040"; //contraseña de red WIFI
const char* mqttServer = "mgalarmasserver1.ddns.net";//dns del broker
const int mqttPort = 1883;//puerto soket del brojer
const char* mqttUser = "";//usuario del boker
const char* mqttPassword = "";//password del broker

WiFiClient espClient; //invoco al constructor de la clase Wificlient
PubSubClient client(espClient); // establecemos objeto de la clase espClient

void adelante(){ //declaramos funcion para ir adelante
  digitalWrite(Dire1, HIGH);
  digitalWrite(Dire2, HIGH);
}

void atras(){ // declaramos funcion para ir para atras
  digitalWrite(Dire1, LOW);
  digitalWrite(Dire2, LOW);
}

void izquierda(){ // declaramos funcion para ir izquierda
  digitalWrite(Dire1, HIGH);
  digitalWrite(Dire2, LOW);
}

void derecha(){ // declaramos funcion para ir derecha
  digitalWrite(Dire1, LOW);
  digitalWrite(Dire2, HIGH);
}

void setup(){
  Serial.begin(9600); // iniciamos serial a 9600 para velocidad de depuracion de errores
  WiFi.begin(ssid, password); //inicia la conexion WIFI

  Serial.print("Conectando ");
  while (WiFi.status() != WL_CONNECTED) //While de espera mientras nos atiende el router 
       {  delay(500);
          Serial.print(".") ;
       }
  Serial.println("Conexion Exitosa a la red de wifi !!"); // publicamos al salir del while


client.setServer(mqttServer, mqttPort);
while (!client.connected())
{      Serial.println("Conectando al broker MQTT...");
       if (client.connect("ESP32Client", mqttUser, mqttPassword ))
           Serial.println("Conectado !!!");
       else
       {   Serial.print("Fallo en la conexion");
           Serial.print(client.state());
           delay(2000);
       }
}

  pinMode(Led, OUTPUT); // establecemos pin como salida
  pinMode(Dire1, OUTPUT); // establecemos pin como salida
  pinMode(Dire2, OUTPUT); // establecemos pin como salida
  pinMode(Velocidad, OUTPUT); // establecemos pin como salida

}

void loop(){





}

