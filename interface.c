#include "interface.h"
#include <ctype.h>

char* word_wrap(char* buffer, char* string, int line_width) {
    int i = 0;
    int k, counter;
    while (i < strlen(string)) {
        for (counter = 1; counter <= line_width; counter++) {
            if (i == strlen(string)) {
                buffer[i] = 0;
                return buffer;
            }
            buffer[i] = string[i];
            if (buffer[i] == '\n') {
                counter = 1;
            }
            i++;
        }
        if (isspace(string[i])) {
            buffer[i] = '\n';
            i++;
        } else {
            for (k = i; k > 0; k--) {
                if (isspace(string[k])) {
                    buffer[k] = '\n';
                    i = k + 1;
                    break;
                }
            }
        }
    }
    buffer[i] = 0;
    return buffer;
}

int Selecao(int x, int y, int Largura, int Altura, char *Opcoes[], int n) {
    int i, Opcao = 0, Tecla, Primeiro = 0;
    TextColoreback(LIGHT_GRAY, BLACK);
    for (i = 0; i < Altura && i < n; i++) {
        GotoXY(x, y + i);
        printf("%*s", -Largura, Opcoes[i + Primeiro]);
    }
    do {
        TextColoreback(LIGHT_GRAY, BLACK);
        GotoXY(x, y + Opcao - Primeiro);
        printf("%*s", -Largura, Opcoes[Opcao]);
        Tecla = GetTecla();
        TextColoreback(LIGHT_GRAY, BLACK);
        GotoXY(x, y + Opcao - Primeiro);
        printf("%*s", -Largura, Opcoes[Opcao]);
        if(Tecla == TEC_ESQ) Opcao--;
        if(Tecla == TEC_DIR) Opcao++;
        if(Tecla == TEC_CIMA) Opcao--;
        if(Tecla == TEC_BAIXO) Opcao++;
        if(Tecla == TEC_ENTER) {
            return Opcao;
        }
        if(Opcao < 0) Opcao = 0;
        if(Opcao >= n) Opcao = n-1;
        if(Opcao - Primeiro < 0 || Opcao >= Altura + Primeiro) {
            if(Opcao - Primeiro < 0) Primeiro--;
            else Primeiro++;
            for (i = 0; i < Altura && i < n; i++) {
                GotoXY(x, y + i);
                printf("%*s", -Largura, Opcoes[i + Primeiro]);
            }
        }
    }
    while(Tecla != TEC_ESC);
    return -1;
}

void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int GetTecla() {
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}

void TextColoreback(int letras, int fundo) { //para mudar a cor de fundo mude o background
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             letras + (fundo << 4));
}

void Borda(int x, int y, int largura, int altura, int tipo, int sombra){
    char C[][6] = {"\xda\xbf\xc0\xd9\xc4\xb3" ,
                   "\xc9\xbb\xc8\xbc\xcd\xba"};
    int i, j;
    GotoXY(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][1]);
    for(j = 0; j < altura; j++) {
        GotoXY(x, y+j+1); printf("%c", C[tipo][5]);

        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][5]);
        if(sombra) printf("\xb2");
    }
    GotoXY(x, y+altura); printf("%c", C[tipo][2]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][3]);
    if(sombra) {
        GotoXY(x+1, y+altura+1);
        for(i = 0; i < largura+2; i++) printf("\xb2");
    }
}

int Menu(char opcoes[][51], int x[], int y[], int opcao, int n) {
    int i; int tecla;
    TextColoreback(LIGHT_GRAY, BLACK);
    for(i = 0; i < n; i++) {
        GotoXY(x[i], y[i]); printf("%s", opcoes[i]);
    }
    do {
        TextColoreback(DARK_GRAY, BLACK);
        GotoXY(x[opcao], y[opcao]);
        printf("%s", opcoes[opcao]);
        tecla = GetTecla();
        TextColoreback(LIGHT_GRAY, BLACK);
        if(tecla == 13) return opcao;
        GotoXY(x[opcao], y[opcao]);
        printf("%s", opcoes[opcao]);
        if(tecla == TEC_BAIXO || tecla == TEC_DIR) opcao ++;
        if(tecla == TEC_CIMA || tecla == TEC_ESQ) opcao --;
        if(opcao < 0) opcao = n - 1;
        if(opcao >= n) opcao = 0;
    } while(tecla != 27);
    return -1;
}
