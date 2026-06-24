#ifndef HEADER_H
#define HEADER_H

#include "ui.h"

typedef struct
{
    char name[30];
    int score;
} Player;

int random(int reach);
void LeaderBoard(void);
void guessing(int reach, Player *p);
void menu(void);
void difficult(void);

#endif
