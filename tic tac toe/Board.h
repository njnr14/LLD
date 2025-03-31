#ifndef Board_h
#define Board_h

#include<bits/stdc++.h>

using namespace std;

class Board{
    private :  
        int dimension;
        vector<vector<char>> board;
    public:
        Board(const int boardSize);
        void displayBoard();
        bool isFull();
        bool UpdateBoard(int r, int c, char symbol);
        bool checkWin(char symbol);

};



#endif