/*
 * employee.h
 *
 *  Created on: 25 sep. 2020
 *      Author: leo
 */

#ifndef EMPLOYEE_H_

	#define EMPLOYEE_H_
	#define LEN_NAME 51
	#define TRUE 1
	#define FALSE 0
	#define MIN_SALARY 0.0
	#define MAX_SALARY 100000.0
	#define MIN_SECTOR 1
	#define MAX_SECTOR 10


	typedef struct
	{
		int id;
		char name[LEN_NAME];
		char lastName[LEN_NAME];
		float salary;
		int sector;
		int isEmpty;
	}Employee;

	void mainEmployee();
	int initEmployees(Employee* list, int len);
	int addEmployee(Employee* list, int len, int id,char name[],char lastName[],float salary,int sector);
	int modifyEmployee(Employee* list, int len);
	int findEmployeeById(Employee* list, int len,int id);
	int removeEmployee(Employee* list, int len, int id);
	int sortEmployees(Employee* list, int len, int order);
	int printEmployees(Employee* list, int length);

	int areDataReceived(int* id, char name[], char lastName[], float* salary, int* sector);
	int employeeReports(Employee* list, int length);
	int totalAndAverageSalaries(Employee* list, int len);

#endif /* EMPLOYEE_H_ */
