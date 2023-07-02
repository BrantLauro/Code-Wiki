#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"
#include "interface.h"

//Dados H[TAM];
Dados LD[1000];
FILE *fp;


void AbrirArquivo() {
    Dados Dado;
    fp = fopen("dados.txt","rb+");
    if(fp == NULL){
        strcpy(Dado.Title, "");
        Dado.Year = 0;
        strcpy(Dado.Type, "");
        Dado.Rank = 0;
        Dado.Users = 0;
        strcpy(Dado.Creator, "");
        strcpy(Dado.Website, "");
        strcpy(Dado.Origin, "");
        strcpy(Dado.Country, "");
        strcpy(Dado.Reference, "");
        strcpy(Dado.Summary, "");
        Dado.prox = 0;
        fp = fopen("dados.txt","wb+");
        if(fp == NULL){
            printf("[ERROR] O programa nao conseguiu abrir o arquivo.");
            exit(1);
        }
        fseek(fp, 0, SEEK_SET);
        for(int i = 0; i < 6011; i++) {
            fwrite(&Dado, sizeof(Dados), 1, fp);
        }
        fflush(fp);
    }
}

void FecharArquivo() {
    fclose(fp);
}

void GravarArquivo(Dados D) {
    int pos = HashString(D.Title), iaux;
    Dados aux;
    fseek(fp, pos * sizeof(Dados), SEEK_SET);
    fread(&aux, sizeof(Dados), 1, fp);
    if(strcmp(aux.Title, "") == 0) {
        fseek(fp, 0, SEEK_END);
        iaux = ftell(fp);
        D.prox = iaux;
        fwrite(&aux, sizeof(Dados), 1, fp);
        fseek(fp, pos * sizeof(Dados), SEEK_SET);
        fwrite(&D, sizeof(Dados), 1, fp);
    }
    else {
        D.prox = 0;
        fwrite(&D, sizeof(Dados), 1, fp);
    }
    fflush(fp);
}

Dados Buscar(char Chave[]){
    Dados dados;
    int id = HashString(Chave);
    fseek(fp, id * sizeof(Dados), SEEK_SET);
    while(fread(&dados, sizeof(Dados), 1, fp)  ) { // Lê o ponteiro da lista encadeada correspondente à posição hash
        if (strcmp(dados.Title, Chave) == 0) {
            return dados;
        }
        id = dados.prox; // Avança para o próximo nó da lista
        if(id == 0) break;
        fseek(fp, id * sizeof(Dados), SEEK_SET);
    }
    strcpy(dados.Title, "");
    return dados; // Title vazio se não encontrou.
}

int HashString(char str[]) {
    int i, TamS = strlen(str);
    int h = 0;
    for(i = 0; i < TamS; i++)
        h += str[i] * (i + 1);
    return h % TAM;
}

void Imprimir(Dados D) {
    char buffer[1000000]; char *p; char *b; char *Opcoes[100];
    int ContOpcoes = 0;
    Borda(0, 0, 118, 28, 1, 0);
    Borda(15, 25, 90, 2, 0,0);
    Borda(30, 1, 60, 2, 0, 0);
    GotoXY(55, 2); printf("Resultado:");
    Borda(3, 4, 112, 2, 0, 0);
    GotoXY(4, 5); printf("Titulo: %s\t\tType: %s\t\tYear: %d\t\tRank: %d\t\tUsers: %d", D.Title, D.Type, D.Year, D.Rank, D.Users);
    Borda(3, 7, 112, 2, 0, 0);
    GotoXY(4, 8); printf("Criador: %s\t\tOrigem: %s\t\tPais: %s", D.Creator, D.Origin, D.Country);
    Borda(3, 10, 112, 2, 0, 0);
    GotoXY(4, 11); printf("Site: %s", D.Website);
    GotoXY(45, 11); printf("Refer.: %s", D.Reference);
    Borda(3, 13, 112, 11, 0, 0);
    b = word_wrap (buffer, D.Summary, 112);
    p = strtok(buffer, "\n");
    for(int i = 0; p != NULL; i++){
        GotoXY(4, 14 + i);
        Opcoes[ContOpcoes++] = p;
        p = strtok(NULL, "\n");
    }
    Selecao(4, 14, 112, 10, Opcoes, ContOpcoes);
    GotoXY(16, 26);
    system("PAUSE");
}

void LerArquivo() {
    char linha[100000], texto[100000];
    int campo = 0, i = 0, j, tam, t, a, aspas;
    FILE *fporigin = fopen("pldb.csv", "r");
    if(fporigin == NULL) {
        printf("Nao abriu pldb.csv\n");
        exit(1);
    }
    fscanf (fporigin, " %[^\n]", linha);
    while (fscanf (fporigin, " %[^\n]", linha)!=EOF) {
        campo = 0;
        texto[0] = 0;
        tam = strlen(linha);
        for(t = 0; t < tam; t++) {
            a = 0;
            aspas = 0;
            while(linha[t] != ',' && t < tam) {
                texto[a++] = linha[t++];
                if(t > 0 && linha[t-1] == '\"') {
                    a--;
                    while(linha[t] != '\"' && t < tam) {
                        texto[a++] = linha[t++];
                    }
                    t++;
                }
            }
            texto[a++] = 0;
            switch(campo) {
                case 0:
                    strncpy (LD[i].Title, texto, 501);
                    break;
                case 1:
                    LD[i].Year = atoi(texto);
                    break;
                case 2:
                    strcpy (LD[i].Type, texto);
                    break;
                case 4:
                    LD[i].Rank = atoi (texto);
                    break;
                case 11:
                    LD[i].Users = atoi (texto);
                    break;
                case 14:
                    strncpy (LD[i].Creator, texto, 99);
                    break;
                case 16:
                    strncpy (LD[i].Website, texto, 99);
                    break;
                case 18:
                    strncpy (LD[i].Origin, texto, 99);
                    break;
                case 19:
                    strncpy (LD[i].Country, texto, 50);
                    break;
                case 21:
                    strncpy (LD[i].Reference, texto, 99);
                    break;
                case 25:
                    strncpy (LD[i].Summary, texto, 9999);
                    break;
            }
            campo++;
        }
        GravarArquivo(LD[i]);
        i++;
    }
    fclose (fporigin);
}
