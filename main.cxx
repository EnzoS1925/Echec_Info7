#include <iostream>
#include "view.hpp"
#include "board.hpp"
#include "mask.hpp"
using namespace std;



int main() {
    PIECE board[SIZE][SIZE]; 
    Masque m;   
    int coup_jouer =0;
    int x,y;
    int pts_blanc=0;
    int pts_noir=0;
    int joueur_actuel = 0;
    init_board(board);
    start(board);
    empty_mask(m); 
    print_board_FEN(board);


    /* TEST DES PIECES QUI PEUVENT BOUGER.
    highlight_movables_pieces(1,board,m);
    print_board_with_mask(board,m);
    clear_mask(m);
    */

    /*TEST DES PIECES QUI PEUVENT ATTAQUER
    set_square(2,3,board,PION_B);
    highlight_attacked_pieces(0,board,m);
    print_board_with_mask(board,m);
    clear_mask(m); */

    /*TEST DES PIECES QUI VONT SE FAIRE ATTAQUER
    set_square(2,3,board,PION_B);
    highlight_take_pieces(0,board,m);
    print_board_with_mask(board,m);
    clear_mask(m);
*/


    while (pts_blanc != 15 && pts_noir != 15){
        mask_choices(joueur_actuel,board,m);
        cout << "Quel pièce voulez-vous déplacer ? (ligne et colonne)";
        cin >> x >> y;
        clear_mask(m);
        highlight_possible_moves(x,y,board,m);
        print_board_with_mask(board,m);
        move_piece(board,x,y,&pts_noir,&pts_blanc); 
        print_board_FEN(board);
        coup_jouer++;
        cout << "Le nombre de coup déja jouer est : " << coup_jouer << endl;
        cout << "Points Noir : "  << pts_noir << "\t Points Blanc : " << pts_blanc << endl;
        if (joueur_actuel == 0){
            joueur_actuel++;
        }else if(joueur_actuel == 1){
            joueur_actuel--;
        }
    }
    return 0;
}