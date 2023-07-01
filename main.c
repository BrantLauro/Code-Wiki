#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "dados.h"

//teste

void TelaPrincipal () {
    TextColoreback(LIGHT_GRAY, BLACK);
    Borda(0, 0, 118, 28, 1, 0);
    GotoXY(17, 1); printf("                            ,,                                    ,,              ,, ");
    GotoXY(17, 2); printf("  .g8\"\"\"bgd               `7MM              `7MMF'     A     `7MF'db  `7MM        db  ");
    GotoXY(17, 3); printf(".dP'     `M                 MM                `MA     ,MA     ,V        MM           ");
    GotoXY(17, 4); printf("dM'       ` ,pW\"Wq.    ,M\"\"bMM  .gP\"Ya         VM:   ,VVM:   ,V `7MM    MM  ,MP'`7MM ");
    GotoXY(17, 5); printf("MM         6W'   `Wb ,AP    MM ,M'   Yb         MM.  M' MM.  M'   MM    MM ;Y     MM  ");
    GotoXY(17, 6); printf("MM.        8M     M8 8MI    MM 8M\"\"\"\"\"\"         `MM A'  `MM A'    MM    MM;Mm     MM  ");
    GotoXY(17, 7); printf("`Mb.     ,'YA.   ,A9 `Mb    MM YM.    ,          :MM;    :MM;     MM    MM `Mb.   MM ");
    GotoXY(17, 8); printf("  `\"bmmmd'  `Ybmd9'   `Wbmd\"MML.`Mbmmd'           VF      VF    .JMML..JMML. YA..JMML.");
    Borda(15, 23, 90, 2, 0,0);
    GotoXY(16, 24); printf("Pesquisa: ");
    GotoXY(30, 9); printf(" ,-\"_,,--'\"\"");
    GotoXY(30, 10); printf("; ,'               .,------,....___");
    GotoXY(30, 11); printf("; ;               /       ;        \"\"\"`---.._");
    GotoXY(30, 12); printf("`.``-.._____,,,,,/       ;                   \"\"``.");
    GotoXY(30, 13); printf("  ``--...___;;;;/-\"\"\"\"\"-;                         \\");
    GotoXY(30, 14); printf("            ```;        ;                         ;;");
    GotoXY(30, 15); printf("              ;        ;                         / ;");
    GotoXY(30, 16); printf("             ;\"----....;___                     ; ;;");
    GotoXY(30, 17); printf("             ;-,,,,,___    \"\"`\"--..._         ,' ; ;");
    GotoXY(30, 18); printf("             ;         \"\"\"\"``---...__\"\"-...,-' ,'  ;");
    GotoXY(30, 19); printf("             ;                       \"`-....,-'   /");
    GotoXY(30, 20); printf("             `-._     _-------_   By T&B |_|>   ,'");
    GotoXY(30, 21); printf("                 \"`--'\"\"\"\"\"\"\"\"\"``--..        ,,'");
    GotoXY(30, 22); printf("                                     \"\"`---'\"");
}

int main() {
    char Title[51];
    Dados* D;
    LerArquivo();
    AbrirArquivo();
    do {
        TelaPrincipal();
        GravarArquivo();
        GotoXY(26, 24); scanf(" %[^\n]", Title);
        if(strcmp(Title, "\\exit") == 0) break;
        D = Busca(Title);
        if(D != NULL) {
            Imprimir(*D);
        } else {
            Borda(13, 8, 91, 10, 1, 0);
            Borda(28, 9, 60, 2, 0, 0);
            GotoXY(48, 10); printf("VALOR NAO ENCONTRADO!!!");
            GotoXY(36, 15); system("PAUSE");
        }
    } while(1);
    FecharArquivo();
    GotoXY(0, 45);
    return  0;
}
