#include "jeu.h"

void menu() {
    init_graphics(400,450);
    point p = {166,51};
    aff_pol("Quitter", 20, p, darkred);
    point p1 = {100,50}, p2 = {300,25};
    draw_rectangle(p1, p2, red);
    p1.y = 75; p2.y = 100;
    draw_rectangle(p1, p2, white);
    p1.y = 125; p2.y = 150;
    draw_rectangle(p1, p2, orchid);
    p1.y = 175; p2.y = 200;
    draw_rectangle(p1, p2, lightgreen);
    p1.y = 225; p2.y = 250;
    draw_rectangle(p1, p2, magenta);
    p1.y = 275; p2.y = 300;
    draw_rectangle(p1, p2, lightblue);
    p.x = 100; p.y = 400;
    aff_pol("Morpion", 50, p, gold);
    p.x = 145; p.y = 300;
    aff_pol("Tic-Tac-Toe", 20, p, lightblue);
    p.x = 167, p.y = 250;
    aff_pol("10x10", 20, p, magenta);
    p.y = 200;
    aff_pol("15x15", 20, p, lightgreen);
    p.x = 180; p.y = 150;
    aff_pol("6x7", 20, p, orchid);
    p.x = 167; p.y = 100;
    aff_pol("Regles", 20, p, white);
    int r = 1;
    int board[15][15];
    int size_tab_x;
    int size_tab_y;
    int nb;
    int winner;
    while(1) {
        p = wait_clic();
        if(p.x < 250 && p.x > 150) {
            if(p.y < 50 && p.y > 25) exit(0);
            if(p.y < 100 && p.y > 75) {
                init_graphics(550, 450);
                p.x = 10, p.y = 425;
                aff_pol("Le but du jeu du morpion est d'aligner 3 jetons de la meme couleur", 15, p, white);
                p.y = 375;
                aff_pol(" en ligne horizontale, verticale ou diagonale.", 15, p, white);
                p.y = 325;
                aff_pol("Il existe plusieurs variantes :", 15, p, white);
                p.y = 275;
                aff_pol(" - 10x10 : il faut aligner 5 jetons dans une table de 10*10 cases,", 15, p, white);
                p.y = 225;
                aff_pol(" - 15x15 : il faut aligner 6 jetons dans une table de 15*15 cases,", 15, p, white);
                p.y = 175;
                aff_pol(" - 6x7 : il faut aligner 4 jetons dans une table de 7*6 cases.", 15, p, white);
                p.y = 125;
                aff_pol("Cliquez n'importe ou pour revenir au menu", 15, p, white);
                p = wait_clic();
                init_graphics(400,450);
                p.x = 166; p.y = 51;
                aff_pol("Quitter", 20, p, darkred);
                p1.x = 100;p1.y = 50; p2.x = 300; p2.y = 25;
                draw_rectangle(p1, p2, red);
                p1.y = 75; p2.y = 100;
                draw_rectangle(p1, p2, white);
                p1.y = 125; p2.y = 150;
                draw_rectangle(p1, p2, orchid);
                p1.y = 175; p2.y = 200;
                draw_rectangle(p1, p2, lightgreen);
                p1.y = 225; p2.y = 250;
                draw_rectangle(p1, p2, magenta);
                p1.y = 275; p2.y = 300;
                draw_rectangle(p1, p2, lightblue);
                p.x = 100; p.y = 400;
                aff_pol("Morpion", 50, p, gold);
                p.x = 145; p.y = 300;
                aff_pol("Tic-Tac-Toe", 20, p, lightblue);
                p.x = 167, p.y = 250;
                aff_pol("10x10", 20, p, magenta);
                p.y = 200;
                aff_pol("15x15", 20, p, lightgreen);
                p.x = 170; p.y = 150;
                aff_pol("6x7", 20, p, orchid);
                p.x = 167; p.y = 100;
                aff_pol("Regles", 20, p, white);
            }
            if(p.y < 150 && p.y > 125) {
                size_tab_x = 7;
                size_tab_y = 6;
                nb = 3;
                break;
            }
            if(p.y < 200 && p.y > 175) {
                size_tab_x = 15;
                size_tab_y = 15;
                nb = 5;
                break;
            }
            if(p.y < 250 && p.y > 225) {
                size_tab_x = 10;
                size_tab_y = 10;
                nb = 4;
                break;
            }
            if(p.y < 300 && p.y > 275) {
                size_tab_x = 3;
                size_tab_y = 3;
                nb = 2;
                break;
            }
        }
    }
    while(r) {
        play(board, &winner, size_tab_x, size_tab_y, nb);
        r = replay(winner);
    }
}

void init_board(int board[15][15], int size_tab_x, int size_tab_y) {
    for(int i = 0; i < size_tab_x; i++) {
        for(int j = 0; j < size_tab_y; j++) {
            board[i][j] = -1;
        }
    }
}

