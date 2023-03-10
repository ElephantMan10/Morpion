#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>

#include "couleur.h"

typedef struct point {int x,y;} point;

typedef Uint32 couleur;

typedef int BOOL;

#define MINDEP 1

#define TRUE 1
#define True 1
#define true 1
#define FALSE 0
#define False 0
#define false 0

void init_graphics(int W, int H);

void affiche_auto_on();
void affiche_auto_off();
void affiche_all();
void synchro();

couleur couleur_RGB(int r, int g, int b);

point get_mouse();
void wait_escape();
point wait_clic();

void fill_screen(couleur color);
void draw_pixel(point p, couleur color);
void draw_line(point p1, point p2, couleur color);
void draw_big_line(point p1, point p2, couleur color);
void draw_rectangle(point p1, point p2, couleur color);
void draw_fill_rectangle(point p1, point p2, couleur color);
void draw_circle(point centre, int rayon, couleur color);
void draw_fill_circle(point centre, int rayon, couleur color);
void draw_square(point p1, int taille, couleur color);
void draw_fill_square(point p1, int taille, couleur color);
void draw_cross(point p, int taille, couleur color);

void aff_pol(char *a_ecrire, int taille, point p, couleur C);
void aff_int(int n, int taille, point p, couleur C);

void attendre(int millisecondes);

int alea_int(int N);

void write_text(char *a_ecrire);

#endif