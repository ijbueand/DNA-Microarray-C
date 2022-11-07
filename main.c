#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define COND 4
#define GEN 3
#define MAX 255

void rellenarGenes(char genes[GEN][MAX]);
void rellenarMicroarray(float microarray[GEN][COND], char genes[GEN][MAX], char cond[COND][MAX]);
void mostrarMicroarray(float microarray[GEN][COND], char genes[GEN][MAX], char cond[COND][MAX]);
void modificarMicroarray(float microarray[GEN][COND], char genes[GEN][MAX], char cond[COND][MAX], char modgen[MAX], char modcond[MAX]);
float calculosMicroarray(float microarray[GEN][COND], char calcgen[MAX],char cond[COND][MAX], char genes[GEN][MAX],char maexprs[MAX]);
void calculoDistancias(float microarray[GEN][COND], float distancias[GEN][GEN]);
void mostrarDistancias(float distancias[GEN][GEN],char genes[GEN][MAX]);
void ordenaDistanciaGen(char gendist[MAX],char genes[GEN][MAX],float distancias[GEN][GEN]);

int main()
{
    int opc=0, fin=0; //OPCIONES A ELEGIR Y FIN DE DO-FOR SI OPC=0
    int check1=0, check2=0; //PARA CHEQUEAR QUE SE HAN INTRODUCIDO NOMBRES DE GENES Y VALORES DEL MICROARRAY
    float media=0.0; //PORQUE ME LO PIDEN EN LA FUNCIÓN MEDIA COMO SALIDA
    char calcgen[MAX]; //GEN DEL QUE QUEREMOS CALCULAR LA MEDIA. ES CADENA DE CARACTERES
    char maexprs[MAX]; //MICROARRAY-EXPRESION, CONDICION PARA LA QUE SE EXPRESA MAS EL GEN
    char gendist[MAX];

    float microarray[GEN][COND]; //MICROARRAY QUE RELLENAMOS EN '2'
    float distancias[GEN][GEN]; //MATRIZ DE DISTANCIAS ENTRE VALORES DE GENES. TRES POR TRES
    char genes[GEN][MAX]; //VECTOR DE CADENA DE CARACTERES
    char cond[COND][MAX]= {"Cond0","Cond1","Cond2","Cond3"}; //VECTOR CON NOMBRES DE LAS CONDICIONES
    char modgen[MAX], modcond[MAX]; //CADENAS DEL NOMBRE DEL GEN Y LA CONDICION QUE QUEREMOS MODIFICAR POSTERIORMENTE



    do
    {
        printf("=========================== MENU ===========================\n");
        printf("  1.- Introducir los nombres de los genes\n");
        printf("  2.- Introducir los datos de la matriz del microarray\n");
        printf("  3.- Mostrar los datos del microarray\n");
        printf("  4.- Modificar el valor de un gen para una condicion\n");
        printf("  5.- Media y condicion que mas se expresa en un gen\n");
        printf("  6.- Calcular la matriz de distancias\n");
        printf("  7.- Mostrar la matriz de distancias\n");
        printf("  8.- Ordenar las distancias de un gen y mostrar\n");
        printf("  0.- Salir\n");
        printf("============================================================\n");
        printf("INTRODUZCA UNA OPCION:");
        scanf("%d", &opc);

        switch( opc )
        {
        case 1: //SIRVE Y FUNCIONA
        {
            printf("\n");
            rellenarGenes(genes);
            check1=1;
            opc=0;
            printf("\n\n");
            break;
        }
        case 2: //SIRVE Y FUNCIONA
        {
            printf("\n");
            rellenarMicroarray(microarray,genes,cond);
            check2=1;
            opc=0;
            printf("\n\n");
            break;
        }
        case 3: //SIRVE Y FUNCIONA
        {
            printf("\n");
            if(check1==1 && check2==1)
                mostrarMicroarray(microarray,genes,cond);
            else
                printf("Por favor, introduzca el nombre de los genes primero\n");
            opc=0;
            printf("\n\n");
            break;
        }
        case 4: //SIRVE Y FUNCIONA
        {
            printf("\n");
            fflush(stdin);
            printf("Introduzca gen a buscar: ");
            gets(modgen);
            printf("Introduzca condicion a buscar: ");
            gets(modcond);
            modificarMicroarray(microarray,genes,cond,modgen,modcond);
            mostrarMicroarray(microarray,genes,cond);
            opc=0;
            printf("\n\n");
            break;
        }
        case 5: //SIRVE Y FUNCIONA
        {
            printf("\n");
            fflush(stdin);
            printf("Introduzca gen a buscar: ");
            gets(calcgen);
            fflush(stdin);
            media = calculosMicroarray(microarray, calcgen, cond, genes, maexprs);
            printf("La media del gen %s es %f\n", calcgen, media);
            printf("La condicion que mas se expresa es %s\n", maexprs);
            opc=0;
            printf("\n\n");
            break;
        }
        case 6: //SIRVE Y FUNCIONA
        {
            calculoDistancias(microarray,distancias);
            opc=0;
            printf("\n\n");
            break;
        }
        case 7: //SIRVE Y FUNCIONA
        {
            mostrarDistancias(distancias, genes);
            opc=0;
            printf("\n\n");
            break;
        }
        case 8: //SIRVE Y FUNCIONA
        {
            printf("Introduzca gen para buscar sus distancias: ");
            fflush(stdin);
            gets(gendist);
            ordenaDistanciaGen(gendist,genes,distancias);
            opc=0;
            printf("\n\n");
            break;
        }
        case 0:
        {
            fin=1;
            printf("\nGracias por usar el programa :D\n");
            break;
        }
        default:
        {
            printf("\nOpcion no disponible, intentelo de nuevo...\n\n");
            opc=0;
            break;
        }
        }

    }
    while(fin!=1);

    return 0;
}

