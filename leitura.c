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


TFIG** v = NULL;
int tam = 0;

TFIG** cria_vetor(int tam){
	TFIG** v = (TFIG**) malloc(sizeof(TFIG*)*tam);
	for (int i=0; i<tam; i++){
		v[i] = (TFIG*) malloc(sizeof(TFIG));
	}
	for (int i=0; i<tam; i++){
		v[i]->param3 = 0;
	}
	return v;
}

int main(int argc, char* argv[])
{
    char const* const fileName = "data2.txt"; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[50];

    while (fgets(line, sizeof(line), file)) tam++;

    fclose(file);

    v = cria_vetor(tam);

    file = fopen(fileName, "r");

    int i = 0;
    while (fgets(line, sizeof(line), file)){
    	char cad[10] = "";
		int j = 0, k = 0;
		for (int l=0; l<strlen(line); l++){
			if (line[l]== '/' && k == 0){
				int cod = atoi(cad);					
				v[i]->cod = cod;
				k++;
				j = 0;
				memset(&cad[0], 0, sizeof(cad));
				continue;
			} else if (line[l]== '/' && k == 1){
				int pai = atoi(cad);					
				v[i]->pai = pai;
				k++;
				j = 0;
				memset(&cad[0], 0, sizeof(cad));
				continue;
			} else if (line[l]== ' ' && k == 2){
				strcpy(v[i]->nom,cad);
				k++;
				j = 0;
				memset(&cad[0], 0, sizeof(cad));
				continue;
			} else if ((line[l] == ' ' || line[l] == '\n') && k == 3){
				int param1 = atoi(cad);
				v[i]->param1 = param1;
				k++;
				j = 0;
				memset(&cad[0], 0, sizeof(cad));
				continue;
			} else if ((line[l] == ' ' || line[l] == '\n') && k == 4){
				int param2 = atoi(cad);
				v[i]->param2 = param2;
				k++;
				j = 0;
				memset(&cad[0], 0, sizeof(cad));
				continue;
			} else if ((line[l] == ' ' || line[l] == '\n') && k == 5){
				int param3 = atoi(cad);
				v[i]->param3 = param3;
				k++;
				j = 0;
				memset(&cad[0], 0, sizeof(cad));
				continue;
			}

			cad[j] = line[l];
			j++;
		}	
    	i++;
    }

    fclose(file);

    for (int i=0; i<tam; i++){
    	printf("COD: %d - PAI: %d - NOM: %s - P1: %d - P2: %d - P3: %d\n",v[i]->cod,v[i]->pai,v[i]->nom,v[i]->param1,v[i]->param2,v[i]->param3);
    }

    for(int i=0; i<tam; i++) free(v[i]);
    free(v);

	//printf("%d\n",v[0]->cod );

    return 0;
}