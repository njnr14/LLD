#include "Board.h"
#include<bits/stdc++.h>
using namespace std;


Board::Board(int n) : dimension(n) , board(n,vector<char>(n,'*')) {}

void Board::displayBoard(){
    for(int i = 0 ; i < dimension ; i++){
        for(int j = 0 ; j < dimension ; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}


bool Board::isFull(){
    for(int i = 0 ; i < dimension ; i++){
        for(int j = 0 ; j < dimension ; j++){
            if(board[i][j]=='*')return false;
        }
    }

    return true;
}

bool Board::UpdateBoard(int r , int c, char symbol){
    if(r<0 || r>= dimension || c<0 ||c>= dimension || board[r][c]!='*'){
        return false;
    }
    board[r][c] = symbol;
    return true;
}


bool Board::checkWin(char symbol){
    for(int i = 0 ; i < dimension ; i++){
        bool rowWin = true;
        bool colWin = true;

        for(int j = 0 ; j < dimension ; j++){
            if(board[i][j]!=symbol){
                rowWin = false;
            }
            if(board[j][i]!=symbol){
                colWin = false;
            }
        }

        if(rowWin || colWin)return true;
    }


    bool diag = true;
    bool antiDiag = true;

    for(int i = 0 ; i < dimension ; i++){
        if(board[i][i]!=symbol)diag = false;
        if(board[i][dimension-i-1]!=symbol)antiDiag = false;
    }

    if(diag || antiDiag)return true;
    return false;
}