#include "mask.hpp"
#include "board.hpp"
#include "view.hpp"
#include <iostream>
using namespace std;

void empty_mask(Masque m){
    for (int i=0;i<SIZE;i++){
        for (int j= 0;j<SIZE;j++){
            m[i][j] = 0;
        }
    }
}

void clear_mask(Masque m){
    empty_mask(m);
}

int get_mask(int x,int y,Masque m){
    if (x>= 0 && x<SIZE && y>=0 && y<SIZE){
        return m[x][y];
    }
    return 0;
}

void set_mask(int x,int y,Masque m,int val){
    if (x>= 0 && x<SIZE && y>=0 && y<SIZE){
        m[x][y]=val;
    }
}

void highlight_possible_moves(int x, int y, Plateau tab, Masque m) {
    PIECE p = get_square(x, y, tab);
    switch(p) {
        case ROI_N: case ROI_B:
            highlight_possible_moves_king(x, y, tab, m);
            break;
        case TOUR_N: case TOUR_B:
            highlight_possible_moves_rook(x, y, tab, m);
            break;
        case FOU_N: case FOU_B:
            highlight_possible_moves_bishop(x,y,tab,m);
            break;
        case PION_N: case PION_B:
            highlight_possible_moves_pawn(x,y,tab,m);
            break;
        case REINE_B: case REINE_N:
            highlight_possible_moves_queen(x,y,tab,m);
            break;
        case CAVALIER_B: case CAVALIER_N:
            highlight_possible_moves_knight(x,y,tab,m);
            break;
    }
}

void highlight_possible_moves_rook(int x, int y, Plateau tab, Masque m) {
    int color = 0;
    PIECE p = get_square(x, y, tab);
    if (p >= ROI_N && p <= PION_N) color = 2;
    else if (p >= ROI_B && p <= PION_B) color = 1;
    int target_color;

    // Vers la droite
    for (int j = y + 1; j < SIZE; j++) {
        PIECE p = get_square(x, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[x][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[x][j] = MASK_CAPTURE;
            break;
        } else {
            m[x][j] = MASK_VIDE;
            break;
        }
    }
    // Vers la gauche
    for (int j = y - 1; j >= 0; j--) {
        PIECE p = get_square(x, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[x][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[x][j] = MASK_CAPTURE;
            break;
        } else {
            m[x][j] = MASK_VIDE;
            break;
        }
    }
    // Vers le bas
    for (int i = x + 1; i < SIZE; i++) {
        PIECE p = get_square(i, y, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][y] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][y] = MASK_CAPTURE;
            break;
        } else {
            m[i][y] = MASK_VIDE;
            break;
        }
    }
    // Vers le haut
    for (int i = x - 1; i >= 0; i--) {
        PIECE p = get_square(i, y, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;

        if (target_color == 0) {
            m[i][y] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][y] = MASK_CAPTURE;
            break;
        } else {
            m[i][y] = MASK_VIDE;
            break;
        }
    }
}

void highlight_possible_moves_bishop(int x, int y, Plateau tab, Masque m) {
    int color = 0;
    PIECE p = get_square(x, y, tab);
    if (p >= ROI_N && p <= PION_N) color = 2;
    else if (p >= ROI_B && p <= PION_B) color = 1;
    int target_color;
    for (int i = x - 1; i >= 0; i--) {
        int j = y - 1 - (x - 1 - i);
        if (j < 0) break;
        PIECE p = get_square(i, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][j] = MASK_CAPTURE;
            break;
        } else {
            m[i][j] = MASK_VIDE;
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        int j = y + 1 + (x - 1 - i);
        if (j >= SIZE) break;
        PIECE p = get_square(i, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][j] = MASK_CAPTURE;
            break;
        } else {
            m[i][j] = MASK_VIDE;
            break;
        }
    }
    for (int i = x + 1; i < SIZE; i++) {
        int j = y - 1 - (i - x - 1);
        if (j < 0) break;
        PIECE p = get_square(i, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][j] = MASK_CAPTURE;
            break;
        } else {
            m[i][j] = MASK_VIDE;
            break;
        }
    }
    for (int i = x + 1; i < SIZE; i++) {
        int j = y + 1 + (i - x - 1);
        if (j >= SIZE) break;
        PIECE p = get_square(i, j, tab);
        if (p >= ROI_N && p <= PION_N) target_color = 2;
        else if (p >= ROI_B && p <= PION_B) target_color = 1;
        else target_color = 0;
        if (target_color == 0) {
            m[i][j] = MASK_MOVE;
        } else if (target_color != color) {
            m[i][j] = MASK_CAPTURE;
            break;
        } else {
            m[i][j] = MASK_VIDE;
            break;
        }
    }
}

