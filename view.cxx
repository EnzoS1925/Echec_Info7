#include <iostream>
#include <types.hpp>
using namespace std;

char piece_2_FEN(PIECE p){
    switch (p){
        case ROI_N:      return 'k'; 
        case ROI_B:      return 'K';
        case REINE_N:    return 'q'; 
        case REINE_B:    return 'Q';
        case TOUR_N:     return 'r'; 
        case TOUR_B:     return 'R';
        case FOU_N:      return 'b'; 
        case FOU_B:      return 'B';
        case CAVALIER_N: return 'n'; 
        case CAVALIER_B: return 'N';
        case PION_N:     return 'p'; 
        case PION_B:     return 'P';
        default:         return '_';
    }
}

void print_board_FEN(PIECE tab[SIZE][SIZE]) {
    cout << "Board classique:" << endl;
    cout << "  -----------------------" << endl;
    cout << "  a b c d e f g h" << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << 8 - i << " "; 
        
        for (int j = 0; j < SIZE; j++) {
            cout << piece_2_FEN(tab[i][j]) << " ";
        }
        cout << 8 - i << endl;
    }

    cout << "  a b c d e f g h" << endl;
    cout << "  -----------------------" << endl;
}

int main(){

    return 0;
}