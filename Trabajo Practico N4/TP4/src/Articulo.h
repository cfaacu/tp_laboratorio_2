/*
 * Articulo.h
 *
 *  Created on: Jun 15, 2021
 *      Author: facu
 */

#ifndef ARTICULO_H_
#define ARTICULO_H_

#include "Dictionary.h"

#define CODIGO_LEN 50
#define DESCRIPCION_LEN 50
#define PAIS_LEN 50
#define NOMBRE_LEN 50
#define NOMENCLATURA_LEN 50

typedef struct
{
	char codigo [CODIGO_LEN];
	char nombre [NOMBRE_LEN];
	char paisDeFabricacion [PAIS_LEN];
	char nomenclaturaPosAr [NOMENCLATURA_LEN];
	float valorFob;
	float peso;
	float ancho;
	float alto;
	float profundidad;
	float valorFinalMaritimo;
	float valorFinalAereo;
}Articulo;

Articulo* art_new(void);
Articulo* art_newParametros(char* codigo,char* nombre,char* paisFabricacion,float valorFob,float peso, float alto, float ancho, float profundidad, char* nomencladorPosAr);
Articulo* art_newParametrosTxt(char* codigo,char* nombre,char* paisFabricacion,char* valorFob,char* peso, char* alto, char* ancho, char* profundidad, char* nomencladorPosAr);

int art_delete(Articulo* this);

int art_setNombre(Articulo* this, char* nombre);
char* art_getNombre(Articulo* this,int* flagError);

int art_setCodigo(Articulo* this, char* codigo);
char* art_getCodigo(Articulo* this,int* flagError);

int art_setPaisFabricacion(Articulo* this, char* paisFabricacion);
char* art_getPaisFabricacion(Articulo* this,int* flagError);

int art_setValorFob(Articulo* this, float valorFob);
float art_getValorFob(Articulo* this,int* flagError);

int art_setPeso(Articulo* this, float peso);
float art_getPeso(Articulo* this,int* flagError);

int art_setAncho(Articulo* this, float ancho);
float art_getAncho(Articulo* this,int* flagError);

int art_setAlto(Articulo* this, float alto);
float art_getAlto(Articulo* this,int* flagError);

int art_setProfundidad(Articulo* this, float profundidad);
float art_getProfundidad(Articulo* this,int* flagError);

int art_setIdAereo(Articulo* this, int idAereo);
int art_getIdAereo(Articulo* this,int* flagError);

int art_setIdMaritimo(Articulo* this, int idMaritimo);
int art_getIdMaritimo(Articulo* this,int* flagError);

int art_setNomenclatura(Articulo* this, char* nomenclatura);
char* art_getNomenclatura(Articulo* this,int* flagError);

int art_setValorFinalAereo(Articulo* this, float valorFinalAereo);
float art_getValorFinalAereo(Articulo* this,int* flagError);

int art_setValorFinalMaritimo(Articulo* this, float valorFinalMaritimo);
float art_getValorFinalMaritimo(Articulo* this,int* flagError);

int art_generarId(void);
void art_setearValorInicialDeId(Dictionary* pDictionaryArticulo);


#endif /* ARTICULO_H_ */
