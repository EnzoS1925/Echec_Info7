#ifndef VIEW_HPP
#define VIEW_HPP

#include "types.hpp"
#include "mask.hpp"

char piece_2_FEN(PIECE p);

void print_board_FEN(Plateau tab);

void print_board(Plateau tab);

void print_board(Masque m);

#endif