#ifndef UI_H
#define UI_H

#include <windows.h>

/* ===================================================
   Console Colors (standard Windows console codes)
   =================================================== */
#define C_BLACK        0
#define C_BLUE         1
#define C_GREEN        2
#define C_CYAN         3
#define C_RED          4
#define C_MAGENTA      5
#define C_YELLOW       6
#define C_WHITE        7
#define C_GRAY         8
#define C_LBLUE        9
#define C_LGREEN       10
#define C_LCYAN        11
#define C_LRED         12
#define C_LMAGENTA     13
#define C_LYELLOW      14
#define C_BWHITE       15

/* combine background + foreground -> (bg << 4) | fg */
#define BG_FG(bg, fg) (((bg) << 4) | (fg))

/* ===================================================
   Basic console control
   =================================================== */
void setColor(int color);
void resetColor(void);
void hideCursor(void);
void showCursor(void);
void clearLine(void);

/* ===================================================
   Animations
   =================================================== */
void typeText(const char *text, int color, int delayMs);
void loadingBar(const char *message, int color);
void spinner(const char *message, int cycles, int color);
void winAnimation(void);
void loseAnimation(void);

/* ===================================================
   Layout helpers
   =================================================== */
void drawHeaderBanner(void);
void drawSeparator(int color);
void drawInfoBox(const char *title, const char *lines[], int lineCount,
                  int titleColor, int borderColor);

/* ===================================================
   Interactive menu ("buttons")
   Navigate with UP/DOWN arrows + ENTER, or press the
   number key directly. Returns 0-based index chosen.
   =================================================== */
int showMenu(const char *title, const char *options[], int optionCount, int titleColor);

#endif
