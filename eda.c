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
} TFIG;

int tam = 0;
TFIG *v = NULL;
TFIG *read_txt(char *filename){    
    v = (TFIG*) malloc(sizeof(TFIG));
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
    int cod;
    TFIG* info;
    double area;
    struct arvolGenerico *primFilho;
    struct arvolGenerico *proxIrmao;
} TAG;

TAG* criaNodo(int cod, TFIG* info){
    TAG* novo = (TAG*) malloc(sizeof(TAG));
    novo->cod = cod;
    novo->info = info; 
    if (strcmp(novo->info->nom,"TRI") == 0) novo->area = (novo->info->param1) * (novo->info->param2)/2;
    else if (strcmp(novo->info->nom,"RET") == 0) novo->area = (novo->info->param1) * (novo->info->param2);
    else if (strcmp(novo->info->nom,"TRA") == 0) novo->area = ((novo->info->param1 + novo->info->param2)/2.0) * (novo->info->param3);
    else if (strcmp(novo->info->nom,"CIR") == 0) novo->area = 3.14 * (novo->info->param1) * (novo->info->param1);
    else if (strcmp(novo->info->nom,"QUA") == 0) novo->area = (novo->info->param1) * (novo->info->param1);      
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    return novo;
}

void busca(TAG* pNo, int cod, TAG** ppNo){
    if (!pNo) return;
    if (pNo->cod == cod){
        *ppNo = pNo;
        return ;
    } 
    busca(pNo->primFilho, cod,ppNo);
    busca(pNo->proxIrmao, cod,ppNo);    
}

int bs_flag = 0;
void busca_simnao(TAG* t, int cod){
    if (!t) return;
    if (t->cod == cod){
        bs_flag = 1;
    } 
    busca_simnao(t->primFilho, cod);
    busca_simnao(t->proxIrmao, cod);  
}

void altera_figuraAG(TAG* t, int cod){
    if (!t) return;
    if (t->cod == cod){
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
            t->area = (nparam1 * nparam2)/2;
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
            t->area = nparam1 * nparam2;
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
            t->area = ((nparam1 + nparam2)/2)*nparam3;
        }
        else if (strcmp(t->info->nom,"CIR") == 0){
            printf("\tCodigo pertencente a CIR\n");
            printf("\t(>) Insira novo raio: \n");
            printf("\t  (ex: 3 )\n");
            printf("\t  (ex: 7 )\n");
            printf("\t>>     ");
            scanf(" %d",&nparam1);
            t->info->param1 = nparam1;
            t->area = 3.14 * nparam1 * nparam1;
        }
        else if (strcmp(t->info->nom,"QUA") == 0){
            printf("\tCodigo pertencente a QUA\n");
            printf("\t(>) Insira novo lado: \n");
            printf("\t  (ex: 8  )\n");
            printf("\t  (ex: 10 )\n");
            printf("\t>>     ");
            scanf(" %d",&nparam1);
            t->info->param1 = nparam1;
            t->area = nparam1 * nparam1;
        }
        printf("=======================================================================================\n");
        printf("\n");
        printf("\tDimensões alteradas!\n");
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    }
    altera_figuraAG(t->primFilho,cod);
    altera_figuraAG(t->proxIrmao,cod);
}

void busca_figuraAG(TAG* t, int cod){
    if (!t) return;
    if (t->cod == cod){
        printf("\n");
        printf("\tFigura encontrada!\n");
        if (strcmp(t->info->nom,"TRI") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE: %d - ALTURA: %d - AREA: %.2f\n",t->cod,t->info->nom,t->info->param1,t->info->param2,t->area);
        }
        else if (strcmp(t->info->nom,"RET") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE: %d - ALTURA: %d - AREA: %.2f\n",t->cod,t->info->nom,t->info->param1,t->info->param2,t->area);
        }
        else if (strcmp(t->info->nom,"TRA") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE MENOR: %d - BASE MAYOR: %d - ALTURA: %d - AREA: %.2f\n",t->cod,t->info->nom,t->info->param1,t->info->param2,t->info->param3,t->area);
        }
        else if (strcmp(t->info->nom,"CIR") == 0){
            printf("\tCODIGO: %d - NOME: %s - RADIO: %d - AREA: %.2f\n",t->cod,t->info->nom,t->info->param1,t->area);
        }
        else if (strcmp(t->info->nom,"QUA") == 0){
            printf("\tCODIGO: %d - NOME: %s - LADO: %d - AREA: %.2f\n",t->cod,t->info->nom,t->info->param1,t->area);
        } 
    }
    busca_figuraAG(t->primFilho,cod);
    busca_figuraAG(t->proxIrmao,cod);
}

