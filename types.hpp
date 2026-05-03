#ifndef TYPES_HPP
#define TYPES_HPP

const int MAX_COUPS = 200;
const int SIZE = 8;
const int MASK_VIDE      = 0;
const int MASK_SELECTED  = 1;
const int MASK_MOVE      = 2;
const int MASK_CAPTURE   = 3;

enum PIECE {
    VIDE,
    ROI_N, REINE_N, TOUR_N, FOU_N, CAVALIER_N, PION_N,
    ROI_B, REINE_B, TOUR_B, FOU_B, CAVALIER_B, PION_B 
};

using Plateau = PIECE [SIZE][SIZE];

using Masque = int [SIZE][SIZE];

// HSISTORIQUE : 

struct Coup {
    int x_dep, y_dep;
    int x_arr, y_arr;
    char piece_fen;
};

struct Game {
    int pts_blanc;
    int pts_noir;
    int joueur_actuel;
    Coup historique[MAX_COUPS];
    int nb_coups;
};

#endif