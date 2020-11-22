#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int lectura;

	Employee* pEmployee;
	char auxId[256];
	char auxNombre[256];
	char auxHorasTrabajadas[256];
	char auxSueldo[256];

	do
	{
		lectura = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",
				auxId,
				auxNombre,
				auxHorasTrabajadas,
				auxSueldo);

		if(lectura == 4)
		{
			pEmployee = employee_newParamTxt(auxId,
					auxNombre,
					auxHorasTrabajadas,
					auxSueldo);

			if(pEmployee != NULL)
			{
				ll_add(pArrayListEmployee, pEmployee);
				retorno = 0;
			}
		}
		else
		{
			break;
		}
	}while(!feof(pFile));

	return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			pEmployee = employee_new();
			if (pEmployee != NULL && fread(pEmployee, sizeof(Employee), 1, pFile) == 1)
			{
				retorno = ll_add(pArrayListEmployee, pEmployee);
			}
			else
			{
				employee_delete(pEmployee);
				break;
			}
		} while (!feof(pFile));
	}
	return retorno;
}

// Añadidos
/** \brief Exporta los datos de los empleados a un nuevo archivo .csv
 *
 * @param pFile
 * @param pArrayListEmployee
 * @return
 */
int parser_EmployeeExportToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee *pEmployee;
	int auxId;
	char auxNombre[256];
	int auxHorasTrabajadas;
	int auxSueldo;
	int len;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);

		fprintf(pFile, "ID,NOMBRE,HORAS TRABAJADAS,SUELDO\n");

		for (int i = 0; i < len; i++)
		{
			pEmployee = (Employee*) ll_get (pArrayListEmployee, i);
			if (pEmployee != NULL &&
					employee_getId(pEmployee, &auxId) == 0 &&
					employee_getNombre(pEmployee, auxNombre) == 0 &&
					employee_getHorasTrabajadas(pEmployee, &auxHorasTrabajadas) == 0 &&
					employee_getSueldo(pEmployee, &auxSueldo) == 0)
			{
				fprintf(pFile, "%d,%s,%d,%d\n",
						auxId,
						auxNombre,
						auxHorasTrabajadas,
						auxSueldo);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/** \brief Exporta los datos de los empleados a un nuevo archivo .bin
 *
 * @param pFile
 * @param pArrayListEmployee
 * @return
 */
int parser_EmployeeExportToBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;
	int len;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for (int i = 0; i < len; i++)
		{
			pEmployee = (Employee*) ll_get (pArrayListEmployee, i);
			if (pEmployee != NULL)
			{
				fwrite(pEmployee, sizeof(Employee), 1, pFile);
			}
		}
		retorno = 0;
	}
	return retorno;
}

