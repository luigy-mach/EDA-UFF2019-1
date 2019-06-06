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
	TAG* temp = t;
	TAG** ppNoAPai = (TAG**)malloc(sizeof(TAG*));
	TAG** ppNoNPai = (TAG**)malloc(sizeof(TAG*));
	TAG** ppNoAnt = (TAG**)malloc(sizeof(TAG*));

	busca(temp, ant_pai, ppNoAPai);
	busca(temp, novo_pai, ppNoNPai);
	busca_antecesor(temp, ant_pai, ppNoAnt);

	TAG* pNoA = *ppNoAPai;
	TAG* pUltimoIr = *ppNoNPai;
	TAG* pUltimoFi = *ppNoNPai;
	TAG* pNoAnt = *ppNoAnt;

	if (!(pUltimoFi->primFilho)){
		pUltimoFi->primFilho = pNoA->primFilho;
	} else {
		pUltimoFi = pUltimoFi->primFilho;
		while(pUltimoFi->proxIrmao) pUltimoFi = pUltimoFi->proxIrmao;
		pUltimoFi->proxIrmao = pNoA->primFilho;
	}

	if (pNoA->proxIrmao == pNoAnt->proxIrmao->proxIrmao){
		pNoAnt->proxIrmao = pNoA->proxIrmao;
	} else {
		while(pUltimoIr->proxIrmao) pUltimoIr = pUltimoIr->proxIrmao;
		pUltimoIr->proxIrmao = pNoA->proxIrmao;
		pNoAnt->primFilho = NULL;
	}

	pNoA->proxIrmao = NULL;
	pNoA->primFilho = NULL;

	free(pNoA);

	return t;
}

void imprimir_rec(TAG* pNo){
    if (!pNo) return;
    printf("CODIGO: %d - PADRE: %d\n",pNo->cod,pNo->info->pai); 
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

int main(void){
	TAG* t = NULL;
	t = carrega(t,"data.txt");
	//imprimir_rec(t);
	//t = retira(t,4,9);
	imprimir_arquivo(t,"arvolGen.dot");
	return 0;
}