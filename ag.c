#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct figure{
  int cod;
  int pai;
  char nom[4];
  int param1;
  int param2;
  int param3;
  double area;
} TFIG;

TFIG* criaFig(int cod, int pai, const char* nom, int p1, int p2, int p3){
    TFIG* novo = (TFIG*) malloc(sizeof(TFIG));

    novo->cod = cod;
    novo->pai = pai;
    strcpy(novo->nom,nom);
    novo->param1 = p1;
    novo->param2 = p2;
    novo->param3 = p3;
    if (strcmp(novo->nom,"TRI") == 0) novo->area = (p1*p2)/2;
    else if (strcmp(novo->nom,"RET") == 0) novo->area = p1*p2;
    else if (strcmp(novo->nom,"TRA") == 0) novo->area = ((p1+p2)/2.0)*p3;
    else if (strcmp(novo->nom,"CIR") == 0) novo->area = 3.14*p1*p1;
    else if (strcmp(novo->nom,"QUA") == 0) novo->area = p1*p1;

    return novo;

}

int tam = 0;
int tam2 = 1;

TFIG *read_txt(char *filename){
    TFIG *v = (TFIG*) malloc(sizeof(TFIG));
    v[0].cod = 0;
    v[0].pai = 0;
    strcpy(v[0].nom," ");
    v[0].param1 = 0;
    v[0].param2 = 0;
    v[0].param3 = 0;

    FILE *filePointer;
    char ch;

    filePointer = fopen(filename, "r");

    int j = 0, k = 0;
    char item[4];

    while ((ch = fgetc(filePointer)) != EOF)
    {
        if (ch == '/'){
            if (k == 0){
                v[tam].cod = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            else if (k == 1){
                v[tam].pai = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            k++;
            j = 0;
            continue;
        }
        if (ch == ' '){
            if (k == 2){
                strcpy(v[tam].nom,item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            } 
            else if (k == 3){
                v[tam].param1 = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            else if (k == 4){
                v[tam].param2 = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            k++;
            j = 0;
            continue;
        }
        if (ch == '\n'){
            if (k == 3){
                v[tam].param1 = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            else if (k == 4){
                v[tam].param2 = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            else if (k == 5){
                v[tam].param3 = atoi(item);
                item[0] = ' ';
                item[1] = ' ';
                item[2] = ' ';
            }
            tam++;
            v = (TFIG*) realloc(v,sizeof(TFIG)*(tam+1));
            v[tam].cod = 0;
            v[tam].pai = 0;
            strcpy(v[tam].nom," ");
            v[tam].param1 = 0;
            v[tam].param2 = 0;
            v[tam].param3 = 0;
            k = 0;
            j = 0;
            continue;
        }
        item[j] = ch;
        j++;
    }

    fclose(filePointer);

    return v;
}

typedef struct arvolGenerico{
    //TFIG info;
    TFIG* info2;
    int cod;
    //double area;
    struct arvolGenerico *prim_filho;
    struct arvolGenerico *prox_irmao;
} TAG;

TAG* inicializa(void){     
    return NULL;
}

/*TAG* cria(TFIG* v){
    TAG* novo = (TAG*) malloc(sizeof(TAG));
    novo->info.cod = v->cod;
    novo->info.pai = v->pai;
    strcpy(novo->info.nom,v->nom);
    novo->info.param1 = v->param1;
    novo->info.param2 = v->param2;
    novo->info.param3 = v->param3;
    if (strcmp(novo->info.nom,"TRI") == 0) novo->area = (v->param1*v->param2)/2;
    else if (strcmp(novo->info.nom,"RET") == 0) novo->area = v->param1*v->param2;
    else if (strcmp(novo->info.nom,"TRA") == 0) novo->area = ((v->param1+v->param2)/2.0)*v->param3;
    else if (strcmp(novo->info.nom,"CIR") == 0) novo->area = 3.14*v->param1*v->param1;
    else if (strcmp(novo->info.nom,"QUA") == 0) novo->area = v->param1*v->param1;
    novo->prim_filho = NULL;
    novo->prox_irmao = NULL;

    return novo;
}*/

TAG* criaNodo(int cod, TFIG* info){
    TAG* novo = (TAG*) malloc(sizeof(TAG));
    novo->cod = cod;
    novo->info2 = info; 
    novo->prim_filho = NULL;
    novo->prox_irmao = NULL;

    return novo;
}


/*TAG* insere(TAG* t, TFIG* v, int** matbus){    
    if (v->cod == 1){
        matbus[0][0] = 1; //Cod del nodo Root
        matbus[1][0] = 0; //Pai del nodo Root
        t = cria(v);
        return t;
    }

    //Caso insercion Cod repetido
    int ins_cod_rep = buscasi_no(v->cod,matbus);
    if (ins_cod_rep){
        printf("Nao pode-se inserir: Codigo repetido\n");
        return;
    } 

    //Caso insercion con Pai inexistente
    int ins_sem_pai = buscasi_no(v->pai,matbus);
    if (!ins_sem_pai){
        printf("Nao pode-se inserir: Pai inexistente\n");
        return;
    } 

    tam2+=1;
    for (int i=0; i<2; i++)
        matbus[i] = realloc(matbus[i],tam2*sizeof(int));
    matbus[0][tam2-1] = v->cod; //Cod del nuevo nodo a ser insertado
    matbus[1][tam2-1] = v->pai; //Pai del nuevo nodo a ser insertado

    //Llegada a nodo padre
        //Comprobacion si tiene hijo
            //Comprobar si es el hmno mayor
            //Descender al nivel del hijo y recorrer hasta el ultimo hermano
            //insercion
        //no tiene hijo
            //insercion

    TAG* p = t;
    while(p->prim_filho){
        p = p->prim_filho;
    } 
    TAG* q = cria(v);
    p->prim_filho = q;

    return t;
}*/

void buscar (TAG* pNo, int cod, TAG** ppNo){
    if (!pNo) return NULL;
    //printf("%p\n",pNo);
    if (pNo->cod == cod){
        printf("ENCONTRE: %d\n", pNo->info2->cod);
        *ppNo = pNo;
        return ;
    } 
    buscar(pNo->prim_filho, cod,ppNo);
    buscar(pNo->prox_irmao, cod,ppNo);
    
}

void imprimir_rec (TAG* pNo){
    if (!pNo) return;
    printf("CODIGO: %d - PADRE: %d\n",pNo->cod,pNo->info2->pai); 
    imprimir_rec(pNo->prim_filho);
    imprimir_rec(pNo->prox_irmao);
    
}

TAG* insert (TAG* t, int cod, TFIG* info){
    if (!t){
        t = criaNodo(cod,info);
        //printf("COD %d - PAI: %d\n",info->cod, info->pai);
        //printf("COD %d\n",cod);
        //printf("PRMER cASO\n");
        return t;
    } 

    TAG* temp = t;
    //printf("ROOT COD: %d - ROOT PAI: %d\n",temp->cod, temp->info2->pai);
    TAG** ppNo = (TAG**)malloc(sizeof(TAG*));
    *ppNo=NULL;
    printf("COD %d - PAI: %d\n",info->cod, info->pai);
    buscar(temp, info->pai, ppNo);
    TAG* pNo = *ppNo;
    printf("         soy PAI: %d\n",pNo->cod);

    //printf("----------------------------\n"); 
    //imprimir_rec(t);
    //printf("----------------------------\n"); 
    
    if (!pNo){
        printf("    NAO HA PAI\n");
        return t;
    } 

    if (!(pNo->prim_filho)){
        pNo->prim_filho = criaNodo(cod,info);
        return t;
    }
    //TAG* pAnt = NULL;
    TAG* pProx = pNo->prim_filho;
    while(pProx->prox_irmao){
        //if (pProx->cod > cod) break;
        //pAnt = pProx;
        pProx = pProx->prox_irmao;
    }

    if(!pProx){
        pProx->prox_irmao = criaNodo(cod,info);
        return t;
    }
    pProx->prox_irmao = criaNodo(cod,info);
    
    return t;

}

/*TAG* busca_insercion(TAG* t, int pai, int** matbus){
    //Secuencia de recorrido para llegar al padre




    TAG* p = t;
    while (p){
        if (cod == p->info.cod)
            return p;
        p = p->prim_filho;
    }
    return NULL;
}*/

int buscasi_no(int cod, int** matbus){
    for (int i=0; i<tam2; i++)
        if (matbus[0][i]==cod) return 1;
    return 0;
}


/*TAG* carrega(TAG* t, TFIG* v, int** matbus){ 
    for (int i=0; i<tam; i++){        
        t = (TAG*) insere(t,&v[i],matbus);
    }
    return t;
}*/

TAG* carrega2(TAG* t, char* filename){ 
    TFIG* v = read_txt(filename);
    printf("ANTES: %d\n",t );
    for (int i=0; i<tam; i++){
        //printf("%d\n",v[i].cod);
        t = insert(t, v[i].cod, &v[i]);

    }
    printf("DSPS: %d\n",t );
    return t;
}

/*
void libera(TAG* t){
    TAG* p = t, *q;
    while(p){
        q = p;
        p = p->prim_filho;
        free(q);
    }
}

void imprime(TAG* t){
    TAG* p = t;
    while(p){
        printf("COD>>%d  PAI>>%d  NOM>>%s  PARAM1>>%d  PARAM2>>%d  PARAM3>>%d  AREA>>%.2f\n",p->info.cod,p->info.pai,p->info.nom,p->info.param1,p->info.param2,p->info.param3,p->area);
        p = p->prim_filho;
    }
}*/

int main(void){   
    
    /*TFIG *v = read_txt("ag.txt");
    TAG* t = inicializa();

    int** matbus = (int**) malloc(2*sizeof(int*));
    for (int i=0; i<2; i++)
        matbus[i] = (int*) malloc(tam2*sizeof(int));

    t = carrega(t,v,matbus);

    free(v);

    TAG* p = t;
    imprime(t); 

    for (int i=0; i<tam2; i++)
        printf("COD: %d --- PAI: %d\n",matbus[0][i],matbus[1][i]);

    /*TAG* r = busca(t,15,matbus);
    if(r!=NULL)
        printf("SI\n");
    else
        printf("NO\n");

    printf("%s\n",buscasi_no(18,matbus)==1?"SI":"NO");

    libera(t);

    for (int i=0; i<2; i++) free(matbus[i]);
    free(matbus);*/


    TFIG* f = criaFig(2,1,"cua",1,1,2);
    printf("%s\n",f->nom );
    TAG* p = criaNodo(2, f);
    printf("%s\n",p->info2->nom );

    TAG* t = NULL;
    t = carrega2(t,"ag.txt");
    imprimir_rec(t);
    //printf("CODDDD: %d\n",t->prim_filho->prim_filho->prim_filho );
    return 0;

}
