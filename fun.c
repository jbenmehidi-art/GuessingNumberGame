#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

/* Reads, sorts descendingly, and prints historical scores stored in a binary file */
void LeaderBoard(void)
{
    FILE *f = fopen("Players.bin", "rb");
    if (f == NULL)
    {
        /* Handles cases where the database file doesn't exist yet */
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

    /* Extract elements safely into an array up to a safe index of 100 */
    while (fread(&p, sizeof(p), 1, f) == 1 && count < 100)
    {
        pl[count] = p;
        count++;
    }
    fclose(f);

    int i, j;
    Player temp;

    /* Bubble sort sorting algorithms descendingly according to higher score records */
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
    printf(  "         ?? TOP PLAYERS LEADERBOARD ??    \n");
    printf(  "   =========================================\n");
    resetColor();

    setColor(C_CYAN);
    printf("     %-4s  %-23s  %-10s\n", "Rank", "Player Name", "Score");
    printf("   -----------------------------------------\n");
    resetColor();

    /* Render structural row formatting with visual reward tier medals */
    for (i = 0; i < count; i++)
    {
        int color;
        const char *medal;

        if (i == 0)      { color = C_LYELLOW; medal = "??"; }
        else if (i == 1) { color = C_BWHITE;  medal = "??"; }
        else if (i == 2) { color = C_LRED;    medal = "??"; }
        else             { color = C_WHITE;   medal = "  "; }

        setColor(color);
        printf("    %s #%-3d  %-23s  %d pts\n", medal, i + 1, pl[i].name, pl[i].score);
        fflush(stdout);
        Sleep(80); // Stagger loop effect for smooth row-by-row rendering animation
    }

    setColor(C_LYELLOW);
    printf("   =========================================\n\n");
    resetColor();

    system("pause"); // Holds screen state allowing the user to view rank outcomes
}

/* Returns a calculated random index bounded by reach inclusive */
int random(int reach)
{
    return rand() % (reach + 1);
}

/* Handles core algorithmic structures for checking target number attempts */
void guessing(int reach, Player *p)
{
    int n = random(reach); /* Secret random target assigned */
    int a;
    int attemps = 0;
    p->score = 100; /* Baseline points tracking value init */

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
    scanf(" %[^\n]", p->name); /* Grabs full string tokens cleanly including gaps */
    setColor(C_LCYAN);
    printf("   =========================================\n");
    resetColor();

    loadingBar("Preparing your challenge...", C_LGREEN);

    system("cls");
    drawHeaderBanner();

    setColor(C_LGREEN);
    printf("\n   [?] Welcome %s! Let's start the game...\n", p->name);
    resetColor();
    printf("    -> Guess the secret number to win!\n\n");

    do
    {
        do
        {
            setColor(C_CYAN);
            printf("   -----------------------------------------\n");
            setColor(C_LYELLOW);
            printf("    ?? Remaining Attempts: [ %-2d ]\n", 10 - attemps);
            setColor(C_CYAN);
            printf("   -----------------------------------------\n");
            resetColor();
            printf("    -> Enter a guess (0-%d): ", reach);
            scanf("%d", &a);

            /* Error verification for checking data entry boundaries */
            if (a < 0 || a > reach)
            {
                setColor(C_LRED);
                printf("\n   [!] Invalid Input! Number must be between 0 and %d.\n\n", reach);
                resetColor();
            }
        } while (a < 0 || a > reach);

        attemps++;
        spinner("?? Checking your guess", 6, C_GRAY);

        /* Loss parameters validation logic check */
        if (attemps == 10 && a != n)
        {
            loseAnimation();
            setColor(C_LRED);
            printf("\n   =========================================\n");
            printf(  "    ?? GAME OVER! You ran out of attempts. \n");
            printf(  "    ?? The secret number was: %d\n", n);
            printf(  "   =========================================\n\n");
            resetColor();
            p->score = 0;
            break;
        }
        else
        {
            /* Dynamic feedback hints loops for numbers closely flanking target scope */
            if (a > n && a < n + 5)
            {
                setColor(C_LYELLOW);
                printf("\n   ?? Almost there!! Your guess is just a bit higher!\n\n");
                resetColor();
            }
            else if (a > n - 5 && a < n)
            {
                setColor(C_LYELLOW);
                printf("\n   ?? Almost there!! Your guess is just a bit lower!\n\n");
                resetColor();
            }
            else
            {
                /* General logical steering feedback boundaries */
                if (a < n)
                {
                    setColor(C_LCYAN);
                    printf("\n   ?? Too Low! The number is GREATER than %d.\n\n", a);
                    resetColor();
                }
                if (a > n)
                {
                    setColor(C_LMAGENTA);
                    printf("\n   ?? Too High! The number is LESS than %d.\n\n", a);
                    resetColor();
                }
                if (a == n)
                {
                    winAnimation();
                    setColor(C_LGREEN);
                    printf("\n   =========================================\n");
                    printf(  "        ?? EXCELLENT JOB, YOU WIN! ??     \n");
                    printf(  "    ?? Found the number (%d) in %d attempts!\n", n, attemps);
                    printf(  "   =========================================\n\n");
                    resetColor();
                    break;
                }
            }
        }
        p->score -= 10; /* Reduces point brackets dynamically per trial loop failure */
    } while (a != n && attemps < 10);
}

/* Coordinates selection states for specific gameplay modes */
void difficult(void)
{
    FILE *f = fopen("Players.bin", "ab"); /* Opens stream in append-binary mode */
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

    /* Retreive targeted option offset indices */
    int choice = showMenu(" CHOOSE DIFFICULTY LEVEL ", options, 3, C_LYELLOW) + 1;

    system("cls");
    drawHeaderBanner();
    loadingBar("Generating the secret number...", C_LMAGENTA);

    /* Assigning multiplier metrics dynamically according to structural tiers chosen */
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

    /* Save profile instances securely into file structural stream */
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

/* Navigational steering router engine for home screen modules */
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
