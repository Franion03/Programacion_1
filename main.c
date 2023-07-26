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

    int num_arg,num_arg_aux,auxMistrtok,cortafuegos=0;

    TVARS *workspace = NULL;
    TVAR *LaGranVariable = NULL;
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

        num_arg = 0;
        cortafuegos = 0;
        comtok[num_arg] = strtok(command, separadores);
        num_arg++;
        while((comtok[num_arg] = strtok(NULL, separadores)) != NULL){
            num_arg++;
        }

        if(comtok[0] == NULL){
            continue;
        }

        LALLAVE = 0;    
        numeroLLAVES = 0;

        for (int i = 0; i < num_arg; i++)
        {
            if(strcmp(comtok[i], "[]") == 0){
                LALLAVE=1;
                numeroLLAVES++;
            }
        }

        if(strcmp(comtok[0], "exit") == 0 && num_arg == 1){

            //liberar memoria

            SetConsoleTextAttribute(hConsole, 2);
            printf("Bye, bye\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 0;
        }
        else if(strcmp(comtok[0], "head") == 0){
            printf("head\n");
        }
        else if(strcmp(comtok[0], "tail") == 0){
            printf("tail\n");
        }
        else if(strcmp(comtok[0], "isIn") == 0){
            printf("isIn\n");
        }
        else if(strcmp(comtok[0], "vars") == 0){
            printf("vars\n");
        }
        else if(strcmp(comtok[0], "save") == 0){
            printf("save\n");
        }
        else if(strcmp(comtok[0], "load") == 0){
            printf("load\n");
        }
        else{
            
            if (strchr(commandAux, '[') == NULL && strchr(commandAux, ']') == NULL){ // No se van a usar los corchetes aqui

                printf("No hay corchetes\n");

                num_arg_aux = 0;
                comtok[num_arg_aux] = MiStrTok(commandAux, separadores, 0);
                num_arg_aux++;
                while ((comtok[num_arg_aux] = MiStrTok(NULL, separadores, 0)) != NULL)
                {
                    printf("comtok[%d]: %s\n", num_arg_aux, comtok[num_arg_aux]);
                    num_arg_aux++;
                }

                for (int i = 0; i < num_arg_aux; i++)
                {
                    printf("%s\n", comtok[i]);
                }

                //buscar variable
                TVAR *variable = buscarVariable(LaGranVariable, comtok[0]);
                VerLista(variable->valor);
                
                

                



            }
            else{

                printf("Hay corchetes\n");

                //validar que todos los corchetes que se abren tambien se cierran
                if(validar_corchetes(commandAux) == 0){
                    printf("Hay corchetes mal escritos\n");
                    continue;
                }

                
                if(strchr(comtok[0], '[') == NULL){ // No hay corchetes en el primer argumento
                    
                    
                    int posicion = 0;
                    int contador = 0;

                    for (int i = 0; i < num_arg; i++){
                        if(strcmp(comtok[i], "[]") == 0 ){ // queremos comprobar en el caso de que haya una lista vacia si esta en la primera posicion
                            LALLAVE=1;
                            posicion = i;
                            contador++;
                        }
                    }
                    
                    printf("posicion: %d\n", posicion);
                    printf("contador: %d\n", contador);
                    printf("LALLAVE: %d\n", LALLAVE);
                    
                    if(LALLAVE == 1){

                        if(contador == 2){ // a = [] + []
 

                            if(strcmp(comtok[1], "=") == 0){

                                TLISTA *listaux = crearLista();

                                listaux->primero = NULL;
                                listaux->ultimo = NULL;

                                TVAR *variable = crearVariable(comtok[0], listaux);


                                //miramos si ya existe la variable
                                TVAR *aux = buscarVariable(LaGranVariable, variable->nombre);

                                if(aux == NULL){ // Variable nueva
                                
                                    //imprimir variable
                                    printf("VARIABLE[%s ", variable->nombre);
                                    VerLista(variable->valor);
                                    printf("]\n");

                                    LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable, variable);

                                    //imprimir LaGranVariable
                                    printf("LA GRAN VARIABLE[");
                                    printf("%s ", LaGranVariable->nombre);
                                    VerLista(LaGranVariable->valor);
                                    printf("]\n");

                                    if(LaGranVariable->anterior == NULL){
                                        printf("LaGranVariable->anterior == NULL\n");
                                    }

                                    if(LaGranVariable->siguiente == NULL){
                                        printf("LaGranVariable->siguiente == NULL\n");
                                    }

                                    
                                }
                                else{ //machacamos el valor de la variable
                                    
                                    printf("Variable repetida\n");
                                    aux->valor = variable->valor;

                                }

                                // Aqui nos muestra todas las variables que hemos creado
                                TVAR *Temp = LaGranVariable;
                                while (Temp != NULL)
                                {
                                    printf("LA GRAN VARIABLE[");
                                    printf("%s ", Temp->nombre);
                                    VerLista(Temp->valor);
                                    printf("]\n");
                                    Temp = Temp->siguiente;
                                }
                                

                            }

                        }
                        else if(contador  == 1){

                            if(posicion == 2){ //a = [] + [1 2 3]   // a = [] + b

                                printf("%s\n", commandAux);

                                char *auxiliarletra;
                                TLISTA *listaux = crearLista();

                                auxiliarletra = strchr(commandAux, '[');
                                auxiliarletra = strchr(auxiliarletra+1, '[');

                                if(auxiliarletra == NULL){ // a = [] + b
                                    
                                    for(int i= 0; i < num_arg; i++){
                                        printf("comtok[%d]: %s\n", i, comtok[i]);
                                    }

                                    if(strcmp(comtok[1], "=") == 0){

                                        if(strcmp(comtok[3], "+") == 0){
                                            //Buscamos la variable a copiar
                                            TVAR *variableBuscar = buscarVariable(LaGranVariable, comtok[4]);
                                            TVAR *variableCrear = buscarVariable(LaGranVariable, comtok[0]);

                                            if(variableBuscar == NULL){
                                                printf("Variable no encontrada\n");
                                                continue;
                                            }

                                            if(variableCrear == NULL){ // Variable nueva

                                                TVAR *variable = crearVariable(comtok[0], variableBuscar->valor);
                                    
                                                //imprimir variable
                                                printf("VARIABLE[%s ", variable->nombre);
                                                VerLista(variable->valor);
                                                printf("]\n");

                                                LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable, variable);

                                                //imprimir LaGranVariable
                                                printf("LA GRAN VARIABLE[");
                                                printf("%s ", LaGranVariable->nombre);
                                                VerLista(LaGranVariable->valor);
                                                printf("]\n");

                                                if(LaGranVariable->anterior == NULL){
                                                    printf("LaGranVariable->anterior == NULL\n");
                                                }

                                                if(LaGranVariable->siguiente == NULL){
                                                    printf("LaGranVariable->siguiente == NULL\n");
                                                }

                                                
                                            }
                                            else{ //machacamos el valor de la variable
                                                
                                                printf("Variable repetida\n");
                                                variableCrear->valor = variableBuscar->valor;

                                            }

                                            // Aqui nos muestra todas las variables que hemos creado
                                            TVAR *Temp = LaGranVariable;
                                            while (Temp != NULL)
                                            {
                                                printf("LA GRAN VARIABLE[");
                                                printf("%s ", Temp->nombre);
                                                VerLista(Temp->valor);
                                                printf("]\n");
                                                Temp = Temp->siguiente;
                                            }

                                            continue;

                                        }
                                        else if(strcmp(comtok[3], "-") == 0){

                                            //Buscamos la variable a copiar
                                            TVAR *variableBuscar = buscarVariable(LaGranVariable, comtok[4]);
                                            TVAR *variableCrear = buscarVariable(LaGranVariable, comtok[0]);

                                            if(variableBuscar == NULL){
                                                printf("Variable no encontrada\n");
                                                continue;
                                            }


                                            if(variableCrear == NULL){ // Variable nueva

                                                TVAR *variable = crearVariable(comtok[0], NULL);
                                    
                                                //imprimir variable
                                                printf("VARIABLE[%s ", variable->nombre);
                                                VerLista(variable->valor);
                                                printf("]\n");

                                                LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable, variable);

                                                //imprimir LaGranVariable
                                                printf("LA GRAN VARIABLE[");
                                                printf("%s ", LaGranVariable->nombre);
                                                VerLista(LaGranVariable->valor);
                                                printf("]\n");

                                                if(LaGranVariable->anterior == NULL){
                                                    printf("LaGranVariable->anterior == NULL\n");
                                                }

                                                if(LaGranVariable->siguiente == NULL){
                                                    printf("LaGranVariable->siguiente == NULL\n");
                                                }

                                                
                                            }
                                            else{ //machacamos el valor de la variable
                                                
                                                printf("Variable repetida\n");
                                                variableCrear->valor = NULL;

                                            }

                                            // Aqui nos muestra todas las variables que hemos creado
                                            TVAR *Temp = LaGranVariable;
                                            while (Temp != NULL)
                                            {
                                                printf("LA GRAN VARIABLE[");
                                                printf("%s ", Temp->nombre);
                                                VerLista(Temp->valor);
                                                printf("]\n");
                                                Temp = Temp->siguiente;
                                            }

                                            continue;


                                        }
                                        else{
                                            printf("Error de sintaxis\n");
                                            continue;
                                        }

                                        
                                    }
                                    else{
                                        printf("Error de sintaxis No has puesto igual\n");
                                        continue;
                                    }


                                }
                                else{ // a = [] + [1 2 3]

                                    char aux[100] = "";
                                    int comprobante = 0;

                                    for(int i = 4; i < num_arg-1; i++){
                                        strcat(aux, comtok[i]);
                                        strcat(aux, " ");
                                    }

                                    strcat(aux, comtok[num_arg-1]);

                                    printf("aux: %s\n", aux);

                                    strcpy(aux, aux+1);
                                    aux[strlen(aux)-1] = '\0';


                                    comprobante = Expansioncorchetes(separadores, aux, listaux);

                                    if(comprobante == 1){
                                        printf("Error de sintaxis COMPROBANTE\n");
                                        continue;
                                    }

                                    if(strcmp(comtok[3], "+") == 0){

                                        //buscar la variable
                                        TVAR *variable = buscarVariable(LaGranVariable, comtok[0]);

                                        if(variable == NULL){ // Variable nueva

                                            TVAR *variable = crearVariable(comtok[0], listaux);
                                
                                            //imprimir variable
                                            printf("VARIABLE[%s ", variable->nombre);
                                            VerLista(variable->valor);
                                            printf("]\n");

                                            LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable, variable);

                                            //imprimir LaGranVariable
                                            printf("LA GRAN VARIABLE[");
                                            printf("%s ", LaGranVariable->nombre);
                                            VerLista(LaGranVariable->valor);
                                            printf("]\n");

                                            if(LaGranVariable->anterior == NULL){
                                                printf("LaGranVariable->anterior == NULL\n");
                                            }

                                            if(LaGranVariable->siguiente == NULL){
                                                printf("LaGranVariable->siguiente == NULL\n");
                                            }

                                            
                                        }
                                        else{ //machacamos el valor de la variable
                                            
                                            printf("Variable repetida\n");
                                            variable->valor = listaux;

                                        }


                                    }
                                    else if(strcmp(comtok[3], "-") == 0){

                                        //buscar la variable
                                        TVAR *variable = buscarVariable(LaGranVariable, comtok[0]);

                                        if(variable == NULL){ // Variable nueva

                                            TVAR *variable = crearVariable(comtok[0], NULL);
                                
                                            //imprimir variable
                                            printf("VARIABLE[%s ", variable->nombre);
                                            VerLista(variable->valor);
                                            printf("]\n");

                                            LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable, variable);

                                            //imprimir LaGranVariable
                                            printf("LA GRAN VARIABLE[");
                                            printf("%s ", LaGranVariable->nombre);
                                            VerLista(LaGranVariable->valor);
                                            printf("]\n");

                                            if(LaGranVariable->anterior == NULL){
                                                printf("LaGranVariable->anterior == NULL\n");
                                            }

                                            if(LaGranVariable->siguiente == NULL){
                                                printf("LaGranVariable->siguiente == NULL\n");
                                            }

                                            
                                        }
                                        else{ //machacamos el valor de la variable
                                            
                                            printf("Variable repetida\n");
                                            variable->valor = NULL;

                                        }

                                    }
                                    else{
                                        printf("Error de sintaxis\n");
                                        continue;
                                    }

                                }   

                            }
                            else if(posicion == 4){ // a = [1 2 3] + []  // a = b + []




                            }


                        }


                    }
                    else{

                        num_arg_aux = 0;
                        comtok[num_arg_aux] = MiStrTok(commandAux, separadores, 0);
                        num_arg_aux++;

                        while ((comtok[num_arg_aux] = MiStrTok(NULL, separadores, 1)) != NULL)
                        {
                            printf("comtok[%d]: %s\n", num_arg_aux, comtok[num_arg_aux]);
                            num_arg_aux++;
                        }

                        printf("num_arg_aux: %d\n", num_arg_aux);


                        if(num_arg_aux != 3 && num_arg_aux != 5){
                            printf("Error de sintaxis\n");
                            continue;
                        }
                        
                    }

                    if(num_arg_aux != 2 && num_arg_aux != 4 && LALLAVE == 1){
                        printf("Error de sintaxis LALLAVE = !\n");
                        continue;
                    }

                    if(num_arg_aux == 3 || (num_arg_aux == 2 && LALLAVE == 1)){  

                        if(strcmp(comtok[1], "=") == 0){ // caso a = [1,2,3] OK

                            //ESTO LO ACABAREMOS BORRANDO
                            // printf("ENTRAMOS A =\n");
                            // cortafuegos = listaOvariable(comtok[0]);
                            // printf("cortafuegos: %d\n", cortafuegos);
                            // cortafuegos = listaOvariable(comtok[2]);
                            // printf("cortafuegos: %d\n", cortafuegos);
                            //--------------------------------

                            if(LALLAVE == 0 && (listaOvariable(comtok[0]) != 0 || listaOvariable(comtok[2]) != 2)){
                                printf("Error de sintaxis linea 180 main\n");
                                continue;
                            }
                            else if(LALLAVE == 1 && (listaOvariable(comtok[0]) != 0)){
                                printf("Error de sintaxis linea 183 main\n");
                                continue;
                            }
                            // if(listaOvariable(comtok[0]) != 0 || listaOvariable(comtok[2]) != 2){
                            //     printf("Error de sintaxis\n");
                            //     continue;
                            // }

                            TLISTA *listaux = crearLista();

                            if(LALLAVE == 0){

                                
                                int comprobante = 0;
                                comprobante = Expansioncorchetes(separadores, comtok[2], listaux);

                                printf("%d\n", comprobante);
                                if(comprobante == 1){
                                    printf("Error de sintaxis COMPROBANTE\n");
                                    continue;
                                }

                            }
                            else{
                                
                                listaux->primero = NULL;
                                listaux->ultimo = NULL;
                            }
                            

                            //imprimir listaux
                            printf(" VARIABLE LISTA 1[");
                            VerLista(listaux);
                            printf("]\n");

                            //crear variable
                            TVAR *variable = crearVariable(comtok[0], listaux);

                            //miramos si ya existe la variable
                            TVAR *aux = buscarVariable(LaGranVariable, variable->nombre);

                            if(aux == NULL){ // Variable nueva
                                
                                //imprimir variable
                                printf("VARIABLE[%s ", variable->nombre);
                                VerLista(variable->valor);
                                printf("]\n");

                                LaGranVariable = insertaUltimaLaGranVariable(LaGranVariable, variable);

                                //imprimir LaGranVariable
                                printf("LA GRAN VARIABLE[");
                                printf("%s ", LaGranVariable->nombre);
                                VerLista(LaGranVariable->valor);
                                printf("]\n");

                                if(LaGranVariable->anterior == NULL){
                                    printf("LaGranVariable->anterior == NULL\n");
                                }

                                if(LaGranVariable->siguiente == NULL){
                                    printf("LaGranVariable->siguiente == NULL\n");
                                }

                                
                            }
                            else{ //machacamos el valor de la variable
                                
                                printf("Variable repetida\n");
                                aux->valor = variable->valor;

                            }

                            // Aqui nos muestra todas las variables que hemos creado
                            TVAR *Temp = LaGranVariable;
                            while (Temp != NULL)
                            {
                                printf("LA GRAN VARIABLE[");
                                printf("%s ", Temp->nombre);
                                VerLista(Temp->valor);
                                printf("]\n");
                                Temp = Temp->siguiente;
                            }
                        
                        }
                        else if(strcmp(comtok[1], "+") == 0){ // a + [1 2 3] OK

                            //ESTO LO ACABAREMOS BORRANDO
                            // printf("ENTRAMOS A +\n");
                            // cortafuegos = listaOvariable(comtok[0]);
                            // printf("cortafuegos: %d\n", cortafuegos);
                            // cortafuegos = listaOvariable(comtok[2]);
                            // printf("cortafuegos: %d\n", cortafuegos);
                            //--------------------------------


                            if(LALLAVE == 0 && (listaOvariable(comtok[0]) != 0 || listaOvariable(comtok[2]) != 2)){
                                printf("Error de sintaxis linea 280 main\n");
                                continue;
                            }
                            else if(LALLAVE == 1 && (listaOvariable(comtok[0]) != 0)){
                                printf("Error de sintaxis linea 283 main\n");
                                continue;
                            }

                            TVAR *variableTemp = buscarVariable(LaGranVariable, comtok[0]);

                            if(variableTemp == NULL){
                                printf("Variable no encontrada\n");
                                continue;
                            }
                            else{

                                int comprobante = 0;
                                TLISTA *listaCorchetesTemporal = crearLista();
                        
                                if(LALLAVE == 0){

                                    comprobante = Expansioncorchetes(separadores, comtok[2], listaCorchetesTemporal);

                                    if(comprobante == 1){
                                        printf("Error de sintaxis COMPROBANTE\n");
                                        continue;
                                    }

                                }
                                else if(LALLAVE == 1){

                                    listaCorchetesTemporal->primero = NULL;
                                    listaCorchetesTemporal->ultimo = NULL;

                                }
                                
                                TLISTA *muestraDatos = CombinacionListas(variableTemp->valor, listaCorchetesTemporal);

                                printf("MOSTRAR DATOS\n");
                                VerLista(muestraDatos);


                            }
                            

                        }
                        else if(strcmp(comtok[1], "-") == 0){ // a - [1 2 3] OK

                            //ESTO LO ACABAREMOS BORRANDO
                            // printf("ENTRAMOS A -\n");
                            // cortafuegos = listaOvariable(comtok[0]);
                            // printf("cortafuegos: %d\n", cortafuegos);
                            // cortafuegos = listaOvariable(comtok[2]);
                            // printf("cortafuegos: %d\n", cortafuegos);
                            //--------------------------------


                            if(LALLAVE == 0 && (listaOvariable(comtok[0]) != 0 || listaOvariable(comtok[2]) != 2)){
                                printf("Error de sintaxis linea 180 main\n");
                                continue;
                            }
                            else if(LALLAVE == 1 && (listaOvariable(comtok[0]) != 0)){
                                printf("Error de sintaxis linea 183 main\n");
                                continue;
                            }

                            TVAR *variableTemp = buscarVariable(LaGranVariable, comtok[0]);

                            if(variableTemp == NULL){
                                printf("Variable no encontrada\n");
                                continue;
                            }
                            else{

                                int comprobante = 0;
                                TLISTA *listaCorchetesTemporal = crearLista();
                        
                                if(LALLAVE == 0){

                                    comprobante = Expansioncorchetes(separadores, comtok[2], listaCorchetesTemporal);

                                    if(comprobante == 1){
                                        printf("Error de sintaxis COMPROBANTE\n");
                                        continue;
                                    }

                                }
                                else if(LALLAVE == 1){

                                    listaCorchetesTemporal->primero = NULL;
                                    listaCorchetesTemporal->ultimo = NULL;

                                }

                                TLISTA *muestraDatos = RestaListas(variableTemp->valor, listaCorchetesTemporal);

                                printf("MOSTRAR DATOS\n");
                                VerLista(muestraDatos);


                            }



                        }
                        else if(strcmp(comtok[1], "#") == 0){ // a # [1 2 3] OK

                            int comprobante = 0;
                            TVAR *aux;

                            TLISTA *listaux = crearLista();
                            TLISTA *listaux2 = crearLista();

                            comprobante = listaOvariable(comtok[0]);

                            if(comprobante == 0){
                                //Buscamos una variable
                                aux = buscarVariable(LaGranVariable, comtok[0]);
                                listaux = aux->valor;

                            }
                            else{
                                printf("Error de sintaxis 1111\n");
                                continue;
                            }


                            //imprimir listaux
                            printf("CONTIENE LISTA 1[");
                            VerLista(listaux);
                            printf("]\n");

                            comprobante = Expansioncorchetes(separadores, comtok[2], listaux2);

                            printf("%d\n", comprobante);
                            if(comprobante == 1){
                                printf("Error de sintaxis COMPROBANTE\n");
                                continue;
                            }

                            //Aqui tenemos que comparar una lista contra otra
                            comprobante = contenidaLista(listaux2, listaux);

                            if(comprobante == 1){
                                printf("TRUE\n");
                            }
                            else{
                                printf("FALSE\n");
                            }


                        }
                        else{
                            printf("Error de sintaxis 2222\n");
                            continue;
                        }
                    }
                    else if(num_arg_aux == 5 ||  (num_arg_aux == 4 && LALLAVE == 1)){ // a = b + [1 2 3]  // a = [1 2 3] + b

                        if(LALLAVE == 1){
                            printf("HOLAAAA");
                        }

                        printf("ENTRAMOS A =\n");


                        if(strcmp(comtok[1], "=") == 0){

                            


                        }
                        else{
                            printf("Error de sintaxis 3333\n");
                            continue;
                        }


                    }
                }
                else{ // Hay corchetes en el primer argumento por lo que solo se va a realizar la muestra de datos por pantalla

                    // Vaciar comtok
                    LALLAVE = 0;
                    int posicion = 0;

                    for (int i = 0; i < num_arg; i++){
                        if(strcmp(comtok[i], "[]") == 0 ){ // queremos comprobar en el caso de que haya una lista vacia si esta en la primera posicion
                            LALLAVE=1;
                            posicion = i;
                        }
                        comtok[i] = NULL;
                    }

                    num_arg_aux = 0;

                    //Revision por si hubiesen listas vacias
                    if(strcmp(commandAux, "[]") == 0 ){ // [] OK
                        printf(" LINEA 432: SOLO []\n");
                        continue;
                    }
                    else if(LALLAVE == 1 && posicion == 0){ // [] + [1 2 3] OK
                        printf("LINEA 436: \n"); 

                        char auxiliarletra[100];
                        strcpy(auxiliarletra, commandAux);

                        strcpy(commandAux, auxiliarletra+3);

                        printf("commandAux: %s\n", commandAux);

                        comtok[0] = NULL;
                        num_arg_aux ++;

                    }
                    else if(LALLAVE == 1 && posicion != 0 && numeroLLAVES < 2){ // [1 2 3] + [] OK
                    
                        printf("numero llaves: %d\n", numeroLLAVES);
                        commandAux[strlen(commandAux)-3] = '\0';
                        printf("456 commandAux: %s\n", commandAux);

                        comtok[2] = NULL;
                    
                    }
                    else if(LALLAVE == 1 && numeroLLAVES == 2){ // [] + []    [] # [] OK

                        // ACORTAMOS POR DELANTE
                        char auxiliarletra[100];
                        strcpy(auxiliarletra, commandAux);
                        strcpy(commandAux, auxiliarletra+3);

                        // ACORTAMOS POR DETRAS
                        commandAux[strlen(commandAux)-3] = '\0';

                        printf("471 commandAux: %s\n", commandAux);

                        if(strcmp(commandAux, "#") == 0){
                            printf("TRUE\n");
                        }
                        else{
                            printf("[]\n");
                        }

                        continue;
                    }

                        
                    comtok[num_arg_aux] = MiStrTok(commandAux, separadores, 1);
                    num_arg_aux++;

                    while ((comtok[num_arg_aux] = MiStrTok(NULL, separadores, 1)) != NULL)
                    {
                        printf("comtok[%d]: %s\n", num_arg_aux, comtok[num_arg_aux]);
                        num_arg_aux++;
                    }

                    if(LALLAVE == 1 && posicion != 0){
                        num_arg_aux++;
                    }

                    

                    if(num_arg_aux == 1){ // [1 2 3] OK

                        int comprobante = 0;
                        
                        TLISTA *listaux = crearLista();
                        comprobante = Expansioncorchetes(separadores, comtok[0], listaux);

                        printf("%d\n", comprobante);
                        if(comprobante == 1){
                            printf("Error de sintaxis COMPROBANTE\n");
                            continue;
                        }

                        //imprimir comtokaux 
                        printf("MAIN[");
                        
                        while (listaux->primero != NULL)
                        {
                            printf("%.11g ", listaux->primero->valor);
                            listaux->primero = listaux->primero->siguiente;
                        }

                        printf("]\n");

                    }
                    else if(num_arg_aux == 3){ // [1 2 3] + [1 2 3]     // [1 2 3] + a   //[1 2 3] # [1 2 3 4]

                        //imprimir comtok
                        for(int i = 0; i < num_arg_aux; i++){
                            printf("AA.%s\n", comtok[i]);
                        }

                        if(strcmp(comtok[1], "+") == 0){ // [1 2 3] + [1 2 3]     // [1 2 3] + a OK

                            int comprobante = 0;

                            TLISTA *listaux = crearLista();
                            TLISTA *listaux2 = crearLista();
                            TLISTA *listauxFinal = crearLista();

                            comprobante = Expansioncorchetes(separadores, comtok[0], listaux);

                            //imprimir listaux
                            printf("LISTA 1[");
                            VerLista(listaux);

                            printf("]\n");

                            printf("%d\n", comprobante);
                            if(comprobante == 1){
                                printf("Error de sintaxis COMPROBANTE\n");
                                continue;
                            }

                            if(listaOvariable(comtok[2]) == 2){
                                comprobante = Expansioncorchetes(separadores, comtok[2], listaux2);
                            }
                            else if(listaOvariable(comtok[2]) == 0){

                                TVAR *aux;
                                aux = buscarVariable(LaGranVariable, comtok[2]);
                                listaux2 = aux->valor;

                            }
                            
                            

                            //imprimir listaux2
                            printf("LISTA 2[");
                            VerLista(listaux2);
                            printf("]\n");

                            printf("%d\n", comprobante);
                            if(comprobante == 1){
                                printf("Error de sintaxis COMPROBANTE\n");
                                continue;
                            }

                            //fusionar en la primera lista
                            printf("ENTRAMOS A COMBINACION\n");
                            listauxFinal = CombinacionListas(listaux, listaux2);

                            VerLista(listauxFinal);

                        }
                        else if(strcmp(comtok[1], "-") == 0){ // [1 2 3] - [1 2 3]     // [1 2 3] - a OK

                            int comprobante = 0;

                            TLISTA *listaux = crearLista();
                            TLISTA *listaux2 = crearLista();
                            TLISTA *listauxFinal = crearLista();

                            comprobante = Expansioncorchetes(separadores, comtok[0], listaux);

                            // //imprimir listaux
                            // printf("LISTA 1[");
                            // VerLista(listaux);
                            // printf("]\n");

                            printf("%d\n", comprobante);
                            if(comprobante == 1){
                                printf("Error de sintaxis COMPROBANTE\n");
                                continue;
                            }

                            comprobante = listaOvariable(comtok[2]);

                            if(comprobante == 0){
                                //Buscamos una variable

                                TVAR *aux;

                                aux = buscarVariable(LaGranVariable, comtok[2]);
                                listaux2 = aux->valor;

                            }
                            else if(comprobante == 2){
                                //Expandimos la lista

                                comprobante = Expansioncorchetes(separadores, comtok[2], listaux2);

                                //imprimir listaux2
                                printf("LISTA 2[");
                                VerLista(listaux2);
                                printf("]\n");

                                printf("%d\n", comprobante);
                                if(comprobante == 1){
                                    printf("Error de sintaxis COMPROBANTE\n");
                                    continue;
                                }

                            }
                            else{
                                printf("Error de sintaxis\n");
                                continue;
                            }


                            //imprimir listaux2
                            printf("637 LISTA 2[");
                            VerLista(listaux2);
                            printf("]\n");

                            //eliminar elementos de una lista en otra
                            printf("ENTRAMOS A RESTA\n");

                            listauxFinal = RestaListas(listaux, listaux2);
                            VerLista(listauxFinal);


                        }
                        else if(strcmp(comtok[1], "#") == 0){ // [1 2 3] # [1 2 3]    [1 2 3] # a OK

                            printf("ENTRAMOS A CONTIENE\n");

                            int comprobante = 0;
                            TVAR *aux;

                            TLISTA *listaux = crearLista();
                            TLISTA *listaux2 = crearLista();

                            comprobante = Expansioncorchetes(separadores, comtok[0], listaux);

                            //imprimir listaux
                            printf("CONTIENE LISTA 1[");
                            VerLista(listaux);
                            printf("]\n");

                            printf("%d\n", comprobante);
                            if(comprobante == 1){
                                printf("Error de sintaxis COMPROBANTE\n");
                                continue;
                            }

                            comprobante = listaOvariable(comtok[2]);

                            if(comprobante == 0){
                                //Buscamos una variable

                                aux = buscarVariable(LaGranVariable, comtok[2]);
                                listaux2 = aux->valor;

                            }
                            else if(comprobante == 2){
                                //Expandimos la lista

                                comprobante = Expansioncorchetes(separadores, comtok[2], listaux2);

                                //imprimir listaux2
                                printf("LISTA 2[");
                                VerLista(listaux2);
                                printf("]\n");

                                printf("%d\n", comprobante);
                                if(comprobante == 1){
                                    printf("Error de sintaxis COMPROBANTE\n");
                                    continue;
                                }

                            }
                            else{
                                printf("Error de sintaxis\n");
                                continue;
                            }

                            //Aqui tenemos que comparar una lista contra otra
                            comprobante = contenidaLista(listaux2, listaux);

                            if(comprobante == 1){
                                printf("TRUE\n");
                            }
                            else{
                                printf("FALSE\n");
                            }


                        }
                        else{ // ERROR DE SINTAXIS

                            printf("Error de sintaxis\n");
                            continue;

                        }

                    }
                    else{ // ERROR DE SINTAXIS

                        printf("Error de sintaxis\n");
                        continue;

                    }

                }  

            }
        }


    
    }

    return 0;
}