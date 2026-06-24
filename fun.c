#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

void LeaderBoard(void)
{
    FILE *f = fopen("Players.bin", "rb");
    if (f == NULL)
    {
        system("cls");
        drawHeaderBanner();

        const char *lines[] = {
            " No games played yet!",
            " Play at least one round to appear",
            " here in the leaderboard."
        };
        drawInfoBox(" LEADERBOARD IS EMPTY ", lines, 3, C_LYELLOW, C_RED);
        printf("\n");
        system("pause");
        return;
    }

    Player p;
    Player pl[100];
    int count = 0;

    while (fread(&p, sizeof(p), 1, f) == 1 && count < 100)
    {
        pl[count] = p;
        count++;
    }
    fclose(f);

    int i, j;
    Player temp;

    // ØªØ±ØªÙŠØ¨ Ø§Ù„Ù„Ø§Ø¹Ø¨ÙŠÙ† ØªÙ†Ø§Ø²Ù„ÙŠØ§Ù‹ Ø­Ø³Ø¨ Ø§Ù„Ø³ÙƒÙˆØ± Ø£Ø¹Ù„Ù‰ ÙØªÙ‚Ù„ÙŠÙ„
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (pl[j].score < pl[j + 1].score)
            {
                temp = pl[j];
                pl[j] = pl[j + 1];
                pl[j + 1] = temp;
            }
        }
    }

    system("cls");
    drawHeaderBanner();

    setColor(C_LYELLOW);
    printf("\n   =========================================\n");
    printf(  "         ðŸ† TOP PLAYERS LEADERBOARD ðŸ†    \n");
    printf(  "   =========================================\n");
    resetColor();

    setColor(C_CYAN);
    printf("     %-4s  %-23s  %-10s\n", "Rank", "Player Name", "Score");
    printf("   -----------------------------------------\n");
    resetColor();

    for (i = 0; i < count; i++)
    {
        int color;
        const char *medal;

        if (i == 0)      { color = C_LYELLOW; medal = "ðŸ¥‡"; }
        else if (i == 1) { color = C_BWHITE;  medal = "ðŸ¥ˆ"; }
        else if (i == 2) { color = C_LRED;    medal = "ðŸ¥‰"; }
        else             { color = C_WHITE;   medal = "  "; }

        setColor(color);
        printf("    %s #%-3d  %-23s  %d pts\n", medal, i + 1, pl[i].name, pl[i].score);
        fflush(stdout);
        Sleep(80); // Ø¥Ø¸Ù‡Ø§Ø± Ø§Ù„ØªØ±ØªÙŠØ¨ ØªØ¯Ø±ÙŠØ¬ÙŠØ§Ù‹ Ø¨ØªØ£Ø«ÙŠØ± Ø­Ø±ÙƒÙŠ Ø¨Ø³ÙŠØ·
    }

    setColor(C_LYELLOW);
    printf("   =========================================\n\n");
    resetColor();

    system("pause"); // Ø¥ÙŠÙ‚Ø§Ù Ø§Ù„Ø´Ø§Ø´Ø© Ù„ÙƒÙŠ ÙŠØªÙ…ÙƒÙ† Ø§Ù„Ù„Ø§Ø¹Ø¨ Ù…Ù† Ø±Ø¤ÙŠØ© Ø§Ù„ØªØ±ØªÙŠØ¨
}

int random(int reach)
{
    return rand() % (reach + 1);
}

