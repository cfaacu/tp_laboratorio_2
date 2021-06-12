/*
 * Empleado.c
 *
 *  Created on: May 18, 2021
 *      Author: facu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"

/** \brief Reserva espacio de memoria para la estructura Empleado.
 * \return Employee* retorna la direccion de memoria reservada.
 */
Employee* empleado_new(void)
{
	/*Empleado* auxEmpleado;
	auxEmpleado = (Empleado*) malloc(sizeof(Empleado));
	return auxEmpleado; */
	return (Employee*) malloc(sizeof(Employee));
}

/** \brief Reserva espacio de memoria para la estructura Empleado y setea sus valores recibidos como texto por parametro .
 * \param char* idStr Recibe el id como string.
 * \param char* nombreStr Recibe el nombre como string.
 * \param char* horasTrabajadasStr Recibe las horas trabajadas como string.
 * \param char* salario Recibe el salario como string.
 * \return Employee* Retorna la direccion de memoria del empleado.
 */
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* salario)
{
	Employee* auxEmpleado = empleado_new();
	if(auxEmpleado != NULL)
	{
		if  ( 	employee_setNombre(auxEmpleado,nombreStr) != 0 ||
				employee_setHorasTrabajadas(auxEmpleado,atoi(horasTrabajadasStr)) != 0 ||
				employee_setSueldo(auxEmpleado,atoi(salario)) != 0 ||
				employee_setId(auxEmpleado,atoi(idStr)) != 0 )
		{
			employee_delete(auxEmpleado);
			auxEmpleado = NULL;
		}
	}
	return auxEmpleado;
}

/** \brief Reserva espacio de memoria para la estructura Empleado y setea sus valores recibidos con sus respectivos datos por parametro .
 * \param int* id Recibe el id como entero.
 * \param char* nombreStr Recibe el nombre como string.
 * \param int* horasTrabajadas Recibe las horas trabajadas como entero.
 * \param int* salario Recibe el salario como entero.
 * \return Employee* Retorna la direccion de memoria del empleado.
 */
Employee* employee_newParametros(int id,char* nombreStr,int horasTrabajadas,int salario)
{

	Employee* auxEmpleado = empleado_new();
	if(auxEmpleado != NULL)
	{

		if  ( 	employee_setNombre(auxEmpleado,nombreStr) != 0 ||
				employee_setHorasTrabajadas(auxEmpleado,horasTrabajadas) != 0 ||
				employee_setSueldo(auxEmpleado,salario) != 0 ||
				employee_setId(auxEmpleado,id) != 0 )
		{
			employee_delete(auxEmpleado);
			auxEmpleado = NULL;
		}
	}
	return auxEmpleado;
}

/** \brief Elimina empleados
 * \param Employee* Puntero de empleado a eliminar.
 * \return int 0 (OK) y -1 (ERROR).
 */
int employee_delete(Employee* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		this=NULL;
		retorno = 0;
	}
	return retorno;
}

/** \brief Setea el valor del id en la estructura empleado.
 * \param Employee* this empleado al cual se le seteara el id.
 * \param int idEmpleado id a setear.
 * \return int 0 (OK) y -1 (ERROR).
 */
int employee_setId(Employee* this, int idEmpleado)
{
	int retorno = -1;
	if(this != NULL && isValidId(idEmpleado)==0)
	{
		this->id = idEmpleado;
		retorno = 0;
	}
	return retorno;
}

/** \brief Pide el Id de un empleado.
 * \param Employee* this puntero a empleado.
 * \param int* flagError int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorna el ID encontrado.
 */
int employee_getId(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->id;
		*flagError = 0;
	}
	return auxId;
}

/** \brief Valida que el id sea correcto.
 * \param int idEmpleado Valor del id a validar
 * \return int 0 (OK) y -1 (ERROR).
 */
int isValidId(int idEmpleado)
{
	int retorno = -1;

	if(idEmpleado>=0)
	{
		retorno = 0;
	}

	return retorno;
}

/** \brief Setea el valor del nombre en la estructura empleado.
 * \param Employee* this empleado al cual se le seteara el nombre
 * \param char* nombre Nombre a setear.
 * \return int 0 (OK) y -1 (ERROR).
 */
int employee_setNombre(Employee* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && isValidNombre(nombre)==0)
	{
		strcpy(this->nombre,nombre);
		retorno = 0;
	}
	return retorno;
}

/** \brief Pide el nombre de un empleado.
 * \param Employee* this puntero a empleado a utilizar.
 * \param int* flagError puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta el nombre como char*.
 */
char* employee_getNombre(Employee* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}

/** \brief Valida que el nombre sea correcto.
 * \param char* nombre puntero a char que representa el nombre a validar.
 * \return int 0 (OK) y -1 (ERROR).
 */

int isValidNombre(char* nombre)
{
	int retorno=-1;

	if(isName(nombre)==0)
	{
		retorno=0;
	}
	return retorno;
}

