/*ISPC.
  Materia: Electronica Microcontrolada.
  Practicas con sistemas embebidos. Shields v1.0 
  
  Ejercicio 1.D 
  Se utiliza una pantalla oled 128x64 con el controlador SSD1306 conectada a un atmega328p, para mostrar el mensaje 
  “Es fácil el desarrollo con shields”.
  El pin scl de la pantalla se conecta con el pin scl del atmega328p.
  El pin sda de la pantalla se conecta con el pin sda del atmega328p.

  Se usan las librerias Wire.h, Adafruit_GFX.h y Adafruit_SSD1306.h
  
  

*/
#include <Arduino.h>


#include <Wire.h>			// libreria para bus I2C
#include <Adafruit_GFX.h>		// libreria generica que ayuda a la visualizacion de texto y graficos en las pantallas
#include <Adafruit_SSD1306.h>		// libreria para controlador SSD1306
 
#define ANCHO 128			// ANCHO de pantalla es 128
#define ALTO 64				// ALTO de pantalla es 64

#define OLED_RESET 4			// necesario por la libreria Adafruit_GFX.h. Es especifico para las pantallas adafruit. 
                          //Aca no lo uso porque la pantalla es generica y no tiene el pin extra de reset
Adafruit_SSD1306 oledProteus(ANCHO, ALTO, &Wire, OLED_RESET);	// crea el objeto oledProteus del tipo Adafruit_SSD1306
/*ANCHO= Ancho de la pantalla.
  ALTO= Alto de la pantalla.
  &Wire= referencia de la libreria Wire.
  OLED_RESET= No lo uso, pero es necesario.
*/

void setup() {
  
  Wire.begin();					// inicializa comunicacion por bus I2C
  oledProteus.begin(SSD1306_SWITCHCAPVCC, 0x3C);	// inicializa pantalla 
  /*SSD1306_SWITCHCAPVCC= Constante definida dentro de la libreria. Se establecer un valor de 3.3v de alimentacion para la pantalla.
    0x3C= Direccion para identificar la pantalla
  */
}
 
void loop() {
  oledProteus.clearDisplay();			// limpia pantalla
  oledProteus.setTextColor(WHITE);		// establece el color blanco para el texto (pantalla monocromo)
  oledProteus.setCursor(0, 0);			// ubica cursor en inicio de coordenadas 0,0 para comenzar a escribir.
  oledProteus.setTextSize(1);			// establece tamano de texto en 1
  oledProteus.print("Es facil"); 	// escribe en pantalla el texto
  oledProteus.setCursor(0, 10);			// ubica cursor en inicio de coordenadas 0,10 para comenzar a escribir.
  oledProteus.print("el desarrollo"); 	// escribe en pantalla el texto
  oledProteus.setCursor(0, 20);			// ubica cursor en inicio de coordenadas 0,20 para comenzar a escribir.
  oledProteus.print("con Shields");   // escribe en pantalla el texto
  oledProteus.setCursor (20, 40);		// ubica cursor en coordenas 20,40 para comenzar a escribir.
  oledProteus.setTextSize(2);			// establece tamano de texto en 2
  oledProteus.print("GRUPO 6");		// escribe valor de millis() dividido por 1000
  oledProteus.display();			// muestra en pantalla todo lo establecido anteriormente
}