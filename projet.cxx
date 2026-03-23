#include <iostream>
using namespace std;

const int SIZE = 8;

enum PIECE {
    VIDE,
    ROI_N, REINE_N, TOUR_N, FOU_N, CAVALIER_N, PION_N,
    ROI_B, REINE_B, TOUR_B, FOU_B, CAVALIER_B, PION_B 
};

using Plateau = PIECE [SIZE][SIZE];

void init_board(PIECE tab[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tab[i][j] = VIDE;
        }
    }
}

void print_board(PIECE tab[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

PIECE get_square(int x, int y,PIECE tab[SIZE][SIZE]) {
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
        return tab[x][y];
    }
    return VIDE;
}

void set_square(int x, int y, PIECE tab[SIZE][SIZE],PIECE p) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        tab[x][y] = p;
    }
}

void start(PIECE tab[SIZE][SIZE]){
    for (int j=0;j<SIZE;j++){
        tab[1][j] = PION_N;
        tab[6][j] = PION_B;
    }
    // TOUR :
    tab[0][0] = TOUR_N;
    tab[0][7] = TOUR_N;
    tab[7][0] = TOUR_B;
    tab[7][7] = TOUR_B;
    // CAVALIER : 
    tab[0][1] = CAVALIER_N;
    tab[0][6] = CAVALIER_N;
    tab[7][1] = CAVALIER_B;
    tab[7][6] = CAVALIER_B;
    // FOU : 
    tab[0][2] = FOU_N;
    tab[0][5] = FOU_N;
    tab[7][2] = FOU_B;
    tab[7][5] = FOU_B;
    // REINE & ROI :
    tab[0][3] = ROI_N;
    tab[0][4] = REINE_N;
    tab[7][3] = REINE_B;
    tab[7][4] = ROI_B;
}


void move_piece(PIECE tab[SIZE][SIZE], int x, int y) {
    PIECE p = get_square(x, y, tab);
    int direction = 0;
    if (p >= ROI_N && p <= PION_N) {
        direction = 1;
    } else if (p >= ROI_B && p <= PION_B) {
        direction = -1;
    }
    int dep;
    cout << "De combien de cases voulez-vous avancer (1 ou 2) ? ";
    cin >> dep;
    if (dep < 1 || dep > 2) {
        return;
    }
    int new_x = x + (dep * direction);
    if (new_x >= 0 && new_x < SIZE) {
        if (get_square(new_x, y, tab) == VIDE) {
            set_square(x, y, tab, VIDE);
            set_square(new_x, y, tab, p);
        }
    }
}

// A mettre dans le fichier view.cxx après : 

char piece_2_FEN(PIECE p){
    switch (p){
        case ROI_N:      return 'k'; 
        case ROI_B:      return 'K';
        case REINE_N:    return 'q'; 
        case REINE_B:    return 'Q';
        case TOUR_N:     return 'r'; 
        case TOUR_B:     return 'R';
        case FOU_N:      return 'b'; 
        case FOU_B:      return 'B';
        case CAVALIER_N: return 'n'; 
        case CAVALIER_B: return 'N';
        case PION_N:     return 'p'; 
        case PION_B:     return 'P';
        default:         return '_';
    }
}

void print_board_FEN(PIECE tab[SIZE][SIZE]) {
    cout << "Board classique:" << endl;
    cout << "  -----------------------" << endl;
    cout << "  a b c d e f g h" << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << 8 - i << " "; 
        
        for (int j = 0; j < SIZE; j++) {
            cout << piece_2_FEN(tab[i][j]) << " ";
        }
        cout << 8 - i << endl;
    }

    cout << "  a b c d e f g h" << endl;
    cout << "  -----------------------" << endl;
}

void write_FEN(PIECE tab[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++) {
        int vides = 0;
        for (int j = 0; j < SIZE; j++) {
            PIECE p = tab[i][j];
            
            if (p == VIDE) {
                vides++;
            } else {
                if (vides > 0) {
                    cout << vides;
                    vides = 0;
                }
                cout << piece_2_FEN(p);
            }
        }
        if (vides > 0){
           cout << vides; 
        } 
        
        if (i < SIZE - 1){
            cout << "/";
        } 
    }
    cout << endl;
}

int main() {
    PIECE board[SIZE][SIZE];    
    init_board(board);
    start(board);
    print_board(board);
    move_piece(board,1,1);
    print_board(board);
    print_board_FEN(board);
    return 0;
}