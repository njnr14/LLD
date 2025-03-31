#include "Player.h"
#include<bits/stdc++.h>

using namespace std;

Player::Player(const string &playerName , char playerSymbol) : name(playerName) , Symbol(playerSymbol) {}

string Player::getName(){
    return name;
}

char Player::getSymbol(){
    return Symbol;
}


