#include "lib.h"

void hola(){ 
    printf("Alumno: XXXXXX\n");
    printf("Email: XXXXXX\n");
}

TVARS *crear_workspace(TVARS *workspace){
    workspace = (TVARS *) malloc(sizeof(TVARS));
    workspace->n = 0;
    workspace->var1 = NULL;
    return workspace;
}

/*  Nos devuelve 0 si esta mal esccrita la variable y 1 si esta bn escrita */
int validar_variable(char *nombre){
    int i=0;
    char nombre_variable[100];

    strcpy(nombre_variable, nombre);

    while(nombre_variable[i] != '\0'){
        
        if(nombre_variable[i] >= 'a' && nombre_variable[i] <= 'z'){
            i++;
        }
        else if(nombre_variable[i] >= 'A' && nombre_variable[i] <= 'Z'){
            i++;
        }
        else if(nombre_variable[i] >= '0' && nombre_variable[i] <= '9'){
            i++;
        }
        else{
            return 0;
        }
    }

    return 1;
}

char * MiStrTok(char *cad1, char *sep, int comillas){
    static char *pt1=NULL;
	static char *pt2=NULL; 
	static char *ptFinal;

	if(cad1!=NULL){
		pt1 = cad1;
		ptFinal = pt1+strlen(cad1);
	}
	else{
		pt1=pt2+1;
	}

	if(comillas == 1){
		while( pt1[0]!='\0' && pt1<ptFinal && strchr(sep, pt1[0])!=NULL && pt1[0]!='[')
			pt1++;
		if(pt1[0]=='['){
			pt1++;
			pt2=pt1;
			while( pt2[0]!='\0' && pt2[0]!=']' )
				pt2++;
			if(pt2[0]=='\0'){
				pt1=pt2=ptFinal=NULL;
				return NULL;
			}
			else{
				pt2[0]='\0';
				return pt1;
			}
		}
	}
	else{
		while( pt1[0]!='\0' && pt1<ptFinal && strchr(sep, pt1[0])!=NULL )
			pt1++;
	}
	if(pt1>=ptFinal){
		pt1=pt2=ptFinal=NULL;
		return NULL;
	}
	pt2=pt1+1;
	while( pt2[0]!='\0' &&  strchr(sep, pt2[0])==NULL )
		pt2++;
	pt2[0]='\0';
	return pt1;
}

// Si es un simbolo devuelve 1, si no 0
int esSimbolo(char *simbolo){

    if(simbolo[0] == '+'){
        return 1;
    }
    else if(simbolo[0] == '-'){
        return 2;
    }
    else if(simbolo[0] == '#'){
        return 3;
    }
    else if(simbolo[0] == '\0'){ //simbolo es igual a null
        return 4;
    }
    else if(simbolo[0] == '='){
        return 0;
    }
    else{  //No se reconoce simbolo
        return -1;
    }

}

TLISTA *crearLista()
{
    TLISTA *nuevoNodo = NULL;

    nuevoNodo = (TLISTA *)malloc(sizeof(TLISTA));

    if (nuevoNodo != NULL)
    {
        nuevoNodo->n = 0;

        nuevoNodo->primero = NULL;
        nuevoNodo->ultimo = NULL;
    }
    return nuevoNodo;
}

TNUM *crearListaNum(double valor, int dec)
{
    TNUM *nuevoNodo = NULL;

    nuevoNodo = (TNUM *)malloc(sizeof(TNUM));

    if (nuevoNodo != NULL)
    {
        nuevoNodo->valor = valor;
        nuevoNodo->decimales = dec;

        nuevoNodo->siguiente = NULL;
        nuevoNodo->anterior = NULL;
    }
    return nuevoNodo;
}

