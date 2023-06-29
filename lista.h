#include "dados.h"
#ifndef CODE_WIKI_LISTA_H
#define CODE_WIKI_LISTA_H

typedef struct lista{
    Dados info;
    struct lista *prox;
}Lista;

void InicializarLista(Lista *l);
void InserirLista(Lista *l, Dados d);
void BuscarLista(Lista *l, Dados d);
void ImprimirLista(Lista *l);
void InicializarTabela(Lista t[]);
int FuncaoHash(int chave);
void InserirHash(Lista t[], Dados d);
int BuscaHash(Lista t[], char letra);
void ImprimirHash(Lista t[]);

#endif //CODE_WIKI_LISTA_H