void guessing(int reach, Player *p)
{
    int n = random(reach);
    int a;
    int attemps = 0;
    p->score = 100;

    system("cls");
    drawHeaderBanner();

    setColor(C_LCYAN);
    printf("\n   =========================================\n");
    printf(  "            PLAYER REGISTRATION            \n");
    printf(  "   =========================================\n");
    resetColor();
    setColor(C_LYELLOW);
    printf("    -> Enter your name: ");
    resetColor();
    scanf(" %[^\n]", p->name);
    setColor(C_LCYAN);
    printf("   =========================================\n");
    resetColor();

    loadingBar("Preparing your challenge...", C_LGREEN);

    system("cls");
    drawHeaderBanner();

    setColor(C_LGREEN);
    printf("\n   [âœ“] Welcome %s! Let's start the game...\n", p->name);
    resetColor();
    printf("    -> Guess the secret number to win!\n\n");

    do
    {
        do
        {
            setColor(C_CYAN);
            printf("   -----------------------------------------\n");
            setColor(C_LYELLOW);
            printf("    ðŸŽ¯ Remaining Attempts: [ %-2d ]\n", 10 - attemps);
            setColor(C_CYAN);
            printf("   -----------------------------------------\n");
            resetColor();
            printf("    -> Enter a guess (0-%d): ", reach);
            scanf("%d", &a);

            if (a < 0 || a > reach)
            {
                setColor(C_LRED);
                printf("\n   [!] Invalid Input! Number must be between 0 and %d.\n\n", reach);
                resetColor();
            }
        } while (a < 0 || a > reach);

        attemps++;
        spinner("ðŸ”Ž Checking your guess", 6, C_GRAY);

        if (attemps == 10 && a != n)
        {
            loseAnimation();
            setColor(C_LRED);
            printf("\n   =========================================\n");
            printf(  "    ðŸ’¥ GAME OVER! You ran out of attempts. \n");
            printf(  "    ðŸ‘‰ The secret number was: %d\n", n);
            printf(  "   =========================================\n\n");
            resetColor();
            p->score = 0;
            break;
        }
        else
        {
            if (a > n && a < n + 5)
            {
                setColor(C_LYELLOW);
                printf("\n   ðŸ”¥ Almost there!! Your guess is just a bit higher!\n\n");
                resetColor();
            }
            else if (a > n - 5 && a < n)
            {
                setColor(C_LYELLOW);
                printf("\n   ðŸ”¥ Almost there!! Your guess is just a bit lower!\n\n");
                resetColor();
            }
            else
            {
                if (a < n)
                {
                    setColor(C_LCYAN);
                    printf("\n   ðŸ”¼ Too Low! The number is GREATER than %d.\n\n", a);
                    resetColor();
                }
                if (a > n)
                {
                    setColor(C_LMAGENTA);
                    printf("\n   ðŸ”½ Too High! The number is LESS than %d.\n\n", a);
                    resetColor();
                }
                if (a == n)
                {
                    winAnimation();
                    setColor(C_LGREEN);
                    printf("\n   =========================================\n");
                    printf(  "        ðŸŽ‰ EXCELLENT JOB, YOU WIN! ðŸŽ‰     \n");
                    printf(  "    ðŸŽ¯ Found the number (%d) in %d attempts!\n", n, attemps);
                    printf(  "   =========================================\n\n");
                    resetColor();
                    break;
                }
            }
        }
        p->score -= 10;
    } while (a != n && attemps < 10);
}

void difficult(void)
{
    FILE *f = fopen("Players.bin", "ab");
    if (f == NULL)
    {
        system("cls");
        drawHeaderBanner();

        const char *lines[] = {
            " Could not save player data!",
            " The program will now close."
        };
        drawInfoBox(" CRITICAL ERROR ", lines, 2, C_LYELLOW, C_RED);
        printf("\n");
        system("pause");
        exit(1);
    }

    Player p;

    const char *options[] = {
        "Easy    (Range: 0 - 50)",
        "Medium  (Range: 0 - 100)",
        "Hard    (Range: 0 - 1000)"
    };

    int choice = showMenu(" CHOOSE DIFFICULTY LEVEL ", options, 3, C_LYELLOW) + 1;

    system("cls");
    drawHeaderBanner();
    loadingBar("Generating the secret number...", C_LMAGENTA);

    switch (choice)
    {
        case 1:
            guessing(50, &p);
            break;
        case 2:
            guessing(100, &p);
            p.score *= 2;
            break;
        case 3:
            guessing(1000, &p);
            p.score *= 3;
            break;
    }

    fwrite(&p, sizeof(p), 1, f);
    fclose(f);

    char line1[60], line2[60];
    snprintf(line1, sizeof(line1), " Player : %s", p.name);
    snprintf(line2, sizeof(line2), " Score  : %d points", p.score);
    const char *lines[] = { line1, line2 };

    drawInfoBox(" RECORD SAVED ", lines, 2, C_LGREEN, C_LGREEN);
    printf("\n");
    system("pause");
}

void menu(void)
{
    const char *options[] = {
        "Start New Game",
        "View Leaderboard",
        "Exit Game"
    };

    int choice = showMenu(" MAIN MENU ", options, 3, C_LYELLOW) + 1;

    switch (choice)
    {
        case 1:
            system("cls");
            difficult();
            break;

        case 2:
            system("cls");
            LeaderBoard();
            break;

        default:
            system("cls");
            drawHeaderBanner();
            typeText("\n   Thank you for playing! See you next time!\n\n", C_LYELLOW, 25);
            Sleep(800);
            exit(0);
            break;
    }
}
