#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* TYPEDEF GERAL FIGURE*/
#define PI 3.1415
#define BUFFER_LINE 50
#define BUFFER_CHAR 10
#define NUM_DIV_INPUT 6
//#define TAM_VEC_ 30

typedef int (*myTypeCmpFunc)(void*, void*);


/*********************************************************************************************/
/************************************** struct FIGURE  **************************************/
/*********************************************************************************************/

typedef struct figure{
  int cod;
  char* nome;
  int* parameters;
  double area;
} TFIG;


TFIG* inicializa_TFIG(){
    return NULL;
}


TFIG* destruir_TFIG(TFIG* fig){
    free(fig->nome);
    free(fig->parameters);
    free(fig);
    return NULL;
} 

int compare_dois_TFIG(TFIG* fig1, TFIG* fig2){
    if(!fig1 || !fig2)
        return -1;
    if(fig1->cod == fig2->cod){
        return 1;
    }
    else{
        return 0;
    }
}

int maior_que_TFIG(TFIG* fig1, TFIG* fig2){
    if(!fig1 || !fig2)
        return -1;
    if(fig1->cod > fig2->cod){
        return 1;
    }
    else{
        return 0;
    }
}

int menor_que_TFIG(TFIG* fig1, TFIG* fig2){
    if(!fig1 || !fig2)
        return -1;
    if(fig1->cod < fig2->cod){
        return 1;
    }
    else{
        return 0;
    }
}

int quan_parameters_TFIG(char* nome){
    if(strcmp(nome,"QUA")==0){//QUA
        return 1;
    }
    if(strcmp(nome,"CIR")==0){//CIR
        return 1;
    }
    if(strcmp(nome,"RET")==0){//RET
        return 2;
    }
    if(strcmp(nome,"TRI")==0){//TRI
        return 2;
    }
    if(strcmp(nome,"TRA")==0){//TRA
        return 3;
    }
    return -1; //error
}

int verifica_nome_TFIG(char* nome){
    if(strcmp(nome,"QUA")==0){//QUA
        return 1;
    }
    if(strcmp(nome,"CIR")==0){//CIR
        return 1;
    }
    if(strcmp(nome,"RET")==0){//RET
        return 1;
    }
    if(strcmp(nome,"TRI")==0){//TRI
        return 1;
    }
    if(strcmp(nome,"TRA")==0){//TRA
        return 1;
    }
    return 0; //error
}

int* cria_parameters_TFIG(char* nome){
    if(strlen(nome)!=3){
        return NULL; //error nome
    }
    int tam = quan_parameters_TFIG(nome);
    if(tam==-1){
        return NULL; //error
    }
    int* parameters = (int*)malloc(sizeof(int)*tam); 
    for(int i=0;i<tam;i++){
        parameters[i]=-1;
    }    
    return parameters; //error
}


double calcula_area_TFIG(char* nome,int* parameters){
    if(!nome || !parameters){
        return -1.0;
    }
    if(strcmp(nome,"QUA")==0){//QUA
        return parameters[0]*parameters[0];
    }
    if(strcmp(nome,"CIR")==0){//CIR
        return PI*(double)(parameters[0]*parameters[0]);
    }
    if(strcmp(nome,"RET")==0){//RET
        return (double)(parameters[0]*parameters[1]);
    }
    if(strcmp(nome,"TRI")==0){//TRI
        return (double)(parameters[0]*parameters[1])/2.0;
    }
    if(strcmp(nome,"TRA")==0){//TRA
        return (double)(parameters[0]+parameters[1])/(2.0)*(double)parameters[2];
    }
    return -1.0;
}


int ler_cod_TFIG(TFIG* fig){
    return fig->cod;
}

char* ler_nome_TFIG(TFIG* fig){
    return fig->nome;
}

int* ler_parameters_TFIG(TFIG* fig){
    return fig->parameters;
}

double ler_area_TFIG(TFIG* fig){
    return fig->area;
}

TFIG* cria_TFIG(int cod, char* nome, int* parameters ){
    if(!parameters || !nome) 
        return NULL; //error cria_TFIG;
    TFIG* novo=(TFIG*)malloc(sizeof(TFIG));
    novo->cod=cod;
    int len_nome=strlen(nome);
    novo->nome=(char*)malloc(sizeof(char)*len_nome);
    strcpy(novo->nome,nome);
    novo->parameters=parameters;
    novo->area=calcula_area_TFIG(nome,parameters);
    return novo; 
}

TFIG* cria_TFIG_vacio(int cod){
    TFIG* novo=(TFIG*)malloc(sizeof(TFIG));
    novo->cod=cod;
    novo->nome=NULL;
    novo->parameters=NULL;
    novo->area=-1;
    return novo; 
}

int mudarCod_TFIG(TFIG* fig, int cod){
    if(!fig){
        return 0;
    }
    fig->cod=cod;
    return 1;
}

int mudarTipo_TFIG(TFIG* fig, char* nome, int* parameters ){
    if(!nome && !parameters){
        return 0; //error
    }
    free(fig->nome);
    free(fig->parameters);
    int len_nome=strlen(nome);
    fig->nome=(char*)malloc(sizeof(char)*len_nome);
    strcpy(fig->nome,nome);
    fig->parameters=parameters;
    fig->area=calcula_area_TFIG(nome,parameters);

    return 1;
}


/*********************************************************************************************/
/************************************** Interface INFO (void*) ********************************/
/*********************************************************************************************/

void* cria_INFO(int cod, char* nome, int* parameters ){
    if(!parameters) 
        return NULL; //error ;
    void* novo = (void*)cria_TFIG(cod,nome,parameters);
    return novo; 
}

void* cria_INFO_vacio(int cod){
    void* novo = (void*)cria_TFIG_vacio(cod);
    return novo; 
}

