#include <iostream>
#include "types.hpp"
#include "view.hpp"
#include <fstream>
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


void move_piece(Plateau tab, int x, int y, int xd, int yd, int* point_noir, int* point_blanc) {
    PIECE p = get_square(x, y, tab);
    PIECE a_prendre = get_square(xd, yd, tab);
    if (a_prendre != VIDE) {
        if (a_prendre >= ROI_B && a_prendre <= PION_B) (*point_noir)++;
        if (a_prendre >= ROI_N && a_prendre <= PION_N) (*point_blanc)++;
    } 
    set_square(xd, yd, tab, p);
    set_square(x, y, tab, VIDE);
}


// Write_FEN doit envoyer dans un fichier txt.
void write_FEN(PIECE tab[SIZE][SIZE]){
    ofstream sortie("Fen.txt");
    if (sortie){
            for (int i = 0; i < SIZE; i++) {
        int vides = 0;
        for (int j = 0; j < SIZE; j++) {
            PIECE p = tab[i][j];
            
            if (p == VIDE) {
                vides++;
            } else {
                if (vides > 0) {
                    sortie << vides;
                    vides = 0;
                }
                sortie << piece_2_FEN(p);
            }
        }
        if (vides > 0){
           sortie << vides; 
        } 
        
        if (i < SIZE - 1){
            sortie << "/";
        } 
    }
    sortie << endl;
    }
    else{
        cout << "ERREUR : Impossible d'ouvrir le fichier." << endl;
    }
}

// READ_FEN lit dans le fichier txt.

void read_FEN(PIECE tab[SIZE][SIZE]){
    ifstream entree("Fen.txt");
    if(entree){
        cout << "Lecture is GOOD"<< endl;
    }
    else{
        cout << "ERREUR : Impossible d'ouvrir le fichier en lecture" << endl;
    }
}

bool king_in_check(Plateau tab, int joueur) {
    int x_roi = -1, y_roi = -1;
    PIECE cible = (joueur == 0) ? ROI_B : ROI_N;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (tab[i][j] == cible) {
                x_roi = i; y_roi = j;
                break;
            }
        }
    }
    Masque m_adv;
    int adversaire = (joueur == 0) ? 1 : 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            PIECE p = tab[i][j];
            bool est_adverse = (adversaire == 0) ? (p >= ROI_B && p <= PION_B) : (p >= ROI_N && p <= PION_N);
            
            if (est_adverse) {
                empty_mask(m_adv);
                highlight_possible_moves(i, j, tab, m_adv);
                if (get_mask(x_roi, y_roi, m_adv) == MASK_CAPTURE) return true;
            }
        }
    }
    return false;
}

int compute_score(Plateau tab, int joueur) {
    int score = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            PIECE p = tab[i][j];
            bool mienne = (joueur == 0) ? (p >= ROI_B && p <= PION_B) : (p >= ROI_N && p <= PION_N);
            if (mienne) {
                if (p == PION_B || p == PION_N) score += 1;
                else if (p == CAVALIER_B || p == CAVALIER_N || p == FOU_B || p == FOU_N) score += 3;
                else if (p == TOUR_B || p == TOUR_N) score += 5;
                else if (p == REINE_B || p == REINE_N) score += 9;
            }
        }
    }
    return score;
}
