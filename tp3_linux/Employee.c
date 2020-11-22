
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "Employee.h"
#include "validaciones.h"
#define SIZE_AUX 64

static int isValidId(int id);
static int isValidNombre(char* nombre);
static int isValidHorasTrabajadas(int horasTrabajadas);
static int isValidSueldo(int sueldo);

/** \brief isValidId(): Valida el atributo id de la entidad Employee.
 * @param int sueldo: campo id de la entidad Employee a validar.
 * @return (1) OK || (0) Error
 */
static int isValidId(int id)
{
	int retorno = 0;
	char auxId[SIZE_AUX];
	if(id > 0)
	{
		snprintf(auxId,SIZE_AUX,"%d",id);
		if(esNumerica(auxId) == 1)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/** \brief isValidNombre(): Valida el atributo nombre de la entidad Employee.
 * @param int sueldo: campo nombre de la entidad Employee a validar.
 * @return (1) OK || (0) Error
 */
static int isValidNombre(char* nombre)
{
	int retorno = 0;
	if(nombre != NULL)
	{
		if(esNombreValido(nombre,SIZE_AUX) == 1)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/** \brief isValidHorasTrabajadas(): Valida el atributo horasTrabajadas de la entidad Employee.
 * @param int sueldo: campo horasTrabajadas de la entidad Employee a validar.
 * @return (1) OK || (0) Error
 */
static int isValidHorasTrabajadas(int horasTrabajadas)
{
	int retorno = 0;
	char auxHorasTrabajadas[SIZE_AUX];
	if(auxHorasTrabajadas > 0)
	{
		snprintf(auxHorasTrabajadas,SIZE_AUX,"%d",horasTrabajadas);
		if(esNumerica(auxHorasTrabajadas) == 1)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/** \brief isValidSueldo(): Valida el atributo sueldo de la entidad Employee.
 * @param int sueldo: campo sueldo de la entidad Employee a validar.
 * @return (1) OK || (0) Error
 */
static int isValidSueldo(int sueldo)
{
	int retorno = 0;
	char auxSueldo[SIZE_AUX];
	if(sueldo > 0)
	{
		snprintf(auxSueldo,SIZE_AUX,"%d",sueldo);
		if(esNumerica(auxSueldo) == 1)
		{
			retorno = 1;
		}
	}
	return retorno;
}

// ***************************************************************************************************************************************************//
// Contructor & Destructor

/** \brief employee_new(): Reserva memoria dinámica para un elemento de la entidad Employee.
 * @return el puntero de la entidad Employee que se construyo.
 */
Employee* employee_new(void)
{
	return (Employee*) malloc (sizeof(Employee));
}

/** \brief employee_newParam(): Reserva memoria dinámica para un elemento de la entidad Employee y
 *        dando valores iniciales a los campos de dicha entidad.
 * @param int id: campo id de la entidad Employee.
 * @param char* nombre: campo nombre de la entidad Employee.
 * @param int horasTrabajadas: campo horasTrabajadas de la entidad Employee.
 * @param int sueldo: campo sueldo de la entidad Employee.
 * @return el puntero de la entidad Employee que se construyo || NULL en caso de no realizarlo.
 */
Employee* employee_newParam(int id, char* nombre, int horasTrabajadas, int sueldo)
{
	Employee* this = employee_new();
	if(this != NULL)
	{
		if(
				!(employee_setId(this, id)) &&
				!(employee_setNombre(this, nombre)) &&
				!(employee_setHorasTrabajadas(this, horasTrabajadas)) &&
				!(employee_setSueldo(this, sueldo))
		)
		{
			return this;
		}
	}
	return NULL;
}

/** \brief employee_newParamTxt(): Reserva memoria dinámica para un elemento de la entidad Employee y
 *        dando valores iniciales a los campos de dicha entidad (mejor acceso a archivos de texto).
 * @param char* id: campo id de la entidad Employee.
 * @param char* nombre: campo nombre de la entidad Employee.
 * @param char* horasTrabajadas: campo horasTrabajadas de la entidad Employee.
 * @param char* sueldo: campo sueldo de la entidad Employee.
 * @return el puntero de la entidad Employee que se construyo || NULL en caso de no realizarlo.
 */
Employee* employee_newParamTxt(char* id, char* nombre, char* horasTrabajadas, char* sueldo)
{
	//return employee_newParam(atoi(id), nombre, atoi(horasTrabajadas), atoi(sueldo));
	Employee* this = employee_new();

	if(this != NULL &&
			id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		if(
				employee_setIdTxt(this, id) == -1 ||
				employee_setNombre(this, nombre) == -1 ||
				employee_setHorasTrabajadasTxt(this, horasTrabajadas) == -1 ||
				employee_setSueldoTxt(this, sueldo) == -1
		)
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
}

/** \brief employee_delete(): Libera la memoria previamente reservada.
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

// ***************************************************************************************************************************************************//
// Set & Get del atributo: id

/** \brief employee_setIdTxt(): Permite asignar un valor validado al campo id de la entidad Employee (mejor acceso a archivos de texto).
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo id.
 * @param char* id: Es el valor del atributo id (como cadena de carateres) que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setIdTxt(Employee* this, char* id)
{
	int retorno = -1;
	if(this != NULL  && id != NULL)
	{
		if(esNumerica(id))
		{
			this->id = atoi(id);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief employee_getIdTxt(): Permite obtener/acceder al valor del atributo id de la entidad Employee (mejor acceso a archivos de texto).
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo id.
 * @param char* id: Es el puntero a ser utilizado para retornar el valor del atributo id.
 * @return (0) OK / (-1) Error
 */
int employee_getIdTxt(Employee* this, char* id)
{
	int retorno = -1;
	if(this != NULL  && id != NULL)
	{
		retorno = 0;
		snprintf(id,(int)sizeof(this->id),"%d",this->id);
	}
	return retorno;
}

/** \brief employee_setId(): Permite asignar un valor validado a un campo de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo id.
 * @param int id: Es el valor del atributo id que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setId(Employee* this, int id)
{
	int retorno = -1;
	if(this != NULL  && id > 0)
	{
		if(isValidId(id))
		{
			this->id = id;
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief employee_getId(): Permite obtener/acceder al valor del atributo id de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo id.
 * @param int id: Es el puntero a ser utilizado para retornar el valor del atributo id.
 * @return (0) OK / (-1) Error
 */
int employee_getId(Employee* this, int* id)
{
	int retorno = -1;
	if(this != NULL  && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

// ***************************************************************************************************************************************************//
// Set & Get del atributo: nombre

/** \brief employee_setNombre(): Permite asignar un valor validado a un campo de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo nombre.
 * @param char* nombre: Es el valor del atributo nombre que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setNombre(Employee* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(isValidNombre(nombre))
		{
			strncpy(this->nombre,nombre,(int)sizeof(this->nombre));
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief employee_getNombre(): Permite obtener/acceder al valor del atributo nombre de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo nombre.
 * @param char* nombre: Es el puntero a ser utilizado para retornar el valor del atributo nombre.
 * @return (0) OK / (-1) Error
 */
int employee_getNombre(Employee* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL  && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre,this->nombre,(int)sizeof(this->nombre));
	}
	return retorno;
}

// ***************************************************************************************************************************************************//
// Set & Get del atributo: horasTrabajadas

/** \brief employee_setHorasTrabajadasTxt(): Permite asignar un valor validado al campo horasTrabajadas de la entidad Employee (mejor acceso a archivos de texto).
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo horasTrabajadas.
 * @param char* horasTrabajadas: Es el valor del atributo horasTrabajadas (como cadena de carateres) que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL  && horasTrabajadas != NULL)
	{
		if(esNumerica(horasTrabajadas))
		{
			this->horasTrabajadas = atoi(horasTrabajadas);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief employee_getHorasTrabajadasTxt(): Permite obtener/acceder al valor del atributo horasTrabajadas de la entidad Employee (mejor acceso a archivos de texto).
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo horasTrabajadas.
 * @param char* horasTrabajadas: Es el puntero a ser utilizado para retornar el valor del atributo horasTrabajadas.
 * @return (0) OK / (-1) Error
 */
int employee_getHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL  && horasTrabajadas != NULL)
	{
		retorno = 0;
		snprintf(horasTrabajadas,(int)sizeof(this->horasTrabajadas),"%d",this->horasTrabajadas);
	}
	return retorno;
}

/** \brief employee_setHorasTrabajadas(): Permite asignar un valor validado al campo horasTrabajadas de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo horasTrabajadas.
 * @param int horasTrabajadas: Es el valor del atributo horasTrabajadas que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL  && isValidHorasTrabajadas(horasTrabajadas))
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

/** \brief employee_getHorasTrabajadas(): Permite obtener/acceder al valor del atributo horasTrabajadas de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo horasTrabajadas.
 * @param int id: Es el puntero a ser utilizado para retornar el valor del atributo horasTrabajadas.
 * @return (0) OK / (-1) Error
 */
int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL  && horasTrabajadas != NULL)
	{
		retorno = 0;
		*horasTrabajadas = this->horasTrabajadas;
	}
	return retorno;
}

// ***************************************************************************************************************************************************//
// Set & Get del atributo: sueldo

/** \brief employee_setSueldoTxt(): Permite asignar un valor validado al campo sueldo de la entidad Employee (mejor acceso a archivos de texto).
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo sueldo.
 * @param char* sueldo: Es el valor del atributo sueldo (como cadena de carateres) que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setSueldoTxt(Employee* this, char* sueldo)
{
	int retorno = -1;
	if(this != NULL  && sueldo != NULL)
	{
		if(esNumerica(sueldo))
		{
			this->sueldo = atoi(sueldo);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief employee_getSueldo(): Permite obtener/acceder al valor del atributo sueldo de la entidad Employee (mejor acceso a archivos de texto).
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo sueldo.
 * @param char* sueldo: Es el puntero a ser utilizado para retornar el valor del atributo sueldo.
 * @return (0) OK / (-1) Error
 */
int employee_getSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL  && sueldo != NULL)
	{
		retorno = 0;
		snprintf(sueldo,(int)sizeof(this->sueldo),"%d",this->sueldo);
	}
	return retorno;
}

/** \brief employee_setSueldo(): Permite asignar un valor validado al campo sueldo de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea setear el atributo sueldo.
 * @param int sueldo: Es el valor del atributo sueldo que se desea setear.
 * @return (0) OK / (-1) Error
 */
int employee_setSueldo(Employee* this, int sueldo)
{
	int retorno = -1;
	if(this != NULL  && sueldo > 0)
	{
		if(isValidSueldo(sueldo))
		{
			this->sueldo = sueldo;
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief employee_getSueldo(): Permite obtener/acceder al valor del atributo sueldo de la entidad Employee.
 * @param Employee* this: El puntero al elemento de la entidad Employee al que se le desea leer el atributo sueldo.
 * @param int* sueldo: Es el puntero a ser utilizado para retornar el valor del atributo sueldo.
 * @return (0) OK / (-1) Error
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL  && sueldo != NULL)
	{
		retorno = 0;
		*sueldo = this->sueldo;
	}
	return retorno;
}

// ***************************************************************************************************************************************************//
// Funciones de ordenamiento

/** \brief employee_sortForId(): Realiza el ordenamiento para el campo id
 *
 * @param firstEmployee
 * @param secondEmployee
 * @return
 */
int employee_sortForId(void* firstEmployee, void* secondEmployee)
{
	int retorno = 0;
	int primerId;
	int segundoId;

	employee_getId(firstEmployee, &primerId);
	employee_getId(secondEmployee, &segundoId);

	if(primerId > segundoId)
	{
		retorno = 1;
	}
	else if(primerId < segundoId)
	{
		retorno = -1;
	}

	return retorno;
}

/** \brief employee_sortForName(): Realiza el ordenamiento para el campo nombre
 *
 * @param firstEmployee
 * @param secondEmployee
 * @return
 */
int employee_sortForName(void* firstEmployee, void* secondEmployee)
{
	int retorno = 0;
	char firstName[256];
	char secondName[256];

	employee_getNombre(firstEmployee, firstName);
	employee_getNombre(secondEmployee, secondName);

	if(strcasecmp(firstName, secondName) > 0) //el primero es mayor
	{
		retorno = 1;
	}
	else if(strcasecmp(firstName, secondName) < 0) // el primero es menor
	{
		retorno = -1;
	}

	return retorno;
}

/** \brief employee_sortForHoursWorked(): Realiza el ordenamiento para el campo horas trabajadas
 *
 * @param firstEmployee
 * @param secondEmployee
 * @return
 */
int employee_sortForHoursWorked(void* firstEmployee, void* secondEmployee)
{
	int retorno = 0;
	int primerHs;
	int segundoHs;

	employee_getHorasTrabajadas(firstEmployee, &primerHs);
	employee_getHorasTrabajadas(secondEmployee, &segundoHs);

	if(primerHs > segundoHs)
	{
		retorno = 1;
	}
	else if(primerHs < segundoHs)
	{
		retorno = -1;
	}

	return retorno;
}

/** \brief employee_sortForSalary(): Realiza el ordenamiento para el campo salario
 *
 * @param firstEmployee
 * @param secondEmployee
 * @return
 */
int employee_sortForSalary(void* firstEmployee, void* secondEmployee)
{
	int retorno = 0;
	int primerSalario;
	int segundoSalario;

	employee_getSueldo(firstEmployee, &primerSalario);
	employee_getSueldo(secondEmployee, &segundoSalario);

	if(primerSalario > segundoSalario)
	{
		retorno = 1;
	}
	else if(primerSalario < segundoSalario)
	{
		retorno = -1;
	}

	return retorno;
}