// Devuelve 0 si todo ok, 1 si hay error
int expansionCorchetes(char* separadores, char* comtok, TLISTA *listaaux) {
    char* comtokaux2[100];
    char cadena[20];
    TNUM *numAux;

    int num_arg = 0;

    printf("Expansioncorchetes\n");

    printf("comtok: %s\n", comtok);
   

    if(comtok == NULL){

        listaaux->n = 0;
        listaaux->primero = NULL;
        listaaux->ultimo = NULL;

        return 0;
    }

    comtokaux2[num_arg] = strtok(comtok, separadores);
    num_arg++;

    // printf("A11.%s\n", comtokaux2[0]);
    // if(comtokaux2[1] == NULL){
    //     printf("A222221.%s\n", comtokaux2[1]);
    //     return 1;
    // }
    // printf("A11111.%s\n", comtokaux2[1]);

    while ((comtokaux2[num_arg] = strtok(NULL, separadores)) != NULL) {
        num_arg++;
    }

    for (int i = 0; i < num_arg; i++) {
        printf("A2.%s\n", comtokaux2[i]);
    }

    if(comtokaux2[1] == NULL){
        
        char aux[20];
        double comtokaux0 = atof(comtokaux2[0]);
        
        TNUM *numero = crearListaNum(comtokaux0, NumDecimales(comtokaux2[0]));
        listaaux->n=listaaux->n+1;
        listaaux->primero = numero;
        listaaux->ultimo = numero;

        return 0;
    }

    if(strcmp(comtokaux2[1], ":") == 0){

        //printf("Estamos en la parte : \n");

        if(num_arg == 3){

            if(decimalValidar(comtokaux2[0]) == 0 || decimalValidar(comtokaux2[2]) == 0){
                printf("ERROR");
                
                return 1;
            }

            char aux[20];
            double comtokaux0 = atof(comtokaux2[0]);
            double comtokaux2INT = atof(comtokaux2[2]);

            if(comtokaux0 < comtokaux2INT){
                TNUM *numero = crearListaNum(comtokaux0, NumDecimales(comtokaux2[0]));
                listaaux->n=listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;
                
                for(double i=comtokaux0+1; i<=comtokaux2INT; i++){

                    sprintf(aux, "%.11g", i);
                    listaaux->n=listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numAux = listaaux->ultimo;
                    numAux->siguiente = numero;
                    numero->anterior = numAux;
                    listaaux->ultimo = numero;
                }

            }
            else if (comtokaux0 > comtokaux2INT){
                TNUM *numero = crearListaNum(comtokaux0, NumDecimales(comtokaux2[0]));
                listaaux->n=listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;
                for(double i=comtokaux0-1; i>=comtokaux2INT; i--){
                    sprintf(aux, "%.11g", i);
                    listaaux->n=listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numAux = listaaux->ultimo;
                    numAux->siguiente = numero;
                    numero->anterior = numAux;
                    listaaux->ultimo = numero;
                }

            }
            else {
                TNUM *numero = crearListaNum(comtokaux0, NumDecimales(comtokaux2[0]));
                listaaux->n=listaaux->n+1;
                listaaux->primero = numero;
                numero->anterior = numAux;
                listaaux->ultimo = numero;
            }
        }
        else{
            printf("ERROR");
    
            return 1;
        }


    } 
    else if (strcmp(comtokaux2[1], "$") == 0 && strcmp(comtokaux2[3], ":") == 0) {

        //printf("Estamos en la parte $ : \n");

        if(num_arg == 5){

            if(decimalValidar(comtokaux2[0]) == 0 || decimalValidar(comtokaux2[2]) == 0 || decimalValidar(comtokaux2[4]) == 0){
                printf("ERROR");
                
                return 1;
            }

            char aux[20];
            double comtokaux0 = atof(comtokaux2[0]);
            double comtokaux2INT = atof(comtokaux2[2]);
            double comtokaux4 = atof(comtokaux2[4]);
            int signo = 0;


            //Comprobamos el signo
            if(comtokaux2INT < 0){
                signo = -1;
            }
            else if(comtokaux2INT > 0){
                signo = 1;
            }
            else{
                printf("ERROR");
                return 1;
            }
            if(comtokaux0 <= comtokaux4){

                if(comtokaux2INT <= 0){
                    printf("ERROR");
                    return 1;
                }

                TNUM *numero = crearListaNum(comtokaux0, NumDecimales(comtokaux2[0]));
                listaaux->n=listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;
                
                for(double i=comtokaux0+comtokaux2INT; i<=comtokaux4; i = i + comtokaux2INT){

                    sprintf(aux, "%.11g", i);
                    listaaux->n=listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numAux = listaaux->ultimo;
                    numAux->siguiente = numero;
                    numero->anterior = numAux;
                    listaaux->ultimo = numero;
                }

            }
            else if (comtokaux0 > comtokaux4){

                if(comtokaux2INT >= 0){
                    printf("ERROR");
                    return 1;
                }

                printf("ENTRAMOS AQUI\n");

                TNUM *numero = crearListaNum(comtokaux0, NumDecimales(comtokaux2[0]));
                listaaux->n=listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;
                for(double i=comtokaux0+comtokaux2INT; i>=comtokaux4; i = i + comtokaux2INT){
                    sprintf(aux, "%.11g", i);
                    listaaux->n=listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numAux = listaaux->ultimo;
                    numAux->siguiente = numero;
                    numero->anterior = numAux;
                    listaaux->ultimo = numero;
                }
            }
        }
        else{
            printf("ERROR");
            return 1;
        }
    } 
    else {

        //printf("Defecto\n");

        for (int i = 0; i < num_arg; i++) {
            if(decimalValidar(comtokaux2[i]) == 0){
                printf("ERROR");
                return 1;
            }
        }

        char aux[20];
        TNUM *numero = crearListaNum(atof(comtokaux2[0]), NumDecimales(comtokaux2[0]));
        listaaux->n=listaaux->n+1;
        listaaux->primero = numero;
        listaaux->ultimo = numero;
        for(int i=1; i< num_arg; i++){

                //printf("A3.%s\n", comtokaux2[i]);
                sprintf(aux, "%.11g", atof(comtokaux2[i]));
                listaaux->n=listaaux->n+1;
                numero = crearListaNum(atof(comtokaux2[i]), NumDecimales(aux));
                numAux = listaaux->ultimo;
                numAux->siguiente = numero; 
                numero->anterior = numAux;
                listaaux->ultimo = numero;
        }
    }

    // TNUM *auxiliar=listaaux->primero;
    // for (int i=0; i<listaaux->n; i++){
    //     printf("\n%d,  %.11g, %d\n",i, auxiliar->valor, auxiliar->decimales);
    //     auxiliar=auxiliar->siguiente;
    // }

    return 0;
}

