#include <iostream>
#include "types.hpp"
#include "board.hpp"
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
    cout << "  a  b  c  d  e  f  g  h " << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " "; 
        
        for (int j = 0; j < SIZE; j++) {
            if ((i+j)%2==0){
                cout << "\x1b[48;5;94m";
            }else{
                cout << "\x1b[48;5;223m";
            }
            // Ci-dessus Unicde en code ASCII pour mettre la couleur sur le plateau
            PIECE p = tab[i][j];
            if (p >= ROI_N && p <= PION_N){
                cout << "\x1b[38;5;0m";
            } else{
                cout << "\x1b[38;5;255m";
            }

            //Ajout des piece comme dans le jeux d'echec et non pas sous forme FEN.

            switch(p){
                case ROI_N:      cout << " ♚ "; break;
                case REINE_N:     cout << " ♛ "; break;
                case TOUR_N:     cout << " ♜ "; break;
                case FOU_N:      cout << " ♝ "; break;
                case CAVALIER_N: cout << " ♞ "; break;
                case PION_N:     cout << " ♟ "; break;
                case ROI_B:      cout << " ♔ "; break;
                case REINE_B:     cout << " ♕ "; break;
                case TOUR_B:     cout << " ♖ "; break;
                case FOU_B:      cout << " ♗ "; break;
                case CAVALIER_B: cout << " ♘ "; break;
                case PION_B:     cout << " ♙ "; break;
                case VIDE:       cout << "   "; break;
            }
            cout << "\x1b[0m";
        }
        cout << i << endl;
    }

    cout << "  a  b  c  d  e  f  g  h" << endl;
    cout << "  -----------------------" << endl;
}

void print_board(Masque m) {
    cout << "  a  b  c  d  e  f  g  h " << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i << " "; 
        for (int j = 0; j < SIZE; j++) {
            if ((i + j) % 2 == 0) {
                cout << "\x1b[48;5;94m";
            } else {
                cout << "\x1b[48;5;223m";
            }
            cout << "\x1b[38;5;0m"; 
            cout << " " << m[i][j] << " ";
            cout << "\x1b[0m";
        }
        cout << " " << i << endl;
    }
    cout << "  a  b  c  d  e  f  g  h" << endl;
}