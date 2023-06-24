#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"

Dados D[100000];

void LerArquivo() {
    char linha[100000];
    char *sub;
    int campo = 0, i = 0, j;

    FILE *fp = fopen("C:\\Users\\brant\\OneDrive\\Documentos\\projetos\\Code-Wiki\\pldb.csv", "r");
    if(fp == NULL) {
        printf("Nao abriu pldb.csv\n");
        exit(1);
    }
    fscanf (fp, " %[^\n]", linha); // Linha dos nomes das colunas
    //printf("%s\n", linha); // Mostra a linha
    while (fscanf (fp, " %[^\n]", linha)!=EOF) {
        campo = 0;
        sub = strtok (linha, ","); // 1a. substring antes da ,
        while (sub!= NULL) {
            switch (campo) {
                case 0:
                    strncpy (D[i].Title, sub, 50);
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
                    strncpy (D[i].Creator, sub, 99);
                    break;
                case 15:
                    strncpy (D[i].Website, sub, 99);
                    break;
                case 17:
                    strncpy (D[i].Origin, sub, 99);
                    break;
                case 18:
                    strncpy (D[i].Country, sub, 50);
                    break;
                case 20:
                    strncpy (D[i].Reference, sub, 99);
                    break;
                case 24:
                    strncpy (D[i].Summary, sub, 9999);
                    break;
            }
            campo++;
            sub = strtok (NULL, ","); // proxima substring separada por,
        }
        i++;
    }
    for(j = 0; j < 40; j++) {
        printf("%s %d %s %d %d %s %s %s %s %s %s\n",
               D[j].Title, D[j].Year, D[j].Type, D[j].Rank, D[j].Users, D[j].Creator, D[j].Website, D[j].Origin,
               D[j].Country, D[j].Reference, D[j].Summary);
    }
    fclose (fp);
}
