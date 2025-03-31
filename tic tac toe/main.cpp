#include<bits/stdc++.h>
#include "Game.h"

using namespace std;



int main(){
    int boardSize;
    string Player1;
    string Player2;

    cout<<"enter the board size: \n";
    cin>>boardSize;

    cout<<"enter player1 name: \n";
    cin>>Player1;
    cout<<"enter player2 name: \n";
    cin>>Player2;

    Game TicTacToe(Player1,Player2,boardSize);

    TicTacToe.start();

}