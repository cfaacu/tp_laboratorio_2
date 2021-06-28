/*
 * Controller.c
 *
 *  Created on: Jun 16, 2021
 *      Author: facu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "LinkedList.h"
#include "Dictionary.h"
#include "Parser.h"
#include "Articulo.h"
#include "PosArancelaria.h"
#include "Controller.h"
#include "Maritimo.h"
#include "Aereo.h"
#include "Informes.h"

int controller_loadArticuloFromText(char* path , Dictionary* pDictionaryArticulo)
{

	if(path!=NULL && pDictionaryArticulo!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_articuloFromText(pFile, pDictionaryArticulo);
			fclose(pFile);
		}
	}
	return 0;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_addArticulo(Dictionary* pDictionaryArticulo, Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	char auxNombre[50];
	char codigo[50];
	char paisDeFabricacion[50];
	float valorFob;
	float pesosEnKg;
	float alto;
	float ancho;
	float profundidad;
	char posArancel[50];
	Articulo* auxArticulo;

	if(pDictionaryArticulo!=NULL && pDictionaryPosArancelaria != NULL)
	{
		if(utn_getString(codigo,sizeof(codigo),"Ingrese el codigo del producto:\n","Error codigo incorrecto.\n",3)==0)
		{
			if(codigoUsado(pDictionaryArticulo,codigo)!=0)
			{
				if(	utn_getString(auxNombre, sizeof(auxNombre), "Ingrese el nombre:\n", "Error nombre incorrecto.\n", 3)==0 &&
					utn_getString(paisDeFabricacion, sizeof(paisDeFabricacion), "Ingrese pais de fabricacion:\n", "Error pais incorrecto.\n", 3)==0 &&
					utn_getNumeroFloat(&valorFob, "Ingrese valor FOB.\n", "Valor FOB incorrecto.\n", 1, 999999, 3)==0 &&
					utn_getNumeroFloat(&pesosEnKg, "Ingrese peso del articulo(KG).\n", "Peso invalido.\n", 0.1, 999999, 3)==0 &&
					utn_getNumeroFloat(&alto, "Medidas(Al*An*Pr):\nIngrese alto del articulo(cm).\n", "Alto invalido.\n", 0.1, 999999, 3)==0 &&
					utn_getNumeroFloat(&ancho, "Ingrese ancho del articulo(cm).\n", "Ancho invalido.\n", 0.1, 999999, 3)==0 &&
					utn_getNumeroFloat(&profundidad, "Ingrese profundidad del articulo(cm).\n", "Profundidad invalida.\n", 0.1, 999999, 3)==0)
				{
					controller_ListarPosArancelaria(pDictionaryPosArancelaria);
					if(utn_getString(posArancel,sizeof(posArancel),"Ingrese el nomenclador de la posicion arancelaria:\n","Error nomenclador incorrecto.\n",3)==0)
					{
						if(posArusado(pDictionaryPosArancelaria,posArancel)==0)
						{
							auxArticulo = art_newParametros(codigo,auxNombre,paisDeFabricacion,valorFob,pesosEnKg,alto,ancho,profundidad,posArancel);
							if(auxArticulo!=NULL)
							{
								dict_insert(pDictionaryArticulo,codigo,auxArticulo);
								printf("Articulo agregado con exito.\n");
								retorno=0;
							}
						}
						else
						{
							printf("Esa posicion arancelaria no existe, prueba con otra.\n");
						}
					}
				}
			}
			else
			{
				printf("El codigo ya es utilizado, pruebe con otro.\n");
			}
		}

	}
	return retorno;
}

/** \brief Modificar datos de un articulo
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editArticulo(Dictionary* pDictionaryArticulo, Dictionary* pDictionaryPosArancelaria)
{
	int retorno = 0;
	char auxNombre[50];
	char auxCodigo[50];
	char paisDeFabricacion[50];
	float valorFob;
	float peso;
	float alto;
	float ancho;
	float profundidad;
	char posArancel[50];
	int opcion;
	Articulo* auxArticulo;

	if(pDictionaryArticulo!=NULL && pDictionaryPosArancelaria!= NULL)
	{
		controller_ListarArticulo(pDictionaryArticulo);
		if(utn_getString(auxCodigo,sizeof(auxCodigo),"Ingrese el codigo del articulo a modificar:\n","[Error]Codigo Incorrecto.\n",3)==0)
		{
			if(codigoUsado(pDictionaryArticulo,auxCodigo)==0)
			{
				auxArticulo = dict_get(pDictionaryArticulo, auxCodigo);
				if(auxArticulo!=NULL)
				{
					if(utn_getNumero(&opcion, "Que desea modificar?\n1)Nombre.\n2)Pais de fabricacion.\n3)Valor FOB.\n"
							"4)Peso(KG).\n5)Alto.\n6)Ancho.\n7)Profundidad.\n8)Nomenclatura PosArancelaria.\n", "[Error]Incorrecto.\n", 1, 8, 3)==0)
					{
						switch (opcion) {
							case 1:
								if(utn_getName(auxNombre, sizeof(auxNombre), "Ingrese nuevo nombre.\n", "[ERROR]Nombre Invalido.\n", 3)==0)
								{
									if(art_setNombre(auxArticulo, auxNombre)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 2:
								if(utn_getString(paisDeFabricacion, sizeof(paisDeFabricacion), "Ingrese nuevo pais de fabricacion:\n", "Error pais incorrecto.\n", 3)==0)
								{
									if(art_setPaisFabricacion(auxArticulo, paisDeFabricacion)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 3:
								if(utn_getNumeroFloat(&valorFob, "Ingrese nuevo valor FOB.\n", "Valor FOB incorrecto.\n", 1, 999999, 3)==0)
								{
									if(art_setValorFob(auxArticulo, valorFob)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 4:
								if(utn_getNumeroFloat(&peso, "Ingrese peso del articulo(KG).\n", "Peso invalido.\n", 0.1, 999999, 3)==0)
								{
									if(art_setPeso(auxArticulo, peso)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 5:
								if(utn_getNumeroFloat(&alto, "Ingrese nuevo alto del articulo(cm).\n", "Alto invalido.\n", 0.1, 999999, 3)==0)
								{
									if(art_setAlto(auxArticulo, alto)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 6:
								if(utn_getNumeroFloat(&ancho, "Ingrese nuevo ancho del articulo(cm).\n", "Ancho invalido.\n", 0.1, 999999, 3)==0)
								{
									if(art_setAncho(auxArticulo, ancho)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 7:
								if(utn_getNumeroFloat(&profundidad, "Ingrese nueva profundiad del articulo(cm).\n", "Profunidad invalida.\n", 0.1, 999999, 3)==0)
								{
									if(art_setProfundidad(auxArticulo, profundidad)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
							case 8:
								controller_ListarPosArancelaria(pDictionaryPosArancelaria);
								if(utn_getString(posArancel,sizeof(posArancel),"Ingrese la nueva posicion arancelaria:\n","Posicion invalida.\n", 3)==0)
								{
									if(art_setNomenclatura(auxArticulo,posArancel)==0)
									{
										printf("Articulo modificado con exito.\n");
									}
								}
								break;
						}
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
int controller_removeArticulo(Dictionary* pDictionaryArticulo)
{
	int retorno=-1;
	char cadenaAEliminar[64];
	Articulo* auxArticulo;

	if(pDictionaryArticulo!=NULL)
	{
		controller_ListarArticulo(pDictionaryArticulo);
		if(utn_getString(cadenaAEliminar,sizeof(cadenaAEliminar),"Ingrese el codigo del articulo a eliminar:\n","[ERROR]\n",3)==0)
		{
			auxArticulo = (Articulo*) dict_get(pDictionaryArticulo, cadenaAEliminar);
			if(auxArticulo != NULL)
			{
				if(art_delete(auxArticulo)==0 && dict_remove(pDictionaryArticulo,cadenaAEliminar)==0)
				{
					printf("Articulo eliminado con exito.\n");
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
int controller_ListarArticulo(Dictionary* pDictionaryArticulo)
{
	int retorno = -1;
	int size;
	int flagError;
	Articulo* auxArticulo;
	LinkedList* listaAux;

	listaAux = dict_getValues(pDictionaryArticulo);
	if(listaAux != NULL)
	{
		size = ll_len(listaAux);
		if(pDictionaryArticulo != NULL)
		{
			for(int i=0;i<size;i++)
			{
				auxArticulo = (Articulo*)ll_get(listaAux, i);
				printf(	"Codigo: [%s]\tNombre: [%s]\tHecho en: [%s]\tValor FOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\n",
						art_getCodigo(auxArticulo, &flagError),art_getNombre(auxArticulo, &flagError),art_getPaisFabricacion(auxArticulo, &flagError),art_getValorFob(auxArticulo, &flagError),
						art_getPeso(auxArticulo, &flagError),art_getAlto(auxArticulo, &flagError),art_getAncho(auxArticulo, &flagError),art_getProfundidad(auxArticulo, &flagError));
			}
			retorno = 0;
		}
	}
    return retorno;
    ll_deleteLinkedList(listaAux);
}

int controller_saveArticuloAsText(char* path , Dictionary* pDictionaryArticulo)
{
   int retorno = -1;
   Articulo* auxArticulo;
   LinkedList* listaAux;
   FILE* pFile;
   int flagError;
   int longitud;

   listaAux = dict_getValues(pDictionaryArticulo);
   longitud = ll_len(listaAux);
   if(path!=NULL && pDictionaryArticulo!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"CODIGO,ITEM,ORIGEN,FOB,KG,ALTO,ANCHO,PROFUNDO,NCM\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxArticulo = ll_get(listaAux, i);
			   if(auxArticulo!=NULL)
			   {
					fprintf(pFile,"%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n",
					art_getCodigo(auxArticulo, &flagError),art_getNombre(auxArticulo, &flagError),art_getPaisFabricacion(auxArticulo, &flagError),art_getValorFob(auxArticulo, &flagError),
					art_getPeso(auxArticulo, &flagError),art_getAlto(auxArticulo, &flagError),
					art_getAncho(auxArticulo, &flagError),art_getProfundidad(auxArticulo, &flagError),
					art_getNomenclatura(auxArticulo, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }
   return retorno;
   ll_deleteLinkedList(listaAux);
}
int controller_ListarArticulosLinkedList(LinkedList* pLista)
{
	int retorno = -1;
	int size;
	int flagError;
	Articulo* auxArticulo;
	size = ll_len(pLista);
	if(pLista != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxArticulo = (Articulo*)ll_get(pLista, i);
			printf("Codigo: [%s]\tNombre: [%s]\tHecho en: [%s]\tFOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\n",art_getCodigo(auxArticulo, &flagError),art_getNombre(auxArticulo, &flagError),art_getPaisFabricacion(auxArticulo, &flagError),art_getValorFob(auxArticulo, &flagError),art_getPeso(auxArticulo, &flagError)
					,art_getAlto(auxArticulo, &flagError),art_getAncho(auxArticulo, &flagError),art_getProfundidad(auxArticulo, &flagError));
		}
		retorno = 0;
	}
    return retorno;
}

int codigoUsado(Dictionary* pDictionaryArt, char* arg)
{
	int retorno = -1;
	int flagError=-1;
	LinkedList* listaAux;
	int size;
	char* codigoAux;
	Articulo* artAux;
	listaAux = dict_getValues(pDictionaryArt);
	size = ll_len(listaAux);
	for(int i=0;i<size;i++)
	{
		artAux = ll_get(listaAux, i);
		codigoAux = art_getCodigo(artAux, &flagError);
		if(strcmp(codigoAux,arg)==0)
		{
			retorno = 0;
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}

int posArusado(Dictionary* pDictionaryPosAr, char* arg)
{
	int retorno = -1;
	int flagError=-1;
	LinkedList* listaAux;
	int size;
	char* nomencladorAux;
	PosArancelaria* artPosAr;
	listaAux = dict_getValues(pDictionaryPosAr);
	size = ll_len(listaAux);
	for(int i=0;i<size;i++)
	{
		artPosAr = ll_get(listaAux, i);
		nomencladorAux = posAr_getNomenclatura(artPosAr, &flagError);
		if(strcmp(nomencladorAux,arg)==0)
		{
			retorno = 0;
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}
/*****************************************************************************************************************************************************/

