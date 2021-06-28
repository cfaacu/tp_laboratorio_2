/*
 * PosArancelaria.h
 *
 *  Created on: Jun 16, 2021
 *      Author: facu
 */

#ifndef POSARANCELARIA_H_
#define POSARANCELARIA_H_

#include "Dictionary.h"
#include "PosArancelaria.h"

#define NOMENCLATURA_LEN 50
#define LICENCIA_LEN 50
typedef struct{
	char nomenclatura [NOMENCLATURA_LEN];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	char tipoDeLicencia[LICENCIA_LEN];
}PosArancelaria;

PosArancelaria* posAr_new(void);
int posAr_delete(PosArancelaria* this);
PosArancelaria* posAr_newParam(char* nomenclatura,float porcentajeSeguro,float porcentajeImportacion,float porcentajeTasaEst,char* tipoLicencia);
PosArancelaria* posAr_newParamTxt(char* nomenclatura,char* porcentajeSeguro,char* porcentajeImportacion,char* porcentajeTasaEst,char* tipoLicencia);

int posAr_setNomenclatura(PosArancelaria* this, char* nomenclatura);
char* posAr_getNomenclatura(PosArancelaria* this,int* flagError);

int posAr_setPorcentajeSeguro(PosArancelaria* this, float porcentajeSeguro);
float posAr_getPorcentajeSeguro(PosArancelaria* this,int* flagError);

int posAr_setPorcentajeImportacion(PosArancelaria* this, float porcentajeImportacion);
float posAr_getPorcentajeImportacion(PosArancelaria* this,int* flagError);

int posAr_setPorcentajeTasaEst(PosArancelaria* this, float porcentajeTasaEst);
float posAr_getPorcentajeTasaEst(PosArancelaria* this,int* flagError);

int posAr_setTipoDeLicencia(PosArancelaria* this, char* tipoDeLicencia);
char* posAr_getTipoDeLicencia(PosArancelaria* this,int* flagError);

int posAr_setearValorInicialDeId(Dictionary* pDictionaryPosArancelaria);
int posAr_generarId(void);

#endif /* POSARANCELARIA_H_ */