void draw_board(int board[15][15], int size_tab_x, int size_tab_y) {
    point p1, p2;
    for(int i = 0; i < size_tab_x; i++) {
        for(int j = 0; j < size_tab_y; j++) {
            p1.x = i*60+60; p1.y = 0;
            p2.x = i*60+60; p2.y = 60*size_tab_y;
            draw_big_line(p1,p2,lightgrey);
            p1.y = i*60+60; p1.x = 0;
            p2.y = i*60+60; p2.x = 60*size_tab_x;
            draw_big_line(p1,p2,lightgrey);
            // draw_player(board, i, j);
        }
    }
}

void draw_player(int board[15][15] ,int i, int j) {
    point p = {i*60+30, j*60+30};
    if(board[i][j] == 0)
        draw_cross(p, 58, blue);
    if(board[i][j] == 1)
        draw_circle(p, 29, red);
}

void play(int board[15][15], int *winner, int size_tab_x, int size_tab_y, int nb) {
    init_graphics(60*size_tab_x,60*size_tab_y);
    init_board(board, size_tab_x, size_tab_y);
    draw_board(board, size_tab_x, size_tab_y);
    int joueur = 1;
    while(end(board, winner, size_tab_x, size_tab_y, nb)) {
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
}

int end(int board[15][15], int *winner, int size_tab_x, int size_tab_y, int nb) {
    for(int i = 0; i < size_tab_x; i++) {
        for(int j = 0; j < size_tab_y; j++) {
            if(board[i][j] != -1 ) {
                if(i+nb < size_tab_x && test_x(board, i, j, nb)) {
                    *winner = board[i][j];
                    return 0;
                }
                if(j+nb < size_tab_y && test_y(board, i, j, nb)) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+nb < size_tab_x && j+nb < size_tab_y && test_xy(board, i, j, nb)) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+nb < size_tab_x && j-nb > 0 && test_yx(board, i, j, nb)) {
                    *winner = board[i][j];
                    return 0;
                }
            }
        }
    }
    int k = 0;
    for(int i = 0; i < size_tab_x; i++) {
        for(int j = 0; j < size_tab_y; j++) {
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

int replay(int winner) {
    init_graphics(300,200);
    point pm; pm.y = 150;
    if(winner==-1) {
        pm.x = 100;
        aff_pol("Match Nul", 20, pm, white);
    }
    if(winner==0) {
        pm.x = 42;
        aff_pol("Joueur bleu a gagne !", 20, pm, blue);
    }
    if(winner==1) {
        pm.x = 40;
        aff_pol("Joueur rouge a gagne !", 20, pm, red);
    }
    point p = {101,86};
    aff_pol("Rejouer ?", 20, p, white);
    point p1 = {100,85}, p2 = {200,60};
    draw_rectangle(p1, p2, white);
    p.y = 51;
    aff_pol("Quitter  ?", 20, p, white);
    p1.y = 50; p2.y = 25;
    draw_rectangle(p1, p2, white);
    while(1) {
        p = wait_clic();
        if(p.x < 200 && p.x > 100) {
            if(p.y < 85 && p.y > 60)
                return 1;
            if(p.y < 50 && p.y > 25)
                return 0;
        }
    }
    return 0;
}

int test_x(int board[15][15], int i, int j, int nbtest){
    if(nbtest == 5)
        return board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j] && board[i][j]==board[i+4][j] && board[i][j]==board[i+5][j];
    if(nbtest == 4)
        return board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j] && board[i][j]==board[i+4][j];
    if(nbtest == 3)
        return board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j];
    if(nbtest == 2)
        return board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j];
    else 
        exit(0);
    return 1;
}

int test_y(int board[15][15], int i, int j, int nbtest){
    if(nbtest == 5)
        return board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3] && board[i][j]==board[i][j+4] && board[i][j]==board[i][j+5];
    if(nbtest == 4)
        return board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3] && board[i][j]==board[i][j+4];
    if(nbtest == 3)
        return board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3];
    if(nbtest == 2)
        return board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2];
    else 
        exit(0);
    return 1;
}

int test_xy(int board[15][15], int i, int j, int nbtest){
    if(nbtest == 5)
        return board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3] && board[i][j]==board[i+4][j+4] && board[i][j]==board[i+5][j+5];
    if(nbtest == 4)
        return board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3] && board[i][j]==board[i+4][j+4];
    if(nbtest == 3)
        return board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3];
    if(nbtest == 2)
        return board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2];
    else 
        exit(0);
    return 1;
}

int test_yx(int board[15][15], int i, int j, int nbtest){
    if(nbtest == 5)
        return board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3] && board[i][j]==board[i+4][j-4] && board[i][j]==board[i+5][j-5];
    if(nbtest == 4)
        return board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3] && board[i][j]==board[i+4][j-4];
    if(nbtest == 3)
        return board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3];
    if(nbtest == 2)
        return board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2];
    else 
        exit(0);
    return 1;
}
