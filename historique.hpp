#ifndef HISTORIQUE_HPP
#define HISTORIQUE_HPP

#include "types.hpp"
#include "board.hpp"

void MAJ_historique(Game *g, int xi, int yi, int xd, int yd, PIECE p);

void play_historique(Game *g);

void backtrack_historique(Game *g, Plateau board);

#endif