int ler_cod_INFO(void* info){
    if(!info){
        return 0;
    }    
    TFIG* temp=(struct figure*)(info);
    return ler_cod_TFIG(temp);
}

char* ler_nome_INFO(void* info){
    if(!info){
        return 0;
    }
    TFIG* temp=(struct figure*)(info);
    return ler_nome_TFIG(temp);
}

int* ler_parameters_INFO(void* info){
    if(!info){
        return 0;
    }
    TFIG* temp=(struct figure*)(info);
    return ler_parameters_TFIG(temp);
}

double ler_area_INFO(void* info){
    if(!info){
        return 0;
    }
    TFIG* temp=(struct figure*)(info);
    return ler_area_TFIG(info);
}

int mudarCod_INFO(void* info, int cod){
    if(!info){
        return 0;
    }
    TFIG* fig = (struct figure*)(info);
    return mudarCod_TFIG(fig,cod);
}

int mudarTipo_INFO(void* info, char* nome, int* parameters ){
    if(!info){
        return 0;
    }
    TFIG* fig = (struct figure*)(info);
    return mudarTipo_TFIG(fig,nome,parameters);
}

int compare_dois_INFO(void* info1, void* info2){
    if(!info1 || !info2){
        return -1;
    }
    TFIG* myfig1=(struct figure*)(info1);
    TFIG* myfig2=(struct figure*)(info2);
    return compare_dois_TFIG(myfig1, myfig2);
}

int maior_que_INFO(void* info1, void* info2){
    if(!info1 || !info2){
        return -1;
    }
    TFIG* myfig1=(struct figure*)(info1);
    TFIG* myfig2=(struct figure*)(info2);
    return maior_que_TFIG(myfig1, myfig2);
}

int menor_que_INFO(void* info1, void* info2){
    if(!info1 || !info2){
        return -1;
    }
    TFIG* myfig1=(struct figure*)(info1);
    TFIG* myfig2=(struct figure*)(info2);
    return menor_que_TFIG(myfig1, myfig2);
}

int verifica_nome_INFO(char* nome){
    return verifica_nome_TFIG(nome);
}

int alterar_nome_INFO(void* info, char* nome){
    if (!nome || !info)
        return -1; // Error
    TFIG* fig = (struct figure*)(info);
    strcpy(fig->nome,nome);
    return 1;
}

void* destruir_INFO(void* info){
    TFIG* fig = (struct figure*)(info);
    fig=destruir_TFIG(fig);
    return (void*)fig;
}


/*********************************************************************************************/
/************************************** ARVORE GENERICA **************************************/
/*********************************************************************************************/

typedef struct arvoreGenerica{
    void* info;
    struct arvoreGenerica* primFilho;
    struct arvoreGenerica* proxIrmao;
} TAG;


TAG* inicializa_AG(){
  return NULL;
}

TAG* criaNo_AG(void* info){
    TAG* novo = (TAG*)malloc(sizeof(TAG));
    novo->info=info;
    novo->primFilho=NULL;
    novo->proxIrmao=NULL;
    return novo;
}

TAG* destruir_No_AG(TAG* pNo){
    pNo->proxIrmao = NULL;
    pNo->primFilho = NULL;
    pNo=destruir_INFO(pNo->info);
    return pNo;
}

TAG* destruir_tudo_AG(TAG* pNo){
    if (!pNo) return NULL;
    destruir_tudo_AG(pNo->primFilho);
    destruir_tudo_AG(pNo->proxIrmao);    
    if (pNo){
        return destruir_No_AG(pNo);
    } 
}

int localizaEndereco_AG(TAG* pNo, void* pInfo, TAG** ppNoReturn, myTypeCmpFunc pCmpFunc ){ // pNo y ppNo
    if (!pNo) return 0;
    if (pCmpFunc(pNo->info,pInfo)==1){ 
        *ppNoReturn = pNo;
        return 1;
    } 
    int value=0;//  0 nao encontrado
                //  1 da certo
    value+=localizaEndereco_AG(pNo->primFilho,pInfo,ppNoReturn,pCmpFunc);
    value+=localizaEndereco_AG(pNo->proxIrmao,pInfo,ppNoReturn,pCmpFunc);    
    return value;
}


int localizaEnderecoAntecesor_AG(TAG* tag, void* pInfo, TAG** ppNoReturn, myTypeCmpFunc pCmpFunc){
    if (!tag) return 0;
    if (tag->proxIrmao && (pCmpFunc(tag->proxIrmao->info,pInfo)==1) ){
        *ppNoReturn = tag;
        return 1;
    } 
    if (tag->primFilho && (pCmpFunc(tag->primFilho->info,pInfo)==1) ){
        *ppNoReturn = tag;
        return 1;
    }
    int value=0;//  0 nao encontrado
                //  1 da certo
    value+=localizaEnderecoAntecesor_AG(tag->primFilho, pInfo, ppNoReturn, pCmpFunc);
    value+=localizaEnderecoAntecesor_AG(tag->proxIrmao, pInfo, ppNoReturn, pCmpFunc);
    return value;
}

void trocar_No_AG(TAG* tag, void* info1, void* info2, myTypeCmpFunc pCmpFunc){
    if(!tag && !info1 && !info2){
        return; //error  NULL
    }
    
    TAG** ppNoReturn1=(TAG**)malloc(sizeof(TAG*)); 
    if(localizaEndereco_AG(tag, info1, ppNoReturn1, pCmpFunc)==0){
        printf("info1 no encontrado\n");
        return;
    }
    TAG** ppNoReturn2=(TAG**)malloc(sizeof(TAG*)); 
    if(localizaEndereco_AG(tag, info2, ppNoReturn2, pCmpFunc)==0){
        printf("info2 no encontrado\n");
        return;
    }
    TAG* pNoInfo1 = (*ppNoReturn1);
    TAG* pNoInfo2 = (*ppNoReturn2);

        void* temp=pNoInfo1->info;
    pNoInfo1->info=pNoInfo2->info;
    pNoInfo2->info=temp;
    return;
}