/** \brief Setea el valor del Horas Trabajadas en la estructura empleado.
 * \param Employee* this empleado al cual se le setearan las horas trabajadas.
 * \param Int horasTrabajadas Horas trabajadas a setear.
 * \return int 0 (OK) y -1 (ERROR).
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && isValidHorasTrabajadas(horasTrabajadas)==0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

/** \brief Pide la cantidad de horas trabajadas.
 * \param Employee* this puntero a empleado a utilizar.
 * \param int* flagError puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta las horas trabajadas del empleado.
 */
int employee_getHorasTrabajadas(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->horasTrabajadas;
		*flagError = 0;
	}
	return auxId;
}

/** \brief Valida que las horas trabajadas sean correctas.
 * \param int HorasTrabajadas Horas trabajadas a corroborar.
 * \return int 0 (OK) -1 (ERROR).
 *
 */
int isValidHorasTrabajadas(int horasTrabajadas)
{
	int retorno = -1;

	if(horasTrabajadas>=35 && horasTrabajadas<=730)
	{
		retorno=0;
	}
	return retorno;
}

/** \brief Setea el valor del sueldo en la estructura empleado.
 * \param Employee* this empleado al cual se le seteara el sueldo.
 * \param Int sueldo Sueldo a setear.
 * \return int 0 (OK) y -1 (ERROR).
 */
int employee_setSueldo(Employee* this, int sueldo)
{
	int retorno = -1;
	if(this != NULL && isValidSueldo(sueldo)==0)
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}

/** \brief Pide el salario.
 * \param Employee* this puntero a empleado a utilizar.
 * \param int* flagError puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta el salario.
 */
int employee_getSueldo(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->sueldo;
		*flagError = 0;
	}
	return auxId;
}

/** \brief Valida el sueldo
 * \param sueldo Valor del sueldo a validar
 * \return int 0 (OK) y -1 (ERROR).
 */
int isValidSueldo(int sueldo)
{
	int retorno = -1;

	if(sueldo>=1000 && sueldo<=99999)
	{
		retorno=0;
	}
	return retorno;
}

static int contador=0;

/** \brief Setea el valor inicial del id obtenido de una lista.
 * \param LinkedList* pArrayListEmployee Lista para obtener los datos.
 * \return void
 */
void emp_setearValorInicialDeId(LinkedList* pArrayListEmployee)
{
	Employee* pEmp;
	int id;
	int idMax;
	int size;
	int flagError;
	size = ll_len(pArrayListEmployee);

	for(int i=0;i<size;i++)
	{
		pEmp = ll_get(pArrayListEmployee, i);
		if(pEmp != NULL)
		{
			id = employee_getId(pEmp, &flagError);
			if(i==0)
			{
				idMax = id;
			}
			else
			{
				if(id > idMax)
				{
					idMax = id;
				}
			}
		}
		contador = idMax;
	}
}

/** \brief Generador de ID
 * \param Void
 * \return int devulve el ID
 */
int employee_generarId(void)
{
	contador++;
	return contador;
}

/*********************************************************************************************************/
/** \brief Busca a un empleado por el ID
 * \param LinkedList* pArrayListEmployee Lista para obtener los datos.
 * \param int idABuscar Recibe el id a buscar el empleado
 * \return Employee* Devuelve la direccion del memoria del empleado encontrado.
 */
Employee* buscarPorId(LinkedList* pArrayListEmployee,int idABuscar)
{
	int i;
	int lenLista ;
	Employee* pEmpEdit;
	Employee* pRet=NULL;
	int idEncontrado;
	int flag;

	if(pArrayListEmployee!=NULL)
	{
		lenLista = ll_len(pArrayListEmployee);

		for(i=0; i<lenLista; i++)
		{
			pEmpEdit = (Employee*)ll_get(pArrayListEmployee, i);

			idEncontrado = employee_getId(pEmpEdit, &flag);

			if(idABuscar == idEncontrado)
			{
				pRet = pEmpEdit;
				break;
			}
		}
	}

	return pRet;
}

/** \brief Funcion criterio a pasar en el sort para comparar.
 * \param void* empleadoUno Recibe el puntero del primer empleado a comparar.
 * \param void* empleadoDos Recibe el puntero del segundo empleado a comparar.
 * \return retorna 1 o -1 segun el resultado de la comparacion
 */
int funcionCriterio(void* empleadoUno, void* empleadoDos)
{
	int retorno = 0;
	Employee* empUno;
	Employee* empDos;
	int flagError;
	char* nombre;
	char* nombreDos;

	if(empleadoUno != NULL && empleadoDos != NULL)
	{
		empUno = (Employee*)empleadoUno;
		empDos = (Employee*)empleadoDos;

		nombre = employee_getNombre(empUno, &flagError);
		nombreDos = employee_getNombre(empDos, &flagError);

		if(strcmp(nombre,nombreDos)>0)
		{
			retorno = 1;
		}
		else
		{
			retorno = -1;
		}
	}
	return retorno;
}
