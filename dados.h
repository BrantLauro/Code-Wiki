#ifndef CODE_WIKI_DADOS_H
#define CODE_WIKI_DADOS_H
#define TAM 6011

struct dados {
    char Title[51];
    int Year;
    char Type[4];
    int Rank;
    int Users;
    char Creator[100];
    char Website[100];
    char Origin[100];
    char Country[51];
    char Reference[100];
    char Summary[10000];
};
typedef struct dados Dados;

// Definição do nó da lista encadeada
typedef struct No {
    Dados dados;
    struct No* prox;
} No;

void LerArquivo();
void AbrirArquivo();
void FecharArquivo();
void GravarArquivo();
void Inicializar(Dados H[]);
int HashString(char str[]);
int Hash(int chave);
void Inserir(Dados H[], Dados P);
Dados* Busca(char Chave[]);
void Imprimir(Dados D);
//void TelaPesquisa();
/* title, appeared, type, rank, numberOfUsers, creators, website, originCommunity
 * country, reference, wikipedia.summary */

#endif //CODE_WIKI_DADOS_H
