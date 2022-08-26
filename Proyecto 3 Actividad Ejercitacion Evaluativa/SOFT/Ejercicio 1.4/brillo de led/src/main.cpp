#include <Arduino.h>
int led =13;
int i;


void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT) ;
  Serial.println ("Bienvenido/a, por favor ingrese un valor entre 0 y 255:");
}
void loop() {

  while((!Serial.available())>0);
{
  i=Serial.parseInt();
  
  if((i>=0)and(i<=255)){
    analogWrite(led,i);
    delay(1000);
  }
}
}