/* COMP11 Fall 2017
 * Homework 6
 * Andrew Sack
 * Signoff by Steven Song 11/17/17 */

#include <iostream>
#include <string>
#include <ctime> // used for seeding random numbers
#include <cstdlib>
using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

class Board {
    private:
        // size of the board
        int dimen;
        // 2D array of tiles
        int **board;
        // game score 
        int score;
        // whether board has been properly initialized
        bool board_exists;

        // places random tile on board
        void add_rand_tile(bool just_2);
        // performs shift/merge for a single row/column
        void single_shift(int vec[], int &new_points);
        // checks that board_exists is true and gives an error otherwise
        bool check_board_exists();               

    public:
        // constructor prototype
        Board();
        // destructor prototype
        ~Board();

        // creates board and places 2 starting 2's
        void start_board();
        // shift and merge tiles in a specified direction
        bool shift_tiles(int direction);
        // simulates shift to see if move is possible
        bool sim_shift_tiles(int direction, int &points);       
        // checks if game is lost 
        bool check_game_over();
        // checks if any free tiles are on board 
        bool check_free_tiles();
        // prints board and score to console with X's replacing 0's
        void display_board();

        // assign value to attribute dimen
        void set_dimen(int);
        // assign value to attribute score
        void set_score(int);
        // assign value to attribute board_exists
        void set_board_exists(bool);

        // get value of dimen
        int get_dimen();
        // get value of score
        int get_score();
        // get value of board_exists
        bool get_board_exists();

        // print function for debugging
        void test_print();
};

#endif