#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"

Dados D[10000];

void LerArquivo() {
    char linha[10000];
    char *sub;
    int campo = 0, i = 0, j;

    FILE *fp = fopen("pldb.csv", "r");
    if(fp == NULL) {
        printf("Nao abriu pldb.csv\n");
        exit(1);
    }
    fscanf (fp, " %[^\n]", linha); // Linha dos nomes das colunas
    //printf("%s\n", linha); // Mostra a linha
    while (fscanf (fp, " %[^\n]", linha)!=EOF) {
        //printf("%s\n", linha); // Mostra a linha
        if(i > 20) break; // testa com os primeiros 20
        campo = 0;
        sub = strtok (linha, ","); // 1a. substring antes da ,
        while (sub!= NULL) {
            switch (campo) {
                case 0:
                    strcpy (D[i].Title, sub);
                    break;
                case 1:
                    D[i].Year = atoi(sub);
                    break;
                case 2:
                    strcpy (D[i].Type, sub);
                    break;
                case 4:
                    D[i].Rank = atoi (sub);
                    break;
                case 11:
                    D[i].Users = atoi (sub);
                    break;
                case 14:
                    strcpy (D[i].Creator, sub);
                    break;
                case 15:
                    strcpy (D[i].Website, sub);
                    break;
                case 17:
                    strcpy (D[i].Origin, sub);
                    break;
                case 18:
                    strcpy (D[i].Country, sub);
                    break;
                case 20:
                    strcpy (D[i].Reference, sub);
                    break;
                case 24:
                    strcpy (D[i].Summary, sub);
                    break;
            }
            campo++;
            sub = strtok (NULL, ","); // proxima substring separada por,
        }
        i++;
    }
    for(j = 0; j < 10; j++) {
        printf("%s %d %s %d %d %s %s %s %s %s %s\n",
               D[j].Title, D[j].Year, D[j].Type, D[j].Rank, D[j].Users, D[j].Creator, D[j].Website, D[j].Origin,
               D[j].Country, D[j].Reference, D[j].Summary);
    }
    fclose (fp);
}