#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#define LEN_NAME 64
#define MAX_SUELDO 99999
#define MAX_HS 1000

static int controller_searchLastId(LinkedList* pArrayListEmployee);
static int controller_createNewId(LinkedList* pArrayListEmployee);
static int controller_modifyName(LinkedList* pArrayListEmployee, Employee* pEmployee);
static int controller_modifyHoursWorked(LinkedList* pArrayListEmployee, Employee* pEmployee);
static int controller_modifySalary(LinkedList* pArrayListEmployee, Employee* pEmployee);


/** \brief controller_searchLastId(): Busca y retorna el ultimo id cargado (si existe)
 * @param pArrayListEmployee
 * @return
 */
static int controller_searchLastId(LinkedList* pArrayListEmployee)
{
	Employee* pEmployee;
	int len;
	int max;
	int id = -1;

	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(int i = 0; i < len; i++)
		{
			pEmployee = ll_get(pArrayListEmployee,i);
			employee_getId(pEmployee,&id);
			if (i == 0 || id > max)
			{
				max = id;
			}
		}
		id = max;
	}
	return id;
}

/** \brief controller_createNewId(): Genera un nuevo id.
 * @param pArrayListEmployee
 * @return
 */
static int controller_createNewId(LinkedList* pArrayListEmployee)
{
	static int id = -1;
	static int esPrimeraVez = 1;

	if(pArrayListEmployee != NULL)
	{
		if(ll_isEmpty(pArrayListEmployee) == 0 && esPrimeraVez == 1)
		{
			id = controller_searchLastId(pArrayListEmployee);
			esPrimeraVez = 0;
		}
		id++;
	}
	return id;
}

/** \brief controller_modifyName(): Modifica el campo nombre.
 * @param pArrayListEmployee
 * @param pEmployee
 * @return
 */
static int controller_modifyName(LinkedList* pArrayListEmployee, Employee* pEmployee)
{
	int retorno = -1;
	char auxName[LEN_NAME];

	if(pArrayListEmployee != NULL && pEmployee != NULL)
	{
		if(utn_getNombre("\n . Ingrese el nuevo Nombre: "," [!] Error!\n", auxName, 2, LEN_NAME) == 0)
		{
			employee_setNombre(pEmployee, auxName);
			retorno = 0;
		}
	}

	return retorno;
}

/** \brief controller_modifyHoursWorked(): Modifica el campo horas trabajadas.
 * @param pArrayListEmployee
 * @param pEmployee
 * @return
 */
static int controller_modifyHoursWorked(LinkedList* pArrayListEmployee, Employee* pEmployee)
{
	int retorno = -1;
	int auxHorasTrabajadas;

	if(pArrayListEmployee != NULL && pEmployee != NULL)
	{
		if(utn_getInt("\n . Ingrese el nuevo Nombre: "," [!] Error!\n", &auxHorasTrabajadas, 2, 0, MAX_HS) == 0)
		{
			employee_setHorasTrabajadas(pEmployee, auxHorasTrabajadas);
			retorno = 0;
		}
	}

	return retorno;
}

/** \brief controller_modifySalary(): Modifica el campo salario.
 * @param pArrayListEmployee
 * @param pEmployee
 * @return
 */
static int controller_modifySalary(LinkedList* pArrayListEmployee, Employee* pEmployee)
{
	int retorno = -1;
	int auxSueldo;

	if(pArrayListEmployee != NULL && pEmployee != NULL)
	{
		if(utn_getInt("\n . Ingrese el nuevo salario: "," [!] Error!\n", &auxSueldo, 2, 0, MAX_SUELDO) == 0)
		{
			employee_setSueldo(pEmployee, auxSueldo);
			retorno = 0;
		}
	}

	return retorno;
}



/** \brief controller_findById(): Busca un id (si existe).
 *
 * @param pArrayListEmployee
 * @param id
 * @return
 */
