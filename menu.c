#include <stdio.h>
#include <stdlib.h>
#include <string.h>







void buscar_figuras_geometrica(){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(>) inserir elemento que será buscado .\n" );
    printf("\t  - ingrese coigo de elemento \n" );
    printf("\n\n\n(q) ou otra tecla para voltar. \n" );
    printf("==============================================================================\n");

    char codigo[10];
  
    printf("\t  Inserte codigo: )\n");
    printf("\t  (ex: 9 )\n");
    printf("\t  (ex: 2 )\n");
    printf("\t>>     ");
    scanf("%s",&codigo);

    //hacer codigo para buscar
    printf("te encontre!");

    printf("\n\n\n==============================================================================\n");
    printf("\n\n\n\n\n\nPrecione q y enter para voltar a menu...\n");
    getchar();

}
void imprimir_arvore(){
    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(>) Arvore impreso! .\n" );

    printf("\n\n\n==============================================================================\n");
    printf("\n\n\n\n\n\nPrecione q y enter para voltar a menu...\n");
    getchar();
}



void inserir_nova_figura(){
    char my_arguments[3][6];

    printf("\033[2J");
    printf("\033[1;1H"); 
    printf("(>) inserte nuevo elemento.\n" );
    printf("\t  - se a figura for um círculo ou um quadrado, uma única dimensão será informada. \n" );
    printf("\t  - se a figura for um triângulo ou um retângulo, as duas dimensões informadas serão a base e a altura. \n" );
    printf("\t  - se a figura for um trapézio, três dimensões: base menor, base maior e altura. \n" );
    printf("\n\n\n(q) ou otra tecla para voltar. \n" );
    printf("==============================================================================\n");
    printf("\t Inserte tipo de figura )\n");
    printf("\t  (ex: QUA )\n");
    printf("\t  (    CIR )\n");
    printf("\t  (    TRI )\n");
    printf("\t  (    TRA )\n");
    printf("\t>>     ");
    char nome_fig[10];
    int num_case=-1;
    int num_arg=-1;
    
    scanf("%s",&nome_fig);
    
    if(0==strcmp(nome_fig, "QUA")){
        num_case=1;
        num_arg=1;
    }
    if(0==strcmp(nome_fig, "CIR")){
        num_case=2;
        num_arg=1;
    }
    if(0==strcmp(nome_fig, "TRI")){
        num_case=3;        
        num_arg=2;
    }
    if(0==strcmp(nome_fig, "TRA")){
        num_case=4;
        num_arg=3;
    }
        
    switch(num_case){
        case 1: //quadrado
                printf("\t  Inserte lado: )\n");
                printf("\t  (ex: 9 )\n");
                printf("\t  (ex: 2 )\n");
                printf("\t>>     ");
                scanf(" %s",&my_arguments[0]);
                break;

        case 2: //circulo
                printf("\t  Inserte Ratio: )\n");
                printf("\t  (ex: 3 )\n");
                printf("\t  (ex: 1 )\n");
                printf("\t>>     ");
                scanf(" %s",&my_arguments[0]);
                break;

        case 3: //Triangulo
                printf("\t  Inserte base y altura: )\n");
                printf("\t  (ex: 3 7 )\n");
                printf("\t  (ex: 7 5 )\n");
                printf("\t>>     ");
                scanf(" %s %s",&my_arguments[0],&my_arguments[1]);
                break;

        case 4: //Trapezio
                printf("\t  base menor, base maior e altura: )\n");
                printf("\t  (ex: 9 1 2 )\n");
                printf("\t  (ex: 7 8 3 )\n");
                printf("\t>>     ");
                scanf(" %s %s %s",&my_arguments[0],&my_arguments[1],&my_arguments[2]);
                break;

        default:
                printf("\t\tERROR: tipo no reconhecido\n");
                printf("\n\n\n\n\n\nPrecione enter para voltar a menu...\n");
                getchar();
                break;

    }

    if(num_arg==-1){
        scanf("%s",nome_fig);
        return;
    }
    
    int my_arguments_int[3];
    int i;
    for(i=0;i<num_arg;i++){
        my_arguments_int[i]=atoi(my_arguments[i]);
        //printf("%s\n ",my_arguments[i]);
    }
    
    for(i=0;i<num_arg;i++){
        printf("%d\n ",my_arguments_int[i]);
    }
    //my_arguments_int array de enteros 
    //num_arg = numero de argumentos usados
    //aqui tengo lista de argumentos listo para ser manipulados
    //funcion insetar aqui

    printf("\n\n\n\n\n\nPrecione q y enter para voltar a menu...\n");
    getchar();

}

void retirar_figura(){
    
    return;
}

void destruir_arvore(){
    return;
}

void alterar_dimensoes_figura(){
    return;
}

void transformar_avl(){

    return ;
}

void tranformar_b(){

    return ;
}





int main(){
    int i;
    char key[2] ;
    while(1){
        printf("\033[2J");
        printf("\033[1;1H"); 
        //printf("Elija su opcion: \e[31mRed\n");
        printf("\t\t\t\t\e[31m@Roger Ripas && @Luigy Machaca \e[00m \n");
        printf("=======================================================================================\n");
        printf("ARVOL GENERICO DE BUSQUEDA: \n");
        printf("\t(a) buscar figuras geométricas\n");
        printf("\t(b) imprimir da árvore \n");
        printf("\t(c) inserir novas figuras\n");
        printf("\t(d) retirar figuras, passando seus descendentes para outro pai\n");
        printf("\t(e) destruir a árvore\n");
        printf("\t(f) alterar as dimensões de figuras\n");
        printf("\t(g) transformar a árvore genérica numa AVL\n");
        printf("\t(h) transformar a árvore genérica numa árvore B\n");
        printf("=======================================================================================\n");
        printf("Insira sua opção: \n");
        printf("\t >>  ");
        scanf("%s",&key);
        printf("=======================================================================================\n");

  
        //char elem[20];
        switch(key[0]) {
            case 'a' :
                buscar_figuras_geometrica();
                //scanf("%s",&elem);
                getchar(); 
                break;

            case 'b' :
                imprimir_arvore();
                //scanf("%s",&elem);
                getchar();
                break;
            case 'c' :
                inserir_nova_figura();
                //scanf("%s",&elem);
                getchar();
                break;
            case 'd' :
                retirar_figura();
                //scanf("%s",&elem);
                getchar();
                break;
            case 'e' :
                destruir_arvore();
                //scanf("%s",&elem);
                getchar();
                break;
            case 'f' :
                alterar_dimensoes_figura();
                //scanf("%s",&elem);
                getchar();
                break;
            case 'g' :
                transformar_avl();
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
                scanf("%s",&key);
                //getchar();
                //i=getchar();
                //system("pause");
                break;
        }
    }
    return 0;
}