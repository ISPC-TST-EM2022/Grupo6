#include <Arduino.h>






void adelante(){

}

void atras(){

}

void izquierda(){

}

void derecha(){

  
}



void setup(){
  Serial.begin(9600);
    pinMode(2, OUTPUT);

}

void loop(){
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
    delay(1000);
}