Manejador de Listas
PRÁCTICA DE FUNDAMENTOS DE PROGRAMACIÓN

Sepiderealizar un programa en Cque, mediante unainterfazdelíneadecomandos,
tambiénllamada CLI ( CommandLineInterface ),permitarealizaroperacionesconlistasde
valores numéricos (enteros y reales). Durante la ejecucióndel programase podrán ir
creando variables y asignarlesun valor,dichovalor será siempreuna lista de valores
numéricos(lalistapodríaestarvacía).Adicionalmente,sepodránhaceroperacionescon
estásvariablesparacalcularnuevosvalores(listas)y/ocrearnuevasvariablesomodificar
elvalordealgunadelasvariablesyacreadas.Encadamomento,elconjuntodevariables
yvaloresquesehayancreadoconstituirán elespaciodetrabajo(oworkspace)quese
deberá poder guardar en disco para poder recuperarlo más adelante.

Sobre el funcionamiento general del programa, al arrancar imprimirá en pantalla el
nombreyapellidosdelalumnoysuemail,yacontinuación,paraqueelusuariopueda
introducir comandos desde teclado, mostrará el siguiente prompt:

<*>:

La ejecución general del programa deberá ser como se indica en el siguiente
pseudocódigo:

1.Imprimir en pantalla datos del alumno:
nombre, apellidos y correo electrónico
2.Mostrar el prompt en color blanco
3.Leer comando (o expresión) introducido por teclado
4.Analizar el comando
⇒ Si el comando es incorrecto se indica con un
mensaje de error en rojo y se vuelve al paso 2
5.Determinar si es posible ejecutar el comando
⇒ Si no es posible ejecutar el comando se indica con
un mensaje de error en rojo y se vuelve al paso 2
6.Si el comando es ‘ exit ’ (sin parámetros) se termina la
ejecución del programa, liberando previamente toda la
memoria y mostrando por pantalla el mensaje " Bye, bye "
en verde y volver al color por defecto blanco
7.Si el comando no es ‘ exit ’ se ejecuta la acción
correspondiente y se vuelve al paso 2. Cuando la acción
implique mostrar alguna salida por pantalla, se mostrará
dicha información en color verde

Enel paso7, donde dice “ se ejecutala acción correspondiente ”habráquerealizar
algunadelasaccionesquesedescribiránalolargodeestedocumento.Nótesequea
veces esas acciones deberán mostrar un resultado por pantalla, en cuyo caso,dicho
resultadosemostraráencolorverde,seguidoinmediatamentedelpromptencolorblanco.
Otrasveces,no seránecesarioproporcionarningunasalida,porloqueinmediatamente
se volverá a mostrar el prompt (siempre en color blanco).

Comoyasehaintroducido,elprogramaarealizardeberáhaceroperacionesconlistas.
Una lista de valores será una serie de números, enteros o reales, colocados entre
corchetesyseparadosporespacios otabuladores,porejemplo,lasiguientedescripción
sería una lista válida:

[12 +33 3.141592 25 18.33 -77.223344 0]

Unalista vacíase representa con unapareja decorchetessinningúncontenidoensu
interior, como se muestra a continuación:

[]

A la hora de declarar una lista se puede hacer de dos formas,de forma explícitao
implícita. La forma explícita es indicando uno tras otro, todos los númerosque debe
contenerlalista,ejemplodeellosonlasdoslistasquesehanpuestomásarriba(unacon
7 elementos yotra, vacía, con 0 elementos).La formaimplícitaconsisteenindicar un
valor inicial, uno final y, opcionalmente, un incremento, según el siguiente patrón:

[valor_inicial : valor_final]
[valor_inicial $ incremento : valor_final]

véanse los siguientes ejemplos (lista implícita ⇒ lista explícita equivalente):

[1 : 5] ⇒ equivale a: [1 2 3 4 5]
[1.5 : 5] ⇒ equivale a: [1.5 2.5 3.5 4.5]
[0 $ 3 : 10] ⇒ equivale a: [0 3 6 9]
[0 $ 0.1 : 1] ⇒ equivale a: [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1]
[1 : 1] ⇒ equivale a: [1]
[1 $ 2 : 1] ⇒ equivale a: [1]

Nóteseque, el valor inicialsiempreaparecealprincipiodelalista,elvalorfinalpuede
aparecerono,peronosepuede sobrepasar.Elincrementopordefectoes+1,siempre
queelvalorinicialseamenorqueelvalorfinal.Sifueraalrevés(valorinicialmayorque
final)elincrementopordefectoserá-1.Opcionalmentesepuede indicarunincremento
diferente tras el carácter ‘$’. En los ejemplos anteriores, los incrementos han sido
positivos,convalorinicialmenorqueelvalorfinal,perotambiéndebenpoderindicarse
incrementos negativos,en esos casos el valorinicial tienequesermayorqueelvalor
final,sinosecumplenestascondiciones,lalistaesincorrecta.Tampocotienesentidoun