int controller_loadPosArancelariaFromText(char* path , Dictionary* pDictionary)
{

	if(path!=NULL && pDictionary!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_posArancelariaFromText(pFile, pDictionary);
			fclose(pFile);
		}
	}
	return 0;
}

int controller_addPosArancelaria(Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	char auxNomenclatura[50];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	char tipoDeLicencia[50];
	PosArancelaria* auxPosArancelaria;

	if(pDictionaryPosArancelaria!=NULL)
	{
		if(utn_getString(auxNomenclatura,sizeof(auxNomenclatura),"Ingrese la nomenclatura:\n","Nomenclatura invalida.\n",3)==0)
		{
			if(posArusado(pDictionaryPosArancelaria, auxNomenclatura)!=0)
			{
				if(	utn_getNumeroFloat(&porcentajeSeguro, "Ingrese el porcentaje del seguro:\n", "Porcentaje invalido.\n", 0,100, 3)==0 &&
					utn_getNumeroFloat(&porcentajeImportacion, "Ingrese el porcentaje de importacion:\n", "Porcentaje invalido.\n", 0,100, 3)==0 &&
					utn_getNumeroFloat(&porcentajeTasaEst, "Ingrese el porcentaje de la tasa de estadistica:\n", "Porcentaje invaludo.\n", 0,100, 3)==0 &&
					utn_getTipo(tipoDeLicencia,sizeof(tipoDeLicencia),"Ingrese el tipo de licencia (AUTOMATICA / NO AUTOMATICA) :\n","Tipo invalido.\n", 3)==0)
				{
					auxPosArancelaria = posAr_newParam(auxNomenclatura, porcentajeSeguro, porcentajeImportacion, porcentajeTasaEst, tipoDeLicencia);
					if(auxPosArancelaria!=NULL)
					{
						dict_insert(pDictionaryPosArancelaria,auxNomenclatura,auxPosArancelaria);
						printf("Posicion arancelaria agregada con exito.\n");
						retorno=0;
					}
				}
			}
			else
			{
				printf("La nomenclatura ya es utilizada, pruebe con otra.\n");
			}
		}

	}
	return retorno;
}