TLISTA * CombinacionListas(TLISTA *listaux, TLISTA *listaux2){

    TLISTA *lista = crearLista();
    //TLISTA *lista1, *lista2;
    char aux[20];
    TNUM *numAux, *numTemp, *numLista;

    printf("DENTRO COMBI LISTA 1[");
    verLista(listaux);
    printf("]\n");

    printf("DENTRO COMBI LISTA 2[");
    verLista(listaux2);
    printf("]\n");

    if(listaux->primero == NULL){
        printf("Listaux es nulo, devolvemos listaux2\n");
        return listaux2;
    }
    else if(listaux2->primero == NULL){
        printf("Listaux2 es nulo, devolvemos listaux\n");
        return listaux;
    }

    lista->n = listaux->n + listaux2->n; /// PETAN LOS PUNTEROS A LA HORA DE COMBINAR LAS LISTAS

    numAux = listaux->primero;
    numTemp = crearListaNum(numAux->valor, numAux->decimales);
    lista->primero = numTemp;
    lista->ultimo = numTemp;
    numAux = numAux->siguiente;

    for (int i=1; i<listaux->n; i++){

        
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        numLista = lista->ultimo;
        numLista->siguiente = numTemp;
        numTemp->anterior = numLista;

        lista->ultimo = numTemp;
        numAux = numAux->siguiente;
        
    }

    numAux = listaux2->primero;   // Nos colocamos en la segunda lista
    
    for (int i=0; i<listaux2->n; i++){

        
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        numLista = lista->ultimo;
        numLista->siguiente = numTemp;
        numTemp->anterior = numLista;

        lista->ultimo = numTemp;
        numAux = numAux->siguiente;
        
    }
    
    printf("SALIMOS\n");

    verLista(lista);

    return lista;
}

// Devuelve una lista con los elementos de lista 1 - menos los elementos de lista 2
TLISTA *RestaListas(TLISTA *listaux, TLISTA *listaux2) {
    if (listaux == NULL) {
        printf("RestaListas: listaux es null\n");
        return NULL;
    }
    if (listaux2 == NULL) {
        printf("RestaListas: listaux2 es null\n");
        return listaux;
    }

    TLISTA *lista = crearLista();
    char aux[20];
    TNUM *numAux, *numAux2, *numTemp, *numLista, *numcontador;
    int cortafuegos = 0;

    // Creamos duplicado de listaux y listaux2
    TLISTA *listaDuplicada = crearDuplicadoLista(listaux);
    TLISTA *listaDuplicada2 = crearDuplicadoLista(listaux2);

    numAux2 = listaDuplicada2->primero;

    while (numAux2 != NULL) {
        
        numAux = listaDuplicada->primero;
        printf("NUMERO A COMPARAR: %.11g\n", numAux2->valor);

        while (numAux != NULL) {

            printf("NUMERO A COMPARAR: %.11g\n", numAux->valor);
            
            if (numAux->valor == numAux2->valor) {
                // Borramos de las listas el numero coincidente
                eliminarElementoLista(listaDuplicada, numAux->valor);
                eliminarElementoLista(listaDuplicada2, numAux2->valor);

                cortafuegos = 1;
                printf("NUMERO REPETIDO\n");
                break;
            }
            numAux = numAux->siguiente; // Avanzamos el puntero de listaDuplicada
        }

        if (cortafuegos == 0) {
            printf("NUMERO NO REPETIDO\n");
            numAux2 = numAux2->siguiente; // Avanzamos el puntero de listaDuplicada2
            //printf("Numero seleccionado: %.11g\n", numAux2->valor);
        }
        else{
            printf("NUMERO REPETIDO\n");
            numAux2 = listaDuplicada2->primero;
            //printf("Numero seleccionado: %.11g\n", numAux2->valor);
        }
        cortafuegos = 0;
    }

    lista = crearDuplicadoLista(listaDuplicada);

    printf("SALIMOS\n");
    verLista(lista);

    return lista;
}


