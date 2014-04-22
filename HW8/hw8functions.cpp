/* 
 * File:   hw8functions.cpp
 * Author: Roy Van Liew and Saqib Zahid
 * This file contains the actual implementations for the application.
 * Last modified on April 21, 2014, 8:36 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "hw8classes.h"

using namespace std;


/********************************************************
 *                      GAME FUNCTIONS                  *
 ********************************************************/

// This function explains how to play the game to the user.
void Game::instructions()
{
    cout << "\nWelcome. In this Tic-Tac-Toe your move should be a number between 0-8:\n\n";
    cout << "\t[ 0 | 1 | 2 ]" << endl;
    cout << "\t[ 3 | 4 | 5 ]" << endl;
    cout << "\t[ 6 | 7 | 8 ]\n" << endl;

}

// This function changes the turn after a player has chosen a spot.
void Game::changeTurn()
{
    if ( turn == 'X')
        turn = 'O';
    else
        turn = 'X';
}

// This function returns a character (X, O, N, or T) based on who won or not.
char Game::checkWinner(Board& gameBoard)
{
    // This 2D array lists all the possible row combinations you can win with.
    // 0 | 1 | 2
    // 3 | 4 | 5
    // 6 | 7 | 8
    const int winRows[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                                {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
    
    // check is a copy of the current game board.
    const vector<char> check = gameBoard.getBoard();

    // Traverse through winRows to find all possible winning rows.
    // Check all three numbers in the winning row.
    // If any winning row has the same character values and is not empty, there is a winner.
    for(int row = 0; row < 8 ; ++row)
    {
        if ( ( check[ winRows[row][0] ] != ' ' ) &&
             ( check[ winRows[row][0] ] == check[ winRows[row][1] ] ) &&
             ( check[ winRows[row][1] ] == check[ winRows[row][2] ] ) )
        {
            return check[ winRows[row][0] ]; // Return the character of the winner (X or O).
        }
    }

    // Getting to this point means there is not a clear winner. Check for a tie (no empty spots left).
    if ( count( check.begin() , check.end() , ' ' ) == 0 )
        return 'T'; // Return 'T' for tie.

    // If there is no winner and there is not a tie, the game is still going.
    return 'N'; // Return 'N' for nobody.
    
}

// When the winner is no longer 'N', that means the board is filled.
// This function outputs the winner or if there was a tie.
void Game::announceWinner( char winner, char computer, char human )
{
    
    if ( winner == computer ) {
        cout << "Computer has won." << endl;
    }
    else if ( winner == human ) {
        cout << "You won." << endl;
    }
    else {
        cout << "It's a tie." << endl;
    }
    
}

/********************************************************
 *                      HUMAN FUNCTIONS                 *
 ********************************************************/

// Ask the user if the user wants to go first in the game.
// This function also sets the user's symbol for the game (X or O).
void Human::goFirst()
{
    char response;
    do
    {
        cout << "Do you want to go first? (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    if (response == 'y'){
        cout << "\nYou are going first.\n";
        symbol = 'X';
    }
    else{
        cout << "\nComputer is going first.\n";
        symbol = 'O';
    }
    
}

// Determine spot to fill in from user.
void Human::playerMove( Board& gameBoard )
{
    int low = 0; // The lowest choice is the first spot in the board.
    int high = gameBoard.getSize() - 1; // Can only choose up to the max size of the board.
    int move; // Player's choice for the board.
    
    // User enters board spot. Spot has to be one that isn't filled in and is in bounds.
    do
    {
        cout << "Where will you move? ( " << low << " - " << high << " ): ";
        cin >> move;
        // If a spot is already occupied, it is not a legal move.
        if( !gameBoard.legal(move) ) {
            cout << "\nSorry, " << move << " is not a valid choice." << endl;
            move = -1;
        }
    } while ( move > high || move < low);
    
    gameBoard.changeBoard( move , symbol ); // Enter this move into the board with the player's symbol.
    cout << "You chose square " << move << endl;

}


/********************************************************
 *                   COMPUTER FUNCTIONS                 *
 ********************************************************/

// Determine the computer's symbol based on what the user entered.
void Computer::computerSymbol(char humanSymbol)
{
    if ( humanSymbol == 'X')
        symbol = 'O';
    else
        symbol = 'X';
}

// Determine spot to fill in from computer.
void Computer::playerMove( Game& game , Board& gameBoard , char human )
{
    
    int move, i; // Counters in the for loops. move determines the position of the symbol.
    cout << "Computer has chosen square ";
    
    // If computer can win on next move, make that move.
    for( move = 0; move < gameBoard.getSize() ; move++ )
    {
        if ( gameBoard.legal( move ) )
        {
            gameBoard.changeBoard( move , symbol );
            // Check if this move made the computer win.
            if ( game.checkWinner( gameBoard ) == symbol )
            {
                cout << move << endl;
                return;
            }
            // If the computer didn't win, undo the move by setting the spot empty again.
            gameBoard.changeBoard( move , ' ' );
        }
    }
        
    // Check if the human can win on the next move, block that move.
    for( move = 0 ; move < gameBoard.getSize() ; move++ )
    {
        if ( gameBoard.legal( move ) )
        {
            // Fill in a spot with the human's symbol and see if the human can win there.
            // If the human can win there, the computer fills in that spot.
            gameBoard.changeBoard( move , human );
            if ( game.checkWinner( gameBoard ) == human )
            {
                gameBoard.changeBoard( move , symbol );
                cout << move << endl;
                return;
            }
            // Otherwise, this means that the human can't win the next move. Set the spot empty again.
            gameBoard.changeBoard( move , ' ' );
        }
    }

    // These are the best moves to make in order.
    const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    
    // Since no one can win on the next move, pick the best open square.
    for( i = 0 ; i < gameBoard.getSize() ; i++ )
    {
        move = BEST_MOVES[i];
        if ( gameBoard.legal( move ) )
        {
            gameBoard.changeBoard( move , symbol );
            cout << move << endl;
            return;
        }
    }
    
}


/********************************************************
 *                   BOARD FUNCTIONS                    *
 ********************************************************/

// Show the current progress of the game. Also indicate the symbols of the players.
void Board::displayBoard( char user , char cpu )
{
    cout << "\n\tUser-" << user << "   AI-" << cpu << endl;
    cout << "\t[ " << board[0] << " | " << board[1] << " | " << board[2] << " ]\t[ 0 | 1 | 2 ]" << endl;
    cout << "\t[ " << board[3] << " | " << board[4] << " | " << board[5] << " ]\t[ 3 | 4 | 5 ]" << endl;
    cout << "\t[ " << board[6] << " | " << board[7] << " | " << board[8] << " ]\t[ 6 | 7 | 8 ]" << endl;
    cout << endl;
}

// Determine if a spot is already filled in.
bool Board::legal(int move)
{
    return ( board[move] == ' ' );
}

// Inserts a player's choice on the board, X or O.
void Board::changeBoard( int choice , char playerSymbol )
{
    board[choice] = playerSymbol;
}