incrementoigualacero,esotambiénseconsiderauncasodeerror.Alahoradeguardar
unalistaenmemoria(verestructurasdedatosmásadelante)odemostrarlaporpantalla
siempreseharáensuformaexplícita,mostrandounotrasotrotodosloselementosdela
lista.Enlosucesivo,sevaadenotarconlosidentificadores L1 , L2 ,..., Lx cualquiervalor
de lista válida, incluida la lista vacía.

Las operacionesarealizar sepuedendividirendosgrupos,lasde asignaciónylasde
muestraderesultadosporpantalla.Adicionalmentehabráalgunasoperacionesmáspara
guardar o leer datos de ficheros o para operaciones booleanas. Las operaciones de
asignación tendrán la siguiente forma:

variable = <expresión>

donde:

● variable : es cualquier identificador válido para una variable, esdecir,cualquier
combinación no vacíadecaracteresalfanuméricos(exceptoeñes,ovocalescon
tildeodiéresis).Laúnicareglaesqueelprimercarácterdebeserunaletradela‘a’
ala‘z’ odela‘A’ala‘Z’,elsegundocarácterysiguientes(siloshubiera)podrán
serletrasodígitosnuméricos.Noseránnombresdevariablesválidostodosaquello
que coincidan con los comandos que se van a describir más adelante.

● <expresión> :unaexpresiónescualquieroperacióndegeneraodevuelveunvalor,
enesteprograma,losvaloresquepuedetomarunavariablesolamentepuedenser
listascomolasdescritasanteriormente,portanto,enunaoperacióndeasignación
las expresionesválidas únicamenteserán aquellascuyo resultadoseaunalista.
Ejemplos de expresiones válidas en una asignación son:

➤ L1 .- Expresión que contiene solo una lista y devuelve la propia lista.

➤ L1+L2.-Concatenación,devuelveunalistaquecontieneloselementosde
ambas listas respetando el orden, primero todos los de L1,seguidos de
todos los de L2.

➤ L1-L2.-Diferencia,devuelveunalistaconloselementosdeL1quenose
encuentranelL2sineliminarvaloresrepetidos,esdecir,sielelemento‘x’
está dos veces en L1 y una vez en L2 solamente se elimina una vez de L1.

Las expresiones pueden contener también variables que hayan sido creadas
previamente y que contengan un valor, por ejemplo, la siguientesecuencia de
instrucciones sería correcta:

a = [1 : 5] // crea la variable ‘a’ con el valor [1 2 3 4 5]
b = a + [20 4 8 16] // crea b ⇐ [1 2 3 4 5 20 4 8 16]
c = b - [4 1 8] // crea c ⇐ [2 3 5 20 4 16]

x = c - a // crea x ⇐ [20 16]
b = [20 $ -4 : 10] + x // modifica b ⇐ [20 16 12 20 16]

En cambio, la siguiente instrucción sería incorrecta:

c = [1 : 5] + z // No existe la variable ‘z’

Nótesequelasvariablespuestasalaizquierdadelsigno‘=’,sinoexistensecrean
nuevas;siyaexistíanconanterioridadsemodifican.Encambio,aladerechadel
signoigualsolopuedenponerselistas(explícitasoimplícitas)yvariablesqueyase
hayan inicializado anteriormente.

Las operaciones de muestrade resultados son expresiones quecalculanunvalorylo
muestran por pantalla, pero no lo asignan aningunavariable. Entodos los ejemplos
anteriores,siseeliminan la variablede la izquierday el signoigual,la expresiónque
queda, ella sola, sería una operación de muestra de resultados válida, es decir, se
calcularíaelresultadodela expresiónen unavariabletemporal,paraluegomostrarpor
pantallaenresultado.Unavariable,ellasola,ounalista,tambiénsola,seríanigualmente
operaciones de muestra de resultados. Véanse los siguientes ejemplos:

<*>: a = [1 : 4] // asignación (no muestra resultados)
<*>: a
[1 2 3 4] // resultado mostrado por pantalla
<*>: a + [-7 +7 -7.5]
[1 2 3 4 -7 7 -7.5] // resultado mostrado por pantalla

Adicionalmente,setienequeimplementarunaexpresiónqueconsistiráenunaoperación
booleana, que devolverá TRUE o FALSE (verdadero o falso). Esta expresión, al no
devolver una lista no se podrá usar como parte derecha de unaasignación, solose
podrá usarcomoexpresióndemuestraderesultados ,dichoresultado,comoseha
indicado,podráserTRUEoFALSE(quesemostraránenverde).Dichaexpresiónutilizará
elcarácter‘#’(almohadilla)comooperadorysusignificadoseráaveriguarsilalistadela
izquierda esta contenida dentro de la lista de la derecha:

<*>: L1 # L2 // ¿está L1 contenido en L2?
TRUE // si L1 esta contenido dentro de L2, si no ⇒ FALSE

Enestaexpresión hayqueconsiderarlosvaloresrepetidos,porejemplo,siL1tieneel
elemento ‘x’ dosveces, yL2 tiene esemismoelementounasolavez,entoncesL1no
estará contenida en L2. Una lista vacía SIEMPRE está contenida en cualquier otra.

Ademásde los operadores‘+’ (más), ‘-’ (menos), ‘=’(igual)y‘#’(almohadilla)hay que
implementarotroscomandosoexpresionesadicionales,algunasdelascualesdevolverán
unalistayotrasno.Lasquedevuelvenunalistasepodránusarcomopartederechaen
una asignación o simplemente como operaciones de muestra de resultados. Las

operaciones que no generan una lista como resultado, solo se podrán usar como
operacionesdemuestraderesultados,esdecir,seráunerrorusarlascomopartederecha
deunaasignación.Nótesequecadaoperacióntieneunnúmeroconcretodeparámetros,
sialescribirunainstrucciónseindicaranmásomenoselementos(parámetros)delosque
correspondaen cada caso,el comando seconsideraráincorrectoy seindicarácon el
correspondiente mensaje de error (en rojo).Las operaciones adicionales que hay que
implementar son:

head n L1 (devuelve una lista)
‘n’ representa un número entero, la operación devuelve una lista con los ‘n’
primeroselementos de la lista ‘L1’.Si‘n’esmenorque1,sedevuelveunalista
vacía.Si‘n’esmayorquelalongituddelalistasedevuelvelalistacompleta.Si‘n’
no es un entero o L1 no es una lista válida se indicará con un mensaje de error.

tail n L1 (devuelve una lista)
‘n’representaunnúmeroentero,laoperacióndevuelveunalistaconlos‘n’últimos
elementosdelalista‘L1’.Si‘n’esmenorque1,sedevuelveunalistavacía.Si‘n’
esmayorquelalongituddela listasedevuelvelalista completa.Si‘n’noesun
entero o L1 no es una lista válida se indicará con un mensaje de error.

isIn n L1 (devuelve un booleano)
‘n’representaunnúmero,enterooreal,laoperacióndevuelveTRUEsielvalor‘n’
está dentro de la lista ‘L1’, devuelve FALSE encaso contrario. Si‘n’ no esun
número correcto o L1 no es una lista válida se indicará con un mensaje de error.

vars (no genera ningún valor)
Muestra por pantalla un listado de las variables que se han generado en el
programa y el número de elementos de cada una (longitud de la lista).

save nombre_fichero (no devuelve ni genera ningúnvalor; ver página siguiente)
Guardaenunficherodetextoelworkspace(espaciode trabajo)actual,esdecir,
todas las variables que se hayan creado junto con sus valores.

load nombre_fichero (no devuelve ni genera ningúnvalor; ver página siguiente)
Lee un espacio de trabajo o workspace delfichero indicadoreemplazando por
completoelworkspaceactual,esdecir,seeliminantodaslasvariablesquehubiera
enmemoriaysesustituyenporlasquehayaenelficheroleído.Sielficherono
existe o no es un workspace correcto, no secambia naday seindica con un
mensaje de error.

exit (no devuelve ni genera ningún valor)
Finalizalaejecucióndelprograma,liberatodalamemoriaquehubierareservada,
muestraelmensaje " Bye, bye " (enverde)yfinaliza elprograma(sevuelveal
prompt de la consola normal del sistema en color blanco).

Un workspace o espacio de trabajo representa el conjunto de variables y valores
generados durante la ejecución de un programa. Almacenado en un ficherode texto
deberá tener la siguiente forma:

El fichero contendrá, por cada variable, un separador formado por una línea con 14
guiones(“--------------”),enlalíneasiguienteelnombrede dichavariable,yellistadode
elementos de dicha variable separados por espacios justo en la línea siguiente.

El comando “save” deberá generar un fichero con el formato que se acaba de indicar.

Elcomando“load”deberásercapazdeleerycapturarlosdatoscontenidosenunfichero
como ese mismo formato.

