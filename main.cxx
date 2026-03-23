#include <iostream>
#include "view.hpp"
#include "board.hpp"
using namespace std;



int main() {
    PIECE board[SIZE][SIZE];    
    init_board(board);
    start(board);
    print_board_FEN(board);
    move_piece(board,1,1);
    print_board_FEN(board);
    return 0;
}