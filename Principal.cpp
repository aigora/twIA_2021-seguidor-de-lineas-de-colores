
#define MAX_BUFFER 200
#define MAX_INTENTOS_READ 4
#define MS_ENTRE_INTENTOS 250
#define SI 1
#define NO 0

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "SerialClass/SerialClass.h"

// Funciones prototipo
//int menu_principal(void);
void configura(void);

void Talk_with_Arduino(Serial* Arduino);
void Send_to_hw(Serial*, char*);
int Receive_from_hw(Serial* Arduino, char* BufferEntrada);
int Send_and_Receive(Serial* Arduino, const char* msg_out, int valor_out, char* msg_in, int* valor_in);
void monitorizar_aforo(Serial*);

int main(void)
{
	Serial* Arduino;
	char puerto[] = "COM3"; //Puerto serie al que está conectado Arduino
	int opc, b;  // Opción del menú principal seleccionada

	// Tareas de configuración y carga
	configura();
	Arduino = new Serial((char*)puerto);  // Establece la conexión con Arduino

	// Bucle principal de la aplicación
	do
	{
		printf("\n1- Verde");
		printf("\n2- Rojo");
		printf("\n3- Azul");
		printf("\n4- Salida");
		printf("\n\nIntroduzca una opcion: ");
		scanf_s("%d", &opc);
		switch (opc)
		{
		case 1:
			printf("El coche seguira la linea de color verde \n");
			break;
		case 2:
			printf("El coche seguira la linea de color rojo \n");
			break;
		case 3:
			printf("El coche seguira la linea de color azul \n");
			break;
		case 4:
			printf("¿Seguro que quieres salir?  SI o NO \n");
			printf("\n 1-SI");
			printf("\n 2-NO");
			scanf_s("%d", &b);
			if (b = 1)
			{
				return 0;
			}
			else
			{
				break;
			}
			break;
		}

	} while (opc != 4);

	// Tareas de desconexión y cierre 
	return 0;
}


void configura(void)
{
	// Establece juego de caracteres castellano
	// Para que funcione hay que partir de un proyecto vacío
	// No utilice la plantilla Aplicación de consola C++
	setlocale(LC_ALL, "spanish");
}

// Ejemplo de función de intercambio de datos con Arduino
void Talk_with_Arduino(Serial* Arduino)
{
	//char BufferSalida[MAX_BUFFER];
	char BufferEntrada[MAX_BUFFER];
	int bytesReceive,numero_recibido;
	
	if (Arduino->IsConnected()) // Si hay conexión con Arduino 
	{

		// Para enviar un mensaje y obtener una respuesta se utiliza la función Send_and_Receive
		// El mensaje está formado por un texto y un entero
		// El mensaje que se recibe está formado también por un texto y un entero.
		// Parámetros de la función:
		// El primero es la referencia a Arduino
		// El segundo es el mensaje que se desea enviar
		// El tercero es un entero que complementa al mensaje que se desea enviar
		// El cuarto es el vector de char donde se recibe la respuesta
		// El quinto es la referencia donde se recibe el entero de la respuesta
		// IMPORTANTE: El mensaje de respuesta que emite Arduino  debe incluir un espacio en blanco separando respuesta de valor
		// La función devuelve un entero con los bytes recibidos. Si es cero no se ha recibido nada.

		bytesReceive = Send_and_Receive(Arduino, "GET_AFORO_MAX", -1, BufferEntrada, &numero_recibido);
		if (bytesReceive == 0)
			printf("No se ha recibido respuesta al mensaje enviado\n");
		else
			printf("Mensaje recibido %s %d\n", BufferEntrada, numero_recibido);
	}
	else
		printf("La comunicación con la plataforma hardware no es posible en este momento\n"); // Req 3
}

// Protocolo de intercambio mensajes entre Pc y platforma hardware
// Envío Mensaje valor
// Recibe Mensaje valor
		// IMPORTANTE: El mensaje de respuesta que emite Arduino  debe incluir un espacio en blanco separando respuesta de valor
// Retorna bytes de la respuesta (0 si no hay respuesta)
int Send_and_Receive(Serial* Arduino, const char* msg_out, int valor_out, char* msg_in, int* valor_in)
{
	char BufferSalida[MAX_BUFFER];
	char BufferEntrada[MAX_BUFFER];
	char* ptr;
	int bytesReceive;

	sprintf_s(BufferSalida, "%s\n%d\n", msg_out, valor_out);
	Send_to_hw(Arduino, BufferSalida);
	bytesReceive = Receive_from_hw(Arduino, BufferEntrada);
	if (bytesReceive != 0)
	{
		ptr = strpbrk(BufferEntrada, " ");
		if (ptr == NULL)
			*valor_in = -1;
		else
		{
			*valor_in = atoi(ptr);
			*ptr = '\0';
		}
		strcpy_s(msg_in, MAX_BUFFER, BufferEntrada);
	}
	return bytesReceive;
}


// Envía un mensaje a la plataforma hardware
void Send_to_hw(Serial* Arduino, char* BufferSalida)
{
	Arduino->WriteData(BufferSalida, strlen(BufferSalida));
}

//Recibe (si existe) un mensaje de la plataforma hardware
//Realiza MAX_INTENTOS_READ para evitar mensajes recortados
int Receive_from_hw(Serial* Arduino, char* BufferEntrada)
{
	int bytesRecibidos, bytesTotales = 0;
	int intentos_lectura = 0;
	char cadena[MAX_BUFFER];

	BufferEntrada[0] = '\0';
	while (intentos_lectura < MAX_INTENTOS_READ)
	{
		cadena[0] = '\0';
		bytesRecibidos = Arduino->ReadData(cadena, sizeof(char) * (MAX_BUFFER - 1));
		if (bytesRecibidos != -1)
		{
			cadena[bytesRecibidos] = '\0';
			strcat_s(BufferEntrada, MAX_BUFFER, cadena);
			bytesTotales += bytesRecibidos;
		}
		intentos_lectura++;
		Sleep(MS_ENTRE_INTENTOS);
	}
	return bytesTotales;
}