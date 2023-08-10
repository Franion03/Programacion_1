#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "lib.h"


//gcc lib.c main.c -o main.exe

/* 
    Verde: 2
    Rojo: 4
    Blanco: 7
*/

int main(int argc, char *argv[])
{
    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Variables
    char prompt[100] = "*";
    char command[100], commandAux[100];
    char separadores[8] = " \t\n";
    char *comtok[100];
    char *comtokaux[100];
    char *corchete, *corcheteAux, *aux;
    int LALLAVE = 0, numeroLLAVES;

    char **AUX;

    int num_arg,auxMistrtok,cortafuegos=0;

    TVARS *workspace = NULL;
    TVAR *LaGranVariable = NULL; // Se guardan todos los datos de las listas (nombre incluido)
    TLISTA *lista = NULL;
    TNUM *elemento = NULL;



    hola();

    //Crear un workspace nuevo
    workspace = crear_workspace(workspace);

    while(1){
        SetConsoleTextAttribute(hConsole, 7);
        printf("<%s>: ", prompt);
        gets(command);
        strcpy(commandAux, command);

        
        if(validar_corchetes(commandAux) == 0){
            printf("corchetes Incorrectos \n");
            continue;
        }
        num_arg = 0;
        comtok[num_arg] = MiStrTok(commandAux, separadores, 1);
        printf("comtok[%d]: %s\n", num_arg, comtok[num_arg]);
        num_arg++;
        while ((comtok[num_arg] = MiStrTok(NULL, separadores, 1)) != NULL){
            printf("comtok[%d]: %s\n", num_arg, comtok[num_arg]);
            num_arg++;
        }
        if(comtok[0] == NULL){
            continue;
        }
        if(strcmp(comtok[0], "exit") == 0 && num_arg == 1){
            //liberar memoria
            SetConsoleTextAttribute(hConsole, 2);
            printf("Bye, bye\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 0;
        } else if(strcmp(comtok[0], "isIn") == 0){  
            if(num_arg != 3){
                printf("Error de sintaxis\n");
                continue;
            }
            if((enteroValidar(comtok[1]) == 0) && (atoi(comtok[1]) <= 0)){
                printf("Error de sintaxis\n");
                continue;
            }
            TVAR *aux;
            TLISTA *listaux = crearLista();
            TLISTA *listaux2 = crearLista();
            listaux = charToList(comtok[1], LaGranVariable);
            listaux2 = charToList(comtok[2], LaGranVariable);
            //Aqui tenemos que comparar una lista contra otra
            if(contenidaLista(listaux2, listaux) == 1){
                printf("TRUE\n");
            } else{
                printf("FALSE\n");
            }
            continue;
        } else if(strcmp(comtok[0], "vars") == 0){
            if(num_arg != 1){
                printf("Error de sintaxis\n");
                continue;
            }
            laGranVista(LaGranVariable);
        } else if(strcmp(comtok[0], "save") == 0){
            if(num_arg != 2){
                printf("Error de sintaxis\n");
                continue;
            }
            workspace->n = imprimirTVAR(LaGranVariable);
            printf("workspace->n: %d\n", workspace->n);
            workspace->var1 = LaGranVariable;
            save(comtok[1], workspace);
        } else if(strcmp(comtok[0], "load") == 0){
            printf("load\n");
        } else if(num_arg > 1 && strcmp(comtok[1], "=") == 0){ // a = [1,2,3] OK
            if(listaOvariable(comtok[0]) != 0){
                printf("Error de sintaxis\n");
                continue;
            }
            
            TVAR *variableAsignar = buscarVariable(LaGranVariable, comtok[0]);
            if(variableAsignar == NULL){
                variableAsignar = crearVariable(comtok[0], NULL);
            }
            variableAsignar->valor = operar(&comtok[2],LaGranVariable,num_arg-2);
            
            verLista(variableAsignar->valor);
            LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable,variableAsignar);
            continue;
        } else if(num_arg > 1 && strcmp(comtok[1], "#") == 0 && num_arg <= 3){ // a = [1,2,3] OK
            int comprobante = 0;
            TVAR *aux;
            TLISTA *listaux = crearLista();
            TLISTA *listaux2 = crearLista();
            
            listaux = charToList(comtok[0], LaGranVariable);
            listaux2 = charToList(comtok[2], LaGranVariable);
            //Aqui tenemos que comparar una lista contra otra
            if(contenidaLista(listaux2, listaux) == 1){
                printf("TRUE\n");
            } else{
                printf("FALSE\n");
            }
            continue;
        } else {
            TLISTA* listToPrint = operar(comtok,LaGranVariable,num_arg);
            if(listToPrint != NULL){
                verLista(listToPrint);
            }
        }
    }    
    return 0;
}