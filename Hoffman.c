#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Nodo{
    char carac;
    int frecuencia;
    struct Nodo *izq; //menores a la izquierda, mayores a la derecha
    struct Nodo *der;
}Arbol;

typedef struct Nodo1{
    char carac;
    int frecuencia;
    struct Nodo1 *sig;
    struct Nodo1 *ant;
    Arbol *tr;
}Lista;

typedef struct Nodo2{
    int frecuencia;
    char carac;
    char clave[10];
    struct Nodo2 *sig;
    struct Nodo2 *ant;
}ListaExt;

typedef struct Nodo3{
    char carac;
    int frecuencia;
    int usado;
    struct Nodo3 *izq; //menores a la izquierda, mayores a la derecha
    struct Nodo3 *der;
}ArbolExt;

typedef struct Nodo4{
    char carac;
    int frecuencia;
    struct Nodo4 *sig;
    struct Nodo4 *ant;
    ArbolExt *tr;
}ListaModif;

char pr[150];
int i=0;
int w=0;
char lets[20];
int letsf[20];
int cifradoBinario[100];

//Funciones Codificacion
Lista* contFrecuencias(char x[100]);
Arbol* crearSubarboles(Lista *n1, Lista *n2);
Arbol* nacimiento(Lista *fr);
Lista* AltaInternaOrdenada(Lista* top,int frecue,char c,Arbol *tr);
Arbol* CrearArbolAsociado(char c, int dato,Arbol *A, Arbol *B);
Lista* CrearListaAsociada(char c,int f,Arbol *sr);
void archivarArbol();
//Funciones Lista
Lista* CrearLista(char c,int f);
Lista* AltaLista(char c, int f, Lista *top);
void ConsultaLista(Lista *top);
Lista* ordenarLista(Lista *top);
int ConteoLista(Lista *top);
Lista* bajaInicio(Lista *top);
Lista* AltaFinalLista(Lista *top, int dato,char c,Arbol *tr);
//funciones arboles
Arbol* CrearArbol(char c, int dato);
void preorder(Arbol *raiz);
//obtencion de codigos
ListaModif* archiALista(char direccion[]);
ArbolExt* renacimiento(ListaModif *top);
void preorderSencillo(ArbolExt *raiz);
ListaExt* CrearListaExt(char c,char clave[],int f);
ListaExt* AltaListaExt(char c, char clave[], ListaExt *top,int f);
void ConsultaListaExt(ListaExt *top);
ArbolExt* CrearArbolExt(char c, int dato);
void preorderG(ArbolExt *raiz);
Lista* listaParaRecorrido();
ListaExt* GeneraCodigos(ArbolExt *raiz,Lista *admitidos);
ListaModif* CrearListaModif(char c,int f);
ListaModif* AltaListaModif(char c, ListaModif *top,int f);
void ConsultaListaModif(ListaModif *top);
//cifrado
void Cifrar(char mensaje[],ListaExt *clavs);
//finales
void Descifrar(char direccionLlave[], char direccionMensaje[]);
void DescifrarF(char direccionLlave[], char direccionMensaje[]);

int main(){
    int opcion,confirma=1;
    printf("Codificacion de Hoffman\n");
    while(confirma==1){
    printf("1. Cifrar\n2. Descifrar\n3. DescifrarF\n");
    scanf("%d",&opcion);
    fflush(stdin);
    if(opcion==1){
        char mensaje[100];
        Lista *frecuencias=NULL,*listaprec=NULL;
        ListaModif *semilla=NULL;
        ArbolExt *renovado=NULL;
        ListaExt *claves=NULL;

        printf("Escriba el mensaje\n");
        gets(mensaje);
        fflush(stdin);
        strlwr(mensaje);
        frecuencias=contFrecuencias(mensaje);
        //ConsultaLista(frecuencias);
        //printf("\n");
        frecuencias=ordenarLista(frecuencias);
        //ConsultaLista(frecuencias);
        nacimiento(frecuencias);
        /*printf("\n");
        printf("pr: \n");
        printf("%s",pr);*/
        archivarArbol();
        char direccion[]="C:\\Users\\leonm\\Desktop\\llavecita.txt";
        char direccion1[]="C:\\Users\\leonm\\Desktop\\cifrado.txt";
        semilla=archiALista(direccion);
        //printf("Lista semilla\n");
        //ConsultaListaModif(semilla);
        //ConsultaLista(semilla);
        renovado=renacimiento(semilla);
        //printf("Nuevo arbol\n");
        //preorderSencillo(renovado);
        //printf("\nCaracteres validos\n");
        preorderG(renovado);
        /*for(i=0;i<w;i++){
            printf("%c/%d ",lets[i],letsf[i]);
        }*/
        //printf("\nNuevaListaRecorrido\n");
        listaprec=listaParaRecorrido();
        //ConsultaLista(listaprec);
        //printf("Claves\n");
        claves=GeneraCodigos(renovado,listaprec);
        //ConsultaListaExt(claves);
        Cifrar(mensaje,claves);
    }else if(opcion==2){
        char direccion[]="C:\\Users\\leonm\\Desktop\\preorder.txt";
        char direccion1[]="C:\\Users\\leonm\\Desktop\\ascii.txt";
        Descifrar(direccion,direccion1);
    }else if(opcion==3){
        char direccion[]="C:\\Users\\leonm\\Desktop\\preorder_huffman.txt";
        char direccion1[]="C:\\Users\\leonm\\Desktop\\cod_num.txt";
        DescifrarF(direccion,direccion1);
    }
    printf("\nPara repetir presione 1, en caso contrario 0\n");
    scanf("%d",&confirma);
    fflush(stdin);
}
    return 0;
}

