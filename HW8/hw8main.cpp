/* 
 * File:   hw8classes.h
 * Author: Roy Van Liew and Saqib Zahid
 * Tic-Tac-Toe main application.
 * Last modified on April 19, 2014, 8:03 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "hw8classes.h"

using namespace std;

//int main()
//{
//    cout << "Instantiating a Critter object.\n\n";
//    
//    Critter crit;
//    crit.Greet();
//
//    return 0;
//}

int main()
{
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);

    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(board);

    while (winner(board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(board, human);
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }

    announceWinner(winner(board), computer, human);

    return 0;
}

