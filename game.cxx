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
        one_run_computer();
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

void choose_movement_computer(Plateau tab, int *x_init, int *y_init, int *x_dest, int *y_dest) {
    Masque m;
    int pieces_noires[64][2];
    int nb_pieces = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            PIECE p = get_square(i, j, tab);
            if (p >= ROI_N && p <= PION_N) {
                pieces_noires[nb_pieces][0] = i;
                pieces_noires[nb_pieces][1] = j;
                nb_pieces++;
            }
        }
    }
    bool mouvement_trouve = false;
    while (!mouvement_trouve && nb_pieces > 0) {
        int r = rand() % nb_pieces;
        int xi = pieces_noires[r][0];
        int yi = pieces_noires[r][1];
        clear_mask(m);
        highlight_possible_moves(xi, yi, tab, m);
        int dest_possibles[64][2];
        int nb_dest = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int val = get_mask(i, j, m);
                if (val == MASK_MOVE || val == MASK_CAPTURE) {
                    dest_possibles[nb_dest][0] = i;
                    dest_possibles[nb_dest][1] = j;
                    nb_dest++;
                }
            }
        }
        if (nb_dest > 0) {
            *x_init = xi;
            *y_init = yi;
            int choix_d = rand() % nb_dest; 
            *x_dest = dest_possibles[choix_d][0];
            *y_dest = dest_possibles[choix_d][1];
            mouvement_trouve = true;
        } else {
            pieces_noires[r][0] = pieces_noires[nb_pieces - 1][0];
            pieces_noires[r][1] = pieces_noires[nb_pieces - 1][1];
            nb_pieces--;
        }
    }
}

void one_run_computer(){
    Plateau board;
    Masque m;
    int xi, yi, xd, yd;
    int pts_B = 0, pts_N = 0;
    int joueur = 0;
    srand(time(NULL));
    init_board(board);
    start(board);
    while (pts_B < 15 && pts_N < 15) {
        print_board_FEN(board);
        if (joueur == 0) {
            cout << "[TOUR HUMAIN - BLANC]" << endl;
            cout << "Ligne et colonne de la piece : ";
            cin >> xi >> yi;
            clear_mask(m);
            highlight_possible_moves(xi, yi, board, m);
            print_board_with_mask(board, m);
            move_piece(board, xi, yi, &pts_N, &pts_B);
        } else {
            cout << "[TOUR ORDINATEUR - NOIR]" << endl;
            choose_movement_computer(board, &xi, &yi, &xd, &yd);
            PIECE p = get_square(xi, yi, board);
            PIECE cible = get_square(xd, yd, board);
            if (cible != VIDE) pts_N++; 
            set_square(xd, yd, board, p);
            set_square(xi, yi, board, VIDE);
            cout << "L'ordinateur a bouge de (" << xi << "," << yi << ") vers (" << xd << "," << yd << ")" << endl;
        }
        joueur = (joueur == 0) ? 1 : 0;
    }
    cout << "PARTIE FINIE. Blanc: " << pts_B << " Noir: " << pts_N << endl;
}