//Funciones Codificacion
Lista* contFrecuencias(char x[100]){
    Lista *nuevo=NULL;
    char tomados[100];
    char letra;
    int i,j,k,contLetra=0,existe,tam=0;
    for(i=0;i<strlen(x);i++){
        letra=x[i];

        for(k=0;k<tam;k++){
            if(letra==tomados[k]){
                existe=0;
                break;
            }

            existe=1;
        }

        if(existe!=0){
            tomados[tam]=letra;
            tam++;
            for(j=0;j<strlen(x);j++){
                if(letra==x[j]){
                    contLetra++;
                }
            }
            nuevo=AltaLista(letra,contLetra,nuevo);
            contLetra=0;
        }
    }
    return nuevo;
}

Lista* CrearListaAsociada(char c,int f,Arbol *sr){
    Lista *nuevo;
    nuevo=(Lista*)malloc(sizeof(Lista));
    nuevo->carac=c;
    nuevo->frecuencia=f;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    nuevo->tr=sr;
    return nuevo;
}

void archivarArbol(){
    FILE *ar;
    char direccion[]="C:\\Users\\leonm\\Desktop\\llavecita.txt";

    ar=fopen(direccion,"wt");
    if(ar == NULL){
		printf("Error al tratar de crear el archivo");
		return;
	}

	fwrite(pr,1,strlen(pr),ar);

	fclose(ar);
}

ListaModif* archiALista(char direccion[]){
    FILE *ar,*ar2,*ar3,*ar4;
    ListaModif *psAr=NULL;
    int c,i=0,j,a,b,a2,b2,cont=0,cont2=0,condi=0,condi2=0,condi3=0;
    int c2,c3,c4;
    int nivel;
    int ramas[200];
    char caracs[200];
    char auxiliar[5];
    char clave[20];
    //char direccion[]="C:\\Users\\leonm\\Desktop\\llavecita.txt";
    ar=fopen(direccion,"r");
    ar2=fopen(direccion,"r");
    ar3=fopen(direccion,"r");
    ar4=fopen(direccion,"r");

	while(!feof(ar2) && i==0){
        c2=fgetc(ar2);
        i++;
	}

	i=0;

	while(!feof(ar4) && i==0){
        c4=fgetc(ar4);
        i++;
	}

	printf("\n");


	while(!feof(ar)){
        c=fgetc(ar);
        j=0;
        a=c-'0';
        if(a>=0 && a<=9 && condi==0){
            auxiliar[0]=c;
            condi2=1;
        }
        while(!feof(ar2) && j==0){
            c2=fgetc(ar2);
            //printf("%c",c2);
            b=c2-'0';
            if((b>=0 && b<=9) && auxiliar[0]==c){
                auxiliar[1]=c2;
                condi=1;
            }else{
                condi=0;
                auxiliar[1]='\0';
            }
            j++;
        }

        if(condi2==1){
            ramas[cont]=atoi(auxiliar);
            cont++;
            condi2=0;
        }
	}

	//obtencion de chars

	while(!feof(ar3)){
        c3=fgetc(ar3);
        a=c3-'0';
        j=0;
        while(!feof(ar4) && j==0){
            c4=fgetc(ar4);
            if(c3==' ' && c4==' ' && condi3!=1){
                caracs[cont2]=' ';
                cont2++;
                condi3=1;
            }
            j++;
        }
        if(a!=0 && a!=1 && a!=2 && a!=3 && a!=4 && a!=5 && a!=6 && a!=7 && a!=8 && a!=9 && c3!=' '){
            caracs[cont2]=c3;
            cont2++;
        }
	}

	/*for(i=0;i<cont2;i++){
        printf("%c",caracs[i]);
	}
	printf("\n");

	for(i=0;i<cont;i++){
        printf("%d ",ramas[i]);
	}
	printf("\n");
	*/

	for(i=0;i<cont;i++){
        psAr=AltaListaModif(caracs[i],psAr,ramas[i]);
	}

	fclose(ar);
	fclose(ar2);
	fclose(ar3);
	fclose(ar4);

	return psAr;

}