TAG* insere_AG(TAG* tag, void* info, void* info_pai, myTypeCmpFunc pCmpFunc ){
    if (!tag){
        tag = criaNo_AG(info);
        return tag;
    }
    TAG* temp = tag;
    TAG** ppNo = (TAG**) malloc(sizeof(TAG*));
    *ppNo = NULL;
    if(localizaEndereco_AG(temp,info_pai,ppNo,pCmpFunc)==0){
        printf("error pai no encontrado\n"); // error pai no encontrado
        return tag;  
    }
    TAG* pNo = *ppNo;
    if (!(pNo->primFilho)){
        pNo->primFilho = criaNo_AG(info);
        return tag;
    }
    TAG* pProx = pNo->primFilho;
    while(pProx->proxIrmao){
        pProx = pProx->proxIrmao;
    }

    if(!pProx){
        pProx->proxIrmao = criaNo_AG(info);
        return tag;
    }
    pProx->proxIrmao = criaNo_AG(info);
    return tag;
}

int buscar_TAG(TAG* pNo, void* pInfo, myTypeCmpFunc pCmpFunc){ // pNo y ppNo
    if (!pNo) return 0;
    if (pCmpFunc(pNo->info,pInfo)==1){ 
        return 1;
    } 
    int value=0;//  0 nao encontrado
                //  1 da certo
    value+=buscar_TAG(pNo->primFilho,pInfo,pCmpFunc);
    value+=buscar_TAG(pNo->proxIrmao,pInfo,pCmpFunc);    
    return value;
}


TAG* retira_AG(TAG* tag, void* pAnt_pai, void* pNovo_pai, myTypeCmpFunc pCmpFunc){
    TAG* atemp = tag;
    TAG** ppP1 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppP2 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppAP1 = (TAG**)malloc(sizeof(TAG*));
    TAG** ppAP2 = (TAG**)malloc(sizeof(TAG*));

    if(localizaEndereco_AG(atemp, pAnt_pai, ppP1, pCmpFunc)==0){
        printf("pAnt_pai no encontrado\n");
        return tag;
    }
    if(localizaEndereco_AG(atemp, pNovo_pai, ppP2, pCmpFunc)==0){
        printf("pNovo_pai no encontrado\n");
        return tag;
    }
    if(localizaEnderecoAntecesor_AG(atemp, pAnt_pai, ppAP1, pCmpFunc)==0){
        printf("pai de pAnt_pai no encontrado\n");
        return tag;
    }
    if(localizaEnderecoAntecesor_AG(atemp, pNovo_pai, ppAP2, pCmpFunc)==0){
        printf("pai de pNovo no encontrado\n");
        return tag;
    }

    TAG* p1 = *ppP1;
    TAG* p2 = *ppP2;
    TAG* pp1 = *ppAP1;
    TAG* pp2 = *ppAP2;
    
    if( buscar_TAG(p1,p2->info,pCmpFunc)==1 ){
        //caso especial.
        printf("no es posible retirar este elemento\n");
        return tag;
    }   

    if(pp1->proxIrmao == p1)
        pp1->proxIrmao = NULL;
    else if(pp1->primFilho == p1)
        pp1->primFilho = NULL;

    TAG* temp = p2;
    while(temp->proxIrmao) temp = temp->proxIrmao;
    temp->proxIrmao = p1->proxIrmao;

    temp = NULL;
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
    p1=destruir_No_AG(p1);

    free(ppP1);
    free(ppP2);
    free(ppAP1);
    free(ppAP2);

    return tag;
}


/*********************************************************************************************/
/************************************** CARREGA ARQUIVO **************************************/
/*********************************************************************************************/

TFIG** cria_vetor_fig_Arquivo(int tam){
	TFIG** vec = (TFIG**) malloc(sizeof(TFIG*)*tam);
	for (int i=0; i<tam; i++){
		vec[i] = NULL;
	}
	return vec;
}

int* cria_vetor_pais_Arquivo(int tam){
	int* vec = (int*) malloc(sizeof(int)*tam);
	for (int i=0; i<tam; i++){
		vec[i] = -1;
	}
	return vec;
}



TAG* carregaDesde_Arquivo(TAG* tag, char* fileName, myTypeCmpFunc pCmpFunc){
    tag=NULL; 
    FILE* file = fopen(fileName, "r"); 
    if(file==NULL){
        printf("error ao abrir arquivo!!");
        exit(-1);
        return NULL;
    }
    int tam = 0;
    char line[BUFFER_LINE];
    while (fgets(line, sizeof(line), file)) tam++;
    fclose(file);

    if(tam==0){
        printf("error ao abrir vacio!!");
        exit(-1);
        return NULL;
    }

    int numline = 0;
    TFIG** vecFIG = NULL;
    int* vecPais = NULL;
    vecFIG  = cria_vetor_fig_Arquivo(tam); // os elementos sao tudos NULL
    vecPais = cria_vetor_pais_Arquivo(tam); // os elemntos sao tudos -1

    file = fopen(fileName, "r");
    while (fgets(line, sizeof(line), file)){
        
        char mat_input[NUM_DIV_INPUT][BUFFER_CHAR];
        for(int i=0;i<NUM_DIV_INPUT;i++){
            memset(mat_input[i], 0, sizeof(mat_input[i])); // setting to zero
        }
		int j = 0, k = 0;
		for (int l=0; l<strlen(line); l++){
			if (line[l]== '/' && k == 0){
				k++;
				j = 0;
				continue;
			} else if (line[l]== '/' && k == 1){
				k++;
				j = 0;
				continue;
			} else if (line[l]== ' ' && k == 2){
				k++;
				j = 0;
				continue;
			} else if ((line[l] == ' ' || line[l] == '\n') && k == 3){
 				k++;
				j = 0;
				continue;
			} else if ((line[l] == ' ' || line[l] == '\n') && k == 4){
				k++;
				j = 0;
				continue;
			} else if ((line[l] == ' ' || line[l] == '\n') && k == 5){
				k++;
				j = 0;
				continue;
			}
            mat_input[k][j]=line[l];
			j++;
		}
        if(k<4 || k>6){
            continue;
        }	
        int cod = atoi(mat_input[0]);					
        int pai = atoi(mat_input[1]);
        int num_parameters = quan_parameters_TFIG(mat_input[2]);
        int* parameters = cria_parameters_TFIG(mat_input[2]); 
		
        for(int i=0;i<num_parameters;i++){
            int temp = atoi(mat_input[i+3]);
            parameters[i]=temp;
        }
        vecFIG[numline] = cria_TFIG(cod, mat_input[2], parameters);
        vecPais[numline] = pai;

    	numline++;
    }
    fclose(file);
    if(numline>tam){
        exit(-1);
        return tag;
    }
    //iterando vecFIG e vecPais
    for(int i=0;i<numline;i++){
        void* temp_pai = cria_INFO_vacio(vecPais[i]);
        tag = insere_AG(tag, (void*)vecFIG[i],(void*)temp_pai , pCmpFunc);
        destruir_TFIG(temp_pai);
    }

    free(vecPais);
    free(vecFIG);

    return tag;
}



