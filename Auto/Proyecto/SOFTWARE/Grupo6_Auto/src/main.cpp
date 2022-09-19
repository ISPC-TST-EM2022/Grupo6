#include <Arduino.h>

int Dire1 =12; // pin de puente H manejo de direccion Mecanica 
int Dire2 =11; // pin de puente H manejo de direccion Mecanica 
int Velocidad = 10; // manjo de velocidad por PWM al puente H
int Led= 2;

void adelante(){
  digitalWrite(Dire1, HIGH);
  digitalWrite(Dire2, HIGH);
}

void atras(){
  digitalWrite(Dire1, LOW);
  digitalWrite(Dire2, LOW);
}

void izquierda(){
  digitalWrite(Dire1, HIGH;
  digitalWrite(Dire2, LOW);
}

void derecha(){
  digitalWrite(Dire1, LOW;
  digitalWrite(Dire2, HIGH);
}

void setup(){
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
  pinMode(Dire1, OUTPUT); 
  pinMode(Dire2, OUTPUT);
  pinMode(velocidad, OUTPUT); 
}

void loop(){

}