//Funciones Lista
Lista* CrearLista(char c,int f){
    Lista *nuevo;
    nuevo=(Lista*)malloc(sizeof(Lista));
    nuevo->carac=c;
    nuevo->frecuencia=f;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    nuevo->tr=NULL;
    return nuevo;
}

Lista* AltaLista(char c, int f, Lista *top){
    Lista *aux, *aux2;
    aux=CrearLista(c,f);
    if(top==NULL){
        return aux;
    }else{
        aux2=top;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=aux;
        aux->ant=aux2;
        return top;
    }
}

Lista* AltaFinalLista(Lista *top, int dato,char c,Arbol *tr){
	Lista *nuevo, *aux;
	aux=top;
	nuevo=CrearListaAsociada(c,dato,tr);
	if(aux==NULL){
		return nuevo;
	}else{
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		aux->sig=nuevo;
		nuevo->ant=aux;
		return top;
	}
}

void ConsultaLista(Lista *top){
    Lista *aux;
    aux=top;
    while(aux!=NULL){
        printf("%c-%d\n",aux->carac,aux->frecuencia);
        aux=aux->sig;
    }
}

Lista* ordenarLista(Lista *top){
    Lista *aux,*aux2,*aux3;
    int i,tam,j=0,k;
    tam=ConteoLista(top);
    aux=top;
    aux3=top;
    if(top==NULL){
        printf("Lista vacia\n");
    }

    for(i=1; i<tam+2; i++){
        aux2=aux;
        while((i>1)&&(aux2->frecuencia  < aux2->ant->frecuencia)){

            aux2->ant->sig=aux2->sig;
            aux2->sig=aux2->ant;
            aux2->ant=aux2->ant->ant;
            aux2->sig->ant=aux2;

            if(aux2->ant!=NULL){
                aux2->ant->sig=aux2;
            }

            if(aux2->sig->sig!=NULL){
                aux2->sig->sig->ant=aux2->sig;
            }

            if(aux3->ant!=NULL){
                aux3=aux3->ant;
            }

            if(aux2->ant==NULL){
                break;
            }


        }
        if(i>1 && i<tam+2){
           aux=aux3;
           for(k=1;k<i;k++){
            aux=aux->sig;
           }
        }else if(i==1){
        aux=aux->sig;
        }
    }

    return aux3;
}

int ConteoLista(Lista *top){
    int i=0;
    if(top==NULL){
        return 0;
    }else{
        while(top!=NULL){
            i++;
            top = top->sig;
        }
        return i;
    }
}

Lista* AltaInternaOrdenada(Lista* top,int frecue,char c,Arbol *tr){
	int i;
	Lista *aux, *nuevo;
	aux=top;
	nuevo=CrearListaAsociada(c,frecue,tr);
	if(top==NULL){
		return nuevo;
	}else{
	    if(aux->sig!=NULL){
            while(aux->sig->frecuencia<=frecue){
                aux=aux->sig;
                i=0;
                if(aux->sig==NULL){
                    i=1;
                    break;
                }
            }
	    }else{
            i=2;
	    }

        if(i==1){
            top=AltaFinalLista(top,frecue,c,tr);
        }else if(i==0){
            nuevo->sig=aux->sig; //se mueven dos anteriores y dos siguientes
            aux->sig->ant=nuevo;
            aux->sig=nuevo;
            nuevo->ant=aux;
        }else if(i==2){
            if(aux->frecuencia<=frecue){
                aux->sig=nuevo;
                nuevo->ant=aux;
            }else{
                nuevo=CrearListaAsociada(c,frecue,tr);
                aux->ant=nuevo;
                nuevo->sig=aux;
                return nuevo;
            }
        }

        return top;

    }
}


