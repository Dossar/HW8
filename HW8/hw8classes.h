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
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

#endif	/* HW8CLASSES_H */

