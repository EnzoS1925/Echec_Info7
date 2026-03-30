#include <iostream>
#include "view.hpp"
#include "board.hpp"
using namespace std;



int main() {
    PIECE board[SIZE][SIZE];    
    int coup_jouer =0;
    int x,y;
    int pts_blanc=0;
    int pts_noir=0;
    init_board(board);
    start(board);
    print_board_FEN(board);
/*
    while (pts_blanc != 15 or pts_noir != 15){
        cout << "Quel pièce voulez-vous déplacer ? (ligne et colonne)";
        cin >> x >> y;
        move_piece(board,x,y,&pts_noir,&pts_blanc);
        print_board_FEN(board);  
        coup_jouer++;
        cout << "Le nombre de coup déja jouer est : " << coup_jouer << endl;
        cout << "Points Noir : "  << pts_noir << "\t Points Blanc : " << pts_blanc << endl;
    }
        */
    write_FEN(board);
    read_FEN(board);
    return 0;
}