void rellenarGenes(char genes[GEN][MAX])
{
    int i;
    for(i=0; i<GEN; i++)
    {
        fflush(stdin);
        printf("Introduzca el NOMBRE del gen %d: ",i+1);
        gets(genes[i]); //los nombres se almacenan en vectores de cadenas (matriz)
    }
}

void rellenarMicroarray(float microarray[GEN][COND], char genes[GEN][MAX], char cond[COND][MAX])
{
    int i,j;

    for(i=0; i<GEN; i++)
    {
        for(j=0; j<COND; j++)
        {
            printf("Introduzca el resultado de exponer el gen '%s' a la condicion '%s':",genes[i], cond[j]);
            scanf("%f",&microarray[i][j]);
        }
    }
}

void mostrarMicroarray(float microarray[GEN][COND], char genes[GEN][MAX], char cond[COND][MAX])
{
    int i,j;

    printf("------------------------------\n");
    printf("  Mostrando el microarray...\n");
    printf("------------------------------\n\n");

    for(i=0; i<(COND); i++)
    {
      printf("\t%s",cond[i]);
    }

printf("\n\n");
    for(i=0; i<GEN; i++) //no se poner para que aparezca condn
    {
        printf("%s",genes[i]);
        for(j=0; j<COND; j++)
        {
            printf("\t%3.3f",microarray[i][j]);
        }
        printf("\n\n");
    }
}

void modificarMicroarray(float microarray[GEN][COND], char genes[GEN][MAX], char cond[COND][MAX], char modgen[MAX], char modcond[MAX])
{
    float valor=0.0;
    int i,j;
    int inf=0;

    fflush(stdin);
    printf("Introduce el valor a modificar del gen '%s' para la condicion '%s': ", modgen, modcond);
    scanf("%f",&valor);

    for(i=0; i<GEN; i++)
    {
        for(j=0; j<COND; j++)
        {
            if(strcmp(genes[i],modgen)==0 && strcmp(cond[j],modcond)==0)
            {
                microarray[i][j]=valor;
                inf=1;
            }
        }
    }

    if (inf==0)
        printf("El gen o la condicion introducida no figura en el microarray\n");
}

