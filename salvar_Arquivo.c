void recorre_AGSALIDA(TAG* tag, FILE *fp){
    if (!tag) return;

    int cod, pai;    
    int* parameters;

    if (ler_cod_INFO(tag->info) == 1){
        cod = 1;
        pai = 0;
        char* nome = ler_nome_INFO(tag->info);
        parameters = ler_parameters_INFO(tag->info);
        if (strcmp(nome,"TRI") == 0) fprintf(fp,"%d/%d/%s %d %d\n",cod,pai,nome,parameters[0],parameters[1]);
        else if (strcmp(nome,"RET") == 0) fprintf(fp,"%d/%d/%s %d %d\n",cod,pai,nome,parameters[0],parameters[1]);
        else if (strcmp(nome,"TRA") == 0) fprintf(fp,"%d/%d/%s %d %d %d\n",cod,pai,nome,parameters[0],parameters[1],parameters[2]);
        else if (strcmp(nome,"CIR") == 0) fprintf(fp,"%d/%d/%s %d\n",cod,pai,nome,parameters[0]);
        else if (strcmp(nome,"QUA") == 0) fprintf(fp,"%d/%d/%s %d\n",cod,pai,nome,parameters[0]);      
    }

    TAG* ant = NULL;
    TAG* pos = NULL;
    if (tag->primFilho){
        pos = tag->primFilho;
        ant = tag;
        cod = ler_cod_INFO(pos->info);
        pai = ler_cod_INFO(ant->info);
        char* nome = ler_nome_INFO(pos->info);        
        parameters = ler_parameters_INFO(pos->info);
        if (strcmp(nome,"TRI") == 0) fprintf(fp,"%d/%d/%s %d %d\n",cod,pai,nome,parameters[0],parameters[1]);
        else if (strcmp(nome,"RET") == 0) fprintf(fp,"%d/%d/%s %d %d\n",cod,pai,nome,parameters[0],parameters[1]);
        else if (strcmp(nome,"TRA") == 0) fprintf(fp,"%d/%d/%s %d %d %d\n",cod,pai,nome,parameters[0],parameters[1],parameters[2]);
        else if (strcmp(nome,"CIR") == 0) fprintf(fp,"%d/%d/%s %d\n",cod,pai,nome,parameters[0]);
        else if (strcmp(nome,"QUA") == 0) fprintf(fp,"%d/%d/%s %d\n",cod,pai,nome,parameters[0]);

        while(pos->proxIrmao){        
            pos = pos->proxIrmao;
            cod = ler_cod_INFO(pos->info);
            char* nome = ler_nome_INFO(pos->info);
            parameters = ler_parameters_INFO(pos->info);
            if (strcmp(nome,"TRI") == 0) fprintf(fp,"%d/%d/%s %d %d\n",cod,pai,nome,parameters[0],parameters[1]);
            else if (strcmp(nome,"RET") == 0) fprintf(fp,"%d/%d/%s %d %d\n",cod,pai,nome,parameters[0],parameters[1]);
            else if (strcmp(nome,"TRA") == 0) fprintf(fp,"%d/%d/%s %d %d %d\n",cod,pai,nome,parameters[0],parameters[1],parameters[2]);
            else if (strcmp(nome,"CIR") == 0) fprintf(fp,"%d/%d/%s %d\n",cod,pai,nome,parameters[0]);
            else if (strcmp(nome,"QUA") == 0) fprintf(fp,"%d/%d/%s %d\n",cod,pai,nome,parameters[0]);
        }
    }        
    
    recorre_AGSALIDA(tag->primFilho,fp);
    recorre_AGSALIDA(tag->proxIrmao,fp);
}

void imprimir_arquivo_AGSALIDA(TAG* tag, char* new_filename){
    FILE *fp = fopen(new_filename, "w");
    if (fp == NULL){
        puts("Arquivo nao abierto\n");
        return;
    }
    recorre_AGSALIDA(tag,fp);

    fclose(fp);
}


///// EJEMPLO EN MAIN 
imprimir_arquivo_AGSALIDA(tag,"salida.txt");

/// (CREALE EN EL MENU PRINCIPAL UNA OPCION QUE SE LLAME "SALVAR ARVORE EM ARQUIVO")

