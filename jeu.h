#ifndef JEU_H
#define JEU_H
#include "graphics.h"

void init_board(int[10][10]);

void draw_board(int[10][10]);

void draw_player(int[10][10] ,int, int);

void play(int[10][10]);

int fin(int[10][10], int*);

#endif