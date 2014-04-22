/* 
 * File:   hw8classes.h
 * Author: Roy Van Liew and Saqib Zahid
 * Tic-Tac-Toe main application.
 * Last modified on April 21, 2014, 8:39 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "hw8classes.h"

using namespace std;


int main()
{
    
    // Create all the classes for the game.
    Board TTT_Board; // TTT for Tic Tac Toe, this is the playing field.
    Game TTT; // TTT for Tic Tac Toe. This object is an instance of one game of Tic Tac Toe.
    Human User;
    Computer AI;
    
    // Welcome the user to a game of Tic Tac Toe and set who's going first.
    TTT.instructions(); 
    User.goFirst();
    AI.computerSymbol( User.getSymbol() ); // Computer's symbol is opposite of player.
    
    // Simulate a round of playing the game. Keep going if the winner is no one 'N'.
    TTT_Board.displayBoard( User.getSymbol() , AI.getSymbol() );
    while ( TTT.checkWinner(TTT_Board) == 'N')
    {
        // See whose turn it is, then have the player fill in a spot on the board.
        if ( TTT.getTurn() == User.getSymbol() )
        {
            User.playerMove( TTT_Board );
        }
        else
        {
            AI.playerMove( TTT , TTT_Board , User.getSymbol() );
        }
        // After the player has filled in a spot, display the board again and change the turn.
        TTT_Board.displayBoard( User.getSymbol() , AI.getSymbol() );
        TTT.changeTurn();
    }
    
    // Getting to here means that there was either a winner or the board is full.
    TTT.announceWinner( TTT.checkWinner( TTT_Board ) , AI.getSymbol() , User.getSymbol() );
    
    return 0;
    
}

