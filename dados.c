#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"

Dados D[100000];

void LerArquivo() {
    char linha[100000], texto[100000];
    char *sub, *sub2;
    int campo = 0, i = 0, j, tam, t, a, aspas;
    //memset(&D[i], 0, sizeof(Dados));

    FILE *fp = fopen("pldb.csv", "r");
    if(fp == NULL)
    {
        printf("Nao abriu pldb.csv\n");
        exit(1);
    }
    fscanf (fp, " %[^\n]", linha); // Linha dos nomes das colunas
    //printf("%s\n", linha); // Mostra a linha
    while (fscanf (fp, " %[^\n]", linha)!=EOF)
    {
        //printf("%s\n", linha); // Mostra a linha
        //if(i > 10) break; // testa com os primeiros 20
        campo = 0;
        texto[0] = 0;
        tam = strlen(linha);
        //memset(&D[i], 0, sizeof(Dados));
        for(t = 0; t < tam; t++)
        {
            a = 0;
            aspas = 0;
            while(linha[t] != ',' && t < tam)
            {
                texto[a++] = linha[t++];
                if(t > 0 && linha[t-1] == '\"')
                {
                    //printf("\n\naspas\n\n");
                    //t++;
                    a--;
                    while(linha[t] != '\"' && t < tam)
                    {
                        texto[a++] = linha[t++];
                    }
                    t++;
                }
            }
            texto[a++] = 0;
            switch (campo)
            {
                case 0:
                    strncpy (D[i].Title, texto, 501);
                    break;
                case 1:
                    D[i].Year = atoi(texto);
                    break;
                case 2:
                    strcpy (D[i].Type, texto);
                    break;
                case 4:
                    D[i].Rank = atoi (texto);
                    break;
                case 11:
                    D[i].Users = atoi (texto);
                    break;
                case 14:
                    strncpy (D[i].Creator, texto, 99);
                    break;
                case 16:
                    strncpy (D[i].Website, texto, 99);
                    break;
                case 18:
                    strncpy (D[i].Origin, texto, 99);
                    break;
                case 19:
                    strncpy (D[i].Country, texto, 50);
                    break;
                case 21:
                    strncpy (D[i].Reference, texto, 99);
                    break;
                case 25:
                    strncpy (D[i].Summary, texto, 9999);
                    //if(strchr(sub, '\"') != NULL){
                    //    //printf("aqui\n");
                    //    sub2 = strtok (NULL, "\"");
                    //    strncat (D[i].Summary, sub2, 9999 - strlen(D[i].Summary));
                    //}
                    break;
            }
            campo++;
            //sub = strtok (NULL, ","); // proxima substring separada por,
        }
        i++;
    }
    for(j = 0; j < 4817; j++)
    {
        printf("%s\n %d\n %s\n %d\n %d\n %s\n %s\n %s\n %s\n %s\n %s\n\n",
               D[j].Title, D[j].Year, D[j].Type, D[j].Rank, D[j].Users,
               D[j].Creator, D[j].Website, D[j].Origin,
               D[j].Country, D[j].Reference, D[j].Summary);
    }
    printf("%s\n", D[4817].Summary);
    fclose (fp);
}
