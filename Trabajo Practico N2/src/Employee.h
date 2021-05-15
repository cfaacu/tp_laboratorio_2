/*
 * Employ.h
 *
 *  Created on: May 11, 2021
 *      Author: facu
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

struct
{
 int id;
 char name[51];
 char lastName[51];
 float salary;
 int sector;
 int isEmpty;
}typedef Employee;

int initEmployees(Employee* list, int len);
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector);
int findEmptyPosition(Employee* list, int len);
int findEmployeeById(Employee* list, int len,int id);
int removeEmployee(Employee* list, int len, int id);
int sortEmployees(Employee* list, int len, int order);
int printEmployeesArray(Employee* list, int length);
int printEmployee(Employee* employee);
int newEmployee(Employee* list, int len, int* idEmployee);
int modifyEmployee(Employee* list, int len, int* idEmployee);
int deleteEmployee(Employee* list, int len, int* idEmployee);
int sortAndPrint(Employee* list,int len);
int calculateAverageAndPrint(Employee* arrayEmploye, int len);
int printEmployeeAverage(Employee* arrayEmploye, int len, float averageSalary);
int calculateAverageSalary(Employee* arrayEmployee, int len, float* averageSalary);

#endif /* EMPLOYEE_H_ */


