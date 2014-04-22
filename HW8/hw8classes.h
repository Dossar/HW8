/* 
 * File:   hw8classes.h
 * Author: Roy Van Liew and Saqib Zahid
 * This is the header file for the Tic Tac Toe OOP design.
 * This has function declarations and class definitions.
 * Last modified on April 22, 2014, 10:48 AM
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
                
	private:
		vector<char> board; // This is the playing field.

};

// Game monitors the status of the Tic Tac Toe game. It changes turns and checks for a winner.
class Game {

	public:
                // First turn is always X. Also initialize the winning rows.
                Game()
                {
                    turn = 'X';
                    //int winRows[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                    //                      {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
                    winRows[0][0] = 0, winRows[0][1] = 1, winRows[0][2] = 2, // {0, 1, 2}
                    winRows[1][0] = 3, winRows[1][1] = 4, winRows[1][2] = 5, // {3, 4, 5}
                    winRows[2][0] = 6, winRows[2][1] = 7, winRows[2][2] = 8, // {6, 7, 8}
                    winRows[3][0] = 0, winRows[3][1] = 3, winRows[3][2] = 6, // {0, 3, 6}
                    winRows[4][0] = 1, winRows[4][1] = 4, winRows[4][2] = 7, // {1, 4, 7}
                    winRows[5][0] = 2, winRows[5][1] = 5, winRows[5][2] = 8, // {2, 5, 8}
                    winRows[6][0] = 0, winRows[6][1] = 4, winRows[6][2] = 8, // {0, 4, 8}
                    winRows[7][0] = 2, winRows[7][1] = 4, winRows[7][2] = 6; // {2, 4, 6}
                }
                
		void instructions(); // Print out instructions
                char getTurn(){ return turn; } // Return what the current turn is.
                void changeTurn(); // Change the turn for after a player fills in a spot.
                char checkWinner( Board& gameBoard ); // Check if there's a winner, tie, or neither.
                void announceWinner(char winner, char computer, char human); // Output the winner.                
                
        private:
                char turn; // Stores the current turn (X or O).
                int winRows[8][3]; // Lists all possible ways to win.
		
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
                // Computer constructor initializes the bestMoves array.
                Computer()
                {
                    // bestMoves[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
                    bestMoves[0] = 4, bestMoves[1] = 0, bestMoves[2] = 2,
                    bestMoves[3] = 6, bestMoves[4] = 8, bestMoves[5] = 1,
                    bestMoves[6] = 3, bestMoves[7] = 5, bestMoves[8] = 7;                
                }
                void playerMove( Game& game , Board& gameBoard , char human ); // Determine computer's move on the board.
                void computerSymbol(char humanSymbol); // Set computer's symbol (X or O) depending on user symbol.
        private:
                int bestMoves[9]; // These are the best moves to make in order.

};

#endif	/* HW8CLASSES_H */

