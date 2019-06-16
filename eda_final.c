#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* TYPEDEF GERAL FIGURE*/
#define PI 3.1415
#define BUFFER_LINE 50
#define BUFFER_CHAR 10
#define NUM_DIV_INPUT 5
#define TAM_VEC_ 30



typedef struct figure{
  int cod;
  char* nome;
  int* parameters;
  double area;
} TFIG;

typedef int (*myTypeCmpFunc)(void*, void*);


TFIG* inicializa_TFIG(){
    return NULL;
}


void destruir_TFIG(TFIG* fig){
    free(fig->nome);
    free(fig->parameters);
    free(fig);
    return;
} 

int compare_dois_TFIG(void* fig1, void* fig2){
    if(!fig1 || !fig2)
        return -1;
    TFIG* myfig1=(struct figure*)(fig1);
    TFIG* myfig2=(struct figure*)(fig2);
    if(myfig1->cod == myfig2->cod){
        return 1;
    }
    else{
        return 0;
    }
}

int oquetipoe_TFIG(char* nome){
    if(strcmp(nome,"QUA")==0){//QUA
        return 1;
    }
    if(strcmp(nome,"CIR")==0){//CIR
        return 2;
    }
    if(strcmp(nome,"RET")==0){//RET
        return 3;
    }
    if(strcmp(nome,"TRI")==0){//TRI
        return 4;
    }
    if(strcmp(nome,"TRA")==0){//TRA
        return 5;
    }
    return -1; //error
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


int* cria_parameters_TFIG(char* nome){
    if(strlen(nome)<2){
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


int init_parameters_TFIG(TFIG* fig){
    if(!fig){
        return -1; //error
    }
    if(!fig->nome){
        return -1; //error
    }
    int tam = quan_parameters_TFIG(fig->nome);
    if(tam==-1){
        return -1; //error
    }
    fig->parameters=(int*)malloc(sizeof(int)*tam);
    for(int i=0;i<tam;i++){
        fig->parameters[i]=-1;
    }    
    return -1; //error
}


double calcula_area_TFIG(char* nome,int* parameters){
    int qtam = quan_parameters_TFIG(nome);
    if((qtam!=-1))
        return -1.0;
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
        return (double)(parameters[0]+parameters[1])/2.0;
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
    if(!parameters) 
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


/*********************************************************************************************/
/************************************** Interface VOID **************************************/
/*********************************************************************************************/



int ler_cod_INFO(void* fig){
    TFIG* temp=(struct figure*)(fig);
    return ler_cod_TFIG(temp);
}

char* ler_nome_INFO(void* fig){
    TFIG* temp=(struct figure*)(fig);
    return ler_nome_TFIG(temp);
}

int* ler_parameters_INFO(void* fig){
    TFIG* temp=(struct figure*)(fig);
    return ler_parameters_TFIG(temp);
}

double ler_area_INFO(void* fig){
    TFIG* temp=(struct figure*)(fig);
    return calcula_area_TFIG(temp->nome,temp->parameters);
}

void destruir_INFO(void* info){
    TFIG* p = (struct figure*)(info);
    destruir_TFIG(info);
    return;
}


/*********************************************************************************************/
/************************************** ARVORE GENERICA **************************************/
/*********************************************************************************************/

typedef struct arvoreGenerica{
    void* info;
    struct arvoreGenerica* primFilho;
    struct arvoreGenerica* proxIrmao;
} TAG;

void destruir_No_AG(TAG* pNo){
    destruir_INFO(pNo->info);
    pNo->proxIrmao = NULL;
    pNo->proxIrmao = NULL;
    return;
}

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

int localizaEnderecoAntecesor_AG(TAG* tag, void* pInfo, TAG** ppAnt, myTypeCmpFunc pCmpFunc){
    if (!tag) return 0;
    if (tag->proxIrmao && (pCmpFunc(tag->proxIrmao->info,pInfo)==1) ){
        *ppAnt = tag;
        return 1;
    } 
    if (tag->primFilho && (pCmpFunc(tag->primFilho->info,pInfo)==1) ){
        *ppAnt = tag;
        return 1;
    }
    int value=0;//  0 nao encontrado
                //  1 da certo
    value+=localizaEnderecoAntecesor_AG(tag->primFilho, pInfo, ppAnt, pCmpFunc);
    value+=localizaEnderecoAntecesor_AG(tag->proxIrmao, pInfo, ppAnt, pCmpFunc);
    return value;
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
    destruir_No_AG(p1);

    return tag;
}


/*********************************************************************************************/
/************************************** CARREGA ARQUIVO **************************************/
/*********************************************************************************************/

TFIG** cria_vetor_Arquivo(int tam){
	TFIG** vec = (TFIG**) malloc(sizeof(TFIG*)*tam);
	for (int i=0; i<tam; i++){
		vec[i] = NULL;
	}
	return vec;
}

TAG* carregaDesde_Arquivo(TAG* tag, char* fileName, myTypeCmpFunc pCmpFunc){ 
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
    vecFIG  = cria_vetor_Arquivo(tam); // os elementos sao tudos NULL
    vecPais = (int*)malloc(sizeof(int)*tam);

    for(int i=0;i<tam;i++) vecPais[i]=-1; // os elementos sao tudos -1

    file = fopen(fileName, "r");
    while (fgets(line, sizeof(line), file)){
        
        char mat_input[NUM_DIV_INPUT][BUFFER_CHAR];
        for(int i=0;i<NUM_DIV_INPUT;i++){
            memset(mat_input[i], 0, sizeof(mat_input[i]));
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
        if(k<4){
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

    for(int i=0;i<numline;i++){
        TFIG* temp_pai = cria_TFIG_vacio(vecPais[i]);
        tag = insere_AG(tag, vecFIG[i],(void*)temp_pai , pCmpFunc);
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





int main(){

    TAG* tag=NULL;
    myTypeCmpFunc pCmpFunc = compare_dois_TFIG;
    tag = carregaDesde_Arquivo(tag,"data.txt",pCmpFunc);
    if(!tag){
        printf("arvore no carregado\n");
    }
    imprimirArquivo_AG_DOT(tag,"arvore_AG.dot");

    TFIG* pNo = cria_TFIG_vacio(69);
    TFIG* novo = cria_TFIG_vacio(555);

    tag = retira_AG(tag, (void*)pNo, (void*)novo, pCmpFunc);
    imprimirArquivo_AG_DOT(tag,"arvore_AG_retirado.dot");

    return 0;

}