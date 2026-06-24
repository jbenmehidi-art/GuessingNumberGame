#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "ui.h"

/* ===================================================
   Basic console control
   =================================================== */

/* Changes the console text and background color */
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

/* Resets the text color back to standard white */
void resetColor(void)
{
    setColor(C_WHITE);
}

/* Hides the console cursor for smoother visual elements/menus */
void hideCursor(void)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/* Restores the visibility of the console cursor */
void showCursor(void)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/* Clears the current line in the console terminal */
void clearLine(void)
{
    printf("\r                                                                                \r");
}

/* ===================================================
   Animations
   =================================================== */

/* Displays text letter-by-letter with a typewriter effect */
void typeText(const char *text, int color, int delayMs)
{
    setColor(color);
    for (size_t i = 0; i < strlen(text); i++)
    {
        putchar((unsigned char)text[i]);
        fflush(stdout);
        Sleep(delayMs);
    }
    resetColor();
}

/* Simulates a filling progress bar (#) with a specific percentage output */
void loadingBar(const char *message, int color)
{
    setColor(color);
    printf("\n   %s\n   ", message);
    resetColor();
    printf("[");
    for (int i = 0; i < 20; i++)
    {
        setColor(C_LGREEN);
        printf("#");
        fflush(stdout);
        Sleep(35);
    }
    resetColor();
    printf("] 100%%\n");
    Sleep(150);
}

/* Displays a quick spinning loading wheel animation */
void spinner(const char *message, int cycles, int color)
{
    const char frames[4] = { '|', '/', '-', '\\' };
    for (int i = 0; i < cycles; i++)
    {
        setColor(color);
        printf("\r   %s %c ", message, frames[i % 4]);
        fflush(stdout);
        Sleep(120);
    }
    clearLine();
    resetColor();
}

/* Plays a flashy color-changing win sequence accompanied by audio beeps */
void winAnimation(void)
{
    int colors[] = { C_LYELLOW, C_LGREEN, C_LCYAN, C_LMAGENTA, C_LRED, C_BWHITE };
    for (int i = 0; i < 10; i++)
    {
        setColor(colors[i % 6]);
        printf("\r   *** YOU WIN! *** ");
        fflush(stdout);
        Beep(600 + i * 80, 80);
        Sleep(90);
    }
    printf("\n");
    resetColor();
}

/* Plays a blinking Game Over screen with descending frequency audio tones */
void loseAnimation(void)
{
    for (int i = 0; i < 4; i++)
    {
        setColor(C_LRED);
        printf("\r   xxx  GAME OVER  xxx   ");
        fflush(stdout);
        Beep(400 - i * 50, 150);
        Sleep(150);
        clearLine();
        Sleep(80);
    }
    setColor(C_LRED);
    printf("\r   xxx  GAME OVER  xxx   \n");
    resetColor();
}

/* ===================================================
   Layout helpers
   =================================================== */

/* Draws the global game title header banner box */
void drawHeaderBanner(void)
{
    setColor(C_LCYAN);
    printf("\n   +-------------------------------------------------+\n");
    printf(  "   |                                                   |\n");
    setColor(C_LYELLOW);
    printf(  "   |          GUESSING NUMBER GAME  (v2.0)            |\n");
    setColor(C_LCYAN);
    printf(  "   |                                                   |\n");
    printf(  "   +-------------------------------------------------+\n");
    resetColor();
}

/* Draws a clean custom separator horizontal line */
void drawSeparator(int color)
{
    setColor(color);
    printf("   -----------------------------------------------------\n");
    resetColor();
}

/* Draws a flexible, well-aligned boxed frame containing text info rows */
void drawInfoBox(const char *title, const char *lines[], int lineCount,
                 int titleColor, int borderColor)
{
    const int width = 47;

    setColor(borderColor);
    printf("\n   +");
    for (int i = 0; i < width; i++) printf("-");
    printf("+\n");

    if (title != NULL)
    {
        setColor(borderColor);
        printf("   |");
        setColor(titleColor);
        printf("%-*s", width, title);
        setColor(borderColor);
        printf("|\n");

        printf("   +");
        for (int i = 0; i < width; i++) printf("-");
        printf("+\n");
    }

    for (int i = 0; i < lineCount; i++)
    {
        setColor(borderColor);
        printf("   |");
        setColor(C_WHITE);
        printf("%-*s", width, lines[i]);
        setColor(borderColor);
        printf("|\n");
    }

    printf("   +");
    for (int i = 0; i < width; i++) printf("-");
    printf("+\n");
    resetColor();
}

/* ===================================================
   Interactive menu ("buttons")
   =================================================== */

/* Renders an interactive navigational menu allowing keyboard button highlights */
int showMenu(const char *title, const char *options[], int optionCount, int titleColor)
{
    int selected = 0;
    int key;

    hideCursor();

    while (1)
    {
        system("cls");
        drawHeaderBanner();

        setColor(titleColor);
        printf("\n   %s\n\n", title);
        resetColor();

        /* Loop through options to highlight the current selection index */
        for (int i = 0; i < optionCount; i++)
        {
            if (i == selected)
            {
                /* Inverted or bright background color choice for the active button */
                setColor(BG_FG(C_GREEN, C_BWHITE));
                printf("    [ %d ]  %-40s", i + 1, options[i]);
                resetColor();
                printf("  <--\n");
            }
            else
            {
                setColor(C_CYAN);
                printf("     %d   ", i + 1);
                setColor(C_WHITE);
                printf("%-40s\n", options[i]);
                resetColor();
            }
            printf("\n");
        }

        setColor(C_GRAY);
        printf("\n   Use UP / DOWN arrows + ENTER, or press a number key.\n");
        resetColor();

        key = _getch();

        if (key == 224 || key == 0) /* Handling extended key codes (Arrow Keys) */
        {
            key = _getch();
            if (key == 72) /* Up Arrow pressed */
                selected = (selected - 1 + optionCount) % optionCount;
            else if (key == 80) /* Down Arrow pressed */
                selected = (selected + 1) % optionCount;
        }
        else if (key == 13) /* Enter Key pressed */
        {
            break;
        }
        else if (key >= '1' && key <= '9' && (key - '1') < optionCount) /* Numeric direct selection */
        {
            selected = key - '1';
            break;
        }
    }

    showCursor();
    return selected;
}