Lista* bajaInicio(Lista *top){
	if(top==NULL){
		printf("Lista vacia\n");
	}else{
		Lista *aux;
		aux=top;
		top=top->sig;
		if(top!=NULL){
			top->ant=NULL;
		}
		free(aux);
		return top;
	}
}
//funciones arboles
Arbol* crearSubarboles(Lista *n1, Lista *n2){
    Arbol *sRaiz,*h1,*h2;
    h1=CrearArbol(n1->carac,n1->frecuencia);
    h2=CrearArbol(n2->carac,n2->frecuencia);

    if(n1->tr==NULL && n2->tr==NULL){
        sRaiz=CrearArbol('-',(n1->frecuencia + n2->frecuencia));

        if(n1->frecuencia > n2->frecuencia){
            sRaiz->izq=h2;
            sRaiz->der=h1;
        }else if((n1->frecuencia <= n2->frecuencia)){
            sRaiz->izq=h1;
            sRaiz->der=h2;
        }
    }else if((n1->tr!=NULL && n2->tr!=NULL)){
        sRaiz=CrearArbolAsociado('-',(n1->frecuencia + n2->frecuencia),n1->tr,n2->tr);
    }else if(n1->tr!=NULL){
        sRaiz=CrearArbol('-',(n1->frecuencia + n2->frecuencia));
        if(n1->tr->frecuencia > n2->frecuencia){
            sRaiz->izq=h2;
            sRaiz->der=n1->tr;
        }else if((n1->tr->frecuencia <= n2->frecuencia)){
            sRaiz->izq=n1->tr;
            sRaiz->der=h2;
        }
    }else if(n2->tr!=NULL){
        sRaiz=CrearArbol('-',(n1->frecuencia + n2->frecuencia));
        if(n1->frecuencia > n2->tr->frecuencia){
            sRaiz->izq=n2->tr;
            sRaiz->der=h1;
        }else if((n1->frecuencia <= n2->tr->frecuencia)){
            sRaiz->izq=h1;
            sRaiz->der=n2->tr;
        }
    }


    //printf("sRaiz %c %d\n",sRaiz->carac,sRaiz->frecuencia);
    return sRaiz;

}

Arbol* CrearArbol(char c, int dato){
    Arbol *nuevo;
    nuevo=(Arbol*)malloc(sizeof(Arbol));
    nuevo->frecuencia=dato;
    nuevo->carac=c;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    return nuevo;
}

Arbol* CrearArbolAsociado(char c, int dato,Arbol *A, Arbol *B){
    Arbol *nuevo;
    nuevo=(Arbol*)malloc(sizeof(Arbol));
    nuevo->frecuencia=dato;
    nuevo->carac=c;
    if(A->frecuencia > B->frecuencia){
        nuevo->der=A;
        nuevo->izq=B;
    }else if(A->frecuencia <= B->frecuencia){
        nuevo->der=B;
        nuevo->izq=A;
    }
    return nuevo;
}


void preorder(Arbol *raiz){
    char x[5]; //pudo ser un fprintf
    int y;
    if(raiz!=NULL){
        printf("%d/",raiz->frecuencia);
        printf("%c ",raiz->carac);
        pr[i]=raiz->carac;
        i++;
        pr[i]=' ';
        i++;
        itoa(raiz->frecuencia,x,10);
        if(raiz->frecuencia<=9){
            pr[i]=x[0];
            i++;
        }else if(raiz->frecuencia>9 && raiz->frecuencia<=99){
            pr[i]=x[0];
            i++;
            pr[i]=x[1];
            i++;
        }else if(raiz->frecuencia>99){
            pr[i]=x[0];
            i++;
            pr[i]=x[1];
            i++;
            pr[i]=x[2];
            i++;
        }
        pr[i]=' ';
        i++;
        preorder(raiz->izq);
        preorder(raiz->der);
    }
}

Arbol* nacimiento(Lista *fr){

    Arbol *aux=NULL;
    Lista *auxL=NULL,*a;
    int tam=ConteoLista(fr);
    int tam2;
    auxL=fr;

    while(tam>1){
        aux=crearSubarboles(auxL,auxL->sig);
        auxL=bajaInicio(auxL);
        tam2=ConteoLista(auxL);
        if(tam2==1){
            break;
        }
        auxL=bajaInicio(auxL);
        ConsultaLista(auxL);
        auxL=AltaInternaOrdenada(auxL,aux->frecuencia,'-',aux);
        tam=ConteoLista(auxL);
    }
    preorder(aux);
    return aux;
}