int controller_editPosArancelaria(Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	//char auxNomenclatura[50];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	char tipoDeLicencia[50];
	char cadenaAModificar[50];
	int opcion;
	PosArancelaria* auxPosArancelaria;

	if(pDictionaryPosArancelaria!=NULL)
	{
		controller_ListarPosArancelaria(pDictionaryPosArancelaria);
		if(utn_getString(cadenaAModificar,sizeof(cadenaAModificar),"Ingrese la nomenclatura de la posicion arancelaria a modificar:\n","Error nomenclatura incorrecta.\n",3)==0)
		{
			auxPosArancelaria = dict_get(pDictionaryPosArancelaria,cadenaAModificar);
			if(auxPosArancelaria!=NULL)
			{
				if(utn_getNumero(&opcion, "Que desea modificar?\n1)Porcentaje de seguro.\n2)Porcentaje de importacion.\n3)Porcentaje de tasa de estadistica.\n"
						"4)Tipo de licencia.\n","[Error]Incorrecto.\n", 1, 4, 3)==0)
				{
					switch (opcion) {
						case 1:
							if(utn_getNumeroFloat(&porcentajeSeguro, "Ingrese el porcentaje del seguro:\n", "Porcentaje invalido.\n", 0,100, 3)==0)
							{
								if(posAr_setPorcentajeSeguro(auxPosArancelaria, porcentajeSeguro)==0)
								{
									printf("Posicion arancelaria modificada con exito.\n");
								}
							}
							break;
						case 2:
							if(utn_getNumeroFloat(&porcentajeImportacion, "Ingrese el porcentaje de importacion:\n", "Porcentaje invalido.\n", 0,100, 3)==0)
							{
								if(posAr_setPorcentajeImportacion(auxPosArancelaria, porcentajeImportacion)==0)
								{
									printf("Posicion arancelaria modificada con exito.\n");
								}
							}
							break;
						case 3:
							if(utn_getNumeroFloat(&porcentajeTasaEst, "Ingrese el porcentaje de la tasa de estadistica:\n", "Porcentaje invaludo.\n", 0,100, 3)==0)
							{
								if(posAr_setPorcentajeTasaEst(auxPosArancelaria, porcentajeTasaEst)==0)
								{
									printf("Posicion arancelaria modificada con exito.\n");
								}
							}
							break;
						case 4:
							if(utn_getTipo(tipoDeLicencia,sizeof(tipoDeLicencia),"Ingrese el tipo de licencia (AUTOMATICO / NO AUTOMATICO):\n","Tipo de licencia invalida.\n",3)==0)
							{
								if(posAr_setTipoDeLicencia(auxPosArancelaria, tipoDeLicencia)==0)
								{
									printf("Posicion arancelaria modificada con exito.\n");
								}
							}
							break;
					}
				}
			}
			else
			{
				printf("La posicion arancelaria no existe.\n");
			}
		}
	}
	return retorno;
}

