/*
 ============================================================================
 Name        : Tp2.c
 Author      : Facu
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "utn2.h"
#include "Employee.h"
#define QTY_EMPLOYEES 1000

int main(void) {

	setbuf(stdout,NULL);
	Employee arrayEmployee[QTY_EMPLOYEES];
	int idEmployee = -1;
	int flagNewEmployee = 0;
	int option;
	int choice;

	initEmployees(arrayEmployee, QTY_EMPLOYEES);

	do
	{
		printf("Ingrese una opcion:\n");
		utn_getNumero(&option, "1)ALTAS.\n2)MODIFICAR.\n3)BAJA.\n4)INFORMES.\n5)SALIR.\n", "[ERROR]Opcion invalida.\n", 1, 5, 3);
		switch(option)
		{
		case 1:
			if(newEmployee(arrayEmployee,QTY_EMPLOYEES, &idEmployee)==0)
			{
				flagNewEmployee=flagNewEmployee+1;
				printf("Empleado cargado con exito!\n");
			}
			break;
		case 2:
			if(flagNewEmployee > 0)
			{
				if(modifyEmployee(arrayEmployee, QTY_EMPLOYEES,&idEmployee)==0)
				{
					printf("Empleado modificado con exito!\n");
				}
			}
			else
			{
				printf("[ERROR]No hay empleados cargados!\n");
			}
			break;
		case 3:
			if(flagNewEmployee > 0)
			{
				if(deleteEmployee(arrayEmployee, QTY_EMPLOYEES, &idEmployee)==0)
				{
					flagNewEmployee=flagNewEmployee-1;
					printf("Empleado eliminado con exito!\n");
				}
			}
			else
			{
				printf("[ERROR]No hay empleados cargados!\n");
			}
			break;
		case 4:
			if(utn_getNumero(&choice, " 1). Listado de los empleados ordenados alfabéticamente por Apellido y Sector.\n"
					" 2). Total y promedio de los salarios, y cuántos empleados superan el salario promedio.", "[ERROR]Opcion Invalida.\n", 1, 2, 3)==0)
			{
				switch (choice) {
					case 1:
						if(sortAndPrint(arrayEmployee, QTY_EMPLOYEES)==0);
						break;
					case 2:
						if(calculateAverageAndPrint(arrayEmployee,QTY_EMPLOYEES)==0);
						break;
					default:
						break;
				}
			}
			break;
		case 5:
			break;
			}
	}
	while(choice!=5);
	return EXIT_SUCCESS;
}


