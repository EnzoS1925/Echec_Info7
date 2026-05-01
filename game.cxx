#include <iostream>
#include "board.hpp"
#include "mask.hpp"
#include "view.hpp"
#include "types.hpp"
using namespace std;

void one_run(){
    int choix;
    cout << "CHOIX TYPE PARTIE" << endl;
    cout << "\t {1} : Humain vs Humain " << endl;
    cout << "\t {2} : Humain vs IA " << endl;
    cout << "\t { } : Choix : " << endl;
    cin >> choix;

    if (choix ==1){
        one_run_human();
    }else{
        one_run_computer();
    }
}

void one_run_human(){

}

void one_run_computer(){
    
}