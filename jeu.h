#ifndef JEU_H
#define JEU_H
#include "graphics.h"

void menu();

void init_board(int[15][15], int, int);

void draw_board(int[15][15], int, int);

void draw_player(int[15][15] ,int, int);

void play(int[15][15], int*, int, int, int);

int end(int[15][15], int*, int, int, int);

int replay(int winner);

void menu();

int test_x(int[15][15], int, int, int);

int test_y(int[15][15], int, int, int);

int test_xy(int[15][15], int, int, int);

int test_yx(int[15][15], int, int, int);

#endif