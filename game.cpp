/********************
* COMP11
* Homework 7
* Andrew Sack
* 12/7/17
*********************/ 

#include <iostream>
#include <string>
#include "game.h"
#include "board.h"
#include "score_file.h"
using namespace std;

// constructor prototype
Game::Game()
{
	game_over = false;
}

// destructor prototype
Game::~Game()
{

}

// performs game initialization 
void Game::start_game()
{
	// start of game

	print_instructions(); // print start messages

	get_user_size(); // determine board size from user

	f.read_file();
	b.start_board();

	int high_score = f.get_top_score();

	cout << "\nStarting game! High Score is " << high_score << endl;

	// main game loop
	while (!game_over)
	{
		b.display_board();
		make_user_move();
		game_over = game_over || b.check_game_over();
	}


	// end game
	end_game();

	return;
}

// prompts user and performs a move
void Game::make_user_move()
{
	char user_char;

	// input move
	cout << "Enter Move: ";
	cin >> user_char;

	// validate that char is valid and call appropriate code
	switch (user_char)
	{
		
		// shift moves
		case 'w':
			b.shift_tiles(0); // up
			break;
			
		case 'a':
			b.shift_tiles(3); //left
			break;
		
		case 's':
			b.shift_tiles(2); //down
			break;
		
		case 'd':
			b.shift_tiles(1); //right
			break;

		// other
		case 'h':
			f.print_high_scores();
			break;

		case 'q':
			game_over = true;
			break;

		case 'i':
			print_instructions();
			break;

		default: // move is invalid
			cout << "Incorrect character entered. " << 
				"Press 'i' to see all possible moves \n"; 
	}

	return;
}

// prompts user for board size
void Game::get_user_size()
{
	int size;
	cout << "Enter the desired board size (Must be at least 2) \n";
	cin >> size;

	if (size >= 2)
	{
		b.set_dimen(size);
	} 
	else 
	{
		get_user_size();
	}

	return;
}

// prints welcome message and instructions
void Game::print_instructions()
{
	cout << "\n\nWelcome to 2048 \n";
	cout << "Combine same-value tiles to get the highest score possible \n\n";
	cout << "Moves: \n";
	cout << "'w' for up \n";
	cout << "'a' for left \n";
	cout << "'s' for down \n";
	cout << "'d' for right \n";
	cout << "'h' to see the top-5 high scores \n";
	cout << "'q' to quit and record the current score in the high-score file\n";
	cout << "'i' to print these instructions again\n\n";

	return;
}

// prompts user for name and performs end of game tasls
void Game::end_game()
{
	b.display_board();

	int score = b.get_score();
	string name;
	cout << "\nGame Over. Your final score was " << score << endl << endl;

	cout << "Please enter your name for the high score list (no spaces) \n";
	cin >> name;

	f.add_score(name, score);
	f.write_file();
	return;
}

// print function for debugging
void Game::test_print()
{
	cout << "This is the Game class. \n";
	return;
}