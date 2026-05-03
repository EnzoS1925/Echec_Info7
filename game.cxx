#include <iostream>
#include "board.hpp"
#include "mask.hpp"
#include "view.hpp"
#include "types.hpp"
#include "game.hpp"
#include "historique.hpp"
using namespace std;

void one_run(){
    int choix;
    cout << "CHOIX TYPE PARTIE" << endl;
    cout << "\t {1} : Humain vs Humain " << endl;
    cout << "\t {2} : Humain vs IA " << endl;
    cout << "\t { } : Choix : ";
    cin >> choix;

    if (choix ==1){
        one_run_human();
    }else{
        one_run_computer();
    }
}

void one_run_human() {
    Game g;
    Plateau board;
    Masque m;
    int xi, yi, xd, yd;
    g.pts_blanc = 0;
    g.pts_noir = 0;
    g.joueur_actuel = 0;
    g.nb_coups = 0;
    init_board(board);
    start(board);
    while (g.pts_blanc < 15 && g.pts_noir < 15 && g.nb_coups < 50) {
        print_board_FEN(board);
    
        if (king_in_check(board, g.joueur_actuel)) {
            cout << "!!! ATTENTION : ROI EN ECHEC !!!" << endl;
        }
        cout << endl << "--- TOUR DU JOUEUR " << (g.joueur_actuel == 0 ? "BLANC" : "NOIR") << " ---" << endl;
        cout << "{1} Jouer | {2} Historique | {3} Annuler dernier coup| {4} Abandonner : ";
        int choix;
        cin >> choix;
        if (choix == 2) {
            play_historique(&g);
            continue;
        } 
        else if (choix == 3) {
            backtrack_historique(&g, board);
            continue;
        }
        else if (choix == 4) {
            cout << "Abandon. Victoire de l'adversaire !" << endl;
            return;
        }
        mask_choices(g.joueur_actuel, board, m);
        cout << "Ligne et colonne de la piece a deplacer : ";
        cin >> xi >> yi;
        PIECE p = get_square(xi, yi, board);
        bool piece_valide = (g.joueur_actuel == 0 && p >= ROI_B && p <= PION_B) ||
                            (g.joueur_actuel == 1 && p >= ROI_N && p <= PION_N);

        if (!piece_valide) {
            cout << "Erreur : Ce n'est pas votre pièce !" << endl;
            continue;
        }
        clear_mask(m);
        highlight_possible_moves(xi, yi, board, m);
        print_board_with_mask(board, m);
        cout << "Destination (ligne colonne) : ";
        cin >> xd >> yd;
        int val_mask = get_mask(xd, yd, m);
        if (val_mask == MASK_MOVE || val_mask == MASK_CAPTURE) {
            Plateau simu;
            for(int r=0; r<SIZE; r++) for(int c=0; c<SIZE; c++) simu[r][c] = board[r][c];
            simu[xd][yd] = simu[xi][yi];
            simu[xi][yi] = VIDE;

            if (king_in_check(simu, g.joueur_actuel)) {
                cout << "Coup interdit : votre Roi reste en échec !" << endl;
                continue;
            }
            MAJ_historique(&g, xi, yi, xd, yd, p);
            move_piece(board, xi, yi, xd, yd, &g.pts_noir, &g.pts_blanc);
            write_FEN(board);
            g.joueur_actuel = (g.joueur_actuel == 0) ? 1 : 0;
            cout << "Coup valide !" << endl;
        } else {
            cout << "Mouvement impossible (case non autorisée) !" << endl;
        }
    }
    int sB = compute_score(board, 0);
    int sN = compute_score(board, 1);
    cout << "SCORE FINAL - Blanc: " << sB << " | Noir: " << sN << endl;
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

void choose_movement_king_in_check_computer(Game *g, Plateau tab, int *xi, int *yi, int *xd, int *yd) {
    Plateau simu;
    bool coup_trouve = false;

    for (int i = 0; i < 100; i++) {
        choose_movement_computer(tab, xi, yi, xd, yd);
        
        // Simulation
        for(int r=0; r<SIZE; r++) for(int c=0; c<SIZE; c++) simu[r][c] = tab[r][c];
        simu[*xd][*yd] = simu[*xi][*yi];
        simu[*xi][*yi] = VIDE;

        if (!king_in_check(simu, g->joueur_actuel)) {
            coup_trouve = true;
            break;
        }
    }
    if (!coup_trouve) cout << "ECHEC ET MAT !" << endl;
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
            cout << "Destination (ligne colonne) : ";
            cin >> xd >> yd;
            move_piece(board, xi, yi, xd, yd, &pts_N, &pts_B);
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