void imprimirFilhos_AG_DOT(TAG* tag, FILE* fp){
    if (!tag) return;
    fprintf(fp, "%d ", ler_cod_INFO(tag->info));
    if (tag->primFilho)
        fprintf(fp, " -> ");
    else
        fprintf(fp, ";");
    
    imprimirFilhos_AG_DOT(tag->primFilho, fp);
    fprintf(fp, "\n");
    imprimirFilhos_AG_DOT(tag->proxIrmao, fp);
}

void imprimirRank_AG_DOT(TAG* tag, FILE* fp){
    static int cont = 1;
    if (!tag) return;
    
    if (tag->proxIrmao && cont ==1){
        fprintf(fp, "{rank=same; ");
        fprintf(fp, "%d", ler_cod_INFO(tag->info) );
        cont++;
    } else if (tag->proxIrmao && cont!=1){
        fprintf(fp, "-> ");
        fprintf(fp, "%d", ler_cod_INFO(tag->info));
    }

    if (!(tag->proxIrmao) && cont!=1){
        fprintf(fp, " -> ");
        fprintf(fp, "%d;}", ler_cod_INFO(tag->info));
        cont = 1;
    }

    imprimirRank_AG_DOT(tag->proxIrmao, fp);
    fprintf(fp, "\n");
    imprimirRank_AG_DOT(tag->primFilho, fp);    
}


