/********************
* COMP11
* Homework 7
* Andrew Sack
* 12/7/17
*********************/ 

#include <iostream>
#include <string>
#include <ctime> // used for seeding random numbers
#include <cstdlib>
#include "board.h"
using namespace std;


// Default constructor
Board::Board()
{
	//initial values
    board = NULL;
	score = 0;
	board_exists = false;

	//seed time
	srand(time(NULL));
}

Board::~Board()
{
	// delete board array
    for (int i = 0; i < dimen; ++i) 
	{
    	delete [] board[i];
	}
	delete []board;
}

// initializes board and places 2 starting 2's
void Board::start_board()
{
	if (dimen >= 2) // make sure board size is valid
	{
		// board initialization to all 0's
		board = new int *[dimen];
		for (int i = 0; i < dimen; i++)
		{
			board[i] = new int[dimen];
			for (int j = 0; j < dimen; j++)
			{
				board[i][j] = 0;
			}
		}

		board_exists = true; // board now properly exists

		// place 2 2's
		bool just_2 = true;
		add_rand_tile( just_2 );
		add_rand_tile( just_2 );

	}

	else // error message
	{
		cerr << "dimen must be initialized to an integer value" << 
			" 2 or greater.\n";
	}

	return;
}

// shift and merge tiles
bool Board::shift_tiles(int direction)
{
	int i;
	int new_points;
	bool did_shift = false;
	
	int *vec = new int[dimen]; // 1 col of board array
	
	switch(direction) // determine which direction was entered
	{
    	case 0 : // up
        	// all 4 cases perform similarly but with different order of loops
            for (int col = 0; col < dimen; col++) // for each col
        	{
        		// copy row into vec in correct order so that direction 
                // of shift is towards vec[0]
                for (int row = 0; row < dimen; row++) 
        		{
        			i = row; 
        			vec[i] = board[row][col];
        		}
        		
        		// run single shift to perform shifting and point
                // calculations on a single col/row
                single_shift(vec, new_points); 
        		score += new_points; // add points earned to total score
        		
                // copy shifted vec back into board array
        		for (int row = 0; row < dimen; row++)
        		{
        			i = row;
        			// if any changes occured, a shift did occur
                    if (board[row][col] != vec[i])
        			{
        				did_shift = true;
                        // only actually changes tiles that are different
                        // from original board
        				board[row][col] = vec[i];
        			}
        		}
        	}
         	break;
      	
      	case 1 : // right
        	// see case 0 for comments
        	for (int row = 0; row < dimen; row++)
        	{
        		for (int col = 0; col < dimen; col++)
        		{
        			i = (dimen - 1) - col;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		score += new_points;
        		
        		for (int col = 0; col < dimen; col++)
        		{
        			i = (dimen - 1) - col;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
        				board[row][col] = vec[i];
        			}
        		}         		
        	}
      		break;

      	case 2 : // down
            // see case 0 for comments
        	for (int col = 0; col < dimen; col++)
        	{
        		for (int row = 0; row < dimen; row++)
        		{
        			i = (dimen - 1) - row;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		score += new_points;
        		
        		for (int row = 0; row < dimen; row++)
        		{
        			i = (dimen - 1) - row;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
        				board[row][col] = vec[i];
        			}
        		}
        	}
      		break;

      	case 3 : // left
      		// see case 0 for comments
        	for (int row = 0; row < dimen; row++)
        	{
        		for (int col = 0; col < dimen; col++)
        		{
        			i = col;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		score += new_points;
        		
        		for (int col = 0; col < dimen; col++)
        		{
        			i = col;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
        				board[row][col] = vec[i];
        			}
        		}        		
        	}
         	break;
      	
      	default :
        	cerr << "Invalid direction entered. Valid directions are: \n";
        	cerr << "Up: 0, Right: 1, Down: 2, Left: 3 \n";
        	return did_shift;

	}
    // if a shift occured (the move was valid) add a new tile
    if (did_shift) 
    {
    	// adds a random tile either 2 OR 4
        bool just_2 = false; 
        add_rand_tile(just_2);
    }

    delete[] vec; // free up memory

    return did_shift;
}