TLISTA *crearDuplicadoLista(TLISTA *lista) {
    TLISTA *listaDuplicada = crearLista();
    TNUM *numAux = lista->primero;
    TNUM *numPrev = NULL;

    while (numAux != NULL) {
        TNUM *numTemp = crearListaNum(numAux->valor, numAux->decimales);

        if (numPrev == NULL) {
            listaDuplicada->primero = numTemp;
            numTemp->anterior = NULL;
        } else {
            numPrev->siguiente = numTemp;
            numTemp->anterior = numPrev;
        }

        listaDuplicada->ultimo = numTemp;
        listaDuplicada->n++;

        numPrev = numTemp;
        numAux = numAux->siguiente;
    }

    return listaDuplicada;
}


void eliminarElementoLista(TLISTA *lista, double valor){

    TNUM *numAux, *numAnterior, *numSieguiente;

    numAux = lista->primero;

    while(numAux != NULL){

        if(numAux->valor == valor){

            //Encontramos cual es el numero de antes y despues
            numAnterior = numAux->anterior;
            numSieguiente = numAux->siguiente;

            //printf("Valor numAnterior: %.11g\n", numAnterior->valor);
           // printf("Valor numSieguiente: %.11g\n", numSieguiente->valor);

            //Recolocamos los nodos
            if(numAnterior == NULL && numSieguiente == NULL){ //Si solo hay un elemento en la lista
                lista->primero = NULL;
                lista->ultimo = NULL;
            }
            else if(numAnterior == NULL){ //Si es el primero de la lista
                lista->primero = numSieguiente;
                numSieguiente->anterior = NULL;
            }
            else if(numSieguiente == NULL){ //Si es el ultimo de la lista
                lista->ultimo = numAnterior;
                numAnterior->siguiente = NULL;
            }
            else{ //Si esta en medio de la lista
                numAnterior->siguiente = numSieguiente;
                numSieguiente->anterior = numAnterior;
            }

            lista->n = (lista->n)-1; 

            numAux->siguiente = NULL;
            numAux->anterior = NULL;

            printf("C");

            //Eliminamos el nodo
            free(numAux);

            printf("D ELIMINAR ELEMENTO\n");

            verLista(lista);

            //Salimos del bucle
            return;

        }

        numAux = numAux->siguiente;

    }

    return;

}

void verLista(TLISTA *lista){

    if(lista->primero == NULL){
        printf("[]\n");
        return;
    }

    TNUM *auxiliar=lista->primero;
    printf("[");
    for (int i=0; i<lista->n; i++){
        if(i == lista->n-1){
            printf("%.11g",auxiliar->valor);
        }
        else{
            printf("%.11g ",auxiliar->valor);
        }
        auxiliar=auxiliar->siguiente;
    }
    printf("]\n");
}

void laGranVista(TVAR *laGranVariable){

    if(laGranVariable == NULL){
        printf("Lista vacia\n");
        return;
    }

    TVAR *auxiliar=laGranVariable;
    int i =0;
    while(auxiliar != NULL){
        i++;
        printf("\n[%d]| Nombre:  %s| Numero Elementos:  %d\n",i, auxiliar->nombre,auxiliar->valor->n);
        verLista(auxiliar->valor);
        auxiliar=auxiliar->siguiente;
    }
}

TLISTA * copiarNlistaPrimeras(TLISTA *lista,int n){
    TNUM *numAux, *numTemp, *numLista;
    TLISTA *listaAux = crearLista();

    if(lista->primero == NULL){
        printf("Lista vacia\n");
        return NULL;
    }
    if(n>lista->n){
        printf("No hay tantos elementos\n");
        n = lista->n;
    }
    listaAux->n = n;
    numAux = lista->primero;
    numTemp = crearListaNum(numAux->valor, numAux->decimales);
    listaAux->primero = numTemp;
    listaAux->ultimo = numTemp;
    numAux = numAux->siguiente;

    for (int i=1; i<n; i++){
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        numLista = listaAux->ultimo;
        numLista->siguiente = numTemp;
        numTemp->anterior = numLista;
        listaAux->ultimo = numTemp;
        numAux = numAux->siguiente;        
    }
    return listaAux;
}

