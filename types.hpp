const int SIZE = 8;

enum PIECE {
    VIDE,
    ROI_N, REINE_N, TOUR_N, FOU_N, CAVALIER_N, PION_N,
    ROI_B, REINE_B, TOUR_B, FOU_B, CAVALIER_B, PION_B 
};

using Plateau = PIECE [SIZE][SIZE];