int controller_removePosArancelaria(Dictionary* pDictionaryPosArancelaria, Dictionary* pDictionaryArticulo)
{
	int retorno=-1;
	int size;
	char* nomenclaturaArt;
	int flagError;
	int flagFirst=0;
	char cadenaAEliminar[50];
	PosArancelaria* auxPosArancelaria;
	Articulo* auxArticulo;
	LinkedList* pLista;

	if(pDictionaryPosArancelaria!=NULL && pDictionaryArticulo != NULL)
	{
		pLista = dict_getValues(pDictionaryArticulo);
		size = ll_len(pLista);
		controller_ListarPosArancelaria(pDictionaryPosArancelaria);
		if(utn_getString(cadenaAEliminar,sizeof(cadenaAEliminar),"Ingrese la nomenclatura a eliminar:\n","Error nomenclatura invalida.\n",3)==0)
		{
			auxPosArancelaria = dict_get(pDictionaryPosArancelaria, cadenaAEliminar);
			if(auxPosArancelaria != NULL)
			{
				for(int i=0;i<size;i++)
				{
					auxArticulo = ll_get(pLista, i);
					nomenclaturaArt = art_getNomenclatura(auxArticulo, &flagError);
					if(strcmp(nomenclaturaArt,cadenaAEliminar)==0)
					{
						flagFirst = 1;
						printf("Codigo: [%s]\tNombre: [%s]\n",art_getCodigo(auxArticulo, &flagError), art_getNombre(auxArticulo, &flagError));
					}
				}
				if(flagFirst == 1)
				{
					printf("ERROR, estos articulos estan utilizando la posicion arancelaria ingresada.\n");
				}
				else
				{
					if(posAr_delete(auxPosArancelaria)==0 && dict_remove(pDictionaryPosArancelaria, cadenaAEliminar)==0)
					{
						printf("Posicion arancelaria eliminada con exito.\n");
					}

				}
			}
			else
			{
				printf("La posicion arancelaria no existe.\n");
			}
		}
	}
	ll_deleteLinkedList(pLista);
	return retorno;
}

