/*
 * employee.c
 *
 *  Created on: 25 sep. 2020
 *      Author: leo
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "arrayEmployee.h"

#define LEN_ARRAY_EMPLOYEE 10

static int searchFreePosition (Employee* list, int len, int *pIndex);
static int generateNewId(void);

/**Added static function
 * @brief: Looks for a free space and returns it that index in a variable of type pointer.
 * @param list
 * @param len
 * @param pIndex
 * @return int Return (-1) if Error
 * [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
static int searchFreePosition(Employee* list, int len, int *pIndex)
{
	int answer = -1;
	if(list != NULL && pIndex != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				*pIndex = i;
				answer = 0;
				break;
			}
		}
	}
	return answer;
}

/**Added static function
 * @brief: the function generates the ids for each employee.
 * @return id
 */
static int generateNewId(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}

/**Added function
 * @brief: Verifies if the data is entered correctly to register in addEmployee().
 * @param id
 * @param name
 * @param lastName
 * @param salary
 * @param sector
 * @return int Return (-1) if Error
 * [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int areDataReceived(int* id, char name[], char lastName[], float* salary, int* sector)
{
	int answer = FALSE;
	char auxName[LEN_NAME];
	char auxLastName[LEN_NAME];
	float auxSalary;
	int auxSector;
	int auxId = generateNewId();

	if(id != NULL && name != NULL && lastName != NULL && salary != NULL && sector != NULL)
	{
		if(utn_getNombre("\n . Name: ","\n > Error!",auxName,2,LEN_NAME) == 0 &&
				utn_getNombre("\n . Last Name: ","\n > Error!",auxLastName,2,LEN_NAME) == 0 &&
				utn_getFloat("\n . Salary: ","\n > Error!",&auxSalary,2,MIN_SALARY,MAX_SALARY) == 0 &&
				utn_getInt("\n . Sector: ","\n > Error!",&auxSector,2,MIN_SECTOR,MAX_SECTOR) == 0
		)
		{
			*id = auxId;
			strncpy(name,auxName,LEN_NAME);
			strncpy(lastName,auxLastName,LEN_NAME);
			*salary = auxSalary;
			*sector = auxSector;
			answer = TRUE;
		}
	}
	return answer;
}

/**
 * ABM options menu function
 */
void mainEmployee()
{
	char option;
	Employee listEmployee[LEN_ARRAY_EMPLOYEE];

	int auxId;
	char auxName[LEN_NAME];
	char auxLastName[LEN_NAME];
	float auxSalary;
	int auxSector;
	int dataCounter = 0;

	initEmployees(listEmployee,LEN_ARRAY_EMPLOYEE);
	do
	{
		utn_getChar(" \n *********************\n TP2 - ABM\n\n a) Add employee\n b) Modify employee\n c) Remove employee\n d) Sort list or Find average salary of employees\n e) Print loaded employees\n f) Exit\n\n ~ Enter option: ",
				" > Error!\n",&option,2,'a','f');
		switch(option)
		{
		case 'a':
			if(areDataReceived(&auxId, auxName, auxLastName, &auxSalary, &auxSector) == TRUE)
			{
				if(addEmployee(listEmployee, LEN_ARRAY_EMPLOYEE, auxId, auxName, auxLastName, auxSalary, auxSector) == 0)
				{
					printf("\n Data loaded successfully!\n");
					dataCounter++;
				}
				else
				{
					printf(" Error! ");
				}
			}
			break;
		case 'b':
			if(dataCounter >= 1)
			{
				if(modifyEmployee(listEmployee, LEN_ARRAY_EMPLOYEE) == 0)
				{
					printf("\n Data modified successfully!\n");
				}
				else
				{
					printf(" Error! ");
				}
			}
			else
			{
				printf(" Error! You have to save at least one employee\n");
			}
			break;
		case 'c':
			if(dataCounter >= 1)
			{
				if(removeEmployee(listEmployee, LEN_ARRAY_EMPLOYEE,auxId) == 0)
				{
					printf("\n Data deleted successfully!\n");
				}
				else
				{
					printf(" Error! ");
				}
			}
			else
			{
				printf(" Error! You have to save at least one employee\n");
			}
			break;
		case 'd':
			if(dataCounter >= 2)
			{
				if(employeeReports(listEmployee, LEN_ARRAY_EMPLOYEE) == 0)
				{
					printf("data updated successfully!\n");
				}
				else
				{
					printf(" Error! Data reading error!");
				}
			}
			else
			{
				printf(" Error! There must be at least 2 or more employees saved\n");
			}
			break;
		case 'e':
			if(dataCounter >= 1)
			{
				printEmployees(listEmployee, LEN_ARRAY_EMPLOYEE);
			}
			else
			{
				printf(" The employee list is empty!\n");
			}
			break;
		}
	}while(option != 'f');
}

