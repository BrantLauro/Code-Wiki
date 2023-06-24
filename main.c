#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "dados.h"

char opcoes[][51] = {"Anexar",  "Pesquisar", "Fechar" };
int x[] = {32, 56, 82};
int y[] = {24, 24,  24};

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
    Borda(27, 23, 15, 2, 0,0);
    Borda(52, 23, 15, 2, 0,0);
    Borda(77, 23, 15, 2, 0,0);
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
    int escolha = 0;
    do {
        TelaPrincipal();
        escolha = Menu(opcoes, x, y, escolha, 3);
        if(escolha == 0) {
            LerArquivo();
            system("PAUSE");
        }
        if(escolha == 1);
        if(escolha == 2)
            break;
    } while(escolha != -1);
    GotoXY(0, 45);
    return  0;
}
