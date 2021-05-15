/*
 * Employ.c
 *
 *  Created on: May 11, 2021
 *      Author: facu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn2.h"
#include "Employee.h"

#define TRUE 0
#define FALSE 1


/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int initEmployees(Employee* list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
		}
	}
	return retorno;
}

/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 *
 */
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int retorno = -1;
	int auxPosition;

	if(list != NULL && len > 0 && id >= 0 && name != NULL && lastName != NULL && salary > 0 && sector >= 0)
	{
		auxPosition = findEmptyPosition(list, len);
		if(auxPosition >= 0)
		{
			retorno = 0;
			list[auxPosition].id = id;
			strncpy(list[auxPosition].name,name,sizeof(list[auxPosition].name));
			strncpy(list[auxPosition].lastName,lastName,sizeof(list[auxPosition].lastName));
			list[auxPosition].salary = salary;
			list[auxPosition].sector = sector;
			list[auxPosition].isEmpty = FALSE;
		}
	}
	return retorno;
}

/** \brief Find an empty position in the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (position) if Ok
 *
 */
int findEmptyPosition(Employee* list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */
int findEmployeeById(Employee* list, int len,int id)
{
	int retorno = -1;
	if(list != NULL && len > 0 && id >= 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].id == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */
int removeEmployee(Employee* list, int len, int id)
{
	int retorno = -1;
	if(list != NULL && len > 0 && id >= 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].id == id)
			{
				list[i].isEmpty = TRUE;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployees(Employee* list, int len, int order)
{
	int retorno = -1;
	int flagSwap;
	int i;
	Employee bufferEmployee;
	int auxiliarCmp;

	if(list != NULL && len >0 && (order == 1 || order == 0))
	{
		switch (order) {
			case 1:
				do
				{
					flagSwap = 0;
					for(i=0;i<len;i++)
					{
						auxiliarCmp = strncmp(list[i].lastName,list[i+1].lastName,sizeof(list[i].lastName));
						if(auxiliarCmp > 0 ||
							(auxiliarCmp == 0 && list[i].sector > list[i+1].sector))
						{
							flagSwap = 1;
							bufferEmployee = list[i];
							list[i] = list[i+1];
							list[i+1] = bufferEmployee;
						}
					}
					len--;
				}while(flagSwap);
				break;
			case 0:
				do
				{
					flagSwap = 0;
					for(i=0;i<len;i++)
					{
						auxiliarCmp = strncmp(list[i].lastName,list[i+1].lastName,sizeof(list[i].lastName));
						if(auxiliarCmp < 0 ||
							(auxiliarCmp == 0 && list[i].sector < list[i+1].sector))
						{
							flagSwap = 1;
							bufferEmployee = list[i];
							list[i] = list[i+1];
							list[i+1] = bufferEmployee;
						}
					}
					len--;
				}while(flagSwap);
				break;
		}
	}
	return retorno;
}


/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int
 *
 */
int printEmployeesArray(Employee* list, int length)
{
	int retorno = -1;

	if(list!=NULL && length>=0)
	{
		for(int i=0;i<length;i++)
		{
			printEmployee(&list[i]);
		}
	}

	return retorno;
}

/** \brief print the content of an employee
 *
 * \param list Employee*
 * \return (0) if ok or (-1)ERROR
 *
 */
int printEmployee(Employee* employee)
{
	int retorno = -1;

	if(employee!=NULL)
	{
		retorno = 0;
		if(employee->isEmpty==FALSE)
		printf("ID: %d ||\tNombre: %s ||\tApellido: %s ||\tSalario: %.2f ||\tSector: %d\n",employee->id,employee->name,employee->lastName,employee->salary,employee->sector);
	}

	return retorno;
}


/** \brief Create a new employee
 *
 * \param list Employee*
 * \param len array lenght
 * \param idEmployee pointer to id
 * \return (0) if ok or (-1)ERROR
 *
 */
int newEmployee(Employee* list, int len, int* idEmployee)
{
	int retorno = -1;
	Employee bufferEmployee;

	if(list != NULL && len > 0 && idEmployee != NULL)
	{
		if(utn_getName(bufferEmployee.name,sizeof(bufferEmployee.name),"Ingrese el nombre:\n","[ERROR]Nombre invalido.\n",3)==0 &&
			utn_getName(bufferEmployee.lastName,sizeof(bufferEmployee.lastName),"Ingrese el apellido:\n","[ERROR]Apellido invalido.\n",3)==0 &&
			utn_getNumeroFloat(&bufferEmployee.salary,"Ingrese el salario:\n","[ERROR]Salario invalido.\n",0,9999,3)==0 &&
			utn_getNumero(&bufferEmployee.sector,"Ingrese el sector:\n","[ERROR]Sector invalido.\n",0,100,3)==0)
		{
			(*idEmployee)++;
			if(addEmployee(list, len, *idEmployee, bufferEmployee.name,bufferEmployee.lastName,bufferEmployee.salary,bufferEmployee.sector)==0)
			{
				retorno = 0;
			}
		}
	}

	return retorno;
}

/** \brief Modify an employee
 *
 * \param list Employee*
 * \param len array lenght
 * \param idEmployee pointer to id
 * \return (0) if ok or (-1)ERROR
 *
 */
int modifyEmployee(Employee* list, int len, int* idEmployee)
{
	int retorno=-1;
	int option;
	int index;
	int id;
		if(list != NULL && len > 0 && idEmployee!= NULL)
		{
			printEmployeesArray(list,len);
			utn_getNumero(&id, "Ingrese ID del empleado a modificar:\n", "[ERROR]ID Invalido.\n", 0,*idEmployee, 3);
			index = findEmployeeById(list, len, id);
			if(list[index].isEmpty==FALSE)
			{
				printf("Que desea modificar?\n");
				printf("1)Nombre\n2)Apellido\n3)Salario\n4)Sector\n");
				utn_getNumero(&option, "Ingrese opcion:\n", "[ERROR]Opcion Invalida.\n", 1, 4, 3);

				switch (option)
				{
					case 1:
						if(utn_getName(list[index].name,sizeof(list[index].name), "Ingrese Nuevo Nombre:\n", "[ERROR]Nombre invalido.\n",3)==0)
						{
							retorno = 0;
						}
						break;
					case 2:
						if(utn_getName(list[index].lastName,sizeof(list[index].lastName), "Ingrese Nuevo Apellido:\n", "[ERROR]Apellido invalido.\n",3)==0)
						{
							retorno = 0;
						}
						break;
					case 3:
						if(utn_getNumeroFloat(&list[index].salary,"Ingrese Nuevo Salario:\n","[ERROR]Salario invalido.\n",0,9999,3)==0)
						{
							retorno = 0;
						}
						break;
					case 4:
						if(utn_getNumero(&list[index].sector,"Ingrese Nuevo Sector:\n","[ERROR]Sector invalido.\n",0,100,3)==0)
						{
							retorno = 0;
						}
						break;
				}
			}

		}
	return retorno;
}

/** \brief Delete an employee
 *
 * \param list Employee*
 * \param len array lenght
 * \param idEmployee pointer to id
 * \return (0) if ok or (-1)ERROR
 *
 */
int deleteEmployee(Employee* list, int len, int* idEmployee)
{
	int retorno = -1;
	int index;

	if(list != NULL && len > 0 && idEmployee != NULL)
	{
		printEmployeesArray(list,len);
		if(utn_getNumero(&index, "Ingrese ID del empleado a eliminar.\n", "[ERROR]ID Invalido.\n", 0,*idEmployee, 3)==0)
		{
			if(list[index].isEmpty == FALSE)
			{
				retorno = 0;
				removeEmployee(list, len,index);
			}
		}
	}
	return retorno;
}

/** \brief Sort the array by name and sector and print
 *
 * \param list Employee*
 * \param len array lenght
 * \param idEmployee pointer to id
 * \return (0) if ok or (-1)ERROR
 *
 */
int sortAndPrint(Employee* list,int lenght)
{
	int retorno = -1;
	if(list!=NULL && lenght>=0)
	{
		sortEmployees(list, lenght, 1);
		printEmployeesArray(list, lenght);
	}

	return retorno;
}

/** \brief Find the avarega salary
 *
 * \param list Employee*
 * \param len array lenght
 * \param averageSalary Avarega salary calculated
 * \return (0) if ok or (-1)ERROR
 *
 */
int calculateAverageSalary(Employee* arrayEmployee, int len, float* averageSalary)
{
	int retorno = -1;
	int qtyEmployees = 0;
	float acumSalary = 0;

	if(arrayEmployee != NULL && len > 0 && averageSalary != NULL)
	{
		for(int i=0;i<len;i++)
		{
			if(arrayEmployee[i].isEmpty==FALSE)
			{
				qtyEmployees=qtyEmployees+1;
				acumSalary = acumSalary + arrayEmployee[i].salary;
			}
		}
		retorno = 0;
		*averageSalary = acumSalary/qtyEmployees;
	}
	return retorno;
}

/** \brief Print employee with over avarage salary
 *
 * \param list Employee*
 * \param len array lenght
 * \param averageSalary Avarega salary calculated
 * \return (0) if ok or (-1)ERROR
 *
 */
int printEmployeeAverage(Employee* arrayEmploye, int len, float averageSalary)
{
	int retorno = -1;

	if(arrayEmploye != NULL && len > 0 && averageSalary > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(arrayEmploye[i].isEmpty==FALSE && arrayEmploye[i].salary >= averageSalary)
			{
				retorno = 0;
				printEmployee(&arrayEmploye[i]);
			}
		}
	}
	return retorno;
}

/** \brief Calculate salary average and print the employee that exceed the avarage salary
 *
 * \param list Employee*
 * \param len array lenght
 * \return (0) if ok or (-1)ERROR
 *
 */
int calculateAverageAndPrint(Employee* arrayEmploye, int len)
{
	int retorno = -1;
	float averageSalary;

	if(arrayEmploye != NULL && len > 0)
	{
		if(calculateAverageSalary(arrayEmploye, len, &averageSalary)==0)
		{
			retorno = 0;
			printf("El promedio de los salarios es: %.2f y los superan: \n",averageSalary);
			printEmployeeAverage(arrayEmploye, len, averageSalary);
		}
	}
	return retorno;
}

