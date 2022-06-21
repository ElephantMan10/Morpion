#include "jeu.h"

void init_board(int board[10][10]) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j] = -1;
        }
    }
}

void draw_board(int board[10][10]) {
    point p1, p2;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            p1.x = i*60+60; p1.y = 0;
            p2.x = i*60+60; p2.y = 600;
            draw_line(p1,p2,black);
            p1.y = i*60+60; p1.x = 0;
            p2.y = i*60+60; p2.x = 600;
            draw_line(p1,p2,black);
            // draw_player(board, i, j);
        }
    }
}

void draw_player(int board[10][10] ,int i, int j) {
    point p = {i*60+30, j*60+30};
    if(board[i][j] == 0)
        draw_cross(p, 60, blue);
    if(board[i][j] == 1)
        draw_circle(p, 30, red);
}

void play(int board[10][10]) {
    int* winner = malloc(sizeof(int));
    int joueur = 1;
    while(fin(board, winner)) {
        point p = wait_clic();
        int pos[2];
        pos[0] = p.x/60;
        pos[1] = p.y/60;
        if(board[pos[0]][pos[1]]==-1) {
            board[pos[0]][pos[1]] = joueur;
            joueur = 1-joueur;
        }
        draw_player(board, pos[0], pos[1]);
    }
    free(winner);
}

int fin(int board[10][10], int *winner) {
    
    int k = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(board[i][j]!=-1)
                k++;
        }
    }
    if(k>=100) {
        *winner = -1;
        return 0;
    }
    return 1;
}