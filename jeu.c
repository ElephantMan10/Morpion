#include "jeu.h"

void menu() {
    // init_graphics(400,400);
    int size_tab = 11;
    int nb = 3;
    int board[15][15];
    int winner;
    int r = 1;
    while(r) {
        play(board, &winner, size_tab, nb);
        r = replay(winner);
    }
}

void init_board(int board[15][15], int size_tab) {
    for(int i = 0; i < size_tab; i++) {
        for(int j = 0; j < size_tab; j++) {
            board[i][j] = -1;
        }
    }
}

void draw_board(int board[15][15], int size_tab) {
    point p1, p2;
    for(int i = 0; i < size_tab; i++) {
        for(int j = 0; j < size_tab; j++) {
            p1.x = i*60+60; p1.y = 0;
            p2.x = i*60+60; p2.y = 60*size_tab;
            draw_big_line(p1,p2,lightgrey);
            p1.y = i*60+60; p1.x = 0;
            p2.y = i*60+60; p2.x = 60*size_tab;
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

void play(int board[15][15], int *winner, int size_tab, int nb) {
    init_graphics(60*size_tab,60*size_tab);
    init_board(board, size_tab);
    draw_board(board, size_tab);
    int joueur = 1;
    while(end(board, winner, size_tab, nb)) {
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

int end(int board[15][15], int *winner, int size_tab, int nb) {
    for(int i = 0; i < size_tab; i++) {
        for(int j = 0; j < size_tab; j++) {
            if(nb == 3) {
                if(i+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(j+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+size_tab < size_tab && j+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+size_tab < size_tab && j-size_tab > 0 && board[i][j] != -1 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3]) {
                    *winner = board[i][j];
                    return 0;
                }
            }
            if(nb == 4) {
                if(i+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j] && board[i][j]==board[i+4][j]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(j+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3] && board[i][j]==board[i][j+4]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+size_tab < size_tab && j+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3] && board[i][j]==board[i+4][j+4]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+size_tab < size_tab && j-size_tab > 0 && board[i][j] != -1 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3] && board[i][j]==board[i+4][j-4]) {
                    *winner = board[i][j];
                    return 0;
                }
            }
            if(nb == 5) {
                if(i+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j] && board[i][j]==board[i+4][j] && board[i][j]==board[i+5][j]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(j+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3] && board[i][j]==board[i][j+4] && board[i][j]==board[i][j+5]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+size_tab < size_tab && j+size_tab < size_tab && board[i][j] != -1 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3] && board[i][j]==board[i+4][j+4] && board[i][j]==board[i+5][j+5]) {
                    *winner = board[i][j];
                    return 0;
                }
                if(i+size_tab < size_tab && j-size_tab > 0 && board[i][j] != -1 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3] && board[i][j]==board[i+4][j-4] && board[i][j]==board[i+5][j-5]) {
                    *winner = board[i][j];
                    return 0;
                }
            }
        }
    }
    int k = 0;
    for(int i = 0; i < size_tab; i++) {
        for(int j = 0; j < size_tab; j++) {
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

// int test_x(int board[15][15], int i, int j, int nbtest){
//     if(nbtest == 5)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j] && board[i][j]==board[i+4][j] && board[i][j]==board[i+5][j];
//     if(nbtest == 4)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j] && board[i][j]==board[i+4][j];
//     if(nbtest == 3)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j];
//     else 
//         exit(0);
//     return 1;
// }

// int test_y(int board[15][15], int i, int j, int nbtest){
//     if(nbtest == 5)
//         return board[i][j] != -1 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3] && board[i][j]==board[i][j+4] && board[i][j]==board[i][j+5];
//     if(nbtest == 4)
//         return board[i][j] != -1 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3] && board[i][j]==board[i][j+4];
//     if(nbtest == 3)
//         return board[i][j] != -1 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3];
//     else 
//         exit(0);
//     return 1;
// }

// int test_xy(int board[15][15], int i, int j, int nbtest){
//     if(nbtest == 5)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3] && board[i][j]==board[i+4][j+4] && board[i][j]==board[i+5][j+5];
//     if(nbtest == 4)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3] && board[i][j]==board[i+4][j+4];
//     if(nbtest == 3)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3];
//     else 
//         exit(0);
//     return 1;
// }

// int test_yx(int board[15][15], int i, int j, int nbtest){
//     if(nbtest == 5)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3] && board[i][j]==board[i+4][j-4] && board[i][j]==board[i+5][j-5];
//     if(nbtest == 4)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3] && board[i][j]==board[i+4][j-4];
//     if(nbtest == 3)
//         return board[i][j] != -1 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3];
//     else 
//         exit(0);
//     return 1;
// }
