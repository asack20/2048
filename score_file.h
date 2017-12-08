/* COMP11 Fall 2017
 * Homework 6
 * Andrew Sack
 * Signoff by Steven Song 11/17/17 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#ifndef SCORE_FILE_H_
#define SCORE_FILE_H_

class Score_File {
    private:
    	// name of high score file
    	string filename;
    	// sorted list of usernames
    	string *names;
    	// corresponding sorted list of high scores
    	int *scores;
    	// length of names and scores arrays
    	int num_scores;
      // num of top scores to display
      int top_n;
      // the current high score
      int top_score;

      // counts number of lines in high score file
      void count_file_lines();

    public:
        // constructor prototype
        Score_File();
        // destructor prototype
        ~Score_File();
        
        // print up to top_n high scores 
        void print_high_scores();
        // read in whole high score file
        void read_file();
        // write out and save high score file
        void write_file();
        // add a new score to the list and sort properly
        void add_score(string new_name, int new_score);

        // assign value to filename attribute
       	void set_filename(string);
       	// get filename value
       	string get_filename();

       	// assign value to num_scores
       	void set_num_scores(int);
       	// get value of num_scores
       	int get_num_scores();

        // assign value to top_n
        void set_top_n(int);
        // get value of top_n
        int get_top_n();

        // set value of top score
        void set_top_score(int);
        // get value of top_score
        int get_top_score();

        // print function for debugging
        void test_print();
};

#endif