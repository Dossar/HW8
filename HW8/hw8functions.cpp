/* 
 * File:   hw8functions.cpp
 * Author: Roy Van Liew and Saqib Zahid
 * This file contains the actual implementations for the application.
 * Last modified on April 19, 2014, 8:02 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "hw8classes.h"

using namespace std;

//void Critter::Greet()    
//{
//    cout << "Hi. I'm a critter.\n";
//}

void instructions()
{
    cout << "In this Tic-Tac-Toe your move should be a number between 0-8.:\n\n";

    // Display sample board for user.
    cout << "       0 | 1 | 2\n";
    cout << "       3 | 4 | 5\n";
    cout << "       6 | 7 | 8\n\n";

}

int askNumber(string question, int high, int low)
{
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    } while (number > high || number < low);

    return number;
}

/*
 * humanPiece asks if the user wants to go first or not.
 * askYesNo is called for the actual input.
 */
char humanPiece()
{
        char response;
    do
    {
        cout << "Do you want to go first? (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    if (response == 'y'){
        cout << "\nHuman player is going first.\n";
        return X;
    }
    else{
        cout << "\nComputer player is going first.\n";
        return O;
    }
}

char opponent(char piece)
{
    if (piece == X)
        return O;
    else
        return X;
}

void displayBoard(const vector<char>& board)
{
    cout << "\n\t*CURRENT*\n";
    cout << "\t" << board[0] << " | " << board[1] << " | " << board[2] << "\t[ 0 1 2 ]" << endl;
    cout << "\t" << board[3] << " | " << board[4] << " | " << board[5] << "\t[ 3 4 5 ]" << endl;
    cout << "\t" << board[6] << " | " << board[7] << " | " << board[8] << "\t[ 6 7 8 ]" << endl;
    cout << "\n";
}

char winner(const vector<char>& board)
{
    // This 2D array lists all the possible row combinations you can win with.
    // 0 | 1 | 2
    // 3 | 4 | 5
    // 6 | 7 | 8
    const int winRows[8][3] = { {0, 1, 2},
                                     {3, 4, 5},
                                     {6, 7, 8},
                                     {0, 3, 6},
                                     {1, 4, 7},
                                     {2, 5, 8},
                                     {0, 4, 8},
                                     {2, 4, 6} };
    const int TOTAL_ROWS = 8;

    // if any winning row has three values that are the same (and not EMPTY),
    // then we have a winner
    for(int row = 0; row < TOTAL_ROWS; ++row)
    {
        if ( ( board[ winRows[row][0] ] != EMPTY ) &&
             ( board[ winRows[row][0] ] == board[ winRows[row][1] ] ) &&
             ( board[ winRows[row][1] ] == board[ winRows[row][2] ] ) )
        {
            return board[ winRows[row][0] ];
        }
    }

    // since nobody has won, check for a tie (no empty squares left)
    if (count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    // since nobody has won and it isn't a tie, the game ain't over
    return NO_ONE;
}

inline bool isLegal(int move, const vector<char>& board)
{
    return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human)
{
    int move = askNumber("Where will you move?", (board.size() - 1));
    while (!isLegal(move, board))
    {
        cout << "\nThe square " << move << " is already occupied.\n";
        move = askNumber("Where will you move?", (board.size() - 1));
    }
    cout << "Human has chosen square " << move << endl;
    return move;
}

int computerMove(vector<char> board, char computer)
{
    cout << "Computer has chosen square ";
    
    // if computer can win on next move, make that move
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, board))
        {
            board[move] = computer;
            if (winner(board) == computer)
            {
                cout << move << endl;
                return move;
            }
            // done checking this move, undo it
            board[move] = EMPTY;
        }
    }
        
    // if human can win on next move, block that move
    char human = opponent(computer);
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, board))
        {
            board[move] = human;
            if (winner(board) == human)
            {
                cout << move << endl;
                return move;
            }
            // done checking this move, undo it
            board[move] = EMPTY;
        }
    }

    // the best moves to make, in order
    const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    // since no one can win on next move, pick best open square
    for(int i = 0; i < board.size(); ++i)
    {
        int move = BEST_MOVES[i];
        if (isLegal(move, board))
        {
            cout << move << endl;
            return move;
        }
    }
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
    {
        cout << winner << "'s won!\n";
        cout << "Computer player has won.\n";
    }

	else if (winner == human)
    {
        cout << winner << "'s won!\n";
        cout << "Human player has won.\n";
    }

	else
    {
        cout << "It's a tie.\n";
	}
}



