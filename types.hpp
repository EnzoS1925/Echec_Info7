#ifndef TYPES_HPP
#define TYPES_HPP

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

#endif