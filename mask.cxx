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
        case FOU_N: case FOU_B:
            highlight_possible_moves_bishop(x,y,tab,m);
        case PION_N: case PION_B:
            highlight_possible_moves_pawn(x,y,tab,m);
    }
}

void highlight_possible_moves_rook(int x, int y, Plateau tab, Masque m) {
    int color = 0;
    PIECE p = get_square(x, y, tab);
    if (p >= ROI_N && p <= PION_N) color = 2;
    else if (p >= ROI_B && p <= PION_B) color = 1;
    int target_color;

    // Vers la droite
    for (int j = y + 1; j < SIZE; j++) {
        PIECE p = get_square(x, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[x][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[x][j] = MASK_CAPTURE;
            break;
        } else {
            m[x][j] = MASK_VIDE;
            break;
        }
    }
    // Vers la gauche
    for (int j = y - 1; j >= 0; j--) {
        PIECE p = get_square(x, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[x][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[x][j] = MASK_CAPTURE;
            break;
        } else {
            m[x][j] = MASK_VIDE;
            break;
        }
    }
    // Direction : bas (i > x)
    for (int i = x + 1; i < SIZE; i++) {
        PIECE p = get_square(i, y, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][y] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][y] = MASK_CAPTURE;
            break;
        } else {
            m[i][y] = MASK_VIDE;
            break;
        }
    }
    // Vers le haut
    for (int i = x - 1; i >= 0; i--) {
        PIECE p = get_square(i, y, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;

        if (target_color == 0) {
            m[i][y] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][y] = MASK_CAPTURE;
            break;
        } else {
            m[i][y] = MASK_VIDE;
            break;
        }
    }
}

void highlight_possible_moves_bishop(int x,int y,Plateau tab,Masque m){
    int color = 0;
    PIECE p = get_square(x, y, tab);
    if (p >= ROI_N && p <= PION_N) color = 2;
    else if (p >= ROI_B && p <= PION_B) color = 1;
    int target_color;
    for(int i= x-1;i>=0;i--){
        for (int j=y-1;j>=0;j--){
            PIECE p = get_square(i,j,tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0){
                m[i][j] = MASK_MOVE;
            }else if(target_color != color) {
                m[i][j] = MASK_CAPTURE;
                break;
            }else{
                m[i][j]= MASK_VIDE;
                break;
            }
        }
    }
    for(int i= x-1;i>=0;i--){
        for (int j=y+1;j<SIZE;j++){
            PIECE p = get_square(i,j,tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0){
                m[i][j] = MASK_MOVE;
            }else if(target_color != color) {
                m[i][j] = MASK_CAPTURE;
                break;
            }else{
                m[i][j]= MASK_VIDE;
                break;
            }
        }
    }
    for(int i= x+1;i<SIZE;i++){
        for (int j=y-1;j>=0;j--){
            PIECE p = get_square(i,j,tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0){
                m[i][j] = MASK_MOVE;
            }else if(target_color != color) {
                m[i][j] = MASK_CAPTURE;
                break;
            }else{
                m[i][j]= MASK_VIDE;
                break;
            }
        }
    }
    for(int i= x+1;i<SIZE;i++){
        for (int j=y+1;j<SIZE;j++){
            PIECE p = get_square(i,j,tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0){
                m[i][j] = MASK_MOVE;
            }else if(target_color != color) {
                m[i][j] = MASK_CAPTURE;
                break;
            }else{
                m[i][j]= MASK_VIDE;
                break;
            }
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
                if (get_square(i,j,tab) != VIDE){
                    m[i][j] = MASK_VIDE;
                }
                if (get_square(x,y,tab) >= ROI_N && get_square(x,y,tab) <= PION_N){ // LE ROI EST NOIR.
                    if (get_square(i,j,tab) >= ROI_B  && get_square(i,j,tab) <= PION_B){  // ON VERIF SI LES PIONS AUTOUR SONT BLANC
                        m[i][j] = MASK_CAPTURE; // SI BLANC ALORS ON PEUX ATTAQUER
                    }
                }
                if (get_square(x,y,tab) >= ROI_B && get_square(x,y,tab) <= PION_B){ // LE ROI EST BLANC.
                    if (get_square(i,j,tab) >= ROI_N  && get_square(i,j,tab) <= PION_N){  // ON VERIF SI LES PIONS AUTOUR SONT NOIR
                        m[i][j] = MASK_CAPTURE; // SI NOIR ALORS ON PEUX ATTAQUER
                    }
                }
            }
        }
    }
}

void highlight_possible_moves_pawn(int x,int y,Plateau tab,Masque m){
    int color;
    if (get_square(x,y,tab) >= ROI_N && get_square(x,y,tab) <= PION_N ) color = 2;
    if (get_square(x,y,tab) >= ROI_B && get_square(x,y,tab) <= PION_B ) color = 1;

    if (color == 2 && x == 1){
        m[x+1][y] = MASK_MOVE;
        m[x+2][y] = MASK_MOVE;
    }
    if (color == 1 && x == 6){
        m[x-1][y] = MASK_MOVE;
        m[x-2][y] =MASK_MOVE;
    }
    if (color == 1){
        m[x-1][y] =MASK_MOVE;
    }else{
        m[x+1][y] =MASK_MOVE;
    }

    int target_color;
    if (color == 2){ // EST NOIR
        if (get_square(x+1,y+1,tab) >= ROI_N && get_square(x+1,y+1,tab) <= PION_N ) target_color = 2;
        if (get_square(x+1,y+1,tab) >= ROI_B && get_square(x+1,y+1,tab) <= PION_B ) target_color = 1;
        if (get_square(x+1,y+1,tab) == VIDE) target_color =0;
        if (target_color ==1){
            m[x+1][y+1] = MASK_CAPTURE;
        }else{
            m[x+1][y+1] = MASK_VIDE;
        }
        if (get_square(x+1,y-1,tab) >= ROI_N && get_square(x+1,y-1,tab) <= PION_N ) target_color = 2;
        if (get_square(x+1,y-1,tab) >= ROI_B && get_square(x+1,y-1,tab) <= PION_B ) target_color = 1;
        if (target_color == 1){
            m[x+1][y-1] = MASK_CAPTURE;
        }else{
            m[x+1][y-1] = MASK_VIDE;
        }
    }

    if (color == 1){ // EST BLANC
        if (get_square(x-1,y+1,tab) >= ROI_N && get_square(x-1,y+1,tab) <= PION_N ) target_color = 2;
        if (get_square(x-1,y+1,tab) >= ROI_B && get_square(x-1,y+1,tab) <= PION_B ) target_color = 1;
        if (get_square(x-1,y+1,tab) == VIDE) target_color =0;
        if (target_color ==2){
            m[x-1][y+1] = MASK_CAPTURE;
        }else{
            m[x-1][y+1] = MASK_VIDE;
        }
        if (get_square(x-1,y-1,tab) >= ROI_N && get_square(x-1,y-1,tab) <= PION_N ) target_color = 2;
        if (get_square(x-1,y-1,tab) >= ROI_B && get_square(x-1,y-1,tab) <= PION_B ) target_color = 1;
        if (target_color == 2){
            m[x-1][y-1] = MASK_CAPTURE;
        }else{
            m[x-1][y-1] = MASK_VIDE;
        }
    }
}