ArbolExt* renacimiento(ListaModif *top){
    ListaModif *act,*retornador=NULL;
    ArbolExt *auxA=NULL;

    act=top;

    while(act!=NULL){ //A cada nodo de la lista se le crea un nodo-arbol asociado con su misma freuencia y caracter
        auxA=CrearArbolExt(act->carac,act->frecuencia);
        act->tr=auxA;
        act=act->sig;
    }

    act=top;
    act=act->sig;
    /*printf("tr relacionados\n");
    while(act!=NULL){
        printf("%d-%c ",act->tr->frecuencia,act->tr->carac);
        act=act->sig;
    }*/
    while(act!=NULL){
        if(act->ant->frecuencia==act->frecuencia){
            act->ant->ant->tr->der=act->tr;
        }else if(act->frecuencia<=act->ant->frecuencia){
            if(act->ant->tr->izq==NULL){
                act->ant->tr->izq=act->tr;
                //printf("la izq de %d%c es %d%c (1)\n",act->ant->frecuencia,act->ant->carac,act->frecuencia,act->carac);
            }else if(act->ant->tr->izq!=NULL){
                act->ant->tr->der=act->tr;
                //printf("la der de %d%c es %d%c (2)\n",act->ant->frecuencia,act->ant->carac,act->frecuencia,act->carac);
            }
        }else if(act->frecuencia>act->ant->frecuencia){
            retornador=act->ant;
            while(act->frecuencia>retornador->frecuencia){
                retornador=retornador->ant;
            }
            if(retornador->ant!=NULL){
                //printf("entre con reto no nulo\n");
                if(retornador->ant->frecuencia<act->frecuencia){ //el antes del llegado fue mas chico
                    retornador->tr->der=act->tr;
                    //printf("la der de %d%c es %d%c (3)\n",retornador->frecuencia,retornador->carac,act->frecuencia,act->carac);
                }else if(retornador->ant->frecuencia>act->frecuencia){
                    //printf("in \n");
                    if(retornador->ant->carac!='-'){
                        retornador->tr->der=act->tr;
                        //printf("la der de %d%c es %d%c (4)\n",retornador->frecuencia,retornador->carac,act->frecuencia,act->carac);

                    }else{
                        if(retornador->tr->der==NULL){
                            retornador->tr->der=act->tr;
                        //printf("la der de %d%c es %d%c (5)\n",retornador->frecuencia,retornador->carac,act->frecuencia,act->carac);
                        }else{
                            retornador->ant->tr->der=act->tr;
                            //printf("la der de %d%c es %d%c (6)\n",retornador->ant->frecuencia,retornador->ant->carac,act->frecuencia,act->carac);
                        }
                    }
                }
            }else if(retornador->ant==NULL){
                retornador->tr->der=act->tr;
                //printf("la der de %d%c es %d%c (7)\n",retornador->frecuencia,retornador->carac,act->frecuencia,act->carac);
            }
        }
        act=act->sig;
    }

    return top->tr;
}

void preorderSencillo(ArbolExt *raiz){
    if(raiz!=NULL){
        printf("%d/",raiz->frecuencia);
        printf("%c ",raiz->carac);
        preorderSencillo(raiz->izq);
        preorderSencillo(raiz->der);
    }
}

ListaExt* GeneraCodigos(ArbolExt *raiz,Lista *admitidos){
    Lista *aux=NULL;
    ArbolExt *act=NULL;
    ListaExt *nuevo=NULL;
    int encontrado,cont,tam,fr,z;
    char c;
    char cla[20];

    aux=admitidos;
    tam=ConteoLista(admitidos);

    while(tam>=1){
        c=aux->carac;
        fr=aux->frecuencia;
        act=raiz;
        encontrado=0;
        cont=0;

        for(z=0;z<20;z++){
            cla[z]='\0';
        }

        while(encontrado==0){
                if(act->izq->frecuencia==fr && act->izq->carac==c){
                    encontrado=1;
                    act->usado=act->usado+1;
                    act->izq->usado=2;
                    cla[cont]='0';
                    cont++;
                    break;
                }else if(act->der->frecuencia==fr && act->der->carac==c){
                        encontrado=1;
                        act->usado=act->usado+1;
                        act->der->usado=2;
                        cla[cont]='1';
                        cont++;
                        break;
                }else if(act->izq->frecuencia>fr && act->izq->usado<2){
                    act=act->izq;
                    cla[cont]='0';
                    cont++;
                }else if(act->der->frecuencia>fr && act->der->usado<2){
                    act=act->der;
                    cla[cont]='1';
                    cont++;
                }else{
                    act->usado=2;
                    act=raiz;
                    for(z=0;z<20;z++){
                        cla[z]='\0';
                    }
                    cont=0;
                }
        }
        /*printf("%c \n",c);
        for(int y=0;y<=cont;y++){
            printf("%c",cla[y]);
        }*/
        //printf("\n");
        nuevo=AltaListaExt(c,cla,nuevo,fr);
        for(z=0;z<20;z++){
            cla[z]='\0';
        }
        aux=bajaInicio(aux);
        tam=ConteoLista(aux);
    }

    return nuevo;

}

ListaExt* CrearListaExt(char c,char clave[],int f){
    ListaExt *nuevo;
    nuevo=(ListaExt*)malloc(sizeof(ListaExt));
    nuevo->frecuencia=f;
    nuevo->carac=c;
    strcpy(nuevo->clave,clave);
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    return nuevo;
}

ListaExt* AltaListaExt(char c, char clave[], ListaExt *top,int f){
    ListaExt *aux, *aux2;
    aux=CrearListaExt(c,clave,f);
    if(top==NULL){
        return aux;
    }else{
        aux2=top;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=aux;
        aux->ant=aux2;
        return top;
    }
}