int controller_savePosArancelariaAsText(char* path , Dictionary* diccionarioPosArancelaria)
{
   int retorno = -1;
   PosArancelaria* auxPosArancelaria;
   LinkedList* listaAux;
   FILE* pFile;
   int flagError;
   int longitud;

   listaAux = dict_getValues(diccionarioPosArancelaria);
   longitud = ll_len(listaAux);
   if(path!=NULL && diccionarioPosArancelaria!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"NCM,SEGURO,DERECHO,TASA,TIPO_LICENCIA\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxPosArancelaria = (PosArancelaria*)ll_get(listaAux, i);
			   if(auxPosArancelaria!=NULL)
			   {
					fprintf(pFile,"%s,%.2f,%.2f,%.2f,%s\n",posAr_getNomenclatura(auxPosArancelaria, &flagError),
															posAr_getPorcentajeSeguro(auxPosArancelaria, &flagError),
															posAr_getPorcentajeImportacion(auxPosArancelaria, &flagError),
															posAr_getPorcentajeTasaEst(auxPosArancelaria, &flagError),
															posAr_getTipoDeLicencia(auxPosArancelaria, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }

   return retorno;
   ll_deleteLinkedList(listaAux);
}

int controller_ListarPosArancelaria(Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	int size;
	int flagError;
	PosArancelaria* auxPosArancelaria;
	LinkedList* listaAux;
	listaAux = dict_getValues(pDictionaryPosArancelaria);
	size = ll_len(listaAux);
	if(pDictionaryPosArancelaria != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxPosArancelaria = (PosArancelaria*)ll_get(listaAux, i);

			printf("Nomenclador:[%s]\tSeguro:[%.2f]\tPorcentajeDeImportacion:[%.2f]\tTasaEstadistica:[%.2f]\tTipoDeLicencia[%s]\n",
					posAr_getNomenclatura(auxPosArancelaria, &flagError),posAr_getPorcentajeSeguro(auxPosArancelaria, &flagError),posAr_getPorcentajeImportacion(auxPosArancelaria, &flagError),
					posAr_getPorcentajeTasaEst(auxPosArancelaria, &flagError),posAr_getTipoDeLicencia(auxPosArancelaria, &flagError));
		}
		retorno = 0;
	}
    return retorno;
    ll_deleteLinkedList(listaAux);
}

/***********************************************************************************************************************************************************/

int controller_loadMaritimoFromText(char* path , LinkedList* pListaMaritimo)
{

	if(path!=NULL && pListaMaritimo!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_maritimoFromText(pFile, pListaMaritimo);
			fclose(pFile);
		}
	}
	return 0;
}

int controller_editMaritimo(LinkedList* pListaMaritimo)
{
	int retorno = -1;
	float metrosCubicos;
	float valorContenedor;
	int posicion = 0;
	int opcion;
	Maritimo* auxMaritimo;

	if(pListaMaritimo!=NULL)
	{
		auxMaritimo = (Maritimo*)ll_get(pListaMaritimo,posicion);
		if(auxMaritimo!=NULL)
		{
			if(utn_getNumero(&opcion, "Que desea modificar?\n1)Metros cubicos.\n2)Valor del contenedor.\n","[Error]Incorrecto.\n", 1, 2, 3)==0)
			{
				switch (opcion) {
					case 1:
						if(utn_getNumeroFloat(&metrosCubicos, "Ingrese nuevos metros cubicos.\n", "Error longitud invalida.\n", 0, 99999, 3)==0)
						{
							if(mar_setMtsCubicos(auxMaritimo, metrosCubicos)==0)
							{
								printf("Valor maritimo modificado con exito.\n");
							}
						}
						break;
					case 2:
						if(utn_getNumeroFloat(&valorContenedor, "Ingrese el nuevo valor del contenedor:\n", "Valor invalido.\n", 1,999999, 3)==0)
						{
							if(mar_setPrecio(auxMaritimo, valorContenedor)==0)
							{
								printf("Valor maritimo modificado con exito.\n");
							}
						}
						break;
				}
			}
		}
	}

	return retorno;
}

int controller_saveMaritimoAsText(char* path , LinkedList* listaMaritimo)
{
   int retorno = -1;
   Maritimo* auxMaritimo;
   FILE* pFile;
   int flagError;
   int longitud;

   longitud = ll_len(listaMaritimo);
   if(path!=NULL && listaMaritimo!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"MetrosCubicos,PrecioContenedor\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxMaritimo = (Maritimo*)ll_get(listaMaritimo, i);
			   if(auxMaritimo!=NULL)
			   {
					fprintf(pFile,"%.2f,%.2f\n",mar_getMtsCubicos(auxMaritimo, &flagError),mar_getPrecio(auxMaritimo, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }

   return retorno;
}

int controller_ListarMaritimo(LinkedList* pListaMaritimo)
{
	int retorno = -1;
	int size;
	int flagError;
	Maritimo* auxMaritimo;
	size = ll_len(pListaMaritimo);
	if(pListaMaritimo != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxMaritimo = (Maritimo*)ll_get(pListaMaritimo, i);

			printf("Metros Cubicos: [%.2f]\t Valor del contenedor: [%.2f]\n",
			mar_getMtsCubicos(auxMaritimo, &flagError),mar_getPrecio(auxMaritimo, &flagError));
		}
		retorno = 0;
	}
    return retorno;
}

/**********************************************************************************************************************************************/

int controller_loadAereoFromText(char* path , LinkedList* pListaAereo)
{

	if(path!=NULL && pListaAereo!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_aereoFromText(pFile, pListaAereo);
			fclose(pFile);
		}
	}
	return 0;
}

int controller_editAereo(LinkedList* pListaAereo)
{
	int retorno = -1;
	float constVolumetrica;
	float valorPorKg;
	int posicion = 0;
	int opcion;
	Aereo* auxAereo;

	if(pListaAereo!=NULL)
	{
		auxAereo = (Aereo*)ll_get(pListaAereo,posicion);
		if(auxAereo!=NULL)
		{
			if(utn_getNumero(&opcion, "Que desea modificar?\n1)Constante volumetrica.\n2)Valor por KG.\n","[Error]Incorrecto.\n", 1, 2, 3)==0)
			{
				switch (opcion) {
					case 1:
						if(utn_getNumeroFloat(&constVolumetrica, "Ingrese nueva constante volumetrica.\n", "Error constante volumetrica invalida.\n", 1, 99999, 3)==0)
						{
							if(aer_setConstVolum(auxAereo, constVolumetrica)==0)
							{
								printf("Valor aereo modificado con exito.\n");
								retorno = 0;
							}

						}
						break;
					case 2:
						if(utn_getNumeroFloat(&valorPorKg, "Ingrese el nuevo valor por KG:\n", "Valor invalido.\n", 1,99999, 3)==0)
						{
							if(aer_setPrecio(auxAereo, valorPorKg)==0)
							{
								printf("Valor aereo modificado con exito.\n");
								retorno = 0;
							}

						}
						break;
				}
			}
		}
	}
	return retorno;
}

int controller_saveAereoAsText(char* path , LinkedList* listaAereo)
{
   int retorno = -1;
   Aereo* auxAereo;
   FILE* pFile;
   int flagError;
   int longitud;

   longitud = ll_len(listaAereo);
   if(path!=NULL && listaAereo!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"ConstanteVolumetrica,ValorXKg\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxAereo = (Aereo*)ll_get(listaAereo, i);
			   if(auxAereo!=NULL)
			   {
					fprintf(pFile,"%.2f,%.2f\n",aer_getConstVolum(auxAereo, &flagError),aer_getPrecio(auxAereo, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }

   return retorno;
}

int controller_ListarAereo(LinkedList* listaAereo)
{
	int retorno = -1;
	int size;
	int flagError;
	Aereo* auxAereo;
	size = ll_len(listaAereo);
	if(listaAereo != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxAereo = (Aereo*)ll_get(listaAereo, i);

			printf("Constante Volumetrica:[%.2f]\tPrecio:[%.2f]\n",
					aer_getConstVolum(auxAereo, &flagError),aer_getPrecio(auxAereo, &flagError));
		}
		retorno = 0;
	}
    return retorno;
}

int controller_ListarOrdenadoYAchicado(Dictionary* pDictionaryArticulo,Dictionary* pDictionaryPosArancelaria,LinkedList* pListaMaritimo, LinkedList* pListaAereo)
{
	int retorno = -1;

	if(pDictionaryArticulo != NULL && pDictionaryPosArancelaria != NULL && pListaAereo != NULL && pListaMaritimo != NULL)
	{
		info_cargarArticulosConCostosFinales(pDictionaryArticulo, pDictionaryPosArancelaria, pListaMaritimo, pListaAereo);
		info_imprimirListaAchicada(pDictionaryArticulo);
	}
	return retorno;
}

