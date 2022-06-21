#include "jeu.h"

void init_board(int board[10][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j] = 0;
        }
    }
}

void draw_board(int board[10][10]) {
    point p1, p2;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            p1.x = i*60+60; p1.y = 0;
            p2.x = i*60+60; p2.y = 600;
            draw_line(p1,p2,blanc);
            p1.y = i*60+60; p1.x = 0;
            p2.y = i*60+60; p2.x = 600;
            draw_line(p1,p2,blanc);
            draw_player(board, i, j);
        }
    }
}

void draw_player(int board[10][10] ,int i, int j) {
    point p = {i*60+30, j*60+30};
    if(board[i][j] == 1)
        draw_cross(p, 60, blue);
    if(board[i][j] == 2)
        draw_circle(p, 30, red);
}