void ConsultaListaExt(ListaExt *top){
    ListaExt *aux;
    aux=top;
    int q;
    while(aux!=NULL){
        printf("%c ",aux->carac);
        for(q=0;q<strlen(aux->clave);q++){
            printf("%c",aux->clave[q]);
        }
        printf("\n");
        aux=aux->sig;
    }
}

ArbolExt* CrearArbolExt(char c, int dato){
    ArbolExt *nuevo;
    nuevo=(ArbolExt*)malloc(sizeof(ArbolExt));
    nuevo->frecuencia=dato;
    nuevo->carac=c;
    nuevo->usado=0;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    return nuevo;
}

void preorderG(ArbolExt *raiz){
    if(raiz!=NULL){
        if(raiz->carac!='-'){
            lets[w]=raiz->carac;
            letsf[w]=raiz->frecuencia;
            w++;
        }
        preorderG(raiz->izq);
        preorderG(raiz->der);
    }
}

Lista* listaParaRecorrido(){
    Lista *nuevo=NULL;
    int x;

    for(x=0;x<w;x++){
        nuevo=AltaLista(lets[x],letsf[x],nuevo);
    }

    return nuevo;
}

ListaModif* CrearListaModif(char c,int f){
    ListaModif *nuevo;
    nuevo=(ListaModif*)malloc(sizeof(ListaModif));
    nuevo->frecuencia=f;
    nuevo->carac=c;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    nuevo->tr=NULL;
    return nuevo;
}

ListaModif* AltaListaModif(char c, ListaModif *top,int f){
    ListaModif *aux, *aux2;
    aux=CrearListaModif(c,f);
    if(top==NULL){
        return aux;
    }else{
        aux2=top;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=aux;
        aux->ant=aux2;
        return top;
    }
}

void Cifrar(char mensaje[],ListaExt *clavs){
    ListaExt *aux;
    int cont=0,contCol=0,i,j,temp,contBin=0;
    char cara;
    int tam=strlen(mensaje);
    //printf("Tam=%d\n",tam);
    int conversor[8]={128,64,32,16,8,4,2,1};
    int Grupo[8];
    int estatus=0,tamBin,contGrupo=0,sonocho=1,decimal=0,diferencia,contTexto=0;
    char nuevoCarac;
    char texto[100];

    char mensajeCifrado[tam][tam];

    FILE *arA;
    char direccion[]="C:\\Users\\leonm\\Desktop\\cifrado.txt";

    arA=fopen(direccion,"wt");

    while(mensaje[cont]!='\0'){
        aux=clavs;
        cara=mensaje[cont]; //obten ek caracter del mensaje
        while(aux!=NULL){
            if(aux->carac==cara){
                for(i=0;i<tam;i++){
                    if(i>=strlen(aux->clave)){
                        mensajeCifrado[i][contCol]='-';
                    }else{
                        mensajeCifrado[i][contCol]=aux->clave[i];
                    }
                }
                /*printf("ContCol=%d\n",contCol);
                for(i=0;i<tam;i++){
                    printf("%c ",mensajeCifrado[i][contCol]);
                }
                printf("\n");*/
                contCol++;
            }
            aux=aux->sig;
        }
        cont++;
    }

    /*for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            printf("%c ",mensajeCifrado[i][j]);
        }
        printf("\n");
    }*/

    for(j=0;j<tam;j++){
        for(i=0;i<tam;i++){
            if(mensajeCifrado[i][j]!='-'){
                temp=mensajeCifrado[i][j]-'0';
                cifradoBinario[contBin]=temp;
                contBin++; //como la ult vez que agregaste tambien se aumento, conBin es el tamaño
            }
        }
    }

    /*for(i=0;i<contBin;i++){
        printf("%d ",cifradoBinario[i]);
    }
    printf("contador bin %d\n",contBin);*/

    tamBin=contBin;

    while(estatus<tamBin){
        //printf("entre con estatus = %d\n",estatus);
        if(sonocho<=8){
            Grupo[contGrupo]=cifradoBinario[estatus];
            sonocho++;
            estatus++;
            contGrupo++;
            //printf("sonocho de salida=%d\n",sonocho);
        }else{
            //printf("else\n");
            for(i=0;i<8;i++){
                if(Grupo[i]!=0){
                    //printf("%d + %d\n",decimal,conversor[i]);
                    decimal=decimal+conversor[i];
                    //printf("decimal=%d\n",decimal);
                }
            }
            nuevoCarac=decimal;
            //printf("nuevoCarac=%c\n",nuevoCarac);
            texto[contTexto]=nuevoCarac;
            contTexto++;

            for(i=0;i<8;i++){
                Grupo[i]='\0';
            }
            decimal=0;
            sonocho=1;
            contGrupo=0;
        }
    }
    if(sonocho>1){
        //printf("el sonocho no llego\n");
        diferencia=8-(sonocho-1);
        for(i=sonocho;i<=8;i++){
            Grupo[i]=0;
        }
        conversor[0]=128;
        for(i=0;i<8;i++){
            if(Grupo[i]!=0){
                //printf("%d + %d\n",decimal,conversor[i]);
                decimal=decimal+conversor[i];
                //printf("decimalr=%d\n",decimal);
                }
            }
            //printf("decimalra=%d\n",decimal);
        nuevoCarac=decimal;
        //printf("nuevoCaracR=%c\n",nuevoCarac);
        texto[contTexto]=nuevoCarac;
        contTexto++;

        for(i=0;i<8;i++){
            Grupo[i]='\0';
        }
        decimal=0;
        sonocho=1;
        contGrupo=0;
    }

    fwrite(texto,1,strlen(texto),arA);
	fclose(arA);

}

