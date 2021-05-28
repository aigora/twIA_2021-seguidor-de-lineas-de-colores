// Referencas a Bibliotecas
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Enumeraciones que facilitan la lectura del código

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// Variables globales

int ENA = 5; 
int IN1 = 2;
int IN2 = 3;

int IN3 = 7;
int IN4 = 8;
int ENB = 9;


void setup()
{ 
 // Tareas de configuración 
  Serial.begin(9600);
   /* Declaramos todos los pines como salidas
pinMode (ENA, OUTPUT);
pinMode (IN1, OUTPUT);
pinMode (IN2, OUTPUT);*/

pinMode (ENB, OUTPUT);
pinMode (IN3, OUTPUT);
pinMode (IN4, OUTPUT);

 Serial.begin(9600);
  
  if (!tcs.begin()) 
  {
    Serial.println("Error al iniciar TCS34725");
    while (1) delay(1000);
  }
}

void loop()
{
    
  if (Serial.available() > 0)  // Si hay mensajes procedentes del PC  
    procesar_mensaje();
	
   // Resto de acciones 
    //Direccion motor 1 y 2
digitalWrite (IN1,LOW);
digitalWrite (IN2, HIGH);
analogWrite (ENA, 100); //Velocidad motor 1
/*
digitalWrite (IN3, LOW);
digitalWrite (IN4, HIGH);
analogWrite (ENB, 200); //Velocidad motor 2*/


  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  Serial.print("Temperatura color: "); Serial.print(colorTemp, DEC); Serial.println(" K");
  Serial.print("Lux : "); Serial.println(lux, DEC);
  Serial.print("Rojo: "); Serial.println(r, DEC);
  Serial.print("Verde: "); Serial.println(g, DEC);
  Serial.print("Azul: "); Serial.println(b, DEC);
  Serial.print("Clear: "); Serial.println(c, DEC);
  Serial.println(" ");
  delay(1000);
  
}
void procesar_mensaje(void)
{
  int numero;
  String cadena = Serial.readStringUntil('\n'); // Lee mensaje
  String valor = Serial.readStringUntil('\n');  // Lee valor
  numero = valor.toInt();  // Transforma valor a entero
  
  if (cadena.equals("")) // Entre las comillas se pone el texto del mensaje que se espera  
    {
        // Acciones asociadas a ese mensaje
		// Si se desea responer a este mensaje 
		// Serial.println("Respuesta_acabada_en_un_espacio_en_blanco ");
		// Serial.println(valor_entero);
    }
	else
	 if (cadena.equals("")) // Y así sucesivamente con todos los posibles mensajes
	  {
	  }
}
