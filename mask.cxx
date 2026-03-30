#include "mask.hpp"
#include "board.hpp"
#include <iostream>
using namespace std;

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

void highlight_possible_moves_rook(int x, int y, Plateau tab, Masque m) {
    int color;
    for (int i=0;i<SIZE;i++){
        if (get_square(x,y,tab) >= ROI_N && get_square(x,y,tab) <= PION_N ) color = 2;
        if (get_square(x,y,tab) >= ROI_B && get_square(x,y,tab) <= PION_B ) color = 1;

    }
    for (int i=0;i<SIZE;i++){
        if (i!=x){
            m[i][y] =MASK_MOVE;
        } 
        if (i!=y){
            m[x][i] = MASK_MOVE; 
        } 
    }
    int target_color;
    // On vérifie les couleurs sur la ligne
    for (int j = 0; j < SIZE; j++) {
        if (j == y) continue; 
        PIECE p = get_square(x, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;

        if (target_color == 0) {
            m[x][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[x][j] = MASK_CAPTURE;
        } else {
            m[x][j] = MASK_VIDE;
        }
    }
    // On vérifie les couleurs sur la colonne
    for (int i = 0; i < SIZE; i++) {
        if (i == x) continue;
        PIECE p = get_square(i, y, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][y] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][y] = MASK_CAPTURE;
        } else {
            m[i][y] = MASK_VIDE;
        }
    }
}

void highlight_possible_moves_king(int x, int y, Plateau tab, Masque m) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                if (!(i == x && j == y)) {
                    m[i][j] = MASK_MOVE;
                }
            }
        }
    }
}