/**
 * @brief: To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array.
 * @param list list Employee* Pointer to array of employees.
 * @param len int Array length.
 * @return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok.
 */
int initEmployees(Employee* list, int len)
{
	int answer = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0; i < len; i++)
		{
			list[i].isEmpty = TRUE;
		}
		answer = 0;
	}
	return answer;
}

/**
 * @brief: Add in a existing list of employees the values received as parameters
 * in the first empty position.
 * @param list
 * @param len
 * @param id
 * @param name
 * @param lastName
 * @param salary
 * @param sector
 * @return int Return (-1) if Error
 * [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int answer = -1;
	int index;
	Employee buffer;

	if(list != NULL && len > 0 && id >= 0 && name != NULL && lastName != NULL)
	{
		if(searchFreePosition(list,len, &index) == 0)
		{
			buffer.id = id;
			strncpy(buffer.name,name,LEN_NAME);
			strncpy(buffer.lastName,lastName,LEN_NAME);
			buffer.salary = salary;
			buffer.sector = sector;
			list[index] = buffer;
			list[index].isEmpty = FALSE;
			answer = 0;
		}
		else
		{
			printf("\n Sorry, there are no more free positions\n");
		}
	}
	return answer;
}

/** Added function
 * @brief Modify the data only if the index corresponds to a NO Empty.
 * @param list Employee*
 * @param len
 * @return Return (-1) if Error
 * [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int modifyEmployee(Employee* list, int len)
{
	int answer = -1;
	int idModify;
	int index;
	int option;
	Employee buffer;

	if(list != NULL && len > 0)
	{
		printf("\n           ******** List of loaded employees ********\n");
		printEmployees(list,len);

		if(utn_getInt("\n . Enter the ID to modify: "," Error!", &idModify,5,1,1000) == 0)
		{
			index = findEmployeeById(list,len,idModify);
			if(index >= 0)
			{
				if(utn_getInt("\n ~ Select the option:\n 1. Name\n 2. Last name\n 3. Salary\n 4. Sector\n 5. All data\n\n > Option: "," Error!", &option, 2, 1, 5) == 0)
				{
					switch(option)
					{
					case 1: // name
						if(utn_getNombre(" Write the new name: "," Error!",buffer.name,2,LEN_NAME) == 0)
						{
							buffer.id = list[index].id;
							strncpy(buffer.lastName,list[index].lastName,LEN_NAME);
							buffer.salary = list[index].salary;
							buffer.sector = list[index].sector;
							list[index] = buffer;
							list[index].isEmpty = FALSE;
							answer = 0;
						}
						break;
					case 2: // last name
						if(utn_getNombre(" Write the new last name: "," Error!",buffer.lastName,2,LEN_NAME) == 0)
						{
							buffer.id = list[index].id;
							strncpy(buffer.name,list[index].name,LEN_NAME);
							buffer.salary = list[index].salary;
							buffer.sector = list[index].sector;
							list[index] = buffer;
							list[index].isEmpty = FALSE;
							answer = 0;
						}
						break;
					case 3: // salary
						if(utn_getFloat(" Write the new salary: "," Error!",&(buffer.salary),2,MIN_SALARY,MAX_SALARY) == 0)
						{
							buffer.id = list[index].id;
							strncpy(buffer.name,list[index].name,LEN_NAME);
							strncpy(buffer.lastName,list[index].lastName,LEN_NAME);
							buffer.sector = list[index].sector;
							list[index] = buffer;
							list[index].isEmpty = FALSE;
							answer = 0;
						}
						break;
					case 4: // sector
						if(utn_getInt(" Write the new sector: "," Error!",&(buffer.sector),2,MIN_SECTOR,MAX_SECTOR) == 0)
						{
							buffer.id = list[index].id;
							strncpy(buffer.name,list[index].name,LEN_NAME);
							strncpy(buffer.lastName,list[index].lastName,LEN_NAME);
							buffer.salary = list[index].salary;
							list[index] = buffer;
							list[index].isEmpty = FALSE;
							answer = 0;
						}
						break;
					case 5: // all data
						if(utn_getNombre(" Write the new name: "," Error!",buffer.name,2,LEN_NAME) == 0 &&
								utn_getNombre(" Write the new last name: "," Error!",buffer.lastName,2,LEN_NAME) == 0 &&
								utn_getFloat(" Write the new salary: "," Error!",&(buffer.salary),2,MIN_SALARY,MAX_SALARY) == 0 &&
								utn_getInt(" Write the new sector: "," Error!",&(buffer.sector),2,MIN_SECTOR,MAX_SECTOR) == 0)
						{
							buffer.id = list[index].id;
							list[index] = buffer;
							list[index].isEmpty = FALSE;
							answer = 0;
						}
						break;
					}
				}
			}
		}
	}
	return answer;
}

/**
 * @brief Find an Employee by Id en returns
 * the index position in array.
 * @param list Employee*
 * @param len
 * @param id
 * @return Return employee index position or (-1) if
 * [Invalid length or NULL pointer received or employee not found]
 */
