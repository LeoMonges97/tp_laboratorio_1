/*
 * utn.h
 *
 *  Created on: 11 sep. 2020
 *      Author: Leo
 */

#ifndef UTN_H_
#define UTN_H_
#define LIMITE_BUFFER_STRING 4096

int utn_getInt(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int minimo,int maximo);
int utn_getFloat(char* mensaje, char* mensajeError, float* pResultado,int reintentos,float minimo,float maximo);
int utn_getChar(char* mensaje, char* mensajeError, char* pResultado,int reintentos);
int utn_getString(char* mensaje,char* mensajeError,char* pResultado,int reintentos,int limite);
int utn_getRespuesta(char* pregunta);
int utn_getOpcionesTipoChar(char* mensaje,char* mensajeError,char* pResultado,int reintentos,char rangoInicial,char rangoFinal);
int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos,int limite);
int utn_normalizarNombreYApellido(char* nombre, char* apellido,char* nombreCompleto);
int utn_getCuilOrCuit(char* cuilOrCuit,int reintentos);
int utn_getAlfaNumerico(char* mensaje,char* mensajeError,char* pResultado,int reintentos,int limite);
void strupr(char* cadena);
void strlwr(char* cadena);
void pause();

#endif /* UTN_H_ */
