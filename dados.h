#ifndef CODE_WIKI_DADOS_H
#define CODE_WIKI_DADOS_H

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

void LerArquivo();
/* title, appeared, type, rank, numberOfUsers, creators, website, originCommunity
 * country, reference, wikipedia.summary */

#endif //CODE_WIKI_DADOS_H