int findEmployeeById(Employee* list, int len, int id)
{
	int answer = -1;
	if (list != NULL && len > 0 && id >= 0)
	{
		for (int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				if(list[i].id == id)
				{
					answer = i;
					break;
				}
			}
		}
	}
	return answer;
}

/**
 * @brief Remove a Employee by Id (put isEmpty Flag in 1).
 * @param list
 * @param len
 * @param id
 * @return int Return (-1) if Error
 * [Invalid length or NULL pointer or if can't find a employee]
 * - (0) if Ok
 */
int removeEmployee(Employee* list, int len, int id)
{
	int answer = -1;
	int idDelete;
	int index;

	if(list != NULL && len > 0 && id >= 0)
	{
		printf("\n           ******** List of loaded employees ********\n");
		printEmployees(list,len);

		if(utn_getInt("\n . Enter the ID to delete: "," Error! ", &idDelete,2,1,1000) == 0)
		{
			index = findEmployeeById(list, len, idDelete);
			if(index >= 0)
			{
				if(	list != NULL && len > 0 && index >= 0 && index < len &&
						list[index].isEmpty == FALSE)
				{
					list[index].isEmpty = TRUE;
					answer = 0;
				}
			}
		}
	}
	return answer;
}

/**
 * @brief Sort the elements in the array of employees,
 * the argument order indicate UP or DOWN order.
 * @param list
 * @param len
 * @param order [1] indicate UP - [0] indicate DOWN.
 * @return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int sortEmployees(Employee* list, int len, int order)
{
	int answer = -1;
	int flagSwap;
	Employee buffer;

	if(list != NULL && len > 0 && (order == 0 || order == 1))
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < len-1;i++)
			{
				if((order == 1 && strncmp(list[i].lastName,list[i+1].lastName,LEN_NAME) > 0) ||
						(order == 0 && strncmp(list[i].lastName,list[i+1].lastName,LEN_NAME) < 0) ||
						(strncmp(list[i].lastName,list[i+1].lastName,LEN_NAME) == 0
								&& list[i].sector > list[i+1].sector)
				)
				{
					buffer = list[i];
					list[i] = list[i+1];
					list[i+1] = buffer;
					flagSwap = 1;
					answer = 0;
				}
			}
		}while(flagSwap);
	}
	return answer;
}

/**
 * @brief Print the content of employees array.
 * @param list
 * @param length
 * @return
 */
