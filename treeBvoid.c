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
/************************************** struct FIGURE  ***************************************/
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



int maior_igual_que_TFIG(TFIG* fig1, TFIG* fig2){
    if(!fig1 || !fig2)
        return -1;
    if(fig1->cod >= fig2->cod){
        return 1;
    }
    else{
        return 0;
    }
}

int menor_igual_que_TFIG(TFIG* fig1, TFIG* fig2){
    if(!fig1 || !fig2)
        return -1;
    if(fig1->cod <= fig2->cod){
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


int maior_igual_que_INFO(void* info1, void* info2){
    if(!info1 || !info2){
        return -1;
    }
    TFIG* myfig1=(struct figure*)(info1);
    TFIG* myfig2=(struct figure*)(info2);
    return maior_igual_que_TFIG(myfig1, myfig2);
}

int menor_igual_que_INFO(void* info1, void* info2){
    if(!info1 || !info2){
        return -1;
    }
    TFIG* myfig1=(struct figure*)(info1);
    TFIG* myfig2=(struct figure*)(info2);
    return menor_igual_que_TFIG(myfig1, myfig2);
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


//*****************************************************************************/
//*****************************************************************************/
//*****************************************************************************/
//*****************************************************************************/




typedef struct ArvB{
  int nchaves, folha; 
  void** chave;
  struct ArvB **filho;
}TAB;


TAB *Cria(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(void*)malloc(sizeof(void*)*((t*2)-1));
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*t*2);
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  return novo;
}


TAB *Libera(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->filho);
    free(a);
    return NULL;
  }
}


void Imprime(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", ler_cod_INFO(a->chave[i]) );
    }
    Imprime(a->filho[i],andar+1);
  }
}


TAB *Busca(TAB* x, void* ch){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while( i < x->nchaves && maior_que_INFO(ch, x->chave[i])==1) i++;
  if( i < x->nchaves && compare_dois_INFO(ch ,x->chave[i])==1) return x;
  if(x->folha) return resp;
  return Busca(x->filho[i], ch);
}


TAB *Inicializa(){
  return NULL;
}


TAB *Divisao(TAB *x, int i, TAB* y, int t){
  TAB *z=Cria(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}


TAB *Insere_Nao_Completo(TAB *x, void* k, int t){
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
  while((i>=0) && ( menor_que_INFO(k,x->chave[i])==1 )) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(maior_que_INFO(k,x->chave[i])==1) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t);
  return x;
}


TAB *Insere(TAB *T, void* k, int t){
  if(Busca(T,k)) return T;
  if(!T){
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t);
  return T;
}


TAB* remover(TAB* arv, void* ch, int t){
  if(!arv) return arv;
  int i;
  printf("Removendo %d...\n", ler_cod_INFO(ch));
  for(i = 0; i<arv->nchaves && menor_que_INFO(arv->chave[i],ch)==1; i++);
  if(i < arv->nchaves && compare_dois_INFO(ch,arv->chave[i])==1){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;      
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
      printf("\nCASO 2A\n");
      TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      void* temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t); 
      //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[0];
      void* temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
      printf("\nCASO 2C\n");
      TAB *y = arv->filho[i];
      TAB *z = arv->filho[i+1];
      y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
      int j;
      for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
        y->chave[t+j] = z->chave[j];
      for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
        y->filho[t+j] = z->filho[j];
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
        arv->chave[j] = arv->chave[j+1];
      for(j=i+1; j <= arv->nchaves; j++)  //remover ponteiro para filho[i+1]
        arv->filho[j] = arv->filho[j+1];
      arv->filho[j] = NULL; //Campello
      arv->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;   
    }   
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i] = z->chave[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        z->chave[j] = z->chave[j+1];
      //z->chave[j] = 0; Rosseti
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        y->chave[j] = y->chave[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){ 
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, void* k, int t){
  if(!arv || !Busca(arv, k)) return arv;
  return remover(arv, k, t);
}





void imprimeInfoB(TAB *a, int andar, FILE *fp, int mynum, int t){
  if(a){
    int i,j;
    int pchaves=(t*2);
    fprintf(fp, "%d%d [shape=record,label=\"{{",andar,mynum*pchaves);
    for (i=0; i<pchaves-1; i++){
        fprintf(fp,"<f%d>",i+(mynum*pchaves));
        if (i<=a->nchaves-1){
            fprintf(fp,"| %d |", ler_cod_INFO(a->chave[i]));
        } else {
            fprintf(fp,"| - |");
        }
    }
    fprintf(fp,"<f%d>}}\"];\n",i+(mynum*pchaves));
    j=0;
    for(i=0; i<(t*2); i++){
        imprimeInfoB(a->filho[i], andar+1, fp, i+(mynum*pchaves),t);
    }
  }
}

void imprimeFlechaB(TAB *a, int andar, FILE *fp, int mynum, int t){
  if(a){
    int i,j;
    int pchaves=(t*2);

    for (i=0; i<pchaves; i++){
        if(a->filho[i]){
            fprintf(fp,"%d%d:<f%d> -> %d%d:<f%d>;\n", andar, mynum*pchaves, i+(mynum*pchaves), andar+1, (i+(mynum*pchaves))*pchaves , (i+(mynum*pchaves))*pchaves );  
        }
    }
    for(i=0; i<pchaves; i++){
        imprimeFlechaB(a->filho[i],andar+1,fp,i+(mynum*pchaves),t);  
    }
  }
}

void imprimir_arquivoB(TAB* t3, char* new_filename, int grado){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    fprintf(fp,"digraph structs {\n");
    fprintf(fp,"nodesep=.5;\n");
    fprintf(fp,"node [shape=record];\n");
    imprimeInfoB(t3,0,fp,0,grado);
    fprintf(fp, "\n");
    imprimeFlechaB(t3,0,fp,0,grado);
    fprintf(fp, "}" );

    fclose(fp);
}







int main(int argc, char *argv[]){
  int grado=2;
  TAB * arvore = Inicializa();
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%i", &num);
    if(num == -9){
      scanf("%d", &from);
      void* temp=cria_INFO_vacio(from);
      arvore = retira(arvore, temp, grado);
      Imprime(arvore,0);
    }
    else if(num == -1){
      printf("\n");
      Imprime(arvore,0);
      Libera(arvore);
      return 0;
    }
    else if(!num){
      printf("\n");
      Imprime(arvore,0);
      imprimir_arquivoB(arvore,"arvoreBB.dot",grado);

    }
    else {
      void* temp=cria_INFO_vacio(num);
      arvore = Insere(arvore, temp, grado);
    }
    printf("\n\n");
  }
}