int controller_findById(LinkedList* pArrayListEmployee, int id)
{
	int retorno = -1;
	int auxId;
	int len;

	Employee* pEmployee;

	if (pArrayListEmployee != NULL && id > 0)
	{
		len = ll_len(pArrayListEmployee);
		for (int i = 0; i < len; i++)
		{
			pEmployee = (Employee*) ll_get (pArrayListEmployee,i);
			if (pEmployee != NULL)
			{
				if(employee_getId(pEmployee, &auxId) == 0 && auxId == id)
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}

/** \brief controller_printEmployee(): Imprime un empleado
 * @param path char*
 * @param pArrayListEmployee LinkedList*
 * @param int index
 * @return int
 *
 */
int controller_printEmployee(LinkedList* pArrayListEmployee, int index)
{
	int retorno = -1;
	Employee* pEmployee;
	Employee auxEmployee;

	if(pArrayListEmployee != NULL && index >= 0)
	{
		pEmployee = (Employee*) ll_get (pArrayListEmployee,index);
		if(	pEmployee != NULL &&
				employee_getId(pEmployee, &auxEmployee.id) == 0 &&
				employee_getNombre(pEmployee, auxEmployee.nombre) == 0 &&
				employee_getHorasTrabajadas(pEmployee, &auxEmployee.horasTrabajadas) == 0 &&
				employee_getSueldo(pEmployee, &auxEmployee.sueldo) == 0)
		{
			printf("\n | %4d | %15s | %7d | $ %7d |",
					auxEmployee.id,
					auxEmployee.nombre,
					auxEmployee.horasTrabajadas,
					auxEmployee.sueldo);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int len = ll_len(pArrayListEmployee);

	if(pArrayListEmployee != NULL)
	{
		printf("\n |  ID  |       NAME      |  HS WK  |   SALARY  |\n");
		printf(" |------|-----------------|---------|-----------|");
		for(int i = 0; i < len; i++)
		{
			controller_printEmployee(pArrayListEmployee,i);
		}
	}

	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			parser_EmployeeFromText(pFile, pArrayListEmployee);
			fclose(pFile);
			retorno = 0;
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE *pFile;

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "rb");
		if (pFile != NULL)
		{
			retorno = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
			fclose(pFile);
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;
	Employee auxEmployee;

	if (pArrayListEmployee != NULL)
	{
		pEmployee = employee_new();
		if(pEmployee != NULL &&
				utn_getNombre("\n . Ingrese Nombre: "," [!] Error!\n", auxEmployee.nombre, 2, sizeof(auxEmployee.nombre)) == 0 &&
				utn_getInt(" . Ingrese HS Trabajadas: "," [!] Error!\n", &auxEmployee.horasTrabajadas, 2, 0, MAX_HS) == 0 &&
				utn_getInt(" . Ingrese Sueldo: "," [!] Error!\n", &auxEmployee.sueldo, 2, 0, MAX_SUELDO) == 0)
		{
			auxEmployee.id = controller_createNewId(pArrayListEmployee);
			if (auxEmployee.id > 0 &&
					employee_setNombre(pEmployee, auxEmployee.nombre) == 0 &&
					employee_setHorasTrabajadas(pEmployee, auxEmployee.horasTrabajadas) == 0 &&
					employee_setSueldo(pEmployee, auxEmployee.sueldo) == 0 &&
					employee_setId(pEmployee,auxEmployee.id) == 0)
			{
				ll_add(pArrayListEmployee, pEmployee);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;
	int idAbuscar;
	int indice;
	int opcionSeleccion;
	int opcionModificacion;

	if (pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getInt("\n\n . Ingrese ID a modificar: "," [!] Error!\n", &idAbuscar, 2, 1, 9999) == 0)
		{
			indice = controller_findById(pArrayListEmployee, idAbuscar);
			if(indice > 0)
			{
				printf("\n . Dato seleccionado:\n");
				printf("\n |  ID  |       NAME      |  HS WK  |   SALARY  |\n");
				printf(" |------|-----------------|---------|-----------|");
				controller_printEmployee(pArrayListEmployee, indice);
				if(utn_getInt("\n\n ~ Desea modificar los datos de este ID?\n\n"
						" 1. Si\n"
						" 2. No\n"
						"\n > Ingrese la opcion: "," [!] Error!\n", &opcionSeleccion, 2, 1, 2) == 0)
				{
					if(opcionSeleccion == 1)
					{
						pEmployee = (Employee*) ll_get (pArrayListEmployee, indice);
						do
						{
							if(utn_getInt("\n\n ~ Elija el campo a modificar:\n\n"
									" 1. Nombre\n"
									" 2. Horas Trabajadas\n"
									" 3. Sueldo\n"
									" 4. Salir\n"
									"\n > Ingrese la opcion: "," [!] Error!\n", &opcionModificacion, 2, 1, 4) == 0)
							{
								switch(opcionModificacion)
								{
								case 1:
									if(controller_modifyName(pArrayListEmployee, pEmployee) == 0)
									{
										printf(" . Nombre modificado con exito!");
									}
									break;
								case 2:
									if(controller_modifyHoursWorked(pArrayListEmployee, pEmployee) == 0)
									{
										printf(" . Horas trabajadas modificado con exito!");
									}
									break;
								case 3:
									if(controller_modifySalary(pArrayListEmployee, pEmployee) == 0)
									{
										printf(" . Sueldo modificado con exito!");
									}
									break;
								case 4:
									retorno = 2;
									break;
								}
							}
						}while(opcionModificacion != 4);
					}
					else
					{
						retorno = 1;
					}
				}
			}
		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;
	int idAbuscar;
	int indice;
	int opcionSeleccion;

	if (pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getInt("\n\n . Ingrese ID a eliminar: "," [!] Error!\n", &idAbuscar, 2, 1, 1000) == 0)
		{
			indice = controller_findById(pArrayListEmployee, idAbuscar);
			if(indice > 0)
			{
				printf("\n . Dato seleccionado:\n");
				printf("\n |  ID  |       NAME      |  HS WK  |   SALARY  |\n");
				printf(" |------|-----------------|---------|-----------|");
				controller_printEmployee(pArrayListEmployee, indice);
				if(utn_getInt("\n\n ~ Desea eliminar los datos de este ID?\n\n"
						" 1. Si\n"
						" 2. No\n"
						"\n > Ingrese la opcion: "," [!] Error!\n", &opcionSeleccion, 2, 1, 2) == 0)
				{
					if(opcionSeleccion == 1)
					{
						pEmployee = (Employee*) ll_get (pArrayListEmployee, indice);
						employee_delete(pEmployee);
						retorno = ll_remove(pArrayListEmployee,indice);
					}
					else
					{
						retorno = 1;
					}
				}
			}
		}
	}
	return retorno;
}

/** \brief controller_menuSort(): Realiza ordenamientos seleccionado el campo a elegir.
 *
 * @param pArrayListEmployee
 * @return
 */
int controller_menuSort(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int opcion;
	int orden;

	if(pArrayListEmployee != NULL)
	{
		do {
			if(utn_getInt(" ~ Elija que campo quiere ordenar:\n\n"
					" 1. Id\n"
					" 2. Nombre\n"
					" 3. Horas Trabajadas\n"
					" 4. Sueldo\n"
					" 5. Salir\n\n"
					" > Ingrese la opcion: "
					, " [!] Error!\n", &opcion, 2, 1, 5) == 0)
			{
				switch(opcion)
				{
				case 1:
					if(utn_getInt(" ~ Que tipo de ordenamiento?\n\n"
							" 1. Ascendete\n"
							" 0. Descendete\n\n"
							" > Ingrese la opcion: "
							, " [!] Error!\n", &orden, 2, 0, 1) == 0)
					{
						printf("\n . Aguarde un momento, se esta realizando el ordenamiento por id...\n");
						ll_sort(pArrayListEmployee, employee_sortForId, orden);
						retorno = 0;
					}
					break;
				case 2:
					if(utn_getInt(" ~ Que tipo de ordenamiento?\n\n"
							" 1. Ascendete\n"
							" 0. Descendete\n\n"
							" > Ingrese la opcion: "
							, " [!] Error!\n", &orden, 2, 0, 1) == 0)
					{
						printf("\n . Aguarde un momento, se esta realizando el ordenamiento por nombre...\n");
						ll_sort(pArrayListEmployee, employee_sortForName, orden);
						retorno = 0;
					}
					break;
				case 3:
					if(utn_getInt(" ~ Que tipo de ordenamiento?\n\n"
							" 1. Ascendete\n"
							" 0. Descendete\n\n"
							" > Ingrese la opcion: "
							, " [!] Error!\n", &orden, 2, 0, 1) == 0)
					{
						printf("\n . Aguarde un momento, se esta realizando el ordenamiento por horas trabajadas...\n");
						ll_sort(pArrayListEmployee, employee_sortForHoursWorked, orden);
						retorno = 0;
					}
					break;
				case 4:
					if(utn_getInt(" ~ Que tipo de ordenamiento?\n\n"
							" 1. Ascendete\n"
							" 0. Descendete\n\n"
							" > Ingrese la opcion: "
							, " [!] Error!\n", &orden, 2, 0, 1) == 0)
					{
						printf("\n . Aguarde un momento, se esta realizando el ordenamiento por salario...\n");
						ll_sort(pArrayListEmployee, employee_sortForSalary, orden);
						retorno = 0;
					}
					break;
				case 5:
					retorno = 1;
					break;
				}
			}
		} while (opcion != 5);
	}
	return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pArrayListEmployee != NULL)
	{
		if(controller_menuSort(pArrayListEmployee) == 0)
		{
			retorno = 0;
		}
		else
		{
			retorno = 1;
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE *pFile;

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "w");
		if (pFile != NULL)
		{
			retorno = parser_EmployeeExportToText(pFile, pArrayListEmployee);
			fclose(pFile);
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE *pFile;

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "wb");
		if (pFile != NULL)
		{
			retorno = parser_EmployeeExportToBinary(pFile, pArrayListEmployee);
			fclose(pFile);
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}




