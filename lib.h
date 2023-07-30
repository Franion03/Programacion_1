#ifndef _lib_H_
#define _lib_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct Numero
{
    double valor;
    int decimales;
    struct Numero *siguiente, *anterior;
   
}TNUM;

typedef struct 
{
    int n; // numero de elementos de la lista
    TNUM *primero, *ultimo;
}TLISTA;

typedef struct Var
{
    char nombre[20];
    TLISTA *valor;
    struct Var *siguiente, *anterior;
}TVAR;

typedef struct 
{
    int n; // numero de elementos de la lista
    TVAR *var1;
}TVARS;


void hola();
TVARS *crear_workspace(TVARS *workspace);
TVAR *crearVariable (char *nombrevariable, TLISTA *lista);
TNUM *crearListaNum(double valor, int dec);
int validar_variable(char *nombre);
char *MiStrTok(char *cad1, char *sep, int comillas);
int esSimbolo(char *simbolo);
int expansionCorchetes(char* separadores, char *comtok, TLISTA *listaaux);
int validar_corchetes(char *cadena); 
int decimalValidar (char *cad);
int enteroValidar (char *cad);
TLISTA *crearLista();
int NumDecimales (char *cad);
TLISTA * CombinacionListas(TLISTA *listaux, TLISTA *listaux2);
void verLista(TLISTA *lista);
TLISTA * RestaListas(TLISTA *listaux, TLISTA *listaux2);
TLISTA *crearDuplicadoLista(TLISTA *lista);
void eliminarElementoLista(TLISTA *lista, double valor);
int listaOvariable(char *cad);
TVAR *insertaUltimaLaGranVariable(TVAR *laGranVariable, TVAR *variable);
TVAR *buscarVariable (TVAR *laGranVariable, char *nombrevariable);
int contenidaLista(TLISTA *listaux, TLISTA *listaux2);
int contarCaracter(char **cadena, char *caracter);
TLISTA *operar(char** cadena, TVAR *laGranVariable,int num_arg);
TLISTA *charToList(char *cadena,TVAR *laGranVariable);
TLISTA *copiarNlistaPrimeras(TLISTA *lista,int n);


#endif