//Esp32 se conecta mediante bluetooth al celular y es controlado por la app ACRICO.
//Esp32 recibe los datos del sensor de gas mq2. Si se detecta presencia de gas se enciende un led

#include <Arduino.h>
#include "BluetoothSerial.h"  //libreria bluetooth 

BluetoothSerial SerialBT;

//declaracion relacionadas con bluetooth
int received; //almacena el parametro recibido por la conexion bluetooth

//declaracion de variables y puertos relacionados con sensor mq2
int cantidadGas;  //variable que almacena los datos del sensor
int ledGas = 22; //pin donde se conecta el led que se enciende con niveles peligrosos de gas
int ledblue = 35; //pin donde se conecta el led de rex comandos 
int sensor_digi = 18; //pin de lectura digital sensor
int sensor_analogo =19; //pin de lectura analogica sensor


//declaracion de variables y puertos relacionados con motores dc
const int MD1 = 33; //motor derecho 1
const int MD2 = 32; //motor derecho 2
const int MI1 = 27; //motor izquierdo 1
const int MI2 = 26; //motor izquierdo 2

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32"); //nombre con el que se identifica la conexion del bluetooth del esp32
  pinMode(ledGas, OUTPUT);  //secdeclara el pin ledGas como salida
  digitalWrite(ledGas,HIGH); //para asegurarnos que este apagado el led
  digitalWrite(ledblue, LOW);
  pinMode(sensor_digi,INPUT);  //se declara el pin sensor como entrada
  pinMode(sensor_analogo,INPUT);  //se declara el pin sensor como entrada
  pinMode(MD1, OUTPUT); //se declara pin MD1 como salida 
  pinMode(MD2, OUTPUT); //se declara pin MD2 como salida 
  pinMode(MI1, OUTPUT); //se declara pin MI1 como salida 
  pinMode(MI2, OUTPUT); //se declara pin MI2 como salida 
  }


void Adelante(){
  // //metodo que mueve el auto hacia adelante
  // //motores lado derecho
   digitalWrite(MD1,HIGH); //se mueve
   digitalWrite(MD2,LOW); 
  // //motores lado izquierdo
  digitalWrite(MI1,HIGH);
  digitalWrite(MI2,LOW); //se mueve
}
void Reversa(){
  // //metodo que mueve el auto en reversa
  digitalWrite(MD1,LOW); //se mueve
  digitalWrite(MD2,HIGH);
  //motores lado izquierdo
  digitalWrite(MI1,LOW); //se mueve
  digitalWrite(MI2,HIGH);
}

void Izquierda(){
  // //metodo que mueve el auto hacia la izquierda
  // //motores lado derecho
   digitalWrite(MD1,LOW); //se mueve
   digitalWrite(MD2,LOW);
  // //motores lado izquierdo
   digitalWrite(MI1,HIGH); //se mueve
   digitalWrite(MI2,LOW);
}
void Derecha(){
  //metodo que mueve el auto hacia la derecha
  //motores lado derecho
   digitalWrite(MD1,HIGH);
   digitalWrite(MD2,LOW); //se mueve
   digitalWrite(MI1,LOW);
   digitalWrite(MI2,LOW); //se mueve
}
void Parar(){
  //metodo que detiene los 4 motores del auto
  //motores lado derecho
  digitalWrite(MD1,LOW); 
  digitalWrite(MD2,LOW);
  //motores lado izquierdo
  digitalWrite(MI1,LOW); 
  digitalWrite(MI2,LOW); 
}

void rx_blue(){
  digitalWrite(ledblue, HIGH);
  delay(200);
  digitalWrite(ledblue, LOW);
  delay(200);
}
void loop() {
   

  rx_blue();
 
  if(digitalRead(sensor_digi)==LOW)//si el senseor mq2 detecta gas se enciende led
  { 
    while (digitalRead(sensor_digi)==LOW)
    {
      digitalWrite(ledGas,LOW);
      delay(100);
      digitalWrite(ledGas,HIGH);
      delay(100);
    }
   
      digitalWrite(ledGas,HIGH);

  }else{//si no detecta gas se apaga el led
    
      digitalWrite(ledGas,HIGH);

    }
  if (SerialBT.available())//si hay un dato proveniente del bluetooth para leer 
   {
      received =SerialBT.read();//lee lo recibido por bluetooth
      rx_blue();
        
    
      if(received == '1')//si recibe un 1 llama al metodo Adelante()
      {
        Adelante();
       
      }
      if(received == '2')//si recibe un 2 llama al metodo Reversa()
      {
 
        Reversa(); 
      }         
      if(received == '3')//si recibe un 3 llama al metodo Izquierda()
      {

        Izquierda();
      }        
      if(received == '4')//si recibe un 4 llama al metodo Derecha()
      {

       Derecha(); 
      }
      if(received == '5')//si recibe un 5 llama al metodo Parar()
      {
        Parar();
      }
      
  }
  delay(20);
}
