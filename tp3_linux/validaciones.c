/*
 * validaciones.c
 *
 *  Created on: 5 nov. 2020
 *      Author: leo
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

/**@brief esNombre(): Verifica una cadena recibida como parametro para
 *                    determinar si es un nombre valido.
 * @param char* cadena: Cadena a analizar.
 * @param int limite: Indica la cantidad de letras maxima de la cadena.
 * @return   (0)  Indica que no es un nombre valido.
 *         (0!/1) Indica que es un nombre valido.
 */
int esNombreValido(char* cadena,int limite)
{
	int respuesta = 1;
	for(int i = 0;i <= limite && cadena[i] != '\0' ;i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				cadena[i] != '.')
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}

/**@brief normalizarNombre(): Corrige la cadena agregando la primera letra en mayusculas y lo demas en minuscula.
 * @param char* nombre: Puntero al espacio de memoria donde se dejara el valor obtenido de nombre.
 * @return char* nombre (Retorna la cadena ya corregida).
 */
char normalizarNombre(char* nombre)
{
	if(nombre != NULL)
	{
		while(*nombre)
		{
			*nombre = tolower(*nombre);
			nombre++;
		}
		nombre[0] = toupper(nombre[0]);
	}
	return *nombre;
}

/**@brief myGets(): Recibe un string con limite.
 * @param char* cadena: Cadena donde dejo la informacion.
 * @param int longitud: Cuantos caracteres quiero leer.
 * @return 0
 */
int myGets(char* cadena, int longitud)
{
	__fpurge(stdin);
	fgets(cadena,longitud,stdin);
	cadena[strlen(cadena)-1] = '\0'; // Clava el '\0' en la ultima posicion que hay un '\n'
	return 0;
}

/**@brief getInt(): Verifica si la cadena ingresada es entero.
 * @param int* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @return (0) OK / (-1) Error
 */
int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[64];

	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer) == 1)
		{
			*pResultado = atoi(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

/**@brief getLong(): Verifica si la cadena ingresada es entero largo.
 * @param int* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @return (0) OK / (-1) Error
 */
int getLong(long* pResultado)
{
	int retorno = -1;
	char buffer[64];
	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer) == 1)
		{
			*pResultado = atol(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

/**@brief esNumerica(): Verifica si la cadena/buffer son solo numeros enteros.
 *                      (Se incluyen valores negativos).
 * @param char* cadena: Cadena de caracteres a ser analizada.
 * @return (1) OK / (0) Error
 */
int esNumerica(char* cadena)
{
	int retorno = 1;
	int i = 0;
	if(cadena[i] == '-')
	{
		i = 1;
	}
	for( ; cadena[i] != '\0'; i++)
	{
		if(cadena[0] == '-')
		{
			continue;
		}
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/**@brief getFloat(): Verifica si la cadena ingresada es flotante.
 * @param float* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @return (0) OK / (-1) Error
 */
int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[64];
	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esFlotante(buffer) == 1)
		{
			*pResultado = atof(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

/**@brief esFlotante(): Verifica si la cadena/buffer son solo numeros flotantes
 *                      (Se incluyen ejemplos como:
 *                       3.14 +3.14 -3.14 .314 +.314 -.314 314. +314. -314.)
 * @param char* cadena: Cadena de caracteres a ser analizada.
 * @return (1) OK / (0) Error
 */
int esFlotante(char* cadena)
{
	int retorno = 1;
	int i = 0;
	int contadorPuntos = 0; //No tiene que haber mas de 2 puntos.

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i = 0; cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

/**@brief esLetra(): Verifica si la variable es una letra.
 * @param char* caracter: Variable a verificar.
 * @return (1) OK / (0) Error
 */
int esLetra(char* caracter)
{
	int respuesta = 1;
	if((*caracter < 'a' || *caracter > 'z') &&
			(*caracter < 'A' || *caracter > 'Z'))
	{
		respuesta = 0;
	}
	return respuesta;
}

/**@brief esAlfaNumerico(): Verifica si la cadena/buffer son solo letras y numeros
 *                          (incluye tambien los espacios  y guiones).
 * @param char* cadena: Cadena de caracteres a ser analizada.
 * @return (1) OK / (0) Error
 */
int esAlfaNumerico(char* cadena, int limite)
{
	int respuesta = 1; //OK

	for(int i = 0;i <= limite && cadena[i] != '\0' ;i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				(cadena[i] < '0' || cadena[i] > '9') &&
				cadena[i] != '.' && cadena[i] != '-')
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}

/**@brief hayEspacioEnBlanco(): Verifica que no se cargue solamente un espacio (' ' o '\n')
 *                    al principio de la cadena.
 * @param char* cadena: Cadena a analizar.
 * @param int limite: Indica la cantidad de letras maxima de la cadena.
 * @return   (0)  Indica que no es fue ingresado el '\n' como unico valor.
 *         (0!/1) Indica que fue ingresado.
 */
int hayEspacioEnBlanco(char* cadena,int limite)
{
	int retorno = 0;
	for(int i = 0; i < limite; i++)
	{
		if(isspace(cadena[0]))
		{
			retorno = 1;
			break;
		}
	}
	return retorno;
}
