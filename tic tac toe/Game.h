#ifndef Game_H
#define Game_H

#include<bits/stdc++.h>
#include "Board.h"
#include "Player.h"
using namespace std;

class Game{
    private:
    Board board;
    Player player1;
    Player player2;
    Player *current_player;
    bool isGameover;

    public:
    Game(const string &player1Name , const string &player2Name , int boardsize);
    void start();
    void playerTurn();
    bool isDraw();
};


#endif