void highlight_possible_moves_knight(int x,int y,Plateau tab,Masque m){
    int color =0;
    PIECE p = get_square(x, y, tab);
    if (p >= ROI_N && p <= PION_N) color = 2;
    else if (p >= ROI_B && p <= PION_B) color = 1;
    int target_color;

    // PARTIE SUPERIEURE GAUCHE : 
    int moves_sup_gauche[2][2] = {{x-2,y-1}, {x-1,y-2}};
    for (int k=0;k<2;k++){
        int i = moves_sup_gauche[k][0];
        int j = moves_sup_gauche[k][1];
        if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
            PIECE p = get_square(i, j, tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0) m[i][j] = MASK_MOVE;
            else if (target_color != color) m[i][j] = MASK_CAPTURE;
            else m[i][j] = MASK_VIDE;
        }
    }
    //PARTIE SUPERIEURE DROITE :
    int moves_sup_droit[2][2] = {{x-2,y+1},{x-1,y+2}};
    for (int k=0;k<2;k++){
        int i = moves_sup_droit[k][0];
        int j = moves_sup_droit[k][1];
        if (i >= 0 && i < SIZE && j >= 0 && j < SIZE){
            PIECE p = get_square(i, j, tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0) m[i][j] = MASK_MOVE;
            else if (target_color != color) m[i][j] = MASK_CAPTURE;
            else m[i][j] = MASK_VIDE;
        }
    }
    //PARTIE INFIERIEURE GAUCHE :
    int moves_inf_gauche[2][2] = {{x+2,y-1},{x+1,y-2}};
    for (int k=0;k<2;k++){
        int i = moves_inf_gauche[k][0];
        int j = moves_inf_gauche[k][1];
        if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
            PIECE p = get_square(i, j, tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0) m[i][j] = MASK_MOVE;
            else if (target_color != color) m[i][j] = MASK_CAPTURE;
            else m[i][j] = MASK_VIDE;
        }
    }
    //PARTIE INFERIEURE DROITE : 
    int moves_inf_droit[2][2] = {{x+2,y+1},{x+1,y+2}};
        for (int k=0;k<2;k++){
        int i = moves_inf_droit[k][0];
        int j = moves_inf_droit[k][1];
        if (i >= 0 && i < SIZE && j >= 0 && j < SIZE){
            PIECE p = get_square(i, j, tab);
            if (p >= ROI_N && p <= PION_N) target_color = 2;
            else if (p >= ROI_B && p <= PION_B) target_color = 1;
            else target_color = 0;
            if (target_color == 0) m[i][j] = MASK_MOVE;
            else if (target_color != color) m[i][j] = MASK_CAPTURE;
            else m[i][j] = MASK_VIDE;
        }
    }
}

void highlight_possible_moves_king(int x, int y, Plateau tab, Masque m) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                if (!(i == x && j == y)) {
                    m[i][j] = MASK_MOVE;
                }
                if (get_square(i,j,tab) != VIDE){
                    m[i][j] = MASK_VIDE;
                }
                if (get_square(x,y,tab) >= ROI_N && get_square(x,y,tab) <= PION_N){ // LE ROI EST NOIR.
                    if (get_square(i,j,tab) >= ROI_B  && get_square(i,j,tab) <= PION_B){  // ON VERIF SI LES PIONS AUTOUR SONT BLANC
                        m[i][j] = MASK_CAPTURE; // SI BLANC ALORS ON PEUX ATTAQUER
                    }
                }
                if (get_square(x,y,tab) >= ROI_B && get_square(x,y,tab) <= PION_B){ // LE ROI EST BLANC.
                    if (get_square(i,j,tab) >= ROI_N  && get_square(i,j,tab) <= PION_N){  // ON VERIF SI LES PIONS AUTOUR SONT NOIR
                        m[i][j] = MASK_CAPTURE; // SI NOIR ALORS ON PEUX ATTAQUER
                    }
                }
            }
        }
    }
}   // ESSAYER DE RENDRE LA FONCTION MOINS LOURDE

