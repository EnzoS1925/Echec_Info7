#ifndef BOARD_HPP
#define BOARD_HPP

#include "types.hpp"

void init_board(Plateau tab);

void start(Plateau tab);

PIECE get_square(int x, int y, Plateau tab);

void set_square(int x, int y, Plateau tab, PIECE p);

void move_piece(Plateau tab, int x, int y, int xd, int yd, int* point_noir, int* point_blanc);

void write_FEN(Plateau tab);

void read_FEN(Plateau tab);

bool king_in_check(Plateau tab, int joueur);

int compute_score(Plateau tab, int joueur);
#endif