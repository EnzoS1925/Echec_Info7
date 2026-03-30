#include <iostream>
#include "types.hpp"
#include "view.hpp"
using namespace std;

void init_board(PIECE tab[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tab[i][j] = VIDE;
        }
    }
}

void print_board(PIECE tab[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

PIECE get_square(int x, int y,PIECE tab[SIZE][SIZE]) {
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
        return tab[x][y];
    }
    return VIDE;
}

void set_square(int x, int y, PIECE tab[SIZE][SIZE],PIECE p) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        tab[x][y] = p;
    }
}

void start(PIECE tab[SIZE][SIZE]){
    for (int j=0;j<SIZE;j++){
        tab[1][j] = PION_N;
        tab[6][j] = PION_B;
    }
    // TOUR :
    tab[0][0] = TOUR_N;
    tab[0][7] = TOUR_N;
    tab[7][0] = TOUR_B;
    tab[7][7] = TOUR_B;
    // CAVALIER : 
    tab[0][1] = CAVALIER_N;
    tab[0][6] = CAVALIER_N;
    tab[7][1] = CAVALIER_B;
    tab[7][6] = CAVALIER_B;
    // FOU : 
    tab[0][2] = FOU_N;
    tab[0][5] = FOU_N;
    tab[7][2] = FOU_B;
    tab[7][5] = FOU_B;
    // REINE & ROI :
    tab[0][3] = ROI_N;
    tab[0][4] = REINE_N;
    tab[7][3] = REINE_B;
    tab[7][4] = ROI_B;
}


void move_piece(PIECE tab[SIZE][SIZE], int x, int y, int* point_noir, int* point_blanc) {
    PIECE p = get_square(x, y, tab);
    int new_x,new_y;
    cout << "Sur quel case voulez-vous aller ? (ligne & colonne) : ";
    cin >> new_x >> new_y;
    if (new_x < 0 || new_x >= SIZE) return;
    if (new_y <0 || new_y >= SIZE) return;
    PIECE a_prendre = get_square(new_x, new_y, tab);
    if (a_prendre == VIDE) {
        set_square(x, y, tab, VIDE);
        set_square(new_x, new_y, tab, p);
    } else {
        bool est_adverse = false;
        if (a_prendre >= ROI_B && a_prendre <= PION_B){
            est_adverse = true;
            (*point_noir)++;
        } 
        if (a_prendre >= ROI_N && a_prendre <= PION_N){
            est_adverse = true;
            (*point_blanc)++;
        }
        if (est_adverse) {
            set_square(new_x, new_y, tab, p);
            set_square(x, y, tab, VIDE);    
        }
    }
}


// Write_FEN doit envoyer dans un fichier txt.
void write_FEN(PIECE tab[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++) {
        int vides = 0;
        for (int j = 0; j < SIZE; j++) {
            PIECE p = tab[i][j];
            
            if (p == VIDE) {
                vides++;
            } else {
                if (vides > 0) {
                    cout << vides;
                    vides = 0;
                }
                cout << piece_2_FEN(p);
            }
        }
        if (vides > 0){
           cout << vides; 
        } 
        
        if (i < SIZE - 1){
            cout << "/";
        } 
    }
    cout << endl;
}

// READ_FEN lit dans le fichier txt.