Elejemplodelafiguraanteriorsecorrespondeconunespaciode trabajooworkspace
quecontiene cinco variables: ‘ A1 ’,‘ a1 ’, ‘ list1 ’,‘ z ’y ‘ list ’.Concretamentelavariable‘ z ’
tiene debajo una línea en blanco, eso quiere decir que se trata de una lista vacía.
Además,sepuedevercomohaydosvariables,‘ A1 ’y‘ a1 ’,quesolosediferencianenque
unaestáenmayúsculasylaotraenminúsculas.Esoquieredecirqueelprogramadebe
distinguirentremayúsculasyminúsculasy,portanto,identificadorescomo‘ var ’,‘ Var ’o
‘ VAR ’seránconsideradosvariablesdistintas(ojo,‘ vars ’noseríaunavariableválidaya
quehay un comandocon esemismonombre,encambio,‘ VARS ’sí seríaunavariable
válidayaquenocoincideconel nombredeningúncomandoal estarescritoconletras
mayúsculas).

Paraalmacenarenmemoriatantolaslistasdevaloresnuméricoscomounworkspacecon
todassusvariablesysusvalores,OBLIGATORIAMENTE hayqueutilizarlassiguientes
estructuras de datos en C para construir listas doblemente enlazadas:

    Para implementar listas de números reales

typedef struct Numero
{
double valor;
int decimales;
struct Numero *siguiente, *anterior
} TNUM;

typedef struct
{
int n; // nº de elementos de la lista
TNUM *primero, *ultimo;
} TLISTA;

    Para implementar la lista de variables que componen el espacio de trabajo

typedef struct Var
{
char nombre[20];
TLISTA *valor;
struct Var *siguiente, *anterior
} TVAR;

typedef struct
{
int n; // nº de elementos de la lista
TVAR *var1;
} TVARS;

Según estas definiciones, un workspace será un puntero a TVARS , en plural,ouna
estructuradetipo TVARS .Estaestructura,asuvezcontieneinternamenteunalista‘ var1 ’
de estructuras (nodos) ‘ TVAR ’, en singular. Cada elemento ‘ TVAR ’ representa una
variable del workspace, por tanto, será una lista de números, representada por la
estructura ‘ TLISTA ’, que asuvezcontendrá nodos de tipo‘ TNUM ’paraguardarcada
número de la lista.

Cuandosealmacenaunnúmeroenunnodo‘ TNUM ’sealmacenasu‘ valor ’ytambiénel
númerode‘ decimales ’conlosquesehaescritoelnúmero,deesaforma,alahorade
imprimirlos en pantalla o en un fichero, se usará esa información paradeterminar el
formato de impresión (la cantidad de decimales).

Tanto la estructura ‘ TVARS ’ (lista de variables) como la estructura ‘ TLISTA ’ (lista de
números) tienen un componente ‘ n ’ que debe utilizarse para llevar la cuenta de la
cantidaddenodosquehayencadalista.Cuandounalistaestévacíaelvalorde‘ n ’debe
ser‘0’ (cero)y los punterosde dichalista,‘ var1 ’enelcasode‘ TVARS ’y, ‘ primero ’y
‘ ultimo ’ en el caso de ‘ TLISTA ’ deberán tener el valor NULL.

La implementación final de la práctica deberá estar formada por tres ficheros:

● main.c :conlafunción‘main()’delprogramay,sisedesea,algunasotrasfunciones
sencillas.

● lib.h :ficherodecabeceraparalalibreríaprincipaldeltrabajo,debecontenertodas
lasdeclaracionesdeestructurasyprototiposdefunciones(lasestructurasquese
han descrito en la página anterior van en este fichero).

● lib.c : fichero con la definición completa de todas las funciones de la librería
principal de la práctica.

MUYIMPORTANTE:Se recomiendaimplementarenlalibreríadeltrabajo(lib.h/lib.c),
entre otras, todas las funciones necesarias para el tratamiento de listas, tanto para
‘ TVARS ’ como ‘ TLIST ’, incorporando funciones para:

➔ Crear una lista nueva vacía
➔ Eliminar toda una lista y liberando toda la memoria ocupada
➔ Incluir un nuevo elemento en la lista (al principio y al final)
➔ Buscar un elemento dentro de la lista
➔ Eliminar un elemento concreto de la lista
➔ etc...

Todo ello haciendo una buena gestión de memoria, reservando el espacio que sea
necesario y liberándolo cuando corresponda, sin dejar basura en memoria.

SI EN ALGÚN MOMENTO, AL RESERVAR MEMORIA, SE DETECTA QUE HAYUN
PROBLEMA Y NO SE PUEDE REALIZAR LA OPERACIÓN, EL PROGRAMA LO
INDICARÁCONUNMENSAJEDEERRORENROJOCOMO“ FALLODEMEMORIA ”(o
algo similar) Y TERMINARÁ LA EJECUCIÓN (en este caso no es necesario dar la
respuesta de “ Bye, bye ”).
