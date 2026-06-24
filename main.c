#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "header.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(NULL));

    system("cls");
    drawHeaderBanner();
    typeText("\n   Welcome to the Guessing Number Game!\n", C_LCYAN, 20);
    loadingBar("Loading game data...", C_LGREEN);
    Sleep(400);

    while (1)
    {
        menu();
    }

    return 0;
}