TLISTA * copiarNlistaUltimas(TLISTA *lista,int n){
    TNUM *numAux, *numTemp, *numLista;
    TLISTA *listaAux = crearLista();

    if(lista->primero == NULL){
        printf("Lista vacia\n");
        return NULL;
    }
    if(n>lista->n){
        printf("No hay tantos elementos\n");
        n = lista->n;
    }
    listaAux->n = n;
    numAux = lista->ultimo;
    numTemp = crearListaNum(numAux->valor, numAux->decimales);
    listaAux->primero = numTemp;
    listaAux->ultimo = numTemp;
    numAux = numAux->anterior;

    for (int i=1; i<n; i++){
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        numLista = listaAux->primero;
        numLista->anterior = numTemp;
        numTemp->siguiente = numLista;
        listaAux->primero = numTemp;
        numAux = numAux->anterior;        
    }
    return listaAux;
}

//Validar cadena bien escrita de corchetes
int validar_corchetes(char *cadena){
    int i=0;
    int contador=0;
    int primeravez=0;
    int corchetesApertura=0;
    int corchetesCierre=0;
    int orden=0;
    while(cadena[i] != '\0'){
        if(cadena[i] == '[' || cadena[i] == ']'){
            contador++;           
        }
        i++;
    }
    if(contador == 0){
        return 1;
    }
    i = 0;
    contador = 0;
    while(cadena[i] != '\0'){
        if(cadena[i] == '[' && contador == 0){
            contador++;
            primeravez = 1;
            
        }
        else if(cadena[i] == ']' && contador == 1){
            contador--;
            
        }

        if(cadena[i] == '['){
            corchetesApertura++;
            if(orden == 1){ //Comprobamos que no haya un corchete de apertura antes que uno de cierre
                return 0;
            }
            orden = 1;
        }
        else if(cadena[i] == ']'){
            corchetesCierre++;
            if(orden == 0){ //Comprobamos que no haya un corchete de cierre antes que uno de apertura
                return 0;
            }
            orden = 0;
        }        
        i++;
    }

    if(contador == 0 && primeravez == 1 && corchetesApertura == corchetesCierre){ //Si contador es 1 es que esta bien escrita
        return 1;
    }
    else{ //Si contador es 0 es que esta mal escrita
        return 0;
    }
}

int NumDecimales (char *cad){

    int i, p=0, j=0;
     
    for(i=0; i<strlen(cad); i++)
    {
        if (p==1 )
        {
            j++;
        }
        if (cad[i]=='.'){
            p=1;
        }
    }     


    return j;
}
//ESTO VALIDA TANTO DECIMALES, REALES y ENTEROS bn 1 mal 0
int decimalValidar (char *cad) 
{
	int i, ini, p=0, j;
	
	if(cad[0]=='+' || cad[0]=='-'){
        ini=1;
    }	
	else{
        ini=0;
    }
		
	for(i=ini; i<strlen(cad); i++)
    {
        if (cad[i]<'0' || cad[i]>'9')
        {
            if (cad[i]=='.'){
                p++;
            }
            else{
                return 0;
            }       
        }
        if (p==2){
            return 0;
        }     
    }
	if (ini==1 && strlen(cad)==1){
        return 0;
    }	
	if (strlen(cad)==0){
        return 0;
    }
		
	if (ini==1 && strlen(cad)==2 && cad[1]=='.'){
        return 0;
    }	
	if (ini==0 && strlen(cad)==1 && cad[0]=='.'){
        return 0;
    }
	return 1;	
}

//Devuelve 1 si es un entero, 0 si es otra cosa
int enteroValidar (char *cad)
{
	int i, ini;
	
	if(cad[0]=='+' || cad[0]=='-') // en el caso de que queramos q sea un numero entero positivo, quitaremos la parte del -
		ini=1;
	else 
		ini=0;
	for (i=ini; i<strlen(cad); i++)
		{
			if (cad[i]<'0' || cad[i]>'9')
				return 0;
		}
	if (ini==1 && strlen(cad)==1)
		return 0;
	if (ini==0 && strlen(cad)==0)
		return 0;
return 1;
}

TVAR *crearVariable (char *nombrevariable, TLISTA *lista)
{
    TVAR *nuevoNodo = NULL;

    nuevoNodo = (TVAR *)malloc(sizeof(TVAR));

    if (nuevoNodo != NULL)
    {
        strcpy(nuevoNodo->nombre, nombrevariable);
        nuevoNodo->valor = lista;

        nuevoNodo->siguiente = NULL;
        nuevoNodo->anterior = NULL;
    }
    return nuevoNodo;
}

