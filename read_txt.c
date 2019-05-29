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
            else if (k == 1) v[tam].pai = atoi(item);
            k++;
            j = 0;
            continue;
        }
        if (ch == ' '){
            if (k == 2) strcpy(v[tam].nom,item);
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

int main()
{
    TFIG *v = read_txt("ag.txt");

    for(int l=0; l<tam; l++){
        printf("COD: %d - PAI: %d - NOM: %s - PAR1: %d - PAR2: %d - PAR3: %d\n", v[l].cod, v[l].pai, v[l].nom, v[l].param1, v[l].param2, v[l].param3);
    }

    free(v);

    return 0;
}
