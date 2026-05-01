#include <iostream>
#include "board.hpp"
#include "mask.hpp"
#include "view.hpp"
#include "types.hpp"
#include "game.hpp"
using namespace std;

void one_run(){
    int choix;
    cout << "CHOIX TYPE PARTIE" << endl;
    cout << "\t {1} : Humain vs Humain " << endl;
    cout << "\t {2} : Humain vs IA " << endl;
    cout << "\t { } : Choix : " << endl;
    cin >> choix;

    if (choix ==1){
        one_run_human();
    }else{
        return;
    }
}

void one_run_human(){
    Plateau board;
    Masque m;
    int x, y;
    int pts_blanc = 0;
    int pts_noir = 0;
    int joueur_actuel = 0;
    int coup_jouer = 0;
    init_board(board);
    start(board);
    empty_mask(m);
    while (pts_blanc < 15 && pts_noir < 15) {
        cout << "TOUR DU JOUEUR " << (joueur_actuel == 0 ? "BLANC" : "NOIR") << endl;
        mask_choices(joueur_actuel, board, m);
        cout << "Quelle piece voulez-vous deplacer ? (ligne et colonne) : ";
        cin >> x >> y;
        PIECE p = get_square(x, y, board);
        bool piece_valide = (joueur_actuel == 0 && p >= ROI_B && p <= PION_B) ||
                            (joueur_actuel == 1 && p >= ROI_N && p <= PION_N);
        if (!piece_valide) {
            cout << "Erreur : Selectionnez une de vos pieces !" << endl;
            continue;
        }
        clear_mask(m);
        highlight_possible_moves(x, y, board, m);
        print_board_with_mask(board, m);
        move_piece(board, x, y, &pts_noir, &pts_blanc);
        print_board_FEN(board);
        coup_jouer++;
        cout << "Coup numero " << coup_jouer << " jouer." << endl;
        cout << "Points Noir : " << pts_noir << " | Points Blanc : " << pts_blanc << endl;
        joueur_actuel = (joueur_actuel == 0) ? 1 : 0;
    }
    cout << "PARTIE TERMINEE !" << endl;
    if (pts_blanc >= 15) cout << "Victoire des BLANCS !" << endl;
    else cout << "Victoire des NOIRS !" << endl;
}

void one_run_computer(){
    
}