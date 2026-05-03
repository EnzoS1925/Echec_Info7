#include "historique.hpp"
#include "view.hpp"
#include <iostream>
using namespace std;

void MAJ_historique(Game *g, int xi, int yi, int xd, int yd, PIECE p) {
    if (g->nb_coups < MAX_COUPS) {
        g->historique[g->nb_coups].x_dep = xi;
        g->historique[g->nb_coups].y_dep = yi;
        g->historique[g->nb_coups].x_arr = xd;
        g->historique[g->nb_coups].y_arr = yd;
        g->historique[g->nb_coups].piece_fen = piece_2_FEN(p);
        g->nb_coups++;
    }
}

void play_historique(Game *g) {
    cout << "=== HISTORIQUE ===" << endl;
    for (int i = 0; i < g->nb_coups; i++) {
        cout << "Coup " << i + 1 << " : [" << g->historique[i].piece_fen << "] ";
        cout << "(" << g->historique[i].x_dep << "," << g->historique[i].y_dep << ") -> ";
        cout << "(" << g->historique[i].x_arr << "," << g->historique[i].y_arr << ")" << endl;
    }
}

void backtrack_historique(Game *g, Plateau board) {
    if (g->nb_coups > 0) {
        g->nb_coups--;
        read_FEN(board); 
        g->joueur_actuel = (g->joueur_actuel == 0) ? 1 : 0;
        cout << "Retour en arriere effectue." << endl;
    } else {
        cout << "Aucun coup a annuler." << endl;
    }
}