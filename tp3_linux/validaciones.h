/*
 * validaciones.h
 *
 *  Created on: 5 nov. 2020
 *      Author: leo
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

int myGets(char* cadena, int longitud);
int esNombreValido(char* cadena, int limite);
int getInt(int* pResultado);
int getLong(long* pResultado);
int esNumerica(char* cadena);
int getFloat(float* pResultado);
int esFlotante(char* cadena);
int esLetra(char* caracter);
int esAlfaNumerico(char* cadena, int limite);
char normalizarNombre(char* nombre);
int hayEspacioEnBlanco(char* cadena,int limite);

#endif /* VALIDACIONES_H_ */
