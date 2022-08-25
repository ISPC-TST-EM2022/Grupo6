#include <Arduino.h>


// Pedir el ingreso de dos números por terminal y mostrar la suma por la pantalla.  
/*Definiciones*/

int num1= 0;
int num2= 0;
int resultado= 0;

void setup() {
 Serial.begin(9600);
 Serial.println("________________________________________________________");
 Serial.println("");
 Serial.println("                  SUMA DE DOS NUMEROS");
 Serial.println("________________________________________________________");
 Serial.println("");
 Serial.println("Ingrese PRIMER numero");

}

void loop() {
  while(!Serial.available() > 0){}//para dejar el cursor en espera...

  num1= Serial.parseInt();//asigno a la variable num1 lo ingresado por teclado
  Serial.println("");
  Serial.println("Ingrese SEGUNDO numero");
  while(!Serial.available() > 0){}//para dejar el cursor en espera...
  num2=Serial.parseInt();//asigno a la variable num2 lo ingresado por teclado

  resultado= num1+num2; //sumo los dos numeros ingresados
  Serial.println("");
  Serial.println("El resultado es: ");
  Serial.println(resultado);
  Serial.println("");
  Serial.println("SI DESEA REALIZAR OTRA SUMA PRESIONE UNA TECLA");
  while(!Serial.available() > 0){}//para dejar el cursor en espera...
  Serial.read(); //lo hago para que no me tome lo ingresado para ser usado como primer numero 
  Serial.println("");
  Serial.println("\nIngrese PRIMER numero");

}