#include <Arduino.h>


// constantes

const int tam = 9; //tamaño del vector

//variables
char buffer[tam]; //vector de caracteres


void setup() {
// Habilito el puerto de comunicacion serie
Serial.begin(9600);

// Habilitar el puerto D como salida
// DDRD = 0xFF;

}

void loop() {

// Serial.println("Ingrese un numero binario de 1 byte: ");  

if(Serial.available()){
  
  byte dato = Serial.readBytes(buffer, tam);

  Serial.print("El dato es: ");
    for(int i=0; i<tam; i++){
      Serial.print(buffer[i]);
    }
  Serial.println('\n');

}

// Deshabitamos el puerto de comunicacion serial
Serial.end();

// Habilito el puerto D, como salida
DDRD = 0xFF;
delay(1);

while(1){
  for (int i = 0; i<tam; i++){
    PORTD = buffer[i];
    delay(1);
  }

// sleep_mode();

}
// PORTD = 0xFF;
// delay(300);
// PORTD = 0x00;
// delay(300);

}