void ConsultaListaModif(ListaModif *top){
    ListaModif *aux;
    aux=top;
    int q;
    while(aux!=NULL){
        printf("%c-%d\n",aux->carac,aux->frecuencia);
        aux=aux->sig;
    }
}

void Descifrar(char direccionLlave[], char direccionMensaje[]){
    FILE *arM;
    ListaModif *semillaD=NULL;
    ListaExt *clavesD=NULL;
    Lista *lpr=NULL;
    char x;
    unsigned char cifradoDeArchivo[1000];
    int contC=0,tempDecimal,contD=0,z,a,contB=0,contColumnas=0,cv,j,contBinF=0;
    int decimales[1000];
    int bina[8];
    int binaF[8];

//--------------Obtencion de Claves----------------------------
    ArbolExt *arbLlave=NULL;
    arM=fopen(direccionMensaje,"r");
    semillaD = archiALista(direccionLlave);
    arbLlave = renacimiento(semillaD);
    //preorderSencillo(arbLlave);
    preorderG(arbLlave);
    lpr=listaParaRecorrido();
    clavesD=GeneraCodigos(arbLlave,lpr);
    ConsultaListaExt(clavesD);
    //printf(":)\n");
//--------------Descifrado-------------------------------------
    //obtencion del mensaje en ascci del archivo
    while(!feof(arM)){
        x=fgetc(arM);
        cifradoDeArchivo[contC]=x;
        //printf("caracter=%c\n",cifradoDeArchivo[contC]);
        contC++;
	}
	printf(":)x2\n");
	for(z=0;z<contC;z++){
        printf("%c ",cifradoDeArchivo[z]);
	}


	//obtencion del codigo binario
	while(cifradoDeArchivo[contD]!='\0'){
        //printf("entre\n");
        tempDecimal=cifradoDeArchivo[contD];
        if(tempDecimal==255){
            //printf("salio 255\n");
            break;
        }
        decimales[contD]=tempDecimal;
        printf("decimal %d\n",decimales[contD]);
        contD++;
        /*if(cifradoDeArchivo[contD]!='\0'){
        //printf("cifrado carac %c\n",cifradoDeArchivo[contD]);
        //printf("valio\n");
        }*/
	}

	int tamF=8*(contD-1);
	int binLargo[tamF];

    for(i=0;i<contD;i++){
        printf("pos[%d]=%d\n",i,decimales[i]);
    }

    for(z=0;z<contD;z++){
        a=decimales[z];
        contB=0;
        if(a%2==0){
            bina[contB]=0;
            contB++;
        }else{
            bina[contB]=1;
            contB++;
        }

        while(a!=1){
            a=a/2;
            if(a%2==0){
                bina[contB]=0;
                contB++;
            }else{
                bina[contB]=1;
                contB++;
            }
        }
        if(contB<8){
            while(contB<8){
                bina[contB]=0;
                contB++;
            }
        }
        //volteamos lo que salio
        cv=7;
        for(i=0;i<8;i++){
            binaF[i]=bina[cv];
            cv--;
        }

        /*printf("codigo de %d: ",decimales[z]);
        for(i=0;i<8;i++){
            printf("%d ",binaF[i]);
        }
        printf("\n");*/

        for(i=0;i<8;i++){
            binLargo[contBinF]=binaF[i];
            contBinF++;
        }
        contColumnas++;

    }

    for(i=0;i<contBinF;i++){
            printf("%d ",binLargo[i]);
    }

    ListaExt *auxClaves;
    int indiceCodigoBinario=0,estado=0,saveIn,indiceMensajeDeco=0;;
    int clTurno[10];
    char mensajeDeco[100];
    auxClaves=clavesD;

    while(indiceCodigoBinario<contBinF-2){
        while(auxClaves!=NULL){
            saveIn=indiceCodigoBinario;
            estado=0;
            //printf("el tamanio a recorrer es %d\n",strlen(auxClaves->clave));
            for(i=0;i<strlen(auxClaves->clave);i++){
                if(auxClaves->clave[i]!='\0'){
                    if((auxClaves->clave[i]-'0')==binLargo[indiceCodigoBinario]){
                        indiceCodigoBinario++;
                        estado=1;
                    }else{
                        estado=0;
                        indiceCodigoBinario=saveIn;
                        break;
                    }
                }
            }
            if(estado==1){
                mensajeDeco[indiceMensajeDeco]=auxClaves->carac;
                printf("%c ",mensajeDeco[indiceMensajeDeco]);
                indiceMensajeDeco++;
            }
            auxClaves=auxClaves->sig;
        }
        auxClaves=clavesD;
    }

}