void imprimirInfo_AG_DOT(TAG* tag, FILE *fp){
    if (!tag) return;
    int cod = ler_cod_INFO(tag->info);
    char* nome = ler_nome_INFO(tag->info);
    int* parameters = ler_parameters_INFO(tag->info);
    double area =ler_area_INFO(tag->info);

    if (strcmp(nome,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                cod,cod,nome,parameters[0],parameters[1],area);
    else if (strcmp(nome,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                cod,cod,nome,parameters[0],parameters[1],area);
    else if (strcmp(nome,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|b: %d, B: %d, h: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                cod,cod,nome,parameters[0],parameters[1],parameters[2],area);
    else if (strcmp(nome,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|r: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                cod,cod,nome,parameters[0],area);
    else if (strcmp(nome,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{{%s|l: %d|Area: %.2f }|<f1> Irmao}|<f2> Filhos}\"];\n",
                cod,cod,nome,parameters[0],area);
    
    imprimirInfo_AG_DOT(tag->proxIrmao, fp);
    imprimirInfo_AG_DOT(tag->primFilho, fp);    
}

void imprimirArquivo_AG_DOT(TAG* tag, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp, "digraph structs {\n");
    fprintf(fp, "nodesep=.5;\n");
    fprintf(fp, "node [shape=record];\n");
    imprimirInfo_AG_DOT(tag,fp);
    fprintf(fp, "\n" );
    imprimirFilhos_AG_DOT(tag, fp);
    fprintf(fp, "\n");
    imprimirRank_AG_DOT(tag, fp);
    fprintf(fp, "}" );

    fclose(fp);
}

/*********************************************************************************************/
/************************************** FUNCOES DO MENU **************************************/
/*********************************************************************************************/

void limpar_janela01(){
    printf("\033[2J");
    printf("\033[1;1H"); 
}

void limpar_janela02(){
    printf("\n=======================================================================================\n");
    printf("\n\n\n\n\n\nPresione Enter para voltar ao Menu principal... ");
    getchar();
}

void buscar_figura_AG(TAG* tag, int cod_buscado){
    if (!tag) return;
    int cod = ler_cod_INFO(tag->info);
    if (cod == cod_buscado){
        printf("\n");
        printf("\tFigura encontrada!\n");
        char* nome = ler_nome_INFO(tag->info);
        int* parameters = ler_parameters_INFO(tag->info);
        double area =ler_area_INFO(tag->info);
        if (strcmp(nome,"TRI") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE: %d - ALTURA: %d - AREA: %.2f\n",cod,nome,parameters[0],parameters[1],area);
        }
        else if (strcmp(nome,"RET") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE: %d - ALTURA: %d - AREA: %.2f\n",cod,nome,parameters[0],parameters[1],area);
        }
        else if (strcmp(nome,"TRA") == 0){
            printf("\tCODIGO: %d - NOME: %s - BASE MENOR: %d - BASE MAYOR: %d - ALTURA: %d - AREA: %.2f\n",cod,nome,parameters[0],parameters[1],parameters[2],area);
        }
        else if (strcmp(nome,"CIR") == 0){
            printf("\tCODIGO: %d - NOME: %s - RADIO: %d - AREA: %.2f\n",cod,nome,parameters[0],area);
        }
        else if (strcmp(nome,"QUA") == 0){
            printf("\tCODIGO: %d - NOME: %s - LADO: %d - AREA: %.2f\n",cod,nome,parameters[0],area);
        }
    }
    buscar_figura_AG(tag->primFilho, cod_buscado);
    buscar_figura_AG(tag->proxIrmao, cod_buscado);
}    
    
void buscar_figura_MENUAG(TAG* tag, myTypeCmpFunc pCmpFunc){
    limpar_janela01();

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

    void* pInfo = cria_INFO_vacio(cod);

    if(buscar_TAG(tag, pInfo, pCmpFunc) == 0){
        printf("\n\tFigura Nao encontrada\n");
        limpar_janela02();
        return;
    } else {
        buscar_figura_AG(tag, cod);
    }

    limpar_janela02();
}

void imprimir_arvore_MENUAG(TAG* tag){
    imprimirArquivo_AG_DOT(tag,"arvore_AG.dot");
    system("dot -Tps arvore_AG.dot -o arvore_AG.pdf");
    system("xdg-open arvore_AG.pdf");
}

TAG* inserir_figura_MENUAG(TAG* tag, myTypeCmpFunc pCmpFunc, int tipo){
    limpar_janela01();

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
    
    scanf(" %s",nome_fig);
    
    if(0==strcmp(nome_fig, "CIR")){
        num_case=1;
    }
    if(0==strcmp(nome_fig, "QUA")){
        num_case=2;
    }
    if(0==strcmp(nome_fig, "TRI")){
        num_case=3;        
    }
    if(0==strcmp(nome_fig, "RET")){
        num_case=4;        
    }
    if(0==strcmp(nome_fig, "TRA")){
        num_case=5;
    }

    int* parameters = cria_parameters_TFIG(nome_fig); 
        
    switch(num_case){
        case 1: //Circulo
                printf("\t(>) Insira Raio:\n");
                printf("\t  (ex: 3 )\n");
                printf("\t  (ex: 1 )\n");
                printf("\t>>     ");
                scanf(" %d",&parameters[0]);
                break;

        case 2: //Quadrado
                printf("\t(>) Insira lado: \n");
                printf("\t  (ex: 9 )\n");
                printf("\t  (ex: 2 )\n");
                printf("\t>>     ");
                scanf(" %d",&parameters[0]);
                break;        

        case 3: //Triangulo
                printf("\t(>) Insira base e altura: \n");
                printf("\t  (ex: 3 7 )\n");
                printf("\t  (ex: 7 5 )\n");
                printf("\t>>     ");
                scanf(" %d %d",&parameters[0],&parameters[1]);
                break;

        case 4: //Retangulo
                printf("\t(>) Insira base e altura: \n");
                printf("\t  (ex: 9 1 )\n");
                printf("\t  (ex: 7 8 )\n");
                printf("\t>>     ");
                scanf(" %d %d",&parameters[0],&parameters[1]);
                break;

        case 5: //Trapezio
                printf("\t(>) Insira base menor, base maior e altura: \n");
                printf("\t  (ex: 2 8 7 )\n");
                printf("\t  (ex: 6 8 3 )\n");
                printf("\t>>     ");
                scanf(" %d %d %d",&parameters[0],&parameters[1],&parameters[2]);
                break;

        default:
                printf("=======================================================================================\n");
                printf("\n");
                printf("\tERROR: Figura Nao conhecida\n");
                printf("\n");
                printf("=======================================================================================\n");
                break;
    }

    int n_cod;
    while(1){
        printf("\t(>) Insira um codigo para a nova figura: \n");
        printf("\t  (ex: 12 )\n");
        printf("\t  (ex: 16 )\n");
        printf("\t>>     ");
        scanf(" %d",&n_cod);

        void* pInfo = cria_INFO_vacio(n_cod);

        if (buscar_TAG(tag, pInfo, pCmpFunc) == 0){
            break;
        } else {
            printf("\tCodigo de figura em uso\n");
        }
    }

    int n_pai;
    
    if (tipo == 0){
        while(1){
            if (!tag){
                n_pai = 0;
                break;
            } else {
                printf("\t(>) Insira o codigo do pai: \n");
                printf("\t  (ex: 4  )\n");
                printf("\t  (ex: 10 )\n");
                printf("\t>>     ");
                scanf(" %d",&n_pai);

                void* pInfo = cria_INFO_vacio(n_pai);

                if (buscar_TAG(tag, pInfo, pCmpFunc) == 1){
                    break;
                } else {
                    printf("\tCodigo do pai nao encontrado\n");
                }
            }            
        }
    } else {
        while(1){
            n_pai = rand() % 20;
            void* pInfo = cria_INFO_vacio(n_pai);

            if (buscar_TAG(tag, pInfo, pCmpFunc) == 1)
                break;
        }
    }    

    void* info = cria_INFO(n_cod, nome_fig, parameters);
    void* info_pai = cria_INFO_vacio(n_pai);

    tag = insere_AG(tag, info ,info_pai , pCmpFunc);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tFigura inserida!\n");

    limpar_janela02();

    return tag;
}

TAG* retirar_figura_MENUAG(TAG* tag, myTypeCmpFunc pCmpFunc){
    limpar_janela01();

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

    void* pInfo = cria_INFO_vacio(cod_apai);
    void* pInfoNovo = cria_INFO_vacio(cod_npai);
    tag = retira_AG(tag, pInfo, pInfoNovo, pCmpFunc);

    printf("\n");
    printf("\tFigura retirada!\n");

    limpar_janela02();

    return tag;
}

TAG* destroi_arvore_MENUAG(TAG* tag){
    limpar_janela01();

    printf("(e) Destruir árvore\n");
    printf("=======================================================================================\n");

    tag = destruir_tudo_AG(tag);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tÁrvore destruido!\n");

    limpar_janela02();

    return tag;
}

void alterar_dimensoes(TAG* tag, int cod_buscado){
    if (!tag) return;
    int cod = ler_cod_INFO(tag->info);
    if (cod == cod_buscado){
        char* nome = ler_nome_INFO(tag->info);

        char* n_nome;
        strcpy(n_nome,nome);

        int* parameters = cria_parameters_TFIG(nome);

        if (strcmp(nome,"TRI") == 0){
            printf("\tCodigo pertencente a TRI\n");
            printf("\t(>) Insira nova base e nova altura: \n");
            printf("\t  (ex: 3 7 )\n");
            printf("\t  (ex: 7 5 )\n");
            printf("\t>>     ");
            scanf(" %d %d",&parameters[0],&parameters[1]);            
        }
        else if (strcmp(nome,"RET") == 0){
            printf("\tCodigo pertencente a RET\n");
            printf("\t(>) Insira nova base e nova altura: \n");
            printf("\t  (ex: 4 8  )\n");
            printf("\t  (ex: 3 10 )\n");
            printf("\t>>     ");
            scanf(" %d %d",&parameters[0],&parameters[1]);
        }
        else if (strcmp(nome,"TRA") == 0){
            printf("\tCodigo pertencente a TRA\n");
            printf("\t(>) Insira nova base menor, nova base mayor e nova altura: \n");
            printf("\t  (ex: 5 9 15 )\n");
            printf("\t  (ex: 3 5 8  )\n");
            printf("\t>>     ");
            scanf(" %d %d %d",&parameters[0],&parameters[1],&parameters[2]);
        }
        else if (strcmp(nome,"CIR") == 0){
            printf("\tCodigo pertencente a CIR\n");
            printf("\t(>) Insira novo raio: \n");
            printf("\t  (ex: 3 )\n");
            printf("\t  (ex: 7 )\n");
            printf("\t>>     ");
            scanf(" %d",&parameters[0]);
        }
        else if (strcmp(nome,"QUA") == 0){
            printf("\tCodigo pertencente a QUA\n");
            printf("\t(>) Insira novo lado: \n");
            printf("\t  (ex: 8  )\n");
            printf("\t  (ex: 10 )\n");
            printf("\t>>     ");
            scanf(" %d",&parameters[0]);
        }

        mudarTipo_INFO(tag->info, n_nome, parameters);
    }
    alterar_dimensoes(tag->primFilho, cod_buscado);
    alterar_dimensoes(tag->proxIrmao, cod_buscado);
}



void alterar_dim_figura_MENUAG(TAG* tag, myTypeCmpFunc pCmpFunc){
    limpar_janela01();

    printf("(g) Alterar dimensões das figuras\n");
    printf("=======================================================================================\n");    

    int cod;
    while(1){
        printf("\t(>) Insira código da figura:\n");
        printf("\t  (ex: 6 )\n");
        printf("\t  (ex: 4 )\n");
        
        char codigo[10];
        printf("\t>>     ");
        scanf(" %s",codigo);    

        cod = atoi(codigo);

        void* pInfo = cria_INFO_vacio(cod);

        if (buscar_TAG(tag, pInfo, pCmpFunc) == 1){
            break;
        } else {
            printf("\tCodigo de figura nao encontrado\n");
        }
    }

    alterar_dimensoes(tag, cod);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tDimensões alteradas!\n");

    limpar_janela02();
}

void alterar_tipo_figura_MENUAG(TAG* tag, myTypeCmpFunc pCmpFunc){
    limpar_janela01();

    printf("(f) Alterar tipo de figura\n");
    printf("=======================================================================================\n");    

    int cod;
    while(1){
        printf("\t(>) Insira código da figura:\n");
        printf("\t  (ex: 6 )\n");
        printf("\t  (ex: 4 )\n");
        
        char codigo[10];
        printf("\t>>     ");
        scanf(" %s",codigo);    

        cod = atoi(codigo);

        void* pInfo = cria_INFO_vacio(cod);

        if (buscar_TAG(tag, pInfo, pCmpFunc) == 1){
            break;
        } else {
            printf("\tCodigo de figura nao encontrado\n");
        }
    }

    char nome_fig[10];
    while(1){
        printf("\t(>) Insira o novo nome da figura:\n");
        printf("\t  (ex: CIR )\n");
        printf("\t  (    QUA )\n");
        printf("\t  (    TRI )\n");
        printf("\t  (    RET )\n");
        printf("\t  (    TRA )\n");
        printf("\t>>     ");

        scanf(" %s",nome_fig);

        if (verifica_nome_INFO(nome_fig)==1)
            break;
    }

    TAG** ppNo = (TAG**) malloc(sizeof(TAG*));
    void* pInfo = cria_INFO_vacio(cod);

    localizaEndereco_AG(tag, pInfo, ppNo, pCmpFunc);
    TFIG* fig = (struct figure*)((*ppNo)->info);
    strcpy(fig->nome,nome_fig);

    alterar_dimensoes(tag, cod);

    printf("=======================================================================================\n");
    printf("\n");
    printf("\tDimensões alteradas!\n");

    limpar_janela02();  
}


/*********************************************************************************************/
/***************************************** ARVORE AVL ****************************************/
/*********************************************************************************************/

typedef struct arvoreAVL{
    void* info;
    struct arvoreAVL *esq;
    struct arvoreAVL *dir;
    int alt;
} TAVL;

TAVL *inicializa_AVL(){
  return NULL;
}

TAVL* cria_nodo_AVL(void* info){
    TAVL* novo = (TAVL*) malloc(sizeof(TAVL));
    novo->info = info; 
    novo->esq = NULL;
    novo->dir = NULL;
    novo->alt = 0;
    return novo;
}

static int calc_alt_AVL(TAVL* m){
    if( m == NULL ) return -1;
    return m->alt;
}

static int max_AVL( int l, int r){
    return l > r ? l: r;
}

static TAVL* rot_dir_AVL( TAVL* k2 ){
    TAVL* k1 = NULL;
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
    k2->alt = max_AVL( calc_alt_AVL( k2->esq ), calc_alt_AVL( k2->dir ) ) + 1;
    k1->alt = max_AVL( calc_alt_AVL( k1->esq ), k2->alt ) + 1;
    return k1; /* nova raiz */
}

static TAVL* rot_esq_AVL( TAVL* k1 ){
    TAVL* k2;
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
    k1->alt = max_AVL( calc_alt_AVL( k1->esq ), calc_alt_AVL( k1->dir ) ) + 1;
    k2->alt = max_AVL( calc_alt_AVL( k2->dir ), k1->alt ) + 1;
    return k2;  /* nova raiz */
}

static TAVL* rot_esq_dir_AVL( TAVL* k3 ){
    k3->esq = rot_esq_AVL( k3->esq );
    return rot_dir_AVL( k3 );
}

static TAVL* rot_dir_esq_AVL( TAVL* k1 ){
    k1->dir = rot_dir_AVL( k1->dir );
    return rot_esq_AVL( k1 );
}

TAVL* insere_AVL(void* info, TAVL* tavl, myTypeCmpFunc pMaiorQue, myTypeCmpFunc pMenorQue){    
    if (tavl == NULL){        
        tavl = cria_nodo_AVL(info);     
    }    ///***********************
    else if (pMenorQue(info,tavl->info) == 1){ 
        tavl->esq = insere_AVL(info, tavl->esq, pMaiorQue, pMenorQue );
        if( calc_alt_AVL( tavl->esq ) - calc_alt_AVL( tavl->dir ) == 2 )
            if( pMenorQue(info,tavl->esq->info) == 1 )
                tavl = rot_dir_AVL( tavl );
            else
                tavl = rot_esq_dir_AVL( tavl );
    } else if (pMaiorQue(info,tavl->info) == 1){//////////--------****
        tavl->dir = insere_AVL(info, tavl->dir, pMaiorQue, pMenorQue);
        if( calc_alt_AVL( tavl->dir ) - calc_alt_AVL( tavl->esq ) == 2 )
            if( pMaiorQue(info,tavl->dir->info) == 1)
                tavl = rot_esq_AVL( tavl );
            else
                tavl = rot_dir_esq_AVL( tavl );
    }
    tavl->alt = max_AVL( calc_alt_AVL( tavl->esq ), calc_alt_AVL( tavl->dir ) ) + 1;
    return tavl;
}

TAVL* transforma_para_AVL(TAG* tag, TAVL* tavl){
    if (!tag) return tavl;
    myTypeCmpFunc pMaior_que = maior_que_INFO;
    myTypeCmpFunc pMenor_que = menor_que_INFO;
    tavl = insere_AVL(tag->info,tavl, pMaior_que, pMenor_que);
    tavl = transforma_para_AVL(tag->primFilho, tavl);
    tavl = transforma_para_AVL(tag->proxIrmao, tavl);
    return tavl; 
}

void imprimirInfoAVLDOT(TAVL* tavl, FILE *fp){
    if (!tavl) return;

    int cod = ler_cod_INFO(tavl->info);
    char* nome = ler_nome_INFO(tavl->info);
    int* parameters = ler_parameters_INFO(tavl->info);
    double area = ler_area_INFO(tavl->info);

    if (strcmp(nome,"TRI") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                cod,cod,nome,parameters[0],parameters[1],area);
    else if (strcmp(nome,"RET") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                cod,cod,nome,parameters[0],parameters[1],area);
    else if (strcmp(nome,"TRA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|b: %d, B: %d, h: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                cod,cod,nome,parameters[0],parameters[1],parameters[2],area);
    else if (strcmp(nome,"CIR") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|r: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                cod,cod,nome,parameters[0],area);
    else if (strcmp(nome,"QUA") == 0)
        fprintf(fp, "%d [shape=record,label=\"{<f0> COD:%d |{%s|l: %d|Area: %.2f }|{<f1> Esq|<f2> Dir}}\"];\n",
                cod,cod,nome,parameters[0],area);
    
    imprimirInfoAVLDOT(tavl->esq, fp);
    imprimirInfoAVLDOT(tavl->dir, fp);    
}

void imprimirEsqAVLDOT(TAVL* tavl, FILE *fp){
    if (!tavl){
        return;
    } 
    if (tavl->esq){
        fprintf(fp, "%d:f1 -> %d;\n", ler_cod_INFO(tavl->info), ler_cod_INFO(tavl->esq->info));    
    }
    imprimirEsqAVLDOT(tavl->esq, fp);
    imprimirEsqAVLDOT(tavl->dir, fp);    
}

void imprimirDirAVLDOT(TAVL* tavl, FILE *fp){
    if (!tavl){
        return;
    } 
    if (tavl->dir){
        fprintf(fp,"%d:f2 -> %d;\n", ler_cod_INFO(tavl->info), ler_cod_INFO(tavl->dir->info));    
    }
    imprimirDirAVLDOT(tavl->dir,fp);    
    imprimirDirAVLDOT(tavl->esq,fp);
}

void imprimirArquivo_AVL_DOT(TAVL* tavl, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp,"digraph structs {\n");
    fprintf(fp,"nodesep=.5;\n");
    fprintf(fp,"node [shape=record];\n");
    imprimirInfoAVLDOT(tavl,fp);
    fprintf(fp, "\n" );
    imprimirEsqAVLDOT(tavl, fp);
    fprintf(fp, "\n" );
    imprimirDirAVLDOT(tavl, fp);
    fprintf(fp, "}" );

    fclose(fp);
}

void imprimir_arvore_menuAVL(TAVL* tavl){    
    imprimirArquivo_AVL_DOT(tavl,"arvoreAVL.dot");
    system("dot -Tps arvoreAVL.dot -o arvoreAVL.pdf");
    system("xdg-open arvoreAVL.pdf");
}

void libera_AVL(TAVL* tavl){
    if( tavl != NULL ){
        libera_AVL( tavl->esq );
        libera_AVL( tavl->dir );
        free( tavl );
    } 
}

TAVL* gerar_arvore_menuAVL(TAG* tag, TAVL* tavl, myTypeCmpFunc pCmpFunc){
    tavl = transforma_para_AVL(tag, tavl);
    imprimirArquivo_AVL_DOT(tavl,"arvoreAVL.dot");
    system("dot -Tps arvoreAVL.dot -o arvoreAVL.pdf");
    system("xdg-open arvoreAVL.pdf");

    char key[2] ;
    while(1){        

        limpar_janela01();
        int salir = 0;
        printf("ÁRVORE AVL: \n");
        printf("\t(a) Inserir novas figuras\n");
        printf("\t(b) Retirar figuras\n");
        printf("\t(c) Imprimir árvore AVL\n");
        printf("\t(d) Imprimir árvore Genérica\n");
        printf("\t(e) Voltar ao Menu principal\n");
        printf("=======================================================================================\n");
        printf("Insira sua opção: \n");
        printf("\t >>  ");
        scanf(" %s",key);
        printf("=======================================================================================\n");

        switch(key[0]) {
            case 'a' :
                tag = inserir_figura_MENUAG(tag, pCmpFunc, 1);
                getchar();
                break;

            case 'b' :
                getchar();
                break;

            case 'c' :
                libera_AVL(tavl);
                tavl = inicializa_AVL();
                tavl = transforma_para_AVL(tag, tavl);
                imprimir_arvore_menuAVL(tavl);
                break;

            case 'd' :
                imprimir_arvore_MENUAG(tag);
                break;

            case 'e' :
                salir = 1;           
                break;            
        }

        if (salir == 1) break;
    }

    limpar_janela02();
    
    return tavl;
}


/*********************************************************************************************/
/****************************************** ARVORE B *****************************************/
/*********************************************************************************************/

/*const int n = 4;

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
}*/




/////////////////////////////////////////////////////////////////////////////////////////////


int main(){

    TAG* tag = inicializa_AG();
    TAVL* tavl;
    //TAB* tab;

    myTypeCmpFunc pCmpFunc = compare_dois_INFO;
    tag = carregaDesde_Arquivo(tag,"data.txt",pCmpFunc);
    if(!tag){
        printf("Arvore nao carregado\n");
    }    

    char key[2] ;
    int sair = 0;
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
        printf("\t(f) Alterar tipo de figura\n");
        printf("\t(g) Alterar dimensões das figuras\n");
        printf("\t(h) Intercambiar figuras\n");
        printf("\t(i) Transformar a árvore genérica numa árvore AVL\n");
        printf("\t(j) Transformar a árvore genérica numa árvore B\n");
        printf("\t(k) Sair do programa\n");
        //printf("\t(i) Cria arvore novo\n");        
        printf("=======================================================================================\n");
        printf("Insira sua opção: \n");
        printf("\t >>  ");
        scanf(" %s",key);
        printf("=======================================================================================\n");

        switch(key[0]) {
            case 'a' :
                buscar_figura_MENUAG(tag, pCmpFunc);
                getchar(); 
                break;

            case 'b' :
                imprimir_arvore_MENUAG(tag);
                break;

            case 'c' :
                tag = inserir_figura_MENUAG(tag, pCmpFunc, 0);
                getchar();
                break;

            case 'd' :                
                tag = retirar_figura_MENUAG(tag, pCmpFunc);
                getchar();
                break;

            case 'e' :
                tag = destroi_arvore_MENUAG(tag);
                getchar();
                break;

            case 'f' :
                alterar_tipo_figura_MENUAG(tag, pCmpFunc);
                getchar();
                break;

            case 'g' :
                alterar_dim_figura_MENUAG(tag, pCmpFunc);
                getchar();
                break;

            case 'i' :
                tavl = inicializa_AVL();
                tavl = gerar_arvore_menuAVL(tag, tavl, pCmpFunc);
                libera_AVL(tavl);
                getchar();
                break;

            case 'k' :
                sair = 1;
                break;
            /*case 'g' :
                if (t2){
                    liberaAVL(t2);
                }
                t2 = NULL;
                t2 = transformar_avl(t,t2);

                imprime_rec(t);
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
                break;*/
            
            default :
                printf("Opcion errada.\n" );
                scanf(" %s",key);
                break;
        }

        if (sair == 1) break;
    }

    tag = destruir_tudo_AG(tag);

    
    //examples trocar
    /*void* info1 = cria_INFO_vacio(1);
    void* info2 = cria_INFO_vacio(37);

    trocar_No_AG(tag,info1,info2,pCmpFunc);
    imprimirArquivo_AG_DOT(tag,"arvore_AG_trocado.dot");


    //example retirar
    void* pInfo = cria_INFO_vacio(4);
    void* pInfoNovo = cria_INFO_vacio(2);
    tag = retira_AG(tag, pInfo, pInfoNovo, pCmpFunc);
    imprimirArquivo_AG_DOT(tag,"arvore_AG_retirado.dot");


    //cambiar elementos
    mudarCod_INFO(tag->info, 999);
    //mudarTipo_INFO(void* info, char* nome, int* parameters );
    imprimirArquivo_AG_DOT(tag,"arvore_AG_cod.dot");



    //example destruir
    tag=destruir_tudo_AG(tag);
    printf("%d \n",tag);
    imprimirArquivo_AG_DOT(tag,"vacio.dot");*/


   

    return 0;

}