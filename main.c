#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "header.h"

int main()
{
    /* Set console code page to UTF-8 to support emojis and custom UI shapes */
    SetConsoleOutputCP(CP_UTF8);
    
    /* Initialize random number generator with current system time */
    srand((unsigned int)time(NULL));

    /* Initial splash screen setup */
    system("cls");
    drawHeaderBanner();
    typeText("\n   Welcome to the Guessing Number Game!\n", C_LCYAN, 20);
    loadingBar("Loading game data...", C_LGREEN);
    Sleep(400);

    /* Infinite loop to keep the game running until the user explicitly exits */
    while (1)
    {
        menu();
    }

    return 0;
}
