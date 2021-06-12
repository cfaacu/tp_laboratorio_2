#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pFile;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			parser_EmployeeFromText(pFile, pArrayListEmployee);
			fclose(pFile);
		}
		emp_setearValorInicialDeId(pArrayListEmployee);
	}
    return 1;
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
	FILE* pFile;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"rb");
		if(pFile != NULL)
		{
			parser_EmployeeFromBinary(pFile, pArrayListEmployee);
			fclose(pFile);
		}
		emp_setearValorInicialDeId(pArrayListEmployee);
	}
    return 1;
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
	char auxNombre[50];
	int auxHorasTrabajadas;
	int auxSalario;
	Employee* auxEmployee;
	int id = 10;
	if(pArrayListEmployee != NULL)
	{
		if(	utn_getName(auxNombre,sizeof(auxNombre), "Ingrese nombre:\n", "[ERROR]Nombre Incorrecto.\n", 3)==0 &&
			utn_getNumero(&auxHorasTrabajadas, "Ingrese Horas trabajadas:\n", "[ERROR]Horas Incorrectas.\n", 35, 730, 3)==0 &&
			utn_getNumero(&auxSalario, "Ingrese Salario:\n", "[ERROR]Salario Incorrecto.\n", 1000,100000, 3)==0)
		{
			id = employee_generarId();
			auxEmployee = employee_newParametros(id, auxNombre, auxHorasTrabajadas, auxSalario);
			if(auxEmployee!=NULL)
			{
				ll_add(pArrayListEmployee, auxEmployee);
				printf("Agregado Correctamente.\n");
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
	int opcion;
	int idAModificar;
	char auxNombre[125];
	int auxSalario;
	int auxHorasTrabajadas;
	Employee* auxEmployee;

	if(pArrayListEmployee != NULL)
	{
		if(utn_getNumero(&idAModificar,"Ingrese el ID:\n","[ERROR]ID invalido",0,99999,3)==0)
		{
			auxEmployee = buscarPorId(pArrayListEmployee, idAModificar);
			if(auxEmployee != NULL)
			{
				if(utn_getNumero(&opcion,"Que desea modificar?\n1)Nombre.\n2)Horas Trabajadas.\n3)Salario.\n","[ERROR]Opcion Invalida",1,3,3)==0)
				{
					switch (opcion)
					{
						case 1:
							if(utn_getName(auxNombre,sizeof(auxNombre),"Ingrese el nuevo nombre:\n","[ERROR]Nombre Incorrecto.\n",3)==0)
							{
								if(employee_setNombre(auxEmployee, auxNombre)==0)
								{
									retorno = 0;
									printf("Modificado Correctamente.\n");
								}
							}
							break;
						case 2:
							if(utn_getNumero(&auxHorasTrabajadas,"Ingrese nuevas horas trabajadas:\n","[ERROR]Horas invalidas.\n",8,730,3)==0)
							{
								if(employee_setHorasTrabajadas(auxEmployee, auxHorasTrabajadas)==0)
								{
									retorno = 0;
									printf("Modificado Correctamente.\n");
								}
							}
							break;
						case 3:
							if(utn_getNumero(&auxSalario,"Ingrese el nuevo salario:\n","[ERROR]Salario incorrecto.\n",1000,100000,3)==0)
							{
								if(employee_setSueldo(auxEmployee,auxSalario)==0)
								{
									retorno = 0;
									printf("Modificado Correctamente.\n");
								}
							}
							break;
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
	int index;
	int idAModificar;
	Employee* auxEmployee;

	if(pArrayListEmployee != NULL)
	{
		if(utn_getNumero(&idAModificar,"Ingrese el ID:\n","[ERROR]ID invalido",0,99999,3)==0)
		{
			auxEmployee = buscarPorId(pArrayListEmployee, idAModificar);
			if(auxEmployee != NULL)
			{
				index = ll_indexOf(pArrayListEmployee, auxEmployee);
				if(index >= 0)
				{
					retorno = 0;
					employee_delete(auxEmployee);
					ll_remove(pArrayListEmployee, index);
					printf("Eliminado Correctamente.\n");
				}
			}
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
	Employee* auxEmpleado;
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		for(int i=0;i<ll_len(pArrayListEmployee);i++)
		{
			auxEmpleado =(Employee*)ll_get(pArrayListEmployee, i);
			printf("ID:[%d]\tNombre:[%s]\tHoras trabajadas:[%d]\tSueldo:[%d]\n",auxEmpleado->id,auxEmpleado->nombre,auxEmpleado->horasTrabajadas,auxEmpleado->sueldo);
		}
		retorno = 0;
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

	if (pArrayListEmployee!=NULL)
	{
		ll_sort(pArrayListEmployee, funcionCriterio, 1);
		printf("Ordenados Correctamente.\n");
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
   Employee* auxEmployee;
   FILE* pFile;
   int auxId;
   char* auxNombre;
   int auxHoras;
   int auxSalario;
   int flagError;

   if(path!=NULL && pArrayListEmployee!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");
		   for(int i=0;i<ll_len(pArrayListEmployee);i++)
		   {
			   auxEmployee = ll_get(pArrayListEmployee, i);
			   if(auxEmployee!=NULL)
			   {
				   auxId = employee_getId(auxEmployee, &flagError);
				   if(!flagError)
				   {
					  auxNombre = employee_getNombre(auxEmployee, &flagError);
					  if(!flagError)
					  {
						  auxHoras = employee_getHorasTrabajadas(auxEmployee, &flagError);
						  if(!flagError)
						  {
							  auxSalario = employee_getSueldo(auxEmployee, &flagError);
							  if(!flagError)
							  {
								  fprintf(pFile,"%d,%s,%d,%d\n",auxId,auxNombre,auxHoras,auxSalario);
								  retorno = 0;
							  }
						  }
					  }
				   }
			   }
			}
		   fclose(pFile);
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
	Employee* auxEmployee;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path,"wb");
		if(pFile!=NULL)
		{
			fprintf(pFile,"id,nombre,horasTrabajadas,sueldo");
			for(int i=0;i<ll_len(pArrayListEmployee);i++)
			{
				auxEmployee = ll_get(pArrayListEmployee, i);
				if(auxEmployee!=NULL)
				{
					fwrite(auxEmployee,sizeof(Employee),1,pFile);
				}
			}
			fclose(pFile);
		}
	}
	return retorno;
}