// 0 si es variable, 1 si es error, 2 si es numero
int listaOvariable(char *cad){ 

    if(cad[0] >= 'a' && cad[0] <='z'){
        return 0;
    }
    else if(cad[0] >= 'A' && cad[0] <= 'Z'){
        return 0;
    }
    else if(cad[0] == '+' || cad[0] == '-'){

        if(cad[1] >= '0' && cad[1] <= '9'){
            return 2;
        }
        else if(cad[1] == '.'){
            if(cad[2] >= '0' && cad[2] <= '9'){
                return 2;
            }
        }
    }
    else if(cad[0] > '0' && cad[0] < '9'){
        return 2;
    }

    return 1;

}


TVAR *insertaUltimaLaGranVariable(TVAR *laGranVariable, TVAR *variable){

    TVAR *auxiliar = laGranVariable;

    if(auxiliar == NULL){
        printf("ES el primer nodo\n");
        printf("Nombre: %s\n", variable->nombre);
        laGranVariable = variable;
        printf("Nombre: %s\n", laGranVariable->nombre);
        laGranVariable->siguiente = NULL;
        laGranVariable->anterior = NULL;
    }
    else{
        while(auxiliar->siguiente != NULL){
            auxiliar = auxiliar->siguiente;
        }
        auxiliar->siguiente = variable;
        variable->anterior = auxiliar;
        variable->siguiente = NULL;
    }

    return laGranVariable;
    
}

//Devuelve puntero apuntando a la variable si  existe y NULL si no existe
TVAR *buscarVariable (TVAR *laGranVariable, char *nombrevariable){

    TVAR *auxiliar = laGranVariable;

    while(auxiliar != NULL){
        printf("%s\n",auxiliar->nombre);
        if(strcmp(auxiliar->nombre, nombrevariable) == 0){
            return auxiliar;
        }

        auxiliar = auxiliar->siguiente;
    }

    return NULL;
}

// Devuelve 1 si L1 esta contenido en L2 y 0 si no
// Primero introduce la lista mas grande (L2) y luego la mas pequeña (L1) sabemos que es mas pequeña porque tiene menos elementos y por eso TRUE
int  contenidaLista(TLISTA *L2, TLISTA *L1){ 

    if(L2 == NULL){
        printf("RestaListas: L2 es null\n");
        return 1;
    }
    if(L1 == NULL){
        printf("RestaListas: L1 es null\n");
        return 0;
    }

    TLISTA *lista = crearLista();

    char aux[20];
    TNUM *numAux, *numAux2, *numTemp, *numLista, *numcontador;

    int bucle2 = 0, bucle1;

    printf("DENTRO COMBI LISTA 1[");
    verLista(L2);
    printf("]\n");

    printf("DENTRO COMBI LISTA 2[");
    verLista(L1);
    printf("]\n");

    //Creamos duplicado de listux2
    TLISTA *listaDuplicada = crearDuplicadoLista(L2);
    TLISTA *listaDuplicada2 = crearDuplicadoLista(L1);

    numAux = listaDuplicada->primero;
    numAux2 = listaDuplicada2->primero;

    numcontador = listaDuplicada->primero;

    bucle2 = 0;
    bucle1 = 0;

    int cortafuegos = 0;
    
    while(numAux2 != NULL){

       printf("Primer bucle %d de %d\n", bucle2, L1->n);

        while(numAux != NULL){

            printf("Segundo bucle %d de %d\n", bucle1, L2->n);

            // printf("NUMERO A COMPARAR: %.11g\n", numAux2->valor);
            // printf("NUMERO A COMPARAR: %.11g\n", numAux->valor);

            if(numAux2 == NULL || numAux == NULL){

                break;

            }
            

            printf("A\n");

            if(numAux->valor == numAux2->valor){

                printf("B\n");
                //Borramos de las listas el numero coincidente
                eliminarElementoLista(listaDuplicada, numAux->valor);
                eliminarElementoLista(listaDuplicada2, numAux2->valor);

                verLista(listaDuplicada);
                verLista(listaDuplicada2);

                numAux = listaDuplicada->primero;
                numAux2 = listaDuplicada2->primero;

                cortafuegos = 1;
               
                printf("NUMERO REPETIDO\n");
            }
            else{

                printf("NUMERO NO REPETIDO\n");

                if(numAux == NULL){
                    printf("NUMERO NULL\n");
                }
                else{
                    printf("NUMERO : %.11g\n", numAux->valor);
                }
                

                numAux = numAux->siguiente; //Avanzamos el puntero de L1

                //printf("NUMERO : %.11g\n", numAux->valor);

            }

            bucle1++;
           
        }

        printf("Peto aqui\n");

        if(numAux2 != NULL){

            printf("Peto aqui 2\n");
            eliminarElementoLista(listaDuplicada2, numAux2->valor);

            numAux = listaDuplicada->primero;
            numAux2 = listaDuplicada2->primero;
        }
        


        bucle2++;

        
        
    }

    lista = crearDuplicadoLista(listaDuplicada);

    printf("SALIMOS\n");

    verLista(lista);
    verLista(L2);

    int numeroelementos = L2->n - L1->n;

    if(lista->n == numeroelementos){
        return 1;
    }
    else{
        return 0;
    }
    
   

    
}