// simulates shift to see if move is possible
// similar to shift_tiles() but does not actually modify main board
// or add to score
bool Board::sim_shift_tiles(int direction, int &points)
{

	int i;
	int new_points;
	bool did_shift = false;
	
	points = 0; // points is a variable of just the points of the move
    // that does not affect the main score

	int *vec = new int[dimen];
	
    // pretty much same as code for shift_tiles()
	switch(direction) 
	{
    	case 0 : // up
        	
        	for (int col = 0; col < dimen; col++)
        	{
        		for (int row = 0; row < dimen; row++)
        		{
        			i = row;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		points += new_points; // add to points instead of score
        		
        		for (int row = 0; row < dimen; row++)
        		{
        			i = row;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
                        // doesn't copy vec back into board
        			}
        		}
        	}
         	break;
      	
      	case 1 : // right
        	
        	for (int row = 0; row < dimen; row++)
        	{
        		for (int col = 0; col < dimen; col++)
        		{
        			i = (dimen - 1) - col;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		points += new_points;
        		
        		for (int col = 0; col < dimen; col++)
        		{
        			i = (dimen - 1) - col;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
        			}
        		}         		
        	}
      		break;

      	case 2 : // down
      		
        	for (int col = 0; col < dimen; col++)
        	{
        		for (int row = 0; row < dimen; row++)
        		{
        			i = (dimen - 1) - row;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		points += new_points;

        		for (int row = 0; row < dimen; row++)
        		{
        			i = (dimen - 1) - row;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
        			}
        		}
        	}
      		break;

      	case 3 : // left
      		
        	for (int row = 0; row < dimen; row++)
        	{
        		for (int col = 0; col < dimen; col++)
        		{
        			i = col;
        			vec[i] = board[row][col];
        		}
        		
        		single_shift(vec, new_points);
        		points += new_points;
        		
        		for (int col = 0; col < dimen; col++)
        		{
        			i = col;
        			if (board[row][col] != vec[i])
        			{
        				did_shift = true;
        			}
        		}        		
        	}
         	break;
      	
      	default :
        	cerr << "Invalid direction entered. Valid directions are: \n";
        	cerr << "Up: 0, Right: 1, Down: 2, Left: 3 \n";
        	return did_shift;

	}

    delete[] vec; // free up memory
    
    // does not add tile

    return did_shift;
	//return false; !!!!
}


// places random tile on board
void Board::add_rand_tile(bool just_2)
{
	int val;
	int rand_row;
	int rand_col;

	if (just_2) // does not have random chance of a 4
	{
		val = 2;
	}
	else // rand 90% chance 2, 10% chance 4
	{
		int val_odds = rand() % 10;
		if (val_odds == 0)
		{
			val = 4;
		} 
		else 
		{
			val = 2;
		}
	}

	do // loop through random coords until an empty tile is found
	{
		rand_row = rand() % dimen;
		rand_col = rand() % dimen;
	} while (board[rand_row][rand_col] != 0);

	board[rand_row][rand_col] = val; // add val in that location
 
	return;
}

// performs shift/merge for a single row/column
// shifts towards 0 index
void Board::single_shift(int vec[], int &new_points)
{
	int ind;
	int merged_index = -1; // high index where a merge has occured
	new_points = 0;

	for (int i = 0; i < dimen; i++)
	{
		if (vec[i] != 0)
		{
			ind = i;
			
			// find ind furthest directly below i where value 0
			while (ind > 0 && vec[ind-1] == 0)
			{
				ind--;
			}
			// shift tile to that ind
			if (ind != i)
			{
				vec[ind] = vec[i];
				vec[i] = 0;
			}
			// merge tiles and add score
			if (vec[ind-1] == vec[ind] && (ind-1) > merged_index)
			{
				new_points += 2*vec[ind-1]; 
				vec[ind-1] = 2*vec[ind-1]; 
				vec[ind] = 0;
				merged_index = ind - 1;
			}
		}
	} 
}

// needs work
// checks if game is lost
bool Board::check_game_over()
{
	bool is_over = true; 
	int temp;

	for (int i = 0; i <= 3; i++) // shift all 4 directions
	{
		// becomes true if shift in any direction is true
		is_over = is_over && !sim_shift_tiles(i, temp);
	} 

	return is_over;// for now
}

// i dont think this is needed
 // checks if any free tiles are on board 
bool Board::check_free_tiles()
{
	bool free_tile = false;

    // loop through each tile on board
	for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; i < dimen; j++)
		{
			// if any are 0, free_tile is true
            if (board[i][j] == 0)
			{
				free_tile = true;
			}
		}
	} 
	
	return free_tile;
}

// unsure whether to keeo this
// checks that board_exists is true and gives an error otherwise
bool Board::check_board_exists()
{
	if (board_exists == false)
	{
		cerr << "Board is not yet properly initialized. " << 
			"Try calling start_board() first.\n";	
	}	
	
	return board_exists;
	
}

// prints board and score to console with X's replacing 0's
void Board::display_board()
{
	cout << "\nCurrent Score: " << score << endl; // print score

	// loop through each tile and print 
    for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; j < dimen; j++)
		{
			if (board[i][j] == 0)
			{
				cout << 'X' << '\t'; // X is char for 0
			}
			else
			{
				cout << board[i][j] << '\t'; // print the number
			}
		}
		cout << endl;
	}

	return;
}


// ----------------- GET AND SET FUNCTIONS ------------------------------------

// assign value to attribute dimen
void Board::set_dimen(int dim)
{
	dimen = dim;
	return;
}
// assign value to attribute score
void Board::set_score(int val)
{
	score = val;
	return;
}
// assign value to attribute board_exists
void Board::set_board_exists(bool exists)
{
	board_exists = exists;
	return;
}


// get value of dimen
int Board::get_dimen()
{
	return dimen;
}
// get value of score
int Board::get_score()
{
	return score;
}
// get value of board_exists
bool Board::get_board_exists()
{
	return board_exists;
}


// print function for debugging
void Board::test_print()
{
	cout << "This is the Board class. \n";

	return;
}