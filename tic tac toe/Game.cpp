#include "Game.h"
#include<bits/stdc++.h>

using namespace std;

Game::Game(const string &player1Name , const string &player2Name , int boardsize): player1(
    player1Name , 'X'
) , player2(player2Name , 'O') , board(boardsize) , current_player(&player1) , isGameover(false){}


void Game::start(){
    cout<<"Tic Tac Toe Game: \n";
    board.displayBoard();

    while(!isGameover){
        playerTurn();
        board.displayBoard();

        if(board.checkWin(current_player->getSymbol())){
        cout<<current_player->getName()<<" is the winner \n";
        isGameover  = true;
        }

        else if(board.isFull()){
            cout<<"it's a draw \n";
            isGameover = true;
        }

        else{
            current_player = current_player== (&player1) ? &player2 : &player1;
        }
    
    }
}

void Game::playerTurn(){
    cout<<current_player->getName()<<" enter the next move i.e (row,col) \n";
    int r ,c;
    cin>>r>>c;

    while(!board.UpdateBoard(r,c,current_player->getSymbol())){
        cout<<"invalid move please enter again \n";
        cin>>r>>c;
    }

}


bool Game::isDraw(){
    return board.isFull() || (!board.checkWin(player1.getSymbol()) && !board.checkWin(player2.getSymbol()));
}