int contarCaracter(char **cadena, char *caracter) {
    int contador = 0;
    int i = 0;

    while (cadena[i] != '\0') {
        if (strcmp(cadena[i], caracter) == 0) {
            contador++;
        }
        i++;
    }

    return contador;
}

TLISTA *charToList(char *cadena,TVAR *laGranVariable) {
    TLISTA *lista = crearLista();
    if(listaOvariable(cadena) == 1){
        printf("ERROR variable\n");
        return NULL;
    } else if(listaOvariable(cadena) == 0){
        TVAR *aux = buscarVariable(laGranVariable, cadena);
        if(aux == NULL){
            printf("ERROR de variable\n");
            return NULL;
        }
        lista = aux->valor;
    } else if(expansionCorchetes(" \t\n", cadena, lista) == 1){
        printf("ERROR\n");
        return NULL;
    }
    return lista;
}

TLISTA *operar(char** cadena, TVAR *laGranVariable,int num_arg){
    TLISTA *lista1 = crearLista();
    TLISTA *lista2 = crearLista();
    if(contarCaracter(cadena, "+") == 1){
        lista1 = charToList(cadena[0], laGranVariable);
        lista2 = charToList(cadena[2], laGranVariable);
        return CombinacionListas(lista1, lista2);
    } else if(contarCaracter(cadena, "-") == 1){
        lista1 = charToList(cadena[0], laGranVariable);
        lista2 = charToList(cadena[2], laGranVariable);
        return RestaListas(lista1, lista2);
    } else if(strcmp(cadena[0], "head") == 0){
        if(num_arg != 3){
            printf("Error de sintaxis\n");
            return NULL;
        }
        if((enteroValidar(cadena[1]) == 0) && (atoi(cadena[1]) <= 0)){
            printf("Error de sintaxis\n");
            return NULL;
        }
        TLISTA *listaux = charToList(cadena[2], laGranVariable);
        if(listaux == NULL){
            printf("Error de sintaxis\n");
            return NULL;
        }
        return copiarNlistaPrimeras(listaux, atoi(cadena[1]));
    } else if(strcmp(cadena[0], "tail") == 0){
        if(num_arg != 3){
            printf("Error de sintaxis\n");
            return NULL;
        }
        if((enteroValidar(cadena[1]) == 0) && (atoi(cadena[1]) <= 0)){
            printf("Error de sintaxis\n");
            return NULL;
        }
        TLISTA *listaux = charToList(cadena[2], laGranVariable);
        if(listaux == NULL){
            printf("Error de sintaxis\n");
            return NULL;
        }
        return copiarNlistaUltimas(listaux, atoi(cadena[1]));
    } else {
        return charToList(cadena[0], laGranVariable);
    }
    free(lista1);
    free(lista2);
    return NULL;
}

void save(char *nombre, TVARS *workspace){ //Estamos escribiendo en el meta

    char aux1[50]="./";
    int numero_tablas = 0;
    int i;

    strcat(aux1,nombre);
    strcat(aux1,".txt");

    printf("Nombre del fichero: %s\n", aux1);
    FILE *fichero; // creamos el meta
    fichero = fopen(aux1,"w+"); // abrimos el txt
    if(fichero != NULL){

        fprintf(fichero, "LIST WORKSPACE\n");
        fprintf(fichero,"--------------\n");
        TVAR *auxiliar = workspace->var1;
        for (int i = 0; i < workspace->n; i++) {
            printf("Nombre: %s\n", auxiliar->nombre);
            fprintf(fichero, "%s\n", auxiliar->nombre);
            TLISTA *auxiliar2 = auxiliar->valor;
            TNUM *numAux=auxiliar2->primero;
            for (int j=0; j<auxiliar2->n; j++){
                if(j == auxiliar2->n-1){
                    fprintf(fichero,"%.11g\n",numAux->valor);
                }
                else{
                    fprintf(fichero,"%.11g ",numAux->valor);
                }
                numAux=numAux->siguiente;
            }
            fprintf(fichero,"--------------\n");
            auxiliar = auxiliar->siguiente;
        }
        
        fclose(fichero); // cerramos el fichero
    }
    else{
        printf("algo salio mal\n");
    }
}

