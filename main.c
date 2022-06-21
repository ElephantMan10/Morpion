#include "jeu.h"

int main() {
    int board[10][10];
    init_graphics(600,600);
    fill_screen(white);
    init_board(board);
    // board[2][6] = 1;
    // board[3][8] = 2;
    draw_board(board);
    play(board);
    wait_escape();
    return 0;
}