#include "lista.h"
#include "stdio.h"
#include "stdlib.h"
#define TAM 4817

void InicializarLista(Lista *l){
    l->info = NULL;
}

void InserirLista(Lista *l, Dados d){
    Lista *novo = malloc(sizeof(Dados));

    if(novo){
        novo->info = d;
        novo->prox = l->info;
        l->info = d;
    } else
        printf("Erro ao alocar memoria!\n");
}

void BuscarLista(Lista *l, char tittle){ //MEXER NESSA FUNCAO
    Dados *aux = l->info;
    while(aux && aux->Title != tittle)
        aux = aux->
}

void ImprimirLista(Lista *l){
    Lista *q;
    for(q = l; q != NULL; q = q->prox)
        printf("")
}

void InicializarTabela(Lista t[]){
    int i;

    for(i = 0; i < TAM; i++)
        InicializarLista(&t[i]);
}

int FuncaoHash(int chave){
    return chave % TAM;
}

void InserirHash(Lista t[], int valor){
    int id = FuncaoHash(valor);
    InserirLista(&t[id], valor);
}

int BuscaHash(Lista t[], char letra){
    int id = FuncaoHash(letra);
    return BuscaHash(&t[id], letra);
}

void ImprimirHash(Lista t[]){
    int i;
    for(i = 0; i < TAM; i++){
        printf("%d = ", i);
        ImprimirLista(&t[i]);
        printf("\n");
    }
}


