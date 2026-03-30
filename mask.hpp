#ifndef MASK_HPP
#define MASK_HPP
#include "types.hpp"

void empty_mask(Masque m);

void clear_mask(Masque m);

int get_mask(int x,int y,Masque m);

void set_mask(int x,int y,Masque m,int val);

void highlight_possible_moves(int x, int y, Plateau tab, Masque m);

void highlight_possible_moves_king(int x, int y, Plateau tab, Masque m);

void highlight_possible_moves_rook(int x, int y, Plateau tab, Masque m);

#endif