float calculosMicroarray(float microarray[GEN][COND],char calcgen[MAX],char cond[COND][MAX], char genes[GEN][MAX],char maexprs[MAX])
{
    //cual es la media de todos los valores para todas las condiciones del gen introducido
    int i, j;
    float media=0.0; //MEDIA DE TODOS LOS VALORES QUE TOMA 'calcgen'
    float valormaexprs=0.0; //VALOR MAXIMO DE LA EXPRESION DEL GEN 'calcgen'


    for(i=0; i<GEN; i++)
    {
        // printf("%s y %s",genes[i],calcgen); PARA HACER EL DEBUG MANUAL
        if(strcmp(genes[i],calcgen)==0) //SI LA CADENA DE GENES ES LA MISMA DE CALCGEN ES QUE HEMOS LLEGADO A SU FILA
        {
            for(j=0; j<COND; j++) //RECORREMOS HORIZONTALMENTE LA FILA DEL GEN PARA TODAS LAS CONDICIONES Y LAS SUMAMOS
            {
                media+=microarray[i][j];

                if(microarray[i][j]>valormaexprs) //SI EL VALOR EN EL PUNTO EN CUESTION ES MAYOR ES MAYOR QUE EL PREVIO SE GUARDA COMO MAXIMO
                {
                    valormaexprs = microarray[i][j];
                    strcpy(maexprs, cond[j]); //LA CONDICION PARA ESE VALOR SE GUARDA EN LA CADENA MicroArrayExpresion
                }

            }
        }
    }


    media=media/COND; //LA SUMATORIA PASA A SER MEDIA ARITMETICA
   // printf("%f", media); PARA DEBUGGEAR MANUALMENTE. YA NO HACE FALTA

    return media;
}

void calculoDistancias(float microarray[GEN][COND], float distancias[GEN][GEN])
{
    int i, j, k; //HEMOS REDEFINIDO LA MATRIZ DISTANCIAS.
    float valor=0.0;

    for(i=0;i<GEN;i++)
    {
        for(j=0;j<GEN;j++)
        {
            valor=0.0;
            for(k=0;k<COND;k++)
            {
                valor+=pow(microarray[i][k]-microarray[j][k],2);//CUADRADO DE LA RESTA DE LOS ELEMENTOS. FALTA RAIZ
            }
            valor=sqrt(valor);
            distancias[i][j]=valor;
        }
    }

    printf("\nDistancia calculada con exito!\n");//PARA QUE SALGA ALGO POR LO MENOS
}

void mostrarDistancias(float distancias[GEN][GEN],char genes[GEN][MAX])
{
    int i,j;

    printf("\n------------------------------\n");
    printf(" Mostrando las distancias...\n");
    printf("------------------------------\n\n");


     for(i=0; i<(GEN); i++){
        printf("\t%s",genes[i]);
     } //ESTO ES PARA PONER LA FILA DE ARRIBA CON EL ESPACIO Y QUE COINCIDA



    printf("\n\n");
    for(i=0; i<GEN; i++)
    {
        printf("%s",genes[i]);
        for(j=0; j<GEN; j++)
        {
            printf("\t%3.3f",distancias[i][j]);
        }
        printf("\n\n");
    }
}

void ordenaDistanciaGen(char gendist[MAX],char genes[GEN][MAX],float distancias[GEN][GEN])
{
    float copiadistancias[GEN];
    char copiagenes[GEN][MAX];
    float faux=0.0;
    char caux[MAX];
    int i,j;
    int existe=0;

    for(i=0; i<GEN; i++)
    {
        if(strcmp(gendist,genes[i])==0)
        {
            existe=1;
            if (existe==1)
            {
                for(j=0; j<GEN; j++)
                {
                    copiadistancias[j]=distancias[i][j];//COPIA DISTANCIA GENES

                }
            }
        }
    }

    for(i=0; i<GEN; i++)
    {
        strcpy(copiagenes[i],genes[i]);//COPIA NOMBRE DE LOS GENES
    }

    if (existe==1)
    {

        for(i=0; i<GEN; i++)
        {
            for(j=i; j<GEN; j++)
            {
                if(copiadistancias[i]>copiadistancias[j])
                {
                    faux=copiadistancias[i];
                    copiadistancias[i]=copiadistancias[j];
                    copiadistancias[j]=faux;

                    strcpy(caux,copiagenes[i]);
                    strcpy(copiagenes[i],copiagenes[j]);
                    strcpy(copiagenes[j],caux);
                }
            }
        }

        printf("\nDISTANCIAS ORDENADAS:\n");
        for(i=0; i<GEN; i++)
        {
            printf("\t- d(%s,%s) = %f\n", gendist, copiagenes[i],copiadistancias[i]);
        }
    }
    if(existe==0)
        printf("\nEL GEN SELECCIONADO NO EXIXTE. PRUEBE DE NUEVO...\n");
}
