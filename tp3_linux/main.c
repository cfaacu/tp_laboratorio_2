#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
   int option = 0;
   int flagFirstTxt = 0;
   int flagFirstBin = 0;
   LinkedList* listaEmpleados = ll_newLinkedList();


	do
	{
		utn_getNumero(&option, "1)Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
				"2)Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n"
				"3)Alta de empleado.\n"
				"4)Modificar datos de empleado.\n"
				"5)Baja de empleado.\n"
				"6)Listar empleados.\n"
				"7)Ordenar empleados.\n"
				"8)Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
				"9)Guardar los datos de los empleados en el archivo data.bin (modo binario).\n"
				"10)Salir.\n"
				"\nIngrese una opcion:", "[ERROR]Opcion invalida.\n", 1,10, 3);
		switch(option)
		{
		case 1:
			controller_loadFromText("data.csv",listaEmpleados);
			flagFirstTxt = 1;
			break;
		case 2:
			controller_loadFromBinary("data.bin",listaEmpleados);
			flagFirstBin = 1;
			break;
		case 3:
			controller_addEmployee(listaEmpleados);
			break;
		case 4:
			controller_editEmployee(listaEmpleados);
			break;
		case 5:
			controller_removeEmployee(listaEmpleados);
			break;
		case 6:
			controller_ListEmployee(listaEmpleados);
			break;
		case 7:
			controller_sortEmployee(listaEmpleados);
			break;
		case 8:
			if(flagFirstTxt == 1)
			{
				controller_saveAsText("data.csv",listaEmpleados);
			}
			else
			{
				printf("No se cargo la lista.\n");
			}
			break;
		case 9:
			if(flagFirstBin == 1)
			{
				controller_saveAsBinary("data.bin",listaEmpleados);
			}
			else
			{
				printf("No se cargo la lista.\n");
			}
			break;
		case 10:
			ll_deleteLinkedList(listaEmpleados);
			break;
		}
	}
	while(option!=10);

	return EXIT_SUCCESS;
}

