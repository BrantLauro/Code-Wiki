#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"
#include "interface.h"

Dados D[100000];
No* H[TAM];
FILE *fp;

void AbrirArquivo() {
    Dados Dado;
    fp = fopen("dados.txt","rb+");
    if(fp == NULL){
        /*strcpy(Dado.Title, "");
        Dado.Year = 0;
        strcpy(Dado.Type, "");
        Dado.Rank = 0;
        Dado.Users = 0;
        strcpy(Dado.Creator, "");
        strcpy(Dado.Website, "");
        strcpy(Dado.Origin, "");
        strcpy(Dado.Country, "");
        strcpy(Dado.Reference, "");
        strcpy(Dado.Summary, "");*/
        fp = fopen("dados.txt","wb+");
        if(fp == NULL){
            printf("[ERROR] O programa nao conseguiu abrir o arquivo.");
            exit(1);
        }
        /*for(int i = 0; i < 6011; i++) {
            GravarArquivo();
        }*/
    }
}
void InserirNo(Dados* D) {
    // Calcula o hash do campo "nome"
    int posicao = HashString(D -> Title);
    // Aloca memória para o novo nó da lista
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    strcpy(novoNo->dados.Title, D -> Title);
    novoNo->dados.Year = D -> Year;
    strcpy(novoNo->dados.Type, D -> Type);
    novoNo->dados.Rank = D -> Rank;
    novoNo -> dados.Users =  D -> Users;
    strcpy(novoNo->dados.Creator, D -> Creator);
    strcpy(novoNo->dados.Website, D -> Website);
    strcpy(novoNo->dados.Origin, D -> Origin);
    strcpy(novoNo->dados.Country, D -> Country);
    strcpy(novoNo->dados.Reference, D -> Reference);
    strcpy(novoNo->dados.Summary, D -> Summary);
    novoNo->prox = H[posicao];
    H[posicao] = novoNo;
}

void GravarArquivo() {
    //AbrirArquivo(fp);

    for (int i = 0; i < TAM; i++) {
        No* atual = H[i];
        while (atual != NULL) {
            fseek(fp, i, SEEK_END);
            fwrite(&(atual->dados), sizeof(Dados), 1, fp);
            atual = atual->prox;
        }
    }

    fflush(fp);
}

/*
void GravarArquivo(Dados Dado, int pos) {
    Dados C;
    fseek(fp, pos, SEEK_END);//Posiciona no fim do arquivo
    fread(&C, sizeof(Dados), 1, fp);
    if(strcmp(C.Title, "") == 0) printf("Deu Certo! %d");
    fwrite(&Dado, sizeof(Dados), 1, fp);//Grava
    printf("%d", C);
    fflush(fp);
}*/

/*
void Inicializar(Dados H[]) {
    int i;
    for(i = 0; i < TAM; i++)
       strcpy(H[i].Title, "");
}*/

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
    fseek(fp, id * sizeof(No), SEEK_SET);
    No* lista = NULL;
    fread(&lista, sizeof(No), 1, fp); // Lê o ponteiro da lista encadeada correspondente à posição hash
    while (lista != NULL) {
        if (strcmp(lista->dados.Title, Chave) == 0) {
            return &(lista->dados);
        }
        lista = lista->prox; // Avança para o próximo nó da lista
    }
    return NULL;
}

void FecharArquivo() {
    fclose(fp);
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
    //Inicializar(H);
    char linha[100000], texto[100000];
    //char *sub, *sub2;
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
            switch (campo) {
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
                    break;
            }
            campo++;
        }
        //Inserir(H, D[i]);
        //GravarArquivo();
        InserirNo(&D[i]);
        i++;
    }
    fclose (fporigin);
}
