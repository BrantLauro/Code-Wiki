#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"
#include "interface.h"

Dados D[100000];
Dados H[TAM];

void Inicializar(Dados H[]) {
    int i;
    for(i = 0; i < TAM; i++)
       strcpy(H[i].Title, "");
}

int HashString(char str[]) {
    int i, TamS = strlen(str);
    unsigned int h = 0;
    for(i = 0; i < TamS; i++)
        h += str[i] * (i + 1);
    return h % TAM;
}

int Hash(int chave){
    return chave % TAM;
}

void Inserir(Dados H[], Dados P){
    int id = HashString(P.Title);
    while(strlen(H[id].Title) > 0){
        id = Hash(id + 1);
    }
    H[id] = P;
}

Dados* Busca(char Chave[]){
    int id = HashString(Chave);
    while(strlen(H[id].Title) > 0){
        if(strcmp(H[id].Title, Chave) == 0)
            return &H[id];
        else
            id = Hash(id + 1);
    }
    return NULL;
}

/*void Imprimir(Dados D){
	printf("%s\n", D.Title);
	printf("%d\n", D.Year);
	printf("%s\n", D.Type);
	printf("%d\n", D.Rank);
	printf("%d\n", D.Users);
	printf("%s\n", D.Creator);
	printf("%s\n", D.Website);
	printf("%s\n", D.Origin);
	printf("%s\n", D.Country);
	printf("%s\n", D.Reference);
	printf("%s\n", D.Summary);
}*/

void Imprimir(Dados D) {
    Borda(0, 0, 118, 28, 1, 0);
    Borda(30, 1, 60, 2, 0, 0);
    GotoXY(55, 2); printf("Resultado:");
    Borda(3, 4, 112, 2, 0, 0);
    GotoXY(4, 5); printf("Titulo: %s\t\tType: %s\t\tYear: %d\t\tRank: %d\t\tUsers: %d", D.Title, D.Type, D.Year, D.Rank, D.Users);
    Borda(3, 7, 112, 2, 0, 0);
    GotoXY(4, 8); printf("Criador: %s\t\tOrigem: %s\t\tPais: %s", D.Creator, D.Origin, D.Country);
    Borda(3, 10, 112, 2, 0, 0);
    GotoXY(6, 11); printf("Site: %s", D.Website);
    GotoXY(43, 11); printf("Refer.: %s", D.Reference);
    Borda(3, 13, 112, 11, 0, 0);
    GotoXY(4, 14); printf("%s", D.Summary);
    Borda(15, 25, 90, 2, 0,0);
    GotoXY(16, 26);
    system("PAUSE");
}

void LerArquivo() {
    Inicializar(H);
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
        Inserir(H, D[i]);
        i++;
    }
    /*for(j = 0; j < 10; j++)
    {
        printf("%s\n %d\n %s\n %d\n %d\n %s\n %s\n %s\n %s\n %s\n %s\n\n",
               D[j].Title, D[j].Year, D[j].Type, D[j].Rank, D[j].Users,
               D[j].Creator, D[j].Website, D[j].Origin,
               D[j].Country, D[j].Reference, D[j].Summary);
    }
    printf("%s\n", D[4817].Summary);*/
    fclose (fp);
}
