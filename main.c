#include "jeu.h"

int main() {
    init_graphics(600,600);
    init_board(board);
    board[2][6] = 1;
    board[3][8] = 2;
    draw_board(board);
    wait_escape();
    return 0;
}