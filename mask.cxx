#include "mask.hpp"
#include "board.hpp"
#include <iostream>

void empty_mask(Masque m){
    for (int i=0;i<SIZE;i++){
        for (int j= 0;j<SIZE;j++){
            m[i][j] = 0;
        }
    }
}

void clear_mask(Masque m){
    empty_mask(m);
}

int get_mask(int x,int y,Masque m){
    if (x>= 0 && x<SIZE && y>=0 && y<SIZE){
        return m[x][y];
    }
    return 0;
}

void set_mask(int x,int y,Masque m,int val){
    if (x>= 0 && x<SIZE && y>=0 && y<SIZE){
        m[x][y]=val;
    }
}

void highlight_possible_moves(int x, int y, Plateau tab, Masque m) {
    clear_mask(m);
    PIECE p = get_square(x, y, tab);
    switch(p) {
        case ROI_N: case ROI_B:
            highlight_possible_moves_king(x, y, tab, m);
            break;
        case TOUR_N: case TOUR_B:
            highlight_possible_moves_rook(x, y, tab, m);
            break;
    }
}

void highlight_possible_moves_king(int x, int y, Plateau tab, Masque m) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) continue;
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                m[i][j] = 1;
            }
        }
    }
}

void highlight_possible_moves_rook(int x, int y, Plateau tab, Masque m) {
    for (int i = 0; i < SIZE; i++) {
        if (i != x) m[i][y] = 1;
        if (i != y) m[x][i] = 1; 
    }
}