int pertenece(TAG* pNo, int cod){
    int t = 0;
    if (!pNo) return 0;
    if (pNo->cod == cod) return 1;
    t+=pertenece(pNo->primFilho,cod);
    t+=pertenece(pNo->proxIrmao,cod);
    return t;
}

TAG* insere(TAG* t, int cod, TFIG* info){
    if (!t){
        t = criaNodo(cod,info);
        return t;
    } 

    TAG* temp = t;
    TAG** ppNo = (TAG**)malloc(sizeof(TAG*));
    *ppNo=NULL;
    busca(temp, info->pai, ppNo);
    TAG* pNo = *ppNo;
  
    if (!pNo) return t;

    if (!(pNo->primFilho)){
        pNo->primFilho = criaNodo(cod,info);
        return t;
    }

    TAG* pProx = pNo->primFilho;
    while(pProx->proxIrmao){
        pProx = pProx->proxIrmao;
    }

    if(!pProx){
        pProx->proxIrmao = criaNodo(cod,info);
        return t;
    }
    pProx->proxIrmao = criaNodo(cod,info);
    
    return t;
}

TAG* carrega(TAG* t, char* filename){ 
    TFIG* v = read_txt(filename);
    for (int i=0; i<tam; i++){
        t = insere(t, v[i].cod, &v[i]);
    }
    return t;
}

void busca_antecesor(TAG* pNo, int cod, TAG** ppAnt){
    if (!pNo) return;
    if (pNo->proxIrmao && pNo->proxIrmao->cod == cod){
        *ppAnt = pNo;
        return;
    } 
    if (pNo->primFilho && pNo->primFilho->cod == cod){
        *ppAnt = pNo;
        return;
    }
    busca_antecesor(pNo->primFilho,cod,ppAnt);
    busca_antecesor(pNo->proxIrmao,cod,ppAnt);
}

