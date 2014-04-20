/* 
 * File:   hw8classes.h
 * Author: Roy Van Liew and Saqib Zahid
 * This is the header file for the Tic Tac Toe OOP design.
 * This has function declarations (not definitions) and class definitions.
 * Last modified on April 19, 2014, 8:00 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef HW8CLASSES_H
#define	HW8CLASSES_H

//class Critter
//{
//public:
//    void Greet();
//};

// global constants
const char X = 'X'; // 1st player
const char O = 'O'; // 2nd player
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

// function prototypes
void instructions();
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

class Game {

	public:
		void instructions(); // Print out instructions
		char askNumber(); // Ask user to enter a choice on the board.
                char getTurn(){ return turn; } // Return what the current turn is.
                char changeTurn();
//                char changeTurn()
//                {
//                        if ( turn == X)
//                                return O;
//                        else
//                                return X;
//                }
                bool isLegal(const vector<char>& board, int move);
                void announceWinner(char winner, char computer, char human);
                
        protected:
                char turn; // This member variable stores whose turn it is (human or computer, X or O).
		

};

class Board : public Game {

	public:
		void displayBoard(); // Shows progress of the game with the current board moves.
                
	protected:
		vector<char> board; // This is the playing field.


};

// Generalization of a tic tac toe player.
// Human and COmputer inherit these members.
class AbstractPlayer : public Board {

	public:
		virtual int playerMove(); // This is for determining where a player moves on the board.
                char getSymbol(){ return symbol; } // Return player's symbol to display (X or O).

	protected:
		int pChoice; // Player's choice during the game to place on the board
		char symbol; // Symbol is either X or O for the game.

};

class Human : public AbstractPlayer {

	public:
                int playerMove(); // Determine user's move on the board.
		char goFirst(); // Prompt user to go first or not, computer does not decide this.

};

class Compter : public AbstractPlayer {
    
        public:
                int playerMove(); // Determine computer's move on the board.
};

#endif	/* HW8CLASSES_H */

