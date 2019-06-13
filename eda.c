#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TYPEDEF GERAL FIGURE*/

typedef struct figure{
  int cod;
  int pai;
  char nom[4];
  int param1;
  int param2;
  int param3;
  double area;
} TFIG;

/* LEITURA DO ARQUIVO */

int tam = 0;
TFIG *v = NULL;

TFIG* resizeVetFig(TFIG* v, int novotam){
    v = (TFIG*) realloc(v,sizeof(TFIG)*(novotam+1));
    v[novotam].cod = 0;
    v[novotam].pai = 0;
    strcpy(v[novotam].nom," ");
    v[novotam].param1 = 0;
    v[novotam].param2 = 0;
    v[novotam].param3 = 0;
    
    return v;
}

TFIG* criarVetFig(){
    v = (TFIG*) malloc(sizeof(TFIG));
    v[0].cod = 0;
    v[0].pai = 0;
    strcpy(v[0].nom," ");
    v[0].param1 = 0;
    v[0].param2 = 0;
    v[0].param3 = 0;
    
    return v;
}

TFIG *read_txt(char *filename){    
    v = criarVetFig();
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
            v = resizeVetFig(v,tam);            
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



/*********************************************************************************************/
/************************************** ARVORE GENERICA **************************************/
/*********************************************************************************************/

typedef struct arvoreGenerica{
    TFIG* info;
    struct arvoreGenerica *primFilho;
    struct arvoreGenerica *proxIrmao;
} TAG;

TAG *inicializaAG(){
  return NULL;
}

TAG* criaNodoAG(int cod, TFIG* info){
    TAG* novo = (TAG*) malloc(sizeof(TAG));
    novo->info = info; 
    if (strcmp(novo->info->nom,"TRI") == 0) novo->info->area = (novo->info->param1) * (novo->info->param2)/2;
    else if (strcmp(novo->info->nom,"RET") == 0) novo->info->area = (novo->info->param1) * (novo->info->param2);
    else if (strcmp(novo->info->nom,"TRA") == 0) novo->info->area = ((novo->info->param1 + novo->info->param2)/2.0) * (novo->info->param3);
    else if (strcmp(novo->info->nom,"CIR") == 0) novo->info->area = 3.14 * (novo->info->param1) * (novo->info->param1);
    else if (strcmp(novo->info->nom,"QUA") == 0) novo->info->area = (novo->info->param1) * (novo->info->param1);      
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    return novo;
}

void localizaEnderecoAG(TAG* pNo, int cod, TAG** ppNo){ // pNo y ppNo
    if (!pNo) return;
    if (pNo->info->cod == cod){
        *ppNo = pNo;
        return ;
    } 
    localizaEnderecoAG(pNo->primFilho, cod,ppNo);
    localizaEnderecoAG(pNo->proxIrmao, cod,ppNo);    
}

int bs_flag = 0;
void buscaSimNaoAG(TAG* t, int cod){
    if (!t) return;
    if (t->info->cod == cod){
        bs_flag = 1;
    } 
    buscaSimNaoAG(t->primFilho, cod);
    buscaSimNaoAG(t->proxIrmao, cod);  
}

int ePredecesorAG(TAG* t, int cod){
    int i = 0;
    if (!t) return 0;
    if (t->info->cod == cod) return 1;
    i+=ePredecesorAG(t->primFilho, cod);
    i+=ePredecesorAG(t->proxIrmao, cod);
    return i;
}

TAG* insereAG(TAG* t, int cod, int pai, TFIG* info){
    if (!t){
        t = criaNodoAG(cod,info);
        return t;
    }

    TAG* temp = t;
    TAG** ppNo = (TAG**) malloc(sizeof(TAG*));
    *ppNo = NULL;

    localizaEnderecoAG(temp, pai, ppNo);
    TAG* pNo = *ppNo;
  
    if (!pNo) return t;

    if (!(pNo->primFilho)){
        pNo->primFilho = criaNodoAG(cod,info);
        return t;
    }

    TAG* pProx = pNo->primFilho;
    while(pProx->proxIrmao){
        pProx = pProx->proxIrmao;
    }

    if(!pProx){
        pProx->proxIrmao = criaNodoAG(cod,info);
        return t;
    }
    pProx->proxIrmao = criaNodoAG(cod,info);
    
    return t;
}

void localizaEnderecoAntecesor(TAG* t, int cod, TAG** ppAnt){
    if (!t) return;
    if (t->proxIrmao && t->proxIrmao->info->cod == cod){
        *ppAnt = t;
        return;
    } 
    if (t->primFilho && t->primFilho->info->cod == cod){
        *ppAnt = t;
        return;
    }
    localizaEnderecoAntecesor(t->primFilho, cod, ppAnt);
    localizaEnderecoAntecesor(t->proxIrmao, cod, ppAnt);
}

void copiarStruct(TAG* t1, TAG* t2){
    t1->info->cod = t2->info->cod;
    t1->info->pai = t2->info->pai;
    strcpy(t1->info->nom, t2->info->nom);
    t1->info->param1 = t2->info->param1;
    t1->info->param2 = t2->info->param2;
    t1->info->param3 = t2->info->param3;
    t1->info->area = t2->info->area;
}

TAG* retiraAG(TAG* t, int ant_pai, int novo_pai){
    TAG* atemp = t;
    TAG** ppP1 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppP2 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppAP1 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppAP2 = (TAG**)malloc(sizeof(TAG*));

    localizaEnderecoAG(atemp, ant_pai, ppP1);
    localizaEnderecoAG(atemp, novo_pai, ppP2);
    localizaEnderecoAntecesor(atemp, ant_pai, ppAP1);
    localizaEnderecoAntecesor(atemp, novo_pai, ppAP2);

    TAG* p1 = *ppP1;
    TAG* p2 = *ppP2;
    TAG* pp1 = *ppAP1;
    TAG* pp2 = *ppAP2;

    if (ePredecesorAG(p1,p2->info->cod)==1){

        copiarStruct(p1,p2);

        TAG* x = p1;
        p1 = p2;
        p2 = x;

        x = pp1;
        pp1 = pp2;
        pp2 = x;
    }

    if(pp1->proxIrmao == p1)
        pp1->proxIrmao = NULL;
    else if(pp1->primFilho == p1)
        pp1->primFilho = NULL;

    TAG* temp = p2;
    while(temp->proxIrmao) temp = temp->proxIrmao;
    temp->proxIrmao = p1->proxIrmao;

    temp = p2;
    if (!(temp->primFilho))
        temp->primFilho = p1->primFilho;
    else{
        temp = temp->primFilho;
        while(temp->proxIrmao) temp = temp->proxIrmao;
        temp->proxIrmao = p1->primFilho;
    }

    p1->proxIrmao = NULL;
    p1->primFilho = NULL;   

    free(p1);

    return t;
}

TAG* carregaDesdeArquivo(TAG* t, char* filename){ 
    TFIG* v = read_txt(filename);
    for (int i=0; i<tam; i++){
        t = insereAG(t, v[i].cod, v[i].pai, &v[i]);
    }
    return t;
}

void buscaFiguraAG(TAG* t, int cod){
    if (!t) return;
    if (t->info->cod == cod){
        printf("\n");
        printf("\tFigura encontrada!\n");
        if (strcmp(t->info->nom,"TRI") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE: %d - ALTURA: %d - AREA: %.2f\n",t->info->cod,t->info->nom,t->info->param1,t->info->param2,t->info->area);
        }
        else if (strcmp(t->info->nom,"RET") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE: %d - ALTURA: %d - AREA: %.2f\n",t->info->cod,t->info->nom,t->info->param1,t->info->param2,t->info->area);
        }
        else if (strcmp(t->info->nom,"TRA") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE MENOR: %d - BASE MAYOR: %d - ALTURA: %d - AREA: %.2f\n",t->info->cod,t->info->nom,t->info->param1,t->info->param2,t->info->param3,t->info->area);
        }
        else if (strcmp(t->info->nom,"CIR") == 0){
            printf("\tCODIGO: %d - NOME: %s - RADIO: %d - AREA: %.2f\n",t->info->cod,t->info->nom,t->info->param1,t->info->area);
        }
        else if (strcmp(t->info->nom,"QUA") == 0){
            printf("\tCODIGO: %d - NOME: %s - LADO: %d - AREA: %.2f\n",t->info->cod,t->info->nom,t->info->param1,t->info->area);
        } 
    }
    buscaFiguraAG(t->primFilho,cod);
    buscaFiguraAG(t->proxIrmao,cod);
}

void imprimirFilhosAGDOT(TAG* t, FILE* fp){
    if (!t) return;

    fprintf(fp, "%d ", t->info->cod);
    if (t->primFilho)
        fprintf(fp, " -> ");
    else
        fprintf(fp, ";");
    
    imprimirFilhosAGDOT(t->primFilho, fp);
    fprintf(fp, "\n");
    imprimirFilhosAGDOT(t->proxIrmao, fp);
}

void imprimirRankAGDOT(TAG* t, FILE* fp){
    static int cont = 1;
    if (!t) return;
    
    if (t->proxIrmao && cont ==1){
        fprintf(fp, "{rank=same; ");
        fprintf(fp, "%d", t->info->cod );
        cont++;
    } else if (t->proxIrmao && cont!=1){
        fprintf(fp, "-> ");
        fprintf(fp, "%d", t->info->cod);
    }

    if (!(t->proxIrmao) && cont!=1){
        fprintf(fp, " -> ");
        fprintf(fp, "%d;}", t->info->cod);
        cont = 1;
    }

    imprimirRankAGDOT(t->proxIrmao, fp);
    fprintf(fp, "\n");
    imprimirRankAGDOT(t->primFilho, fp);    
}

void imprimirInfoAGDOT(TAG* t, FILE *fp){
    if (!t) return;

    if (strcmp(t->info->nom,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                t->info->cod,t->info->cod,t->info->nom,t->info->param1,t->info->param2,t->info->area);
    else if (strcmp(t->info->nom,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                t->info->cod,t->info->cod,t->info->nom,t->info->param1,t->info->param2,t->info->area);
    else if (strcmp(t->info->nom,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, B: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                t->info->cod,t->info->cod,t->info->nom,t->info->param1,t->info->param2,t->info->param3,t->info->area);
    else if (strcmp(t->info->nom,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|r: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                t->info->cod,t->info->cod,t->info->nom,t->info->param1,t->info->area);
    else if (strcmp(t->info->nom,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|l: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                t->info->cod,t->info->cod,t->info->nom,t->info->param1,t->info->area);
    
    imprimirInfoAGDOT(t->proxIrmao, fp);
    imprimirInfoAGDOT(t->primFilho, fp);    
}

void imprimirArquivoAGDOT(TAG* t, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp, "digraph structs {\n");
    fprintf(fp, "nodesep=.5;\n");
    fprintf(fp, "node [shape=record];\n");
    imprimirInfoAGDOT(t,fp);
    fprintf(fp, "\n" );
    imprimirFilhosAGDOT(t, fp);
    fprintf(fp, "\n");
    imprimirRankAGDOT(t, fp);
    fprintf(fp, "}" );

    fclose(fp);
}

TAG* destruirAG(TAG* t){
    if (!t) return NULL;    
    destruirAG(t->primFilho);
    destruirAG(t->proxIrmao);
    free(t);
    return NULL;
}

void alteraFiguraAG(TAG* t, int cod){
    if (!t) return;
    if (t->info->cod == cod){
        int nparam1 = 0, nparam2 = 0, nparam3 = 0;
        if (strcmp(t->info->nom,"TRI") == 0){
            printf("\tCodigo pertencente a TRI\n");
            printf("\t(>) Insira nova base e nova altura: \n");
            printf("\t  (ex: 3 7 )\n");
            printf("\t  (ex: 7 5 )\n");
            printf("\t>>     ");
            scanf(" %d %d",&nparam1,&nparam2);
            t->info->param1 = nparam1;
            t->info->param2 = nparam2;
            t->info->area = (nparam1 * nparam2)/2;
        }
        else if (strcmp(t->info->nom,"RET") == 0){
            printf("\tCodigo pertencente a RET\n");
            printf("\t(>) Insira nova base e nova altura: \n");
            printf("\t  (ex: 4 8  )\n");
            printf("\t  (ex: 3 10 )\n");
            printf("\t>>     ");
            scanf(" %d %d",&nparam1,&nparam2);
            t->info->param1 = nparam1;
            t->info->param2 = nparam2;
            t->info->area = nparam1 * nparam2;
        }
        else if (strcmp(t->info->nom,"TRA") == 0){
            printf("\tCodigo pertencente a TRA\n");
            printf("\t(>) Insira nova base menor, nova base mayor e nova altura: \n");
            printf("\t  (ex: 5 9 15 )\n");
            printf("\t  (ex: 3 5 8  )\n");
            printf("\t>>     ");
            scanf(" %d %d %d",&nparam1,&nparam2,&nparam3);
            t->info->param1 = nparam1;
            t->info->param2 = nparam2;
            t->info->param3 = nparam3;
            t->info->area = ((nparam1 + nparam2)/2)*nparam3;
        }
        else if (strcmp(t->info->nom,"CIR") == 0){
            printf("\tCodigo pertencente a CIR\n");
            printf("\t(>) Insira novo raio: \n");
            printf("\t  (ex: 3 )\n");
            printf("\t  (ex: 7 )\n");
            printf("\t>>     ");
            scanf(" %d",&nparam1);
            t->info->param1 = nparam1;
            t->info->area = 3.14 * nparam1 * nparam1;
        }
        else if (strcmp(t->info->nom,"QUA") == 0){
            printf("\tCodigo pertencente a QUA\n");
            printf("\t(>) Insira novo lado: \n");
            printf("\t  (ex: 8  )\n");
            printf("\t  (ex: 10 )\n");
            printf("\t>>     ");
            scanf(" %d",&nparam1);
            t->info->param1 = nparam1;
            t->info->area = nparam1 * nparam1;
        }
        printf("=======================================================================================\n");
        printf("\n");
        printf("\tDimensões alteradas!\n");
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    }
    alteraFiguraAG(t->primFilho,cod);
    alteraFiguraAG(t->proxIrmao,cod);
}

void liberarVetorFigs(TFIG* t){
    tam = 0;
    free(t);
}

TFIG* criarNovoVetorFigs(){
    v = criarVetFig();    
}

/*********************************************************************************************/
/***************************************** ARVORE AVL ****************************************/
/*********************************************************************************************/

typedef struct arvoreAVL{
    TFIG* info;
    struct arvoreAVL *esq;
    struct arvoreAVL *dir;
    int alt;
} TAVL;

TAVL *inicializaAVL(){
  return NULL;
}

TAVL* criaNodoAVL(const TAG* t){
    TAVL* novo = (TAVL*) malloc(sizeof(TAVL));
    novo->info = t->info; 
    novo->esq = NULL;
    novo->dir = NULL;
    novo->alt = 0;
    return novo;
}

static int calcAltAVL(TAVL* m){
    if( m == NULL ) return -1;
    return m->alt;
}

static int maxAVL( int l, int r){
    return l > r ? l: r;
}

static TAVL* rotDirAVL( TAVL* k2 ){
    TAVL* k1 = NULL;
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
    k2->alt = maxAVL( calcAltAVL( k2->esq ), calcAltAVL( k2->dir ) ) + 1;
    k1->alt = maxAVL( calcAltAVL( k1->esq ), k2->alt ) + 1;
    return k1; /* nova raiz */
}

static TAVL* rotEsqAVL( TAVL* k1 ){
    TAVL* k2;
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
    k1->alt = maxAVL( calcAltAVL( k1->esq ), calcAltAVL( k1->dir ) ) + 1;
    k2->alt = maxAVL( calcAltAVL( k2->dir ), k1->alt ) + 1;
    return k2;  /* nova raiz */
}

static TAVL* rotEsqDirAVL( TAVL* k3 ){
    k3->esq = rotEsqAVL( k3->esq );
    return rotDirAVL( k3 );
}

static TAVL* rotDirEsqAVL( TAVL* k1 ){
    k1->dir = rotDirAVL( k1->dir );
    return rotEsqAVL( k1 );
}

TAVL* insereAVL(TAG* t, TAVL* t2){    
    if (t2 == NULL){        
        t2 = criaNodoAVL(t);     
    }    
    else if (t->info->cod < t2->info->cod){
        t2->esq = insereAVL(t, t2->esq );
        if( calcAltAVL( t2->esq ) - calcAltAVL( t2->dir ) == 2 )
            if( t->info->cod < t2->esq->info->cod )
                t2 = rotDirAVL( t2 );
            else
                t2 = rotEsqDirAVL( t2 );
    } else if (t->info->cod > t2->info->cod){
        t2->dir = insereAVL(t, t2->dir );
        if( calcAltAVL( t2->dir ) - calcAltAVL( t2->esq ) == 2 )
            if( t->info->cod > t2->dir->info->cod )
                t2 = rotEsqAVL( t2 );
            else
                t2 = rotDirEsqAVL( t2 );
    }
    t2->alt = maxAVL( calcAltAVL( t2->esq ), calcAltAVL( t2->dir ) ) + 1;
    return t2;
}

TAVL* transformaParaAVL(TAG* t, TAVL* t2){
    if (!t) return t2;
    t2 = insereAVL(t,t2);
    t2 = transformaParaAVL(t->primFilho, t2);
    t2 = transformaParaAVL(t->proxIrmao, t2);
    return t2; 
}

void imprimirRecAVL(TAVL* t2){
    if (!t2) return;
    printf("CODIGO: %d\n", t2->info->cod);    
    imprimirRecAVL(t2->dir);    
    imprimirRecAVL(t2->esq);
}

void imprimirInfoAVLDOT(TAVL* t2, FILE *fp){
    if (!t2) return;


    if (strcmp(t2->info->nom,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->info->area);
    else if (strcmp(t2->info->nom,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->info->area);
    else if (strcmp(t2->info->nom,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, B: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->info->param3,t2->info->area);
    else if (strcmp(t2->info->nom,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|r: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->area);
    else if (strcmp(t2->info->nom,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|l: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->area);
    
    imprimirInfoAVLDOT(t2->esq, fp);
    imprimirInfoAVLDOT(t2->dir, fp);    
}

void imprimirEsqAVLDOT(TAVL* t2, FILE *fp){
    if (!t2){
        return;
    } 
    if (t2->esq){
        fprintf(fp, "%d:f1 -> %d;\n", t2->info->cod, t2->esq->info->cod);    
    }
    imprimirEsqAVLDOT(t2->esq, fp);
    imprimirEsqAVLDOT(t2->dir, fp);    
}

void imprimirDirAVLDOT(TAVL* t2, FILE *fp){
    if (!t2){
        return;
    } 
    if (t2->dir){
        fprintf(fp,"%d:f2 -> %d;\n", t2->info->cod, t2->dir->info->cod);    
    }
    imprimirDirAVLDOT(t2->dir,fp);    
    imprimirDirAVLDOT(t2->esq,fp);
}

void imprimirArquivoAVLDOT(TAVL* t2, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp,"digraph structs {\n");
    fprintf(fp,"nodesep=.5;\n");
    fprintf(fp,"node [shape=record];\n");
    imprimirInfoAVLDOT(t2,fp);
    fprintf(fp, "\n" );
    imprimirEsqAVLDOT(t2, fp);
    fprintf(fp, "\n" );
    imprimirDirAVLDOT(t2, fp);
    fprintf(fp, "}" );

    fclose(fp);
}

void liberaAVL(TAVL* t){
    if( t != NULL ){
        liberaAVL( t->esq );
        liberaAVL( t->dir );
        free( t );
    }
}



/*********************************************************************************************/
/****************************************** ARVORE B *****************************************/
/*********************************************************************************************/

const int n = 2;

typedef struct arvoreB{
  int nchaves, folha, *chave;
  struct arvoreB **filho;
}TAB;

TAB *inicializaB(){
  return NULL;
}

TAB *criaNodoB(int n){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(int*)malloc(sizeof(int*)*((n*2)-1));
  novo->folha = 1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*n*2);
  int i;
  for(i=0; i<(n*2); i++) novo->filho[i] = NULL;
  return novo;
}

TAB *buscaB(TAB* t3, int ch){
  TAB *resp = NULL;
  if(!t3) return resp;
  int i = 0;
  while(i < t3->nchaves && ch > t3->chave[i]) i++;
  if(i < t3->nchaves && ch == t3->chave[i]) return t3;
  if(t3->folha) return resp;
  return buscaB(t3->filho[i], ch);
}

TAB *divisaoB(TAB *x, int i, TAB* y, int n){
  TAB *z = criaNodoB(n);
  z->nchaves = n - 1;
  z->folha = y->folha;
  int j;
  for(j=0; j<n-1; j++) z->chave[j] = y->chave[j+n];
  if(!y->folha){
    for(j=0; j<n; j++){
      z->filho[j] = y->filho[j+n];
      y->filho[j+n] = NULL;
    }
  }
  y->nchaves = n-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[n-1];
  x->nchaves++;
  return x;
}

TAB *insere_Nao_CompletoB(TAB *x, int k, int n){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k<x->chave[i])){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = k;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (k<x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*n)-1)){
    x = divisaoB(x, (i+1), x->filho[i], n);
    if(k>x->chave[i]) i++;
  }
  x->filho[i] = insere_Nao_CompletoB(x->filho[i], k, n);
  return x;
}

TAB *insereB(TAB* t3, TAG* t, int n){
  int cod = t->info->cod;
  if(buscaB(t3, cod)) return t3;
  if(!t3){
    t3 = criaNodoB(n);
    t3->chave[0] = cod;
    t3->nchaves = 1;
    return t3;
  }
  if(t3->nchaves == (2*n)-1){
    TAB *S = criaNodoB(n);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = t3;
    S = divisaoB(S,1,t3,n);
    S = insere_Nao_CompletoB(S,cod,n);
    return S;
  }
  t3 = insere_Nao_CompletoB(t3,cod,n);
  return t3;
}

TAB* transformaB(TAG* t, TAB* t3, int n){
    if (!t) return t3;
    t3 = insereB(t3,t,n);
    t3 = transformaB(t->primFilho, t3, n);
    t3 = transformaB(t->proxIrmao, t3, n);    
}

void imprimeB(TAB *t3, int andar){
  if(t3){
    int i,j;
    for(i=0; i<=t3->nchaves-1; i++){
      imprimeB(t3->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", t3->chave[i]);
    }
    imprimeB(t3->filho[i],andar+1);
  }
}

void imprimeInfoB(TAB *a, int andar, FILE *fp, int mynum){
  if(a){
    int i,j;
    int pchaves=(n*2);
    fprintf(fp, "%d%d [shape=record,label=\"{{",andar,mynum*pchaves);
    for (i=0; i<pchaves-1; i++){
        fprintf(fp,"<f%d>",i+(mynum*pchaves));
        if (i<=a->nchaves-1){
            fprintf(fp,"| %d |", a->chave[i]);
        } else {
            fprintf(fp,"| - |");
        }
    }
    fprintf(fp,"<f%d>}}\"];\n",i+(mynum*pchaves));
    j=0;
    for(i=0; i<(n*2); i++){
        imprimeInfoB(a->filho[i], andar+1, fp, i+(mynum*pchaves) );
    }
  }
}

void imprimeFlechaB(TAB *a, int andar, FILE *fp, int mynum){
  if(a){
    int i,j;
    int pchaves=(n*2);

    for (i=0; i<pchaves; i++){
        if(a->filho[i]){
            fprintf(fp,"%d%d:<f%d> -> %d%d:<f%d>;\n", andar, mynum*pchaves, i+(mynum*pchaves), andar+1, (i+(mynum*pchaves))*pchaves , (i+(mynum*pchaves))*pchaves );  
        }
    }
    for(i=0; i<pchaves; i++){
        imprimeFlechaB(a->filho[i],andar+1,fp,i+(mynum*pchaves));  
    }
  }
}

void imprimir_arquivoB(TAB* t3, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp,"digraph structs {\n");
    fprintf(fp,"nodesep=.5;\n");
    fprintf(fp,"node [shape=record];\n");
    imprimeInfoB(t3,0,fp,0);
    fprintf(fp, "\n");
    imprimeFlechaB(t3,0,fp,0);
    fprintf(fp, "}" );

    fclose(fp);
}

TAB *liberaB(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) liberaB(a->filho[i]);
    }
    free(a->chave);
    free(a->filho);
    free(a);
    return NULL;
  }
}

/*********************************************************************************************/
/****************************************** MENU AG ******************************************/
/*********************************************************************************************/

void buscar_figura_geometrica(TAG* t){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(a) Buscar figura geométrica\n");
    printf("=======================================================================================\n");
    printf("\t(>) Insira código da figura buscada:\n");
    printf("\t  (ex: 9 )\n");
    printf("\t  (ex: 2 )\n");

    char codigo[10];
    printf("\t>>     ");
    scanf(" %s",codigo);
    printf("=======================================================================================\n");

    int cod = atoi(codigo);
    bs_flag = 0;
    buscaSimNaoAG(t,cod);    
    if (bs_flag==0){
        printf("\n\tFigura Nao encontrada\n");
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return;
    } 

    buscaFiguraAG(t,cod);

    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

void imprimir_arvore(TAG* t){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(b) Imprimir árvore\n");
    printf("=======================================================================================\n");
    printf("\n");
    imprimirArquivoAGDOT(t,"arvoreG.dot");
    printf("\tÁrvore impressa!\n");
    system("dot -Tps arvoreG.dot -o arvoreG.pdf");
    system("xdg-open arvoreG.pdf");

    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

TAG* inserir_nova_figura(TAG* t){
    char my_arguments[3][6];

    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(c) Inserir novas figuras\n");
    printf("=======================================================================================\n");
    printf("\t- Se a figura for um círculo, uma única dimensão (Raio) será informada. \n" );
    printf("\t- Se a figura for um quadrado, uma única dimensão (Lado) será informada. \n" );
    printf("\t- Se a figura for um triângulo, duas dimensões (Base e Altura) serão informadas. \n" );
    printf("\t- Se a figura for um retângulo, duas dimensões (Base e Altura) serão informadas. \n" );
    printf("\t- Se a figura for um trapézio, três dimensões (Base menor, Base maior e Altura) \n" );
    printf("\t  serão informadas. \n" );
    printf("=======================================================================================\n");
    printf("\t(>) Insira nome da figura:\n");
    printf("\t  (ex: CIR )\n");
    printf("\t  (    QUA )\n");
    printf("\t  (    TRI )\n");
    printf("\t  (    RET )\n");
    printf("\t  (    TRA )\n");
    printf("\t>>     ");
    char nome_fig[10];
    int num_case=-1;
    int num_arg=-1;
    
    scanf(" %s",nome_fig);
    
    if(0==strcmp(nome_fig, "CIR")){
        num_case=1;
        num_arg=1;
    }
    if(0==strcmp(nome_fig, "QUA")){
        num_case=2;
        num_arg=1;
    }
    if(0==strcmp(nome_fig, "TRI")){
        num_case=3;        
        num_arg=2;
    }
    if(0==strcmp(nome_fig, "RET")){
        num_case=4;        
        num_arg=2;
    }
    if(0==strcmp(nome_fig, "TRA")){
        num_case=5;
        num_arg=3;
    }
        
    switch(num_case){
        case 1: //Circulo
                printf("\t(>) Insira Raio:\n");
                printf("\t  (ex: 3 )\n");
                printf("\t  (ex: 1 )\n");
                printf("\t>>     ");
                scanf(" %s",my_arguments[0]);
                break;

        case 2: //Quadrado
                printf("\t(>) Insira lado: \n");
                printf("\t  (ex: 9 )\n");
                printf("\t  (ex: 2 )\n");
                printf("\t>>     ");
                scanf(" %s",my_arguments[0]);
                break;        

        case 3: //Triangulo
                printf("\t(>) Insira base e altura: \n");
                printf("\t  (ex: 3 7 )\n");
                printf("\t  (ex: 7 5 )\n");
                printf("\t>>     ");
                scanf(" %s %s",my_arguments[0],my_arguments[1]);
                break;

        case 4: //Retangulo
                printf("\t(>) Insira base e altura: \n");
                printf("\t  (ex: 9 1 )\n");
                printf("\t  (ex: 7 8 )\n");
                printf("\t>>     ");
                scanf(" %s %s",my_arguments[0],my_arguments[1]);
                break;

        case 5: //Trapezio
                printf("\t(>) Insira base menor, base maior e altura: \n");
                printf("\t  (ex: 2 8 7 )\n");
                printf("\t  (ex: 6 8 3 )\n");
                printf("\t>>     ");
                scanf(" %s %s %s",my_arguments[0],my_arguments[1],my_arguments[2]);
                break;

        default:
                printf("=======================================================================================\n");
                printf("\n");
                printf("\tERROR: Figura Nao conhecida\n");
                printf("\n");
                printf("=======================================================================================\n");
                break;
    }

    if(num_arg==-1){
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return t;
    }    
    
    int my_arguments_int[3];
    int i;
    for(i=0;i<num_arg;i++){
        my_arguments_int[i]=atoi(my_arguments[i]);
    }

    bs_flag = 1;
    int n_cod;
    while(bs_flag == 1){
        printf("\t(>) Insira um codigo para a nova figura: \n");
        printf("\t  (ex: 12 )\n");
        printf("\t  (ex: 16 )\n");
        printf("\t>>     ");
        scanf(" %d",&n_cod);
        bs_flag = 0;
        buscaSimNaoAG(t,n_cod);
        if(bs_flag == 1) printf("\tCodigo de figura em uso\n");
    }

    bs_flag = 0;
    int n_pai;
    while(bs_flag == 0){
        printf("\t(>) Insira o codigo do pai: \n");
        printf("\t  (ex: 4  )\n");
        printf("\t  (ex: 10 )\n");
        printf("\t>>     ");
        scanf(" %d",&n_pai);
        bs_flag = 0;
        buscaSimNaoAG(t,n_pai);
        if(bs_flag == 0) printf("\tCodigo do pai nao encontrado\n");
    }

    tam++;

    v = resizeVetFig(v,tam+1);
    t->info->cod = 1;
    v[tam].cod = n_cod;
    v[tam].pai = n_pai;

    if (strcmp(nome_fig,"TRI") == 0){
        strcpy(v[tam].nom,"TRI");
        v[tam].param1 = my_arguments_int[0];
        v[tam].param2 = my_arguments_int[1];
        v[tam].param3 = 0;
    }
    else if (strcmp(nome_fig,"RET") == 0){
        strcpy(v[tam].nom,"RET");
        v[tam].param1 = my_arguments_int[0];
        v[tam].param2 = my_arguments_int[1];
        v[tam].param3 = 0;
    }
    else if (strcmp(nome_fig,"TRA") == 0){
        strcpy(v[tam].nom,"TRA");
        v[tam].param1 = my_arguments_int[0];
        v[tam].param2 = my_arguments_int[1];
        v[tam].param3 = my_arguments_int[2];
    }
    else if (strcmp(nome_fig,"CIR") == 0){
        strcpy(v[tam].nom,"CIR"); 
        v[tam].param1 = my_arguments_int[0];
        v[tam].param2 = 0;
        v[tam].param3 = 0;  
    }
    else if (strcmp(nome_fig,"QUA") == 0){
        strcpy(v[tam].nom,"QUA");
        v[tam].param1 = my_arguments_int[0];
        v[tam].param2 = 0;
        v[tam].param3 = 0;
    }

    t = insereAG(t,n_cod,n_pai,&v[tam]);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tFigura inserida!\n");
    printf("\n");
    printf("=======================================================================================\n");

    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
    return t;
}

TAG* retirar_figura(TAG* t){  
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(d) Retirar figuras\n");
    printf("=======================================================================================\n");
    printf("\t(>) Insira código da figura para retirar:\n");
    printf("\t  (ex: 9 )\n");
    printf("\t  (ex: 2 )\n");
    
    char codigo_apai[10];
    printf("\t>>     ");
    scanf(" %s",codigo_apai);
    printf("=======================================================================================\n");

    printf("\t(>) Insira código da figura novo pai:\n");
    printf("\t  (ex: 5 )\n");
    printf("\t  (ex: 7 )\n");
    
    char codigo_npai[10];
    printf("\t>>     ");
    scanf(" %s",codigo_npai);
    printf("=======================================================================================\n");

    int cod_apai = atoi(codigo_apai);
    int cod_npai = atoi(codigo_npai);

    bs_flag = 0;
    buscaSimNaoAG(t,cod_apai);
    if (bs_flag == 0){
        printf("\n");
        printf("\tCodigo de figura para retirar nao encontrado\n");        
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return t;        
    } 

    bs_flag = 0;
    buscaSimNaoAG(t,cod_npai);
    if (bs_flag == 0){
        printf("\n");
        printf("\tCodigo de figura novo pai nao encontrado\n");
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return t;   
    }

    bs_flag = 0;
    t = retiraAG(t, cod_apai, cod_npai);

    printf("\n");
    printf("\tFigura retirada!\n");
    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
    return t;
}

TAG* destruir_arvoreAG(TAG* t){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(e) Destruir árvore\n");
    printf("=======================================================================================\n");

    t = destruirAG(t);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tÁrvore destruido!\n");
    printf("\n");
    printf("=======================================================================================\n");
    getchar();

    return t;
}

void alterar_dimensoes_figura(TAG* t){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(f) Alterar dimensões das figuras\n");
    printf("=======================================================================================\n");
    printf("\t(>) Insira código da figura:\n");
    printf("\t  (ex: 6 )\n");
    printf("\t  (ex: 4 )\n");
    
    char codigo[10];
    printf("\t>>     ");
    scanf(" %s",codigo);    

    int cod = atoi(codigo);
    bs_flag = 0;
    buscaSimNaoAG(t,cod);
    if (bs_flag==0){
        printf("=======================================================================================\n");
        printf("\n");
        printf("\tCodigo de figura nao encontrado\n");        
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return;
    }
    alteraFiguraAG(t,cod);
    getchar();
}


void inserir_figuraAVL(TAG* t){
    /*printf("\033[2J");
    printf("\033[1;1H"); 
    printf("=======================================================================================\n");
    printf("\n");
    printf("\tFigura inserida!\n");
    printf("\n");
    printf("=======================================================================================\n");

    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();*/
    inserir_nova_figura(t);
}

void retirar_figuraAVL(TAG* t){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("=======================================================================================\n");
    printf("\n");
    printf("\tFigura retirada!\n");
    printf("\n");
    printf("=======================================================================================\n");

    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}


void imprimir_AVL(TAG* t){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("=======================================================================================\n");
    printf("\n");
    printf("\tÁrvore impressa!\n");
    printf("\n");
    printf("=======================================================================================\n");

    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

TAG* inserir_desde_zeroAG(TAG* t){
    v = criarNovoVetorFigs();
    v[0].cod = 1;
    v[0].pai = 0;
    strcpy(v[0].nom,"CIR");
    v[0].param1 = 5;
    v[0].param2 = 0;
    v[0].param3 = 0;
    t = insereAG(t,0,0,&v[0]);

    return t;
}

TAVL* transformar_avl(TAG* t, TAVL* t2){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(g) Transformar a árvore genérica numa árvore AVL\n");
    printf("=======================================================================================\n");
    printf("\n");
    TAG* temp = t;
    t2 = transformaParaAVL(temp,t2);
    imprimirArquivoAVLDOT(t2,"arvoreAVL.dot");
    printf("\tÁrvore transformado!\n");
    printf("\n=======================================================================================\n");
    system("dot -Tps arvoreAVL.dot -o arvoreAVL.pdf");
    system("xdg-open arvoreAVL.pdf");

    /*char key[2] ;
    int cont = 0;
    while(1){
        if (cont != 0){
            printf("\033[2J");
            printf("\033[1;1H"); 
        }
        printf("ÁRVORE AVL: \n");
        printf("\t(a) Inserir novas figuras\n");
        printf("\t(b) Retirar figuras\n");
        printf("\t(c) Imprimir árvore\n");
        printf("\t(d) Voltar ao Menu principal\n");
        printf("=======================================================================================\n");
        printf("Insira sua opção: \n");
        printf("\t >>  ");
        scanf(" %s",key);
        printf("=======================================================================================\n");

        switch(key[0]) {
            case 'a' :
                inserir_figuraAVL(t);
                cont++;
                //scanf("%s",&elem);
                getchar();
                break;
            case 'b' :
                retirar_figuraAVL(t);
                cont++;
                //scanf("%s",&elem);
                getchar();
                break;
            case 'c' :
                imprimir_AVL(t);
                cont++;
                //scanf("%s",&elem);
                getchar();
                break;
            case 'd' :                
                //scanf("%s",&elem);
                getchar();
                return;
                break;            
        }
    }*/

    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
    
    return t2;
}

void tranformar_b(TAG* t, TAB* t3){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(h) Transformar a árvore genérica numa árvore B\n");
    printf("=======================================================================================\n");
    printf("\n");
    t3 = transformaB(t,t3,n);
    imprimir_arquivoB(t3,"arvoreBB.dot");
    system("dot -Tps arvoreBB.dot -o arvoreBB.pdf");
    system("xdg-open arvoreBB.pdf");
    printf("\tÁrvore transformado!\n");
    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();

    return ;
}

int main(){
    TAG* t = inicializaAG();
    TAVL* t2 = inicializaAVL();
    TAB* t3 = inicializaB();    
    t = carregaDesdeArquivo(t,"data.txt");
    //t3 = transformaB(t,t3,n);
    //imprimeB(t3,0);
    //imprimir_arquivoB(t3,"arvolB.dot");
    
    int i;
    char key[2] ;
    while(1){
        printf("\033[2J");
        printf("\033[1;1H"); 
        //printf("Elija su opcion: \e[31mRed\n");
        printf("\t\t\t\t\e[33;1m@Roger Ripas && @Luigy Machaca \e[00m \n");
        printf("=======================================================================================\n");
        printf("ÁRVORE GENERICO: \n");
        printf("\t(a) Buscar figura geométrica\n");
        printf("\t(b) Imprimir árvore \n");
        printf("\t(c) Inserir novas figuras\n");
        printf("\t(d) Retirar figuras\n");
        printf("\t(e) Destruir árvore\n");
        printf("\t(f) Alterar dimensões das figuras\n");
        printf("\t(g) Transformar a árvore genérica numa árvore AVL\n");
        printf("\t(h) Transformar a árvore genérica numa árvore B\n");
        //printf("\t(i) Cria arvore novo\n");        
        printf("=======================================================================================\n");
        printf("Insira sua opção: \n");
        printf("\t >>  ");
        scanf(" %s",key);
        printf("=======================================================================================\n");

        switch(key[0]) {
            case 'a' :
                buscar_figura_geometrica(t);
                //scanf("%s",&elem);
                getchar(); 
                break;

            case 'b' :
                imprimir_arvore(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'c' :
                if (!t){
                    printf("Arvore precisa pelo menos de um nodo pai\n");
                    getchar();
                } 
                else t = inserir_nova_figura(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'd' :                
                t = retirar_figura(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'e' :
                t = destruir_arvoreAG(t);
                liberarVetorFigs(v);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'f' :
                alterar_dimensoes_figura(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'g' :
                if (t2){
                    liberaAVL(t2);
                }
                t2 = NULL;
                t2 = transformar_avl(t,t2);
                getchar();
                break;
            case 'h' :
                if (t3){
                    liberaB(t3);
                }              
                t3 = NULL;  
                tranformar_b(t,t3);
                //scanf("%s",&elem);
                getchar();
                break;

            case 'i':
                if (!t){
                    printf("Destruir arvore primeiro\n");
                    getchar();
                } 
                else t = inserir_desde_zeroAG(t);
                //scanf("%s",&elem);
                getchar();
                break;
            
            default :
                printf("Opcion errada.\n" );
                scanf(" %s",key);
                //getchar();
                //i=getchar();
                //system("pause");
                break;
        }
    }

    t = destruir_arvoreAG(t);
    liberarVetorFigs(v);
    return 0;
}
