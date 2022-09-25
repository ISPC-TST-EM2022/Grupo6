#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

int Dire1 = 35;     // pin de puente H manejo de direccion Mecanica
int Dire2 = 32;     // pin de puente H manejo de direccion Mecanica
int Dire3 = 33;     // pin de puente H manejo de direccion Mecanica
int Dire4 = 25;     // pin de puente H manejo de direccion Mecanica
int Velocidad_1 = 34; // manejo de velocidad por PWM al puente H
int Velocidad_2 = 26;

int Led = 2;
int Sensor = 25;                                      // Led indicador de comando recibido
const char *ssid = "TP-LINK_B33E";                    // nombre de la red a donde me conecto
const char *password = "50868155";                    // contraseña de red WIFI
const char *mqttServer = "mgalarmasserver1.ddns.net"; // dns del broker
const int mqttPort = 1883;                            // puerto soket del broker
const char *mqttUser = "";                            // usuario del boker
const char *mqttPassword = "";                        // password del broker
const char *topic = "/grupo6/app/";

WiFiClient espClient;           // invoco al constructor de la clase Wificlient
PubSubClient client(espClient); // establecemos objeto de la clase espClient

void adelante()
{ // declaramos funcion para ir adelante
  digitalWrite(Dire1, HIGH);
  digitalWrite(Dire2, LOW);
  digitalWrite(Dire3, HIGH);
  digitalWrite(Dire4, LOW);
  digitalWrite(Velocidad_1, HIGH);
  digitalWrite(Velocidad_2, HIGH);

}

void atras()
{ // declaramos funcion para ir para atras
  digitalWrite(Dire1, LOW);
  digitalWrite(Dire2, LOW);
}

void izquierda()
{ // declaramos funcion para ir izquierda
  digitalWrite(Dire1, HIGH);
  digitalWrite(Dire2, LOW);
}

void derecha()
{ // declaramos funcion para ir derecha
  digitalWrite(Dire1, LOW);
  digitalWrite(Dire2, HIGH);
}

void medir()
{
  int mq7 = analogRead(Sensor);                   // Lemos la salida analógica del MQ
  float voltaje = mq7 * (5.0 / 1023.0);           // Convertimos la lectura en un valor de voltaje
  float Rs = 1000 * ((5 - voltaje) / voltaje);    // preset con una resitencia ideal de 1000 ohms
  double monox = 0.4091 * pow(Rs / 5463, -1.497); // concentración  de CO ecu segun fabricante
}


 void Suscribe_MQTT()
{
//   client.subscribe(topic); // client.subscribe(ID+topico);
// }

// void Publica_MQTT(){
//   //client.publish(topic, monoxido);
// }


// void callback(char *topic, byte *payload, unsigned int length)//rutina de llegada de datos por MQTT
// {
//   Serial.print("hola llego algo");
//   Serial.print("Llego un dato");
//   if ((char)payload[0] == '1') //cargamos el valor de arreglo indice 0 en una variable para el case
//   {
//     for (int i = 0; i < 10; i++)
//     {
//       digitalWrite(Led, HIGH);
//       delay(1000);
//       digitalWrite(Led, LOW);
//       delay(1000);
//     }
//   }
 }

void setup()
{
  Serial.begin(9600);         // iniciamos serial a 9600 para velocidad de depuracion de errores
  WiFi.begin(ssid, password); // inicia la conexion WIFI

  // Serial.print("Conectando ");
  // while (WiFi.status() != WL_CONNECTED) // While de espera mientras nos atiende el router
  // {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.println("Conexion Exitosa a la red de wifi !!"); // publicamos al salir del while

  // client.setServer(mqttServer, mqttPort); // me conecto al broker
  // while (!client.connected())             // bucle de espera hasta conexion exitosa
  // {
  //   String clientId = "Grupo6";              // cargo nombre de usuario
  //   clientId += String(random(0xffff), HEX); // sumo al usuario numero random para que me acepte broker

  //   Serial.println("Conectando al broker MQTT...");
  //   if (client.connect(clientId.c_str()))
  //   { // usuario broker random ante caidas
  //     Serial.println("Conectado !!!");
  //     Serial.print("Usuario: ");
  //     Serial.print(clientId.c_str());
  //   }
  //   else
  //   {
  //     Serial.print("Fallo en la conexion"); // en caso de no conectarse
  //     Serial.print(client.state());         // publico por el serial el estado de la conexion al broker
  //     delay(2000);
  //   }
  // }
  // client.setCallback(callback);
  pinMode(Led, OUTPUT);       // establecemos pin como salida
  pinMode(Dire1, OUTPUT);     // establecemos pin como salida
  pinMode(Dire2, OUTPUT);     // establecemos pin como salida
  pinMode(Dire3, OUTPUT);     // establecemos pin como salida
  pinMode(Dire4, OUTPUT);     // establecemos pin como salida
  pinMode(Velocidad_1, OUTPUT); // establecemos pin como salida
}

void loop()
{
  //client.loop();


adelante();
delay(1000);
 
}
