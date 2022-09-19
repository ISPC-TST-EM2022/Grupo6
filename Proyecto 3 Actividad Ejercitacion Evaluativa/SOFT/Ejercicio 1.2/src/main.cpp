#include <Arduino.h>

String Nombre;
String Apellido;
String Direccion;
String Celular;

void setup() {

Serial.begin(9600);
Serial.println("Ejercicio 1 item 2"); //mensaje de inicio
 
}

void loop() {
  //solicito que ingrese los datos y que los lea
Serial.println("Ingrese Nombre:");
  while (!Serial.available()>0){ 
    
}
Nombre = Serial.readStringUntil('\n');


Serial.println("Ingrese Apellido:");
  while (!Serial.available()>0){
    
  }
Apellido = Serial.readStringUntil('\n');


Serial.println("Ingrese direccion:");
while (!Serial.available()>0){
}


Direccion = Serial.readStringUntil('\n');
Serial.println("Ingrese celular:");
while (!Serial.available()>0){
}
 

Celular = Serial.readStringUntil('\n');

//muestro los resultados
Serial.println("Resultados de Datos");
Serial.println("");
Serial.println("Nombre: " + Nombre);
Serial.println("Apellido: "  + Apellido);
Serial.println("Direccion: " + Direccion);
Serial.println("Celular: " + Celular);
Serial.println("");
Serial.println("Fin del codigo");


}