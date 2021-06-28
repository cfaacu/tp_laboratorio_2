/*
 * Articulo.c
 *
 *  Created on: Jun 15, 2021
 *      Author: facu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Dictionary.h"
#include "utn.h"
#include "Articulo.h"

Articulo* art_new(void)
{
	return (Articulo*) malloc(sizeof(Articulo));
}

Articulo* art_newParametros(char* codigo,char* nombre,char* paisFabricacion,float valorFob,float peso, float alto, float ancho, float profundidad, char* nomencladorPosAr)
{
	Articulo* auxArticulo = art_new();
	if(auxArticulo != NULL)
	{
		if  (	art_setCodigo(auxArticulo,codigo) < 0 ||
				art_setNombre(auxArticulo, nombre) < 0 ||
				art_setPaisFabricacion(auxArticulo, paisFabricacion) < 0 ||
				art_setValorFob(auxArticulo, valorFob) < 0 ||
				art_setPeso(auxArticulo, peso) < 0 ||
				art_setAlto(auxArticulo, alto) < 0 ||
				art_setAncho(auxArticulo, ancho) < 0 ||
				art_setProfundidad(auxArticulo, profundidad) < 0 ||
				art_setNomenclatura(auxArticulo, nomencladorPosAr) < 0)
		{
			art_delete(auxArticulo);
			auxArticulo = NULL;
		}
	}
	return auxArticulo;;
}

Articulo* art_newParametrosTxt(char* codigo,char* nombre,char* paisFabricacion,char* valorFob,char* peso, char* alto, char* ancho, char* profundidad, char* nomencladorPosAr)
{
	Articulo* auxArticulo = art_new();
	if(auxArticulo != NULL)
	{
		if  (	art_setCodigo(auxArticulo, codigo) < 0 ||
				art_setNombre(auxArticulo, nombre) < 0 ||
				art_setPaisFabricacion(auxArticulo, paisFabricacion) < 0 ||
				art_setValorFob(auxArticulo, atof(valorFob)) < 0 ||
				art_setPeso(auxArticulo, atof(peso)) < 0 ||
				art_setAncho(auxArticulo, atof(ancho)) < 0 ||
				art_setAlto(auxArticulo, atof(alto)) < 0 ||
				art_setProfundidad(auxArticulo, atof(profundidad)) < 0 ||
				art_setNomenclatura(auxArticulo, nomencladorPosAr) < 0)
		{
			art_delete(auxArticulo);
			auxArticulo = NULL;
		}
	}
	return auxArticulo;
}

int art_delete(Articulo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int art_setNombre(Articulo* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && isNombreArticulo(nombre)==0 )
	{
		strcpy(this->nombre,nombre);
		retorno = 0;
	}
	return retorno;
}

char* art_getNombre(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre = NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}

int art_setCodigo(Articulo* this, char* codigo)
{
	int retorno = -1;
	if(this != NULL && codigo != NULL && isAlphanumeric(codigo)==0 )
	{
		strcpy(this->codigo,codigo);
		retorno = 0;
	}
	return retorno;
}

char* art_getCodigo(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxCodigo= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxCodigo = this->codigo;
		*flagError = 0;
	}
	return auxCodigo;
}

int art_setPaisFabricacion(Articulo* this, char* paisFabricacion)
{
	int retorno = -1;
	if(this != NULL && paisFabricacion != NULL && isName(paisFabricacion)==0 )
	{
		strcpy(this->paisDeFabricacion,paisFabricacion);
		retorno = 0;
	}
	return retorno;
}

char* art_getPaisFabricacion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxPaisFabricacion= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxPaisFabricacion = this->paisDeFabricacion;
		*flagError = 0;
	}
	return auxPaisFabricacion;
}

int art_setValorFob(Articulo* this, float valorFob)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(valorFob)==0 )
	{
		this->valorFob = valorFob;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFob(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxValorFob = -1;
	if(this != NULL && flagError != NULL )
	{
		auxValorFob=this->valorFob;
		*flagError = 0;
	}
	return auxValorFob;
}

int art_setPeso(Articulo* this, float peso)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(peso)==0 )
	{
		this->peso = peso;
		retorno = 0;
	}
	return retorno;
}

float art_getPeso(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxPeso = -1;
	if(this != NULL && flagError != NULL )
	{
		auxPeso=this->peso;
		*flagError = 0;
	}
	return auxPeso;
}

int art_setAncho(Articulo* this, float ancho)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(ancho)==0)
	{
		this->ancho = ancho;
		retorno = 0;
	}
	return retorno;
}

float art_getAncho(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxAncho = -1;
	if(this != NULL && flagError != NULL )
	{
		auxAncho=this->ancho;
		*flagError = 0;
	}
	return auxAncho;
}

int art_setAlto(Articulo* this, float alto)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(alto)==0)
	{
		this->alto = alto;
		retorno = 0;
	}
	return retorno;
}

float art_getAlto(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxAlto = -1;
	if(this != NULL && flagError != NULL )
	{
		auxAlto=this->alto;
		*flagError = 0;
	}
	return auxAlto;
}

int art_setProfundidad(Articulo* this, float profundidad)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(profundidad)==0)
	{
		this->profundidad = profundidad;
		retorno = 0;
	}
	return retorno;
}

float art_getProfundidad(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxProfundidad = -1;
	if(this != NULL && flagError != NULL )
	{
		auxProfundidad=this->profundidad;
		*flagError = 0;
	}
	return auxProfundidad;
}

int art_setNomenclatura(Articulo* this, char* nomenclatura)
{
	int retorno = -1;
	if(this != NULL && nomenclatura != NULL && isAlphanumeric(nomenclatura)==0 )
	{
		strcpy(this->nomenclaturaPosAr,nomenclatura);
		retorno = 0;
	}
	return retorno;
}

char* art_getNomenclatura(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* nomenclatura = NULL;
	if(this != NULL && flagError != NULL )
	{
		nomenclatura = this->nomenclaturaPosAr;
		*flagError = 0;
	}
	return nomenclatura;
}

int art_setValorFinalAereo(Articulo* this, float valorFinalAereo)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(valorFinalAereo)==0 )
	{
		this->valorFinalAereo = valorFinalAereo;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFinalAereo(Articulo* this,int* flagError)
{
	*flagError = -1;
	float valorFinalAereo = -1;
	if(this != NULL && flagError != NULL )
	{
		valorFinalAereo=this->valorFinalAereo;
		*flagError = 0;
	}
	return valorFinalAereo;
}

int art_setValorFinalMaritimo(Articulo* this, float valorFinalMaritimo)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(valorFinalMaritimo)==0 )
	{
		this->valorFinalMaritimo = valorFinalMaritimo;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFinalMaritimo(Articulo* this,int* flagError)
{
	*flagError = -1;
	float valorFinalMaritimo = -1;
	if(this != NULL && flagError != NULL )
	{
		valorFinalMaritimo=this->valorFinalMaritimo;
		*flagError = 0;
	}
	return valorFinalMaritimo;
}
/********************************************************************************************************************************/

//static int contador=0;

/** \brief Setea el valor inicial del id obtenido de una lista.
 * \param LinkedList* pArrayListEmployee Lista para obtener los datos.
 * \return void
 */
/*void art_setearValorInicialDeId(Dictionary* pDictionaryArticulo)
{
	Articulo* pArt;
	LinkedList* listaAux;
	int id;
	int idMax;
	int size;
	int flagError;

	if(pDictionaryArticulo != NULL)
	{
		listaAux = dict_getValues(pDictionaryArticulo);
		size = ll_len(listaAux);
		for(int i=0;i<size;i++)
		{
			pArt = ll_get(listaAux, i);
			if(pArt != NULL)
			{
				id = art_getIdArticulo(pArt, &flagError);
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
}
*/
/** \brief Generador de ID
 * \param Void
 * \return int devulve el ID
 */
/*int art_generarId(void)
{
	contador++;
	return contador;
}*/