TAG* retira(TAG* t, int ant_pai, int novo_pai){
    TAG* atemp = t;
    TAG** ppP1 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppP2 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppAP1 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppAP2 = (TAG**)malloc(sizeof(TAG*));

    busca(atemp, ant_pai, ppP1);
    busca(atemp, novo_pai, ppP2);
    busca_antecesor(atemp, ant_pai, ppAP1);
    busca_antecesor(atemp, novo_pai, ppAP2);

    TAG* p1 = *ppP1;
    TAG* p2 = *ppP2;
    TAG* pp1 = *ppAP1;
    TAG* pp2 = *ppAP2;

    if (pertenece(p1,p2->cod)==1){
        int tempcod = p1->cod;
        p1->cod = p2->cod;
        p2->cod = tempcod;

        TFIG* t = p1->info;
        p1->info = p2->info;
        p2->info = t;

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

void imprimir_rec(TAG* pNo){
    if (!pNo) return;
    printf("CODIGO: %d\n", pNo->cod); 
    imprimir_rec(pNo->primFilho);
    imprimir_rec(pNo->proxIrmao);    
}

void imprimir_irmaos(TAG* pNo, FILE* fp){
    if (!pNo) return;

    fprintf(fp,"%d ",pNo->cod);
    if (pNo->proxIrmao)
        fprintf(fp," -> ");
    else
        fprintf(fp, ";");

    imprimir_irmaos(pNo->proxIrmao,fp);
    fprintf(fp,"\n");
    imprimir_irmaos(pNo->primFilho,fp);    
}

void imprimir_filhos(TAG* pNo, FILE* fp){
    if (!pNo) return;

    fprintf(fp,"%d ",pNo->cod);
    if (pNo->primFilho)
        fprintf(fp," -> ");
    else
        fprintf(fp, ";");
    
    imprimir_filhos(pNo->primFilho, fp);
    fprintf(fp,"\n");
    imprimir_filhos(pNo->proxIrmao, fp);
}

void imprimir_rank(TAG* pNo, FILE* fp){
    static int cont = 1;
    if (!pNo) return;
    
    if (pNo->proxIrmao && cont ==1){
        fprintf(fp, "{rank=same; ");
        fprintf(fp, "%d",pNo->cod );
        cont++;
    } else if (pNo->proxIrmao && cont !=1){
        fprintf(fp,"-> ");
        fprintf(fp, "%d",pNo->cod );
    }

    if (!(pNo->proxIrmao)&& cont !=1){
        fprintf(fp," -> ");
        fprintf(fp, "%d;}",pNo->cod );
        cont = 1;
    }

    imprimir_rank(pNo->proxIrmao,fp);
    fprintf(fp,"\n");
    imprimir_rank(pNo->primFilho,fp);    
}

void imprimir_info(TAG* pNo, FILE *fp){
    if (!pNo) return;

    if (strcmp(pNo->info->nom,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                pNo->info->cod,pNo->info->cod,pNo->info->nom,pNo->info->param1,pNo->info->param2,pNo->area);
    else if (strcmp(pNo->info->nom,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                pNo->info->cod,pNo->info->cod,pNo->info->nom,pNo->info->param1,pNo->info->param2,pNo->area);
    else if (strcmp(pNo->info->nom,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, B: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                pNo->info->cod,pNo->info->cod,pNo->info->nom,pNo->info->param1,pNo->info->param2,pNo->info->param3,pNo->area);
    else if (strcmp(pNo->info->nom,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|r: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                pNo->info->cod,pNo->info->cod,pNo->info->nom,pNo->info->param1,pNo->area);
    else if (strcmp(pNo->info->nom,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|l: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                pNo->info->cod,pNo->info->cod,pNo->info->nom,pNo->info->param1,pNo->area);
    
    imprimir_info(pNo->proxIrmao,fp);
    imprimir_info(pNo->primFilho,fp);    
}

void imprimir_arquivo(TAG* pNo, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp,"digraph structs {\n");
    fprintf(fp,"nodesep=.5;\n");
    fprintf(fp,"node [shape=record];\n");
    imprimir_info(pNo,fp);
    //imprimir_irmaos(pNo, fp);
    fprintf(fp, "\n" );
    imprimir_filhos(pNo, fp);
    fprintf(fp,"\n");
    imprimir_rank(pNo,fp);
    fprintf(fp, "}" );

    fclose(fp);
}

///////////////////////////////////////////////////////////////////////// GENERADOR DE AVL

typedef struct arvolAVL{
    int cod;
    TFIG* info;
    double area;
    struct arvolAVL *esq;
    struct arvolAVL *dir;
    int alt;
} TAVL;

TAVL* criaNodoAVL(TAG* pNo){
    TAVL* novo = (TAVL*) malloc(sizeof(TAVL));
    novo->cod = pNo->cod;
    novo->info = pNo->info; 
    novo->area = pNo->area;    
    novo->esq = NULL;
    novo->dir = NULL;
    novo->alt = 0;
    return novo;
}

static int calc_alt(TAVL* n ){
    if( n == NULL ) return -1;
    return n->alt;
}

static int max( int l, int r){
    return l > r ? l: r;
}

static TAVL* rot_dir( TAVL* k2 ){
    TAVL* k1 = NULL;
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
    k2->alt = max( calc_alt( k2->esq ), calc_alt( k2->dir ) ) + 1;
    k1->alt = max( calc_alt( k1->esq ), k2->alt ) + 1;
    return k1; /* nova raiz */
}


static TAVL* rot_esq( TAVL* k1 ){
    TAVL* k2;
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
    k1->alt = max( calc_alt( k1->esq ), calc_alt( k1->dir ) ) + 1;
    k2->alt = max( calc_alt( k2->dir ), k1->alt ) + 1;
    return k2;  /* nova raiz */
}


static TAVL* rot_esq_dir( TAVL* k3 ){
    k3->esq = rot_esq( k3->esq );
    return rot_dir( k3 );
}


static TAVL* rot_dir_esq( TAVL* k1 ){
    k1->dir = rot_dir( k1->dir );
    return rot_esq( k1 );
}

TAVL* insereAVL(TAG* pNo, TAVL* t2){    
    if (t2 == NULL){        
        t2 = criaNodoAVL(pNo);     
    }    
    else if (pNo->cod < t2->cod){
        t2->esq = insereAVL(pNo, t2->esq );
        if( calc_alt( t2->esq ) - calc_alt( t2->dir ) == 2 )
            if( pNo->cod < t2->esq->cod )
                t2 = rot_dir( t2 );
            else
                t2 = rot_esq_dir( t2 );
    } else if (pNo->cod > t2->cod){
        t2->dir = insereAVL(pNo, t2->dir );
        if( calc_alt( t2->dir ) - calc_alt( t2->esq ) == 2 )
            if( pNo->cod > t2->dir->cod )
                t2 = rot_esq( t2 );
            else
                t2 = rot_dir_esq( t2 );
    }
    t2->alt = max( calc_alt( t2->esq ), calc_alt( t2->dir ) ) + 1;
    return t2;
}

TAVL* transformaAVL(TAG* t, TAVL* t2){
    if (!t) return t2;
    t2 = insereAVL(t,t2);
    t2 = transformaAVL(t->primFilho, t2);
    t2 = transformaAVL(t->proxIrmao, t2);
    return t2; //////////////////////////////// REVISAR //////////////////////////////////////////////////////////////////////////////
}

void imprimir_recAVL(TAVL* t2){
    if (!t2) return;
    printf("CODIGO: %d\n", t2->cod);    
    imprimir_recAVL(t2->dir);    
    imprimir_recAVL(t2->esq);
}

void imprimir_infoAVL(TAVL* t2, FILE *fp){
    if (!t2) return;

    if (strcmp(t2->info->nom,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->area);
    else if (strcmp(t2->info->nom,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->area);
    else if (strcmp(t2->info->nom,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, B: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->info->param3,t2->area);
    else if (strcmp(t2->info->nom,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|r: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->area);
    else if (strcmp(t2->info->nom,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|l: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->area);
    
    imprimir_infoAVL(t2->esq,fp);
    imprimir_infoAVL(t2->dir,fp);    
}

void imprimir_esqAVL(TAVL* t2, FILE *fp){
    if (!t2){
        return;
    } 
    if (t2->esq){
        fprintf(fp,"%d:f1 -> %d;\n", t2->cod, t2->esq->cod);    
    }
    imprimir_esqAVL(t2->esq,fp);
    imprimir_esqAVL(t2->dir,fp);    
}


void imprimir_dirAVL(TAVL* t2, FILE *fp){
    if (!t2){
        return;
    } 
    if (t2->dir){
        fprintf(fp,"%d:f2 -> %d;\n", t2->cod, t2->dir->cod);    
    }
    imprimir_dirAVL(t2->dir,fp);    
    imprimir_dirAVL(t2->esq,fp);
}


void imprimir_arquivoAVL(TAVL* t2, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp,"digraph structs {\n");
    fprintf(fp,"nodesep=.5;\n");
    fprintf(fp,"node [shape=record];\n");
    imprimir_infoAVL(t2,fp);
    fprintf(fp, "\n" );
    imprimir_esqAVL(t2, fp);
    fprintf(fp, "\n" );
    imprimir_dirAVL(t2, fp);
    //fprintf(fp, "\n" );
    //imprimir_filhos(pNo, fp);
    //fprintf(fp,"\n");
    //imprimir_rank(pNo,fp);
    fprintf(fp, "}" );

    fclose(fp);
}

/////////////////////////////////////////////////////////////////////////

const int n = 2;

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB **filho;
}TAB;

TAB *criaB(int n){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(int*)malloc(sizeof(int*)*((n*2)-1));
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*n*2);
  int i;
  for(i=0; i<(n*2); i++) novo->filho[i] = NULL;
  return novo;
}

TAB *buscaB(TAB* x, int ch){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]) i++;
  if(i < x->nchaves && ch == x->chave[i]) return x;
  if(x->folha) return resp;
  return buscaB(x->filho[i], ch);
}

TAB *inicializaB(){
  return NULL;
}

TAB *divisaoB(TAB *x, int i, TAB* y, int n){
  TAB *z=criaB(n);
  z->nchaves= n - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<n-1;j++) z->chave[j] = y->chave[j+n];
  if(!y->folha){
    for(j=0;j<n;j++){
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


TAB *insereB(TAB *T, TAG* tag, int n){
  int cod = tag->cod;
  if(buscaB(T,cod)) return T;
  if(!T){
    T=criaB(n);
    T->chave[0] = cod;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*n)-1){
    TAB *S = criaB(n);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = divisaoB(S,1,T,n);
    S = insere_Nao_CompletoB(S,cod,n);
    return S;
  }
  T = insere_Nao_CompletoB(T,cod,n);
  return T;
}

TAB* transformaB(TAG* tag, TAB* t3, int n){
    if (!tag) return t3;
    t3 = insereB(t3,tag,n);
    t3 = transformaB(tag->primFilho, t3, n);
    t3 = transformaB(tag->proxIrmao, t3, n);    
}

void imprimeB(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      imprimeB(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", a->chave[i]);
    }
    imprimeB(a->filho[i],andar+1);
  }
}

/*void imprimir_infoB(TAB* t3, FILE *fp){
    if (!t3) return;

    /*if (strcmp(t2->info->nom,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->area);
    else if (strcmp(t2->info->nom,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->area);
    else if (strcmp(t2->info->nom,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, B: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->info->param2,t2->info->param3,t2->area);
    else if (strcmp(t2->info->nom,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|r: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->area);
    else if (strcmp(t2->info->nom,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|l: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                t2->info->cod,t2->info->cod,t2->info->nom,t2->info->param1,t2->area);
    

    imprimir_infoB(t->esq,fp);
    imprimir_infoB(t2->dir,fp);    
}

void imprimir_esqAVL(TAVL* t2, FILE *fp){
    if (!t2){
        return;
    } 
    if (t2->esq){
        fprintf(fp,"%d:f1 -> %d;\n", t2->cod, t2->esq->cod);    
    }
    imprimir_esqAVL(t2->esq,fp);
    imprimir_esqAVL(t2->dir,fp);    
}


void imprimir_dirAVL(TAVL* t2, FILE *fp){
    if (!t2){
        return;
    } 
    if (t2->dir){
        fprintf(fp,"%d:f2 -> %d;\n", t2->cod, t2->dir->cod);    
    }
    imprimir_dirAVL(t2->dir,fp);    
    imprimir_dirAVL(t2->esq,fp);
}*/


void imprime2(TAB *a, int andar, FILE *fp, int mynum){
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
        imprime2(a->filho[i], andar+1, fp, i+(mynum*pchaves) );
    }
  }
}

void imprime4(TAB *a, int andar, FILE *fp, int mynum){
  if(a){
    int i,j;
    int pchaves=(n*2);

    for (i=0; i<pchaves; i++){
        if(a->filho[i]){
            fprintf(fp,"%d%d:<f%d> -> %d%d:<f%d>;\n", andar, mynum*pchaves, i+(mynum*pchaves), andar+1, (i+(mynum*pchaves))*pchaves , (i+(mynum*pchaves))*pchaves );  
        }
    }
    for(i=0; i<pchaves; i++){
        imprime4(a->filho[i],andar+1,fp,i+(mynum*pchaves));  
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
    imprime2(t3,0,fp,0);
    fprintf(fp, "\n");
    //imprime3(t3,0,fp,0);
    imprime4(t3,0,fp,0);
    /*imprimir_infoAVL(t2,fp);
    fprintf(fp, "\n" );
    imprimir_esqAVL(t2, fp);
    fprintf(fp, "\n" );
    imprimir_dirAVL(t2, fp);*/
    //fprintf(fp, "\n" );
    //imprimir_filhos(pNo, fp);
    //fprintf(fp,"\n");
    //imprimir_rank(pNo,fp);
    fprintf(fp, "}" );

    fclose(fp);
}

/////////////////////////////////////////////////////////////////////////

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
    busca_simnao(t,cod);    
    if (bs_flag==0){
        printf("\n\tFigura Nao encontrada\n");
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return;
    } 

    busca_figuraAG(t,cod);

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
    imprimir_arquivo(t,"arvolG.dot");
    printf("\tÁrvore impressa!\n");
    system("dot -Tps arvolG.dot -o arvolG.pdf");
    system("xdg-open arvolG.pdf");

    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

void inserir_nova_figura(TAG* t){
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
        return;
    }    
    
    int my_arguments_int[3];
    int i;
    for(i=0;i<num_arg;i++){
        my_arguments_int[i]=atoi(my_arguments[i]);
    }

    bs_flag = 0;
    busca_simnao(t,1);
    int n_cod;
    while(bs_flag == 1){
        printf("\t(>) Insira um codigo para a nova figura: \n");
        printf("\t  (ex: 12 )\n");
        printf("\t  (ex: 16 )\n");
        printf("\t>>     ");
        scanf(" %d",&n_cod);
        bs_flag = 0;
        busca_simnao(t,n_cod);
        if(bs_flag == 1) printf("\tCodigo de figura em uso\n");
    }

    bs_flag = 0;
    busca_simnao(t,-1);
    int n_pai;
    while(bs_flag == 0){
        printf("\t(>) Insira o codigo do pai: \n");
        printf("\t  (ex: 4  )\n");
        printf("\t  (ex: 10 )\n");
        printf("\t>>     ");
        scanf(" %d",&n_pai);
        bs_flag = 0;
        busca_simnao(t,n_pai);
        if(bs_flag == 0) printf("\tCodigo do pai nao encontrado\n");
    }

    tam++;
    v = (TFIG*) realloc(v,sizeof(TFIG)*(tam+1));
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

    t = insere(t,n_cod,&v[tam]);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tFigura inserida!\n");
    printf("\n");
    printf("=======================================================================================\n");

    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

void retirar_figura(TAG* t){  
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
    busca_simnao(t,cod_apai);
    if (bs_flag == 0){
        printf("\n");
        printf("\tCodigo de figura para retirar nao encontrado\n");        
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return;        
    } 

    bs_flag = 0;
    busca_simnao(t,cod_npai);
    if (bs_flag == 0){
        printf("\n");
        printf("\tCodigo de figura novo pai nao encontrado\n");
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return;   
    }

    bs_flag = 0;
    t = retira(t, cod_apai, cod_npai);

    printf("\n");
    printf("\tFigura retirada!\n");
    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

void destruir_arvore(){
    return;
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
    busca_simnao(t,cod);
    if (bs_flag==0){
        printf("=======================================================================================\n");
        printf("\n");
        printf("\tCodigo de figura nao encontrado\n");        
        printf("\n=======================================================================================\n");
        printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
        getchar();
        return;
    }
    altera_figuraAG(t,cod);
    getchar();
}

void transformar_avl(TAG* t, TAVL* t2){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(g) Transformar a árvore genérica numa árvore AVL\n");
    printf("=======================================================================================\n");
    printf("\n");
    t2 = transformaAVL(t,t2);
    imprimir_arquivoAVL(t2,"arvolAVL.dot");
    printf("\tÁrvore transformado!\n");
    system("dot -Tps arvolAVL.dot -o arvolAVL.pdf");
    system("xdg-open arvolAVL.pdf");
    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
    
    return ;
}

void tranformar_b(){

    return ;
}


/*int main(void){
    TAG* t = NULL;
    t = carrega(t,"data.txt");
    //imprimir_rec(t);
    //t = retira(t,5,3);
    t = retira(t,3,10);
    //t = retira(t,10,6);
    //imprimir_rec(t);
    imprimir_arquivo(t,"arvolGen.dot");
    TAVL* t2 = NULL;
    t2 = transformaAVL(t,t2);
    //imprimir_recAVL(t2);
    imprimir_arquivoAVL(t2,"arvolAVL.dot");
    return 0;
}*/

int main(){
    TAG* t = NULL;
    TAVL* t2 = NULL;
    TAB* t3 = NULL;    
    t = carrega(t,"data.txt");
    t3 = transformaB(t,t3,n);
    imprimeB(t3,0);
    imprimir_arquivoB(t3,"arvolB.dot");
    
    /*int i;
    char key[2] ;
    while(1){
        printf("\033[2J");
        printf("\033[1;1H"); 
        //printf("Elija su opcion: \e[31mRed\n");
        printf("\t\t\t\t\e[33;1m@Roger Ripas && @Luigy Machaca \e[00m \n");
        printf("=======================================================================================\n");
        printf("ARVOL GENERICO: \n");
        printf("\t(a) Buscar figura geométrica\n");
        printf("\t(b) Imprimir árvore \n");
        printf("\t(c) Inserir novas figuras\n");
        printf("\t(d) Retirar figuras\n");
        printf("\t(e) Destruir árvore\n");
        printf("\t(f) Alterar dimensões das figuras\n");
        printf("\t(g) Transformar a árvore genérica numa árvore AVL\n");
        printf("\t(h) Transformar a árvore genérica numa árvore B\n");
        printf("=======================================================================================\n");
        printf("Insira sua opção: \n");
        printf("\t >>  ");
        scanf(" %s",key);
        printf("=======================================================================================\n");

  
        //char elem[20];
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
                inserir_nova_figura(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'd' :                
                retirar_figura(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'e' :
                destruir_arvore();
                //scanf("%s",&elem);
                getchar();
                break;
            case 'f' :
                alterar_dimensoes_figura(t);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'g' :
                transformar_avl(t,t2);
                //scanf("%s",&elem);
                getchar();
                break;
            case 'h' :
                tranformar_b();
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
    }*/
    return 0;
}