void DescifrarF(char direccionLlave[], char direccionMensaje[]){
    FILE *arM;
    ListaModif *semillaD=NULL;
    ListaExt *clavesD=NULL;
    Lista *lpr=NULL;
    char x;
    unsigned char cifradoDeArchivo[1000];
    int contC=0,tempDecimal,contD=0,z,a,contB=0,contColumnas=0,cv,j,contBinF=0;
    int decimales[1000];
    int bina[8];
    int binaF[8];
    int lectura[23];

//--------------Obtencion de Claves----------------------------
    ArbolExt *arbLlave=NULL;
    arM=fopen(direccionMensaje,"r");
    semillaD = archiALista(direccionLlave);
    arbLlave = renacimiento(semillaD);
    preorderG(arbLlave);
    lpr=listaParaRecorrido();
    clavesD=GeneraCodigos(arbLlave,lpr);
    ConsultaListaExt(clavesD);
//--------------Descifrado-------------------------------------
    //obtencion del mensaje en ascci del archivo
    fscanf(arM,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&lectura[0],&lectura[1],&lectura[2],&lectura[3],&lectura[4],&lectura[5],&lectura[6],&lectura[7],&lectura[8],&lectura[9],&lectura[10],&lectura[11],&lectura[12],&lectura[13],&lectura[14],&lectura[15],&lectura[16],&lectura[17],&lectura[18],&lectura[19],&lectura[20],&lectura[21],&lectura[22]);
    for(z=0;z<23;z++){
        printf("%d ",lectura[z]);
	}
	//obtencion del codigo binario

	for(z=0;z<23;z++){
        decimales[z]=lectura[z];
	}

	int tamF=184;
	int binLargo[tamF];

    for(z=0;z<23;z++){
        a=decimales[z];
        contB=0;
        if(a%2==0){
            bina[contB]=0;
            contB++;
        }else{
            bina[contB]=1;
            contB++;
        }

        while(a!=1){
            a=a/2;
            if(a%2==0){
                bina[contB]=0;
                contB++;
            }else{
                bina[contB]=1;
                contB++;
            }
        }
        if(contB<8){
            while(contB<8){
                bina[contB]=0;
                contB++;
            }
        }
        //volteamos lo que salio
        cv=7;
        for(i=0;i<8;i++){
            binaF[i]=bina[cv];
            cv--;
        }

        printf("codigo de %d: ",decimales[z]);
        for(i=0;i<8;i++){
            printf("%d ",binaF[i]);
        }
        printf("\n");

        for(i=0;i<8;i++){
            binLargo[contBinF]=binaF[i];
            contBinF++;
        }
        contColumnas++;

    }

    for(i=0;i<contBinF;i++){
            printf("%d ",binLargo[i]);
    }

    ListaExt *auxClaves;
    int indiceCodigoBinario=0,estado=0,saveIn,indiceMensajeDeco=0;;
    int clTurno[10];
    char mensajeDeco[100];
    auxClaves=clavesD;

    while(indiceCodigoBinario<contBinF-2){
        while(auxClaves!=NULL){
            saveIn=indiceCodigoBinario;
            estado=0;
            //printf("el tamanio a recorrer es %d\n",strlen(auxClaves->clave));
            for(i=0;i<strlen(auxClaves->clave);i++){
                if(auxClaves->clave[i]!='\0'){
                    if((auxClaves->clave[i]-'0')==binLargo[indiceCodigoBinario]){
                        indiceCodigoBinario++;
                        estado=1;
                    }else{
                        estado=0;
                        indiceCodigoBinario=saveIn;
                        break;
                    }
                }
            }
            if(estado==1){
                mensajeDeco[indiceMensajeDeco]=auxClaves->carac;
                printf("%c ",mensajeDeco[indiceMensajeDeco]);
                indiceMensajeDeco++;
            }
            auxClaves=auxClaves->sig;
        }
        auxClaves=clavesD;
    }

}