int printEmployees(Employee* list, int len)
{
	int answer = -1;
	if(list != NULL && len > 0)
	{
		printf("\n |  ID  |    NAME    |    LAST NAME    |   SALARY   |  SECTOR  |\n");
		for(int i = 0;i < len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				printf("     %d  %12s\t %12s\t  $ %.2f\t  %d\n",
						list[i].id,
						list[i].name,
						list[i].lastName,
						list[i].salary,
						list[i].sector);
			}
		}
		answer = 0;
	}
	return answer;
}

/** Added function
 * @brief Function containing for 2 function calls
 * ( totalAndAverageSalaries() and sortEmployees() ).
 * @param list Employee*
 * @param len
 * @return Return (-1) if Error
 * [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int employeeReports(Employee* list, int len)
{
	int answer = -1;
	int option;
	int optionOrder;

	if(list != NULL && len > 0)
	{
		printf("\n           ******** Employee Reports ********\n");
		if(utn_getInt("\n 1) Sort lists\n 2) Total and average salaries\n\n > Option: "," Error!", &option,2,1,3) == 0)
		{
			switch(option)
			{
			case 1:
				if(utn_getInt("\n ~ Select sort order:\n 1) A - Z\n 0) Z - A\n\n > Order: "," Error!", &optionOrder,2,0,1) == 0)
				{
					if(sortEmployees(list, len, optionOrder) == 0)
					{
						printf("\n  Data sorted successfully and\n");
						answer = 0;
					}
					else
					{
						printf(" Error!\n");
					}
				}
				else
				{
					printf(" Error!\n");
				}
				break;
			case 2:
				if(totalAndAverageSalaries(list, len) == 0)
				{
					printf("\n > Recently received data and ");
					answer = 0;
				}
				else
				{
					printf(" Error!\n");
				}
			}
		}
		else
		{
			printf(" Error!\n");
		}
	}
	return answer;
}

/** Added function
 * @brief Performs the task of giving total and average salaries.
 * @param list Employee*
 * @param len
 * @return Return (-1) if Error
 * [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int totalAndAverageSalaries(Employee* list, int len)
{
	int answer = -1;
	float totalPromedy;

	int countEmployees = 0;
	float accumPayments = 0;
	int highestPaidEmployee = 0;
	int idsEmployees = 0;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				accumPayments += list[i].salary;
				countEmployees++;
			}
		}

		totalPromedy = (float) accumPayments / countEmployees;

		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE && list[i].salary > totalPromedy)
			{
				highestPaidEmployee++;
				idsEmployees += list[i].id;
			}
		}

		printf("\n ******** Data Report ******** \n . Total Salaries: $ %.2f (%d employees)\n . Promedy: $ %.2f\n",
				accumPayments,
				countEmployees,
				totalPromedy);

		if(highestPaidEmployee == 1)
		{
			printf(" . There is %d employee who is above the average salary.\n", highestPaidEmployee);
		}
		else if(highestPaidEmployee < 1)
		{
			printf(" . There are no employees who exceed the average salary.\n");
		}
		else
		{
			printf(" . There are %d employees that exceed the average salary.\n", highestPaidEmployee);
		}
		answer = 0;
	}
	return answer;
}
