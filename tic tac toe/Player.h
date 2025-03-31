#ifndef PLAYER_H
#define PLAYER_H

#include<bits/stdc++.h>

using namespace std;

class Player{
    protected :
    string name;
    char Symbol;

    public :
    Player(const string & playName ,char playerSymbol);
    string getName();
    char getSymbol();
};





#endif