#ifndef CODE_WIKI_DADOS_H
#define CODE_WIKI_DADOS_H
#define TAM 6029

typedef struct dados {
    char Title[51];
    int Year;
    char Type[10];
    int Rank;
    int Users;
    char Creator[100];
    char Website[100];
    char Origin[100];
    char Country[51];
    char Reference[100];
    char Summary[10000];
    int prox;
} Dados;

void AbrirArquivo();
void FecharArquivo();
void GravarArquivo(Dados D);
Dados Buscar(char Chave[]);
int HashString(char str[]);
void Imprimir(Dados D);
void TelaBBinaria(int chave);
int BuscaBinaria(int n, int chave);
void LerArquivo();

#endif //CODE_WIKI_DADOS_H
