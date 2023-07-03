#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"
#include "interface.h"

FILE *fp;
int HashAcessos;

void AbrirArquivo() {
    Dados Dado;
    fp = fopen("dados.txt","rb+");
    if(fp == NULL){
        strncpy(Dado.Title, "", 50);
        Dado.Year = 0;
        strncpy(Dado.Type, "", 10);
        Dado.Rank = 0;
        Dado.Users = 0;
        strncpy(Dado.Creator, "", 100);
        strncpy(Dado.Website, "", 100);
        strncpy(Dado.Origin, "", 100);
        strncpy(Dado.Country, "", 51);
        strncpy(Dado.Reference, "", 100);
        strncpy(Dado.Summary, "", 10000);
        Dado.prox = 0;
        fp = fopen("dados.txt","wb+");
        if(fp == NULL){
            printf("[ERROR] O programa nao conseguiu abrir o arquivo.");
            exit(1);
        }
        fseek(fp, 0, SEEK_SET);
        for(int i = 0; i < TAM; i++) {
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
    if(strcmp(aux.Title, "") != 0) {
        fseek(fp, 0, SEEK_END);
        iaux = ftell(fp);
        D.prox = iaux;
        fwrite(&aux, sizeof(Dados), 1, fp);
        fseek(fp, pos * sizeof(Dados), SEEK_SET);
        fwrite(&D, sizeof(Dados), 1, fp);
    }
    else {
        D.prox = 0;
        fseek(fp, pos * sizeof(Dados), SEEK_SET);
        fwrite(&D, sizeof(Dados), 1, fp);
    }
    fflush(fp);
}

Dados Buscar(char Chave[]){
    Dados dados;
    int id = HashString(Chave);
    int pos = id * sizeof(Dados);
    HashAcessos = 0;
    fseek(fp, pos, SEEK_SET);
    while(fread(&dados, sizeof(Dados), 1, fp)  ) { // Lê o ponteiro da lista encadeada correspondente à posição hash
        HashAcessos++;
        if (strncmp(dados.Title, Chave, strlen(Chave)) == 0) {
            return dados;
        }
        pos = dados.prox; // Avança para o próximo nó da lista
        if(pos == 0) break;
        fseek(fp, pos, SEEK_SET);
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
    char opcoes[][51] = {"Busca Binaria","Fechar" };
    int x[] = {24, 85};
    int y[] = {26, 26};
    char buffer[1000000]; char *p; char *b; char *Opcoes[100];
    int ContOpcoes = 0, escolha = 0;
    do {
        Borda(0, 0, 118, 28, 1, 0);
        //Borda(15, 25, 90, 2, 0, 0);
        Borda(30, 1, 60, 2, 0, 0);
        Borda(18, 25, 25, 2, 0,0);
        Borda(75, 25, 25, 2, 0,0);
        GotoXY(55, 2);
        printf("Resultado:");
        Borda(3, 4, 112, 2, 0, 0);
        GotoXY(4, 5);
        printf("Titulo: %s\t\tType: %s\t\tYear: %d\t\tRank: %d\t\tUsers: %d", D.Title, D.Type, D.Year, D.Rank, D.Users);
        Borda(3, 7, 112, 2, 0, 0);
        GotoXY(4, 8);
        printf("Criador: %s\t\tOrigem: %s\t\tPais: %s", D.Creator, D.Origin, D.Country);
        Borda(3, 10, 112, 2, 0, 0);
        GotoXY(4, 11);
        printf("Site: %s", D.Website);
        GotoXY(45, 11);
        printf("Refer.: %s", D.Reference);
        GotoXY(85, 26); printf("Fechar");
        GotoXY(24, 26); printf("Busca Binaria");
        Borda(3, 13, 112, 11, 0, 0);
        b = word_wrap(buffer, D.Summary, 112);
        p = strtok(buffer, "\n");
        for (int i = 0; p != NULL; i++) {
            GotoXY(4, 14 + i);
            Opcoes[ContOpcoes++] = p;
            p = strtok(NULL, "\n");
        }
        Selecao(4, 14, 112, 10, Opcoes, ContOpcoes);
        GotoXY(16, 26);
        escolha = Menu(opcoes, x, y, escolha, 2);
        if(escolha == 0) {
            TelaBBinaria(D.Rank);
            break;
        }
    } while(escolha != 1);
}

void TelaBBinaria(int chave) {
    Borda(0, 0, 118, 28, 1, 0);
    GotoXY(24, 1); printf("  _   _           _                   ____  _                  _       ");
    GotoXY(24, 2); printf(" | | | | __ _ ___| |__   __   _____  | __ )(_)_ __   __ _ _ __(_) __ _ ");
    GotoXY(24, 3); printf(" | |_| |/ _` / __| '_ \\  \\ \\ / / __| |  _ \\| | '_ \\ / _` | '__| |/ _` |");
    GotoXY(24, 4); printf(" |  _  | (_| \\__ \\ | | |  \\ V /\\__ \\ | |_) | | | | | (_| | |  | | (_| |");
    GotoXY(24, 5); printf(" |_| |_|\\__,_|___/_| |_|   \\_/ |___/ |____/|_|_| |_|\\__,_|_|  |_|\\__,_|");
    Borda(15, 25, 90, 2, 0,0);
    GotoXY(14, 13); printf("Quantidade de Acessos:");
    GotoXY(84, 13); printf("Quantidade de Acessos:");
    Borda(12, 14, 25, 2, 0,0);
    Borda(82, 14, 25, 2, 0,0);
    GotoXY(20, 15); printf("%d Acessos", HashAcessos);
    GotoXY(90, 15); printf("%d Acessos", 0 /*BuscaBinaria(chave)*/);
    GotoXY(20, 10);
    GotoXY(38, 26); system("PAUSE");
}

void LerArquivo() {
    char linha[100000], texto[100000];
    Dados LD;
    int campo = 0, i = 0, j, tam, t, a, aspas;
    FILE *fporigin = fopen("pldb.csv", "r");
    if(fporigin == NULL) {
        printf("Nao abriu pldb.csv\n");
        exit(1);
    }
    fscanf (fporigin, " %[^\n]", linha);
    while (fscanf (fporigin, " %[^\n]", linha)!=EOF) {
        memset(&LD, 0, sizeof(Dados));
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
                    strncpy (LD.Title, texto, 501);
                    break;
                case 1:
                    LD.Year = atoi(texto);
                    break;
                case 2:
                    strncpy (LD.Type, texto, 9);
                    break;
                case 4:
                    LD.Rank = atoi (texto);
                    break;
                case 11:
                    LD.Users = atoi (texto);
                    break;
                case 14:
                    strncpy (LD.Creator, texto, 99);
                    break;
                case 16:
                    strncpy (LD.Website, texto, 99);
                    break;
                case 18:
                    strncpy (LD.Origin, texto, 99);
                    break;
                case 19:
                    strncpy (LD.Country, texto, 50);
                    break;
                case 21:
                    strncpy (LD.Reference, texto, 99);
                    break;
                case 25:
                    strncpy (LD.Summary, texto, 9999);
                    break;
            }
            campo++;
        }
        GravarArquivo(LD);
        i++;
    }
    fclose (fporigin);
}
