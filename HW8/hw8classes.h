/* 
 * File:   hw8classes.h
 * Author: Roy Van Liew and Saqib Zahid
 * This is the header file for the Tic Tac Toe OOP design.
 * This has function declarations and class definitions.
 * Last modified on April 21, 2014, 8:37 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef HW8CLASSES_H
#define	HW8CLASSES_H

// Board is the class that represents a playing field of Tic Tac Toe.
class Board {

	public:
                // Create an empty tic tac toe board. 9 spots, fill with space characters.
                Board()
                {
                    int i;
                    for ( i = 0 ; i < 9 ; i++ )
                        board.push_back(' ');
                }
                
                // Board functions, including mutator
		void displayBoard( char user , char cpu ); // Shows progress of the game.
                void changeBoard( int choice , char playerSymbol ); // Mutator, inserts character into board
                bool legal(int move); // Determines if player's choice is acceptable               

                // Board accessors.
                vector<char> getBoard(){ return board; } // Get a copy of the board.
                int getSize(){ return board.size(); } // Get the size of the board for bounds.
                
	protected:
		vector<char> board; // This is the playing field.


};

// Game monitors the status of the Tic Tac Toe game. It changes turns and checks for a winner.
class Game {

	public:
                // First turn is always X.
                Game()
                {
                    turn = 'X';
                }
                
		void instructions(); // Print out instructions
                char getTurn(){ return turn; } // Return what the current turn is.
                void changeTurn(); // Change the turn for after a player fills in a spot.
                char checkWinner( Board& gameBoard ); // Check if there's a winner, tie, or neither.
                void announceWinner(char winner, char computer, char human); // Output the winner.
                
        protected:
                char turn; // This member variable stores whose turn it is (human or computer, X or O).
		

};

// Generalization of a tic tac toe player. Human and Computer inherit these members.
class AbstractPlayer {

	public:
		virtual void playerMove( Board& gameBoard ){} // This is for determining where a player moves on the board.
                char getSymbol(){ return symbol; } // Return player's symbol to display (X or O).

	protected:
		char symbol; // Symbol is either X or O for the game.

};

// The class for the user playing. The user decides who goes first.
class Human : public AbstractPlayer {

	public:
                void playerMove( Board& gameBoard ); // Determine user's move on the board.
		void goFirst(); // Set the user's symbol (X or O), determines if user goes first or not.

};

// The class for the computer player.
class Computer : public AbstractPlayer {
    
        public:
                void playerMove( Game& game , Board& gameBoard , char human ); // Determine computer's move on the board.
                void computerSymbol(char humanSymbol); // Set computer's symbol (X or O) depending on user symbol.

};

#endif	/* HW8CLASSES_H */

