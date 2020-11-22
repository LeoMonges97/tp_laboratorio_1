
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
#define OPCION 10

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
 *****************************************************/

int main()
{
	int option;
	int testing;
	int flagArchivoCargado = 0;

	LinkedList* listaEmpleados = ll_newLinkedList();

	do{
		utn_getInt("\n\n ********* TP3 - 1H (Leonel Monges) *********\n\n"
				" ~ Menu:\n\n"
				" 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
				" 2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n"
				" 3. Alta de empleado.\n"
				" 4. Modificar datos de empleado.\n"
				" 5. Baja de empleado.\n"
				" 6. Listar empleados.\n"
				" 7. Ordenar empleados.\n"
				" 8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
				" 9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n"
				" 10. Salir.\n\n"
				" ~ Ingrese la opcion a elegir: ","\n [!] Error!\n",&option,2,1,OPCION);
		switch(option)
		{
		case 1:
			testing = controller_loadFromText("data.csv",listaEmpleados);
			if(testing == 0)
			{
				flagArchivoCargado = 1;
				printf("\n . Datos cargados correctamente!\n");
			}
			else if(testing == -1)
			{
				printf("\n [!] Error! No se pudo cargar el archivo!\n");
			}
			else
			{
				printf("\n [!] Error! El archivo no existe!\n");
			}
			break;
		case 2:
			testing = controller_loadFromBinary("data.bin",listaEmpleados);
			if(testing == 0)
			{
				flagArchivoCargado = 1;
				printf("\n . Datos cargados correctamente!\n");
			}
			else if(testing == -1)
			{
				printf("\n [!] Error! No se pudo cargar el archivo!\n");
			}
			else
			{
				printf("\n [!] Error! El archivo no existe!\n");
			}
			break;
		case 3:
			if(flagArchivoCargado == 1)
			{
				testing = controller_addEmployee(listaEmpleados);
				if(testing == 0)
				{
					printf("\n . Datos añadidos correctamente!\n");
				}
				else
				{
					printf("\n [!] Error! No se pudo guardar los datos del nuevo empleado!");
				}
			}
			else
			{
				printf("\n [!] Warning! Primero cargue el archivo...\n");
			}
			break;
		case 4:
			if(flagArchivoCargado == 1)
			{
				testing = controller_editEmployee(listaEmpleados);
				if(testing == 0)
				{
					printf("\n . Datos modificado correctamente!\n");
				}
				else if(testing == -1)
				{
					printf("\n [!] Error! No se pudo guardar los datos de la modificacion!");
				}
				else if(testing == 1)
				{
					printf("\n . Ok! Datos sin tocar!");

				}
				else
				{
					printf("\n . Ok! Volviendo al menu...");
				}
			}
			else
			{
				printf("\n [!] Warning! Primero cargue el archivo...\n");
			}
			break;
		case 5:
			if(flagArchivoCargado == 1)
			{
				testing = controller_removeEmployee(listaEmpleados);
				if(testing == 0)
				{
					printf("\n . Datos eliminados correctamente!\n");
				}
				else if(testing == -1)
				{
					printf("\n [!] Error! No se pudo eliminar los datos!");
				}
				else
				{
					printf("\n . Ok! Dato salvado/sin borrar!");
				}
			}
			else
			{
				printf("\n [!] Warning! Primero cargue el archivo...\n");
			}
			break;
		case 6:
			if(flagArchivoCargado == 1)
			{
				controller_ListEmployee(listaEmpleados);
			}
			else
			{
				printf("\n [!] No hay datos para mostrar! Primero cargue el archivo...\n");
			}
			break;
		case 7:
			if(flagArchivoCargado == 1)
			{
				testing = controller_sortEmployee(listaEmpleados);
				if(testing == 0)
				{
					printf("\n . Datos ordenados correctamente!\n");
				}
				else if(testing == -1)
				{
					printf("\n [!] Error! No se pudo ordenar los datos\n");
				}
				else
				{
					printf("\n Ok! Datos sin ordenar\n");
				}
			}
			else
			{
				printf("\n [!] Warning! Primero cargue el archivo...\n");
			}
			break;
		case 8:
			if(flagArchivoCargado == 1)
			{
				testing = controller_saveAsText("data(modified).csv",listaEmpleados);
				if(testing == 0)
				{
					printf("\n . Datos guardados en nuevo archivo!\n");
				}
				else if(testing == -1)
				{
					printf("\n [!] Error! No se pudo guardar los datos!\n");
				}
				else
				{
					printf("\n [!] Error! No existen los datos!\n");
				}
			}
			else
			{
				printf("\n [!] Warning! Primero cargue el archivo...\n");
			}
			break;
		case 9:
			if(flagArchivoCargado == 1)
			{
				testing = controller_saveAsBinary("data.bin",listaEmpleados);
				if(testing == 0)
				{
					printf("\n . Datos guardados en un nuevo archivo binario!\n");
				}
				else if(testing == -1)
				{
					printf("\n [!] Error! No se pudo guardar los datos!\n");
				}
				else
				{
					printf("\n [!] Error! No existen los datos!\n");
				}
			}
			else
			{
				printf("\n [!] Warning! Primero cargue el archivo...\n");
			}
			break;
		}
	}while(option != OPCION);

	return 0;
}