int imprimirTVAR(TVAR* LaGranLista){     
    TVAR* aux = LaGranLista;  
    int i = 0;   
    while(aux != NULL){        
        i++; 
        aux = aux->siguiente;    
    } 
    return i;
}

TVARS* load(char *nombre){ //Carga las tablas en memoria

    TVARS *workspace=NULL, *tablanueva;
    FILE *fileWorkspace;
    char aux1[50]="";
    char linea[1000],val[100];
    int num_tabla,num_campos, i, j;
    char *nombre_tabla;
    char **nombre_campo;
    

    strcpy(aux1,nombre);
    strcat(aux1,".txt");

    fileWorkspace = fopen(aux1, "r"); // abrimos el meta en modo lectura
    if(fileWorkspace == NULL){
        printf("ERROR inesperado");
        return 0;
    }
    fgets(linea,1000,fileWorkspace); // leemos los primeros mil caracteres de una linea
    ObtenerCampo(linea,":",1,val); // optenemos el valor del campo 1
    Trim(val);                  // le quitamos los espacios al valor
    num_tabla = atoi(val);      // lo convertimos a numero

    for(i=0; i<num_tabla;i++){ // vamos a hacer este proceso tantas veces como tablas tengamos en el meta

        fgets(linea,1000,fileWorkspace); // IGNORAMOS LOS GUIONES DEL META
        fgets(linea,1000,fileWorkspace); // cogemos la linea del nombre de la tabla y num de campos. "CANDELA: 2"
        ObtenerCampo(linea, ":", 0,val); // cogemos el primer valor de la linea hasta los dos puntos "CANDELA"
        Trim(val);                  // Quita los espacios
        nombre_tabla=strdup(val);   // apuntamos nombre_tabla al valor de val
        ObtenerCampo(linea,":",1,val); // cogemos el numero de campos "2"
        Trim(val);                  //quita los espacios
        num_campos=atoi(val);       // convertimos a numero el valor de numcampos "2" 

        nombre_campo = malloc(sizeof(char*)*num_campos); // reservamos memoria tipo puntero para los parametros
        tipos = malloc(sizeof(TYPE*)*num_campos); //Reservmos memoria para los tipos
        
        for(j=0;j<num_campos;j++){ // lo vamos a hacer por cada columna de la tabla
            fgets(linea,1000,fileWorkspace); // cogemos la linea
            ObtenerCampo(linea,":",0,val);  // vemos el nombre del campo
            Trim(val);
            nombre_campo[j]=strdup(val); // lo copiamos en la caja de nombre_campo que es un puntero doble
            ObtenerCampo(linea,":",1,val); // cogemos el tipo
            Trim(val);
            tipos[j]=tipo(val); // lo metemos en la caja de tipos
        }

        tablanueva = inicializar_tabla(nombre_tabla,num_campos, nombre_campo, tipos); // creamos la tabla

        if(workspace==NULL){ // si es la primera tabla
            workspace=tablanueva;
                    
        }
        else{ // sino la insertamos la ultima
            insertarUltima(workspace, tablanueva);          
        }

    }
    fclose(fileWorkspace); // cerramos el meta
    return workspace;
}

void Trim(char *cad){
	int c, i, j, n=strlen(cad);
	
	if (cad==NULL || n<1)
		return;
	n--;
	while(n>=0 && ((c=cad[n])==' ' || c=='\t' || c=='\n' || c=='\r' || c=='"'))
		n--;
	cad[n+1]='\0';
	i=0;
	while (i<=n && ((c=cad[i])==' ' || c=='\t' || c=='\n' || c=='\r' || c=='"'))
		i++;
	for (j=0 ; j<=n-i+1; j++)
		cad[j]=cad[j+i];
}

char* ObtenerCampo(char *lin, char *sep, int id, char *val) {                                                           
	int i, tamSep=1;
	char *p1, *p2;
	
	if (lin==NULL || lin[0]=='\0')
		return NULL;
	
	p1=lin;
	p2=strstr(lin, sep);
	
	for(i=0; i<id;i++)
	{
		p1=p2+tamSep;
		p2=strstr(p1, sep);
	}
	if(p2==NULL)
		strcpy(val,p1);
	else
	{
		strncpy(val, p1, p2-p1);
		val [p2-p1]='\0';
	}
	return val;
}