void highlight_possible_moves_queen(int x,int y,Plateau tab,Masque m){
    highlight_possible_moves_bishop(x,y,tab,m);
    highlight_possible_moves_rook(x,y,tab,m);
}

void highlight_possible_moves_pawn(int x, int y, Plateau tab, Masque m) {
    int color = 0;
    if (get_square(x,y,tab) >= ROI_N && get_square(x,y,tab) <= PION_N) color = 2;
    if (get_square(x,y,tab) >= ROI_B && get_square(x,y,tab) <= PION_B) color = 1;
    if (color == 2) {
        if (x + 1 < SIZE && get_square(x+1, y, tab) == VIDE) {
            m[x+1][y] = MASK_MOVE;
            if (x == 1 && x + 2 < SIZE && get_square(x+2, y, tab) == VIDE)
                m[x+2][y] = MASK_MOVE;
        }
        if (x + 1 < SIZE && y + 1 < SIZE) {
            PIECE target = get_square(x+1, y+1, tab);
            if (target >= ROI_B && target <= PION_B)
                m[x+1][y+1] = MASK_CAPTURE;
        }
        if (x + 1 < SIZE && y - 1 >= 0) {
            PIECE target = get_square(x+1, y-1, tab);
            if (target >= ROI_B && target <= PION_B)
                m[x+1][y-1] = MASK_CAPTURE;
        }
    }
    if (color == 1) {
        if (x - 1 >= 0 && get_square(x-1, y, tab) == VIDE) {
            m[x-1][y] = MASK_MOVE;
            if (x == 6 && x - 2 >= 0 && get_square(x-2, y, tab) == VIDE)
                m[x-2][y] = MASK_MOVE;
        }
        if (x - 1 >= 0 && y + 1 < SIZE) {
            PIECE target = get_square(x-1, y+1, tab);
            if (target >= ROI_N && target <= PION_N)
                m[x-1][y+1] = MASK_CAPTURE;
        }
        if (x - 1 >= 0 && y - 1 >= 0) {
            PIECE target = get_square(x-1, y-1, tab);
            if (target >= ROI_N && target <= PION_N)
                m[x-1][y-1] = MASK_CAPTURE;
        }
    }
}

void highlight_movables_pieces(int Player, Plateau tab, Masque m) {
    int color;
    if (Player == 0){
        color = 1;
    }else if (Player == 1){
        color = 2;
    }
    Masque temp_mask;
    empty_mask(temp_mask);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            PIECE p = get_square(i, j, tab);
            bool is_player_piece = (color == 2 && p >= ROI_N && p <= PION_N)
                                || (color == 1 && p >= ROI_B && p <= PION_B);
            if (!is_player_piece) continue;
            empty_mask(temp_mask);
            highlight_possible_moves(i, j, tab, temp_mask);
            bool can_move = false;
            for (int i = 0; i < SIZE && !can_move; i++) {
                for (int j = 0; j < SIZE && !can_move; j++) {
                    if (temp_mask[i][j] == MASK_MOVE or temp_mask[i][j] == MASK_CAPTURE) {
                        can_move = true;
                    }
                }
            }
            if (can_move) {
                m[i][j] = MASK_MOVE;
            }
        }
    }
}

void highlight_attacked_pieces(int Player, Plateau tab, Masque m){
    int color;
    if (Player==0){
        color = 1;
    }else if (Player == 1){
        color=2;
    }
    Masque attack_mask;
    empty_mask(attack_mask);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            PIECE p = get_square(i, j, tab);
            bool is_player_piece = (color == 2 && p >= ROI_N && p <= PION_N)
                                || (color == 1 && p >= ROI_B && p <= PION_B);
            if (!is_player_piece) continue;
            empty_mask(attack_mask);
            highlight_possible_moves(i, j, tab, attack_mask);
            bool can_attack = false;
            for (int i = 0; i < SIZE && !can_attack; i++) {
                for (int j = 0; j < SIZE && !can_attack; j++) {
                    if (attack_mask[i][j] == MASK_CAPTURE) {
                        can_attack = true;
                    }
                }
            }
            if (can_attack) {
                m[i][j] = MASK_CAPTURE;
            }
        }
    }
}

void highlight_take_pieces(int Player, Plateau tab, Masque m){
    int color;
    if (Player==0){
        color = 2;
    }else if (Player == 1){
        color=1;
    }
    Masque being_attacked_mask;
    empty_mask(being_attacked_mask);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            PIECE p = get_square(i, j, tab);
            bool is_player_piece = (color == 2 && p >= ROI_N && p <= PION_N)
                                || (color == 1 && p >= ROI_B && p <= PION_B);
            if (!is_player_piece) continue;
            empty_mask(being_attacked_mask);
            highlight_possible_moves(i, j, tab, being_attacked_mask);
            bool can_attack = false;
            for (int i = 0; i < SIZE && !can_attack; i++) {
                for (int j = 0; j < SIZE && !can_attack; j++) {
                    if (being_attacked_mask[i][j] == MASK_CAPTURE) {
                        can_attack = true;
                    }
                }
            }
            if (can_attack) {
                m[i][j] = MASK_CAPTURE;
            }
        }
    }
}

void mask_choices_menu(int Player,Plateau tab,Masque m){
        cout << "=====================================";
        int choix;
        cout << endl << "Pour voir les possibilités taper 1 " << endl;
        cout << "Pour déplacer les pièces sans regarder les possibilités taper 2 :";
        cin >> choix;
        if (choix == 1){
            cout << "=====================================" << endl;
            cout << "Menu des possibilités : "  << endl;
            int choix_masques;
            cout << "\t {1} : Pièces qui peuvent bouger" << endl << "\t {2} : Pièces qui peuvent attaquer" << endl << "\t {3} : Pièces qui peuvent se faire attaquer"<< endl
            << "\t {4} : Retour"<< endl;
            cin >> choix_masques;
            if (choix_masques == 1){
                highlight_movables_pieces(Player,tab,m);
                print_board_with_mask(tab,m);
            }else if (choix_masques == 2){
                highlight_attacked_pieces(Player,tab,m);
                print_board_with_mask(tab,m);
            }else if(choix_masques == 3){
                highlight_take_pieces(Player,tab,m);
                print_board_with_mask(tab,m);
            }else if (choix_masques == 4){
                print_board_with_mask(tab,m);
            }
        }
        if (choix == 2){
            return;
        }
}

void mask_choices(int Player,Plateau tab,Masque m){
    cout << "=====================================" << endl;
    int choix;
    cout << "{1} : Voir les possibilités." << endl << "{2} : Faire la combinaison de plusieurs de possibilités." << endl <<"{3} : Deplacer simplement les pièces : ";
    cin >> choix;
    if (choix == 1){
        cout << "=====================================" << endl;
        cout << "Menu des possibilités : "  << endl;
        int choix_masques;
        cout << "\t {1} : Pièces qui peuvent bouger" << endl << "\t {2} : Pièces qui peuvent attaquer" << endl << "\t {3} : Pièces qui peuvent se faire attaquer"<< endl
        << "\t {4} : Retour"<< endl;
        cin >> choix_masques;
        if (choix_masques == 1){
            clear_mask(m);
            highlight_movables_pieces(Player,tab,m);
            print_board_with_mask(tab,m);
        }else if (choix_masques == 2){
            clear_mask(m);
            highlight_attacked_pieces(Player,tab,m);
            print_board_with_mask(tab,m);
        }else if(choix_masques == 3){
            clear_mask(m);
            highlight_take_pieces(Player,tab,m);
            print_board_with_mask(tab,m);
        }else if (choix_masques == 4){
            print_board_with_mask(tab,m);
        }
    }else if (choix == 2){
        cout << "=====================================" << endl;
        cout << "Menu des possibilités : " << endl;
        int choix_masques;
        cout << "\t {1} : Pièces qui peuvent attaquer et se déplacer." << endl << "\t {2} : Pièces pouvant se deplacer et être attaqué.";
        cout << endl << "\t {3} : Pièces pouvant attaquer et être attaqué" << endl << "\t {4} : Retour : ";
        cin >> choix_masques;
        if (choix_masques == 1){
            highlight_movables_pieces(Player,tab,m);
            highlight_attacked_pieces(Player,tab,m);
            print_board_with_mask(tab,m);
        }else if (choix_masques == 2){
            highlight_movables_pieces(Player,tab,m);
            highlight_take_pieces(Player,tab,m);
            print_board_with_mask(tab,m);
        }else if(choix_masques == 3){
            highlight_take_pieces(Player,tab,m);
            highlight_attacked_pieces(Player,tab,m);
            print_board_with_mask(tab,m);
        }else if (choix_masques == 4){
            print_board_with_mask(tab,m);
        }
    }else if(choix == 3){
        print_board_with_mask(tab,m);
    }

}

