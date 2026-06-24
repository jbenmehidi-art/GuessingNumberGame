#ifndef HEADER_H
#define HEADER_H

#include "ui.h"

/* Structure to store player data for the leaderboard */
typedef struct
{
    char name[30]; /* Stores the player's name */
    int score;     /* Stores the final score achieved */
} Player;

/* Function prototypes shared across the game modules */
int random(int reach);
void LeaderBoard(void);
void guessing(int reach, Player *p);
void menu(void);
void difficult(void);

#endif
