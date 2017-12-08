/* COMP11 Fall 2017
 * Homework 6
 * Andrew Sack
 * Signoff by Steven Song 11/17/17 */

#include <iostream>
#include <string>
#include "board.h"
#include "score_file.h"
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game {
    private:
    	// Board object
    	Board b;
    	// Score_File object
    	Score_File f;
        // whether the game is over
        bool game_over;

        // prompts user and performs a move
        void make_user_move();
        // prompts user for board size
        void get_user_size();
        // prints welcome message and instructions
        void print_instructions();
        // prompts user for name and performs end of game tasls
        void end_game();

    public:
        // constructor prototype
        Game();
        // destructor prototype
        ~Game();

        // performs game initialization 
        void start_game();

        // print function for debugging
        void test_print();
};

#endif