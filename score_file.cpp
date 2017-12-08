/********************
* COMP11
* Homework 7
* Andrew Sack
* 12/7/17
*********************/ 

#include <iostream>
#include <string>
#include <fstream>
#include "score_file.h"
using namespace std;

// constructor prototype
Score_File::Score_File()
{
	names = NULL;
	scores = NULL;
	top_n = 5; //default value
	filename = "high_scores.txt"; // default value
}

// destructor prototype
Score_File::~Score_File()
{
	delete []names;
	delete []scores;
}

// print up to top int high scores 
void Score_File::print_high_scores()
{
	int num_disp;
	cout << endl;
	
	// determine the number of scores to display 
	// for if less than top_n scores exist
	if (top_n <= num_scores)
	{
		num_disp = top_n;
	}
	else
	{
		num_disp = num_scores;
	}

	// print out scores
	cout << "High Scores: \n";
	for (int i = 0; i < num_disp; i++)
	{
		cout << (i+1) << ". " << names[i] << "\t" <<
			scores[i] << endl;
	}

	return;
}

// counts number of lines in high score file
void Score_File::count_file_lines()
{
	num_scores = 0;
	string throw_away;
	
	ifstream fin; // create input object for file
	fin.open(filename.c_str()); // open file
	
	if (fin.is_open()) // verify that file opened fine
	{
		while (!fin.eof()) // until end of file is reached
		{
			getline(fin, throw_away, '\n'); // read a whole line (value is ignored)
			num_scores++; 
		}
	}
	
	fin.close();

	return;
}

// read in whole high score file
void Score_File::read_file()
{
	count_file_lines(); // count lines in file
	
	// allocate arrays
	scores = new int[num_scores];
	names = new string[num_scores];

	ifstream fin; // create input object for file
	fin.open(filename.c_str()); // open file

	if (fin.is_open()) // verify that file opened fine
	{
		// loop to read in each name and score to array
		for (int i = 0; i < num_scores; i++)
		{
			fin >> names[i];
			fin >> scores[i];
		} 
	}

	fin.close(); // close file
	
	if (num_scores >= 1) // if there is at least 1 score in file
	{
		top_score = scores[0]; // sets top_score to first element in array
	}
	else 
	{
		top_score = 0;
	}

	return;
}

// write out and save high score file
void Score_File::write_file()
{
	ofstream fout; // create file output object
	fout.open(filename.c_str());

	if (fout.is_open()) // make sure file is open
	{
		// loop through each score
		for (int i = 0; i < num_scores; i++)
		{
			// write to file
			fout << names[i] << " " << scores[i];
			if (i < num_scores - 1)
			{
				fout << endl;
			}
			//cout << names[i] << " " << scores[i] << endl;
		}
	}

	fout.close(); // close file

	return;
}

// add a new score to the list and sort properly
void Score_File::add_score(string new_name, int new_score)
{
	// create temp arrays
	string *temp_names = new string[num_scores];	
	int *temp_scores = new int[num_scores];

	// copy all data to temp arrays
	for (int i = 0; i < num_scores; i++)
	{
		temp_names[i] = names[i];
		temp_scores[i] = scores[i];
	}

	// delete original arrays
	delete[] names;
	delete[] scores;

	// increase scores by 1
	num_scores++;
	
	// reallocate arrays as 1 longer
	names = new string[num_scores];
	scores = new int[num_scores];


	int k = 0; // temp_scores index var
	bool not_used = true; // whether new_score has yet been used
	// copy temp arrays back into orig arrays
	// putting new name/score in the correct place
	for (int i = 0; i < num_scores; i++) // controls index of scores
	{
		// if new_score greater than next score in temp array
		if (new_score >= temp_scores[k] && not_used)
		{
			// put new in orig array at that spot
			scores[i] = new_score;
			names[i] = new_name;
			not_used = false;
		}
		else 
		{
			// copy temp vals to orig array	
			scores[i] = temp_scores[k];
			names[i] = temp_names[k];
			k++; // increase temp_scores index
		}
	}

	// delete temp arrays
	delete[] temp_names;
	delete[] temp_scores;

	return;
}

// ----------------- GET AND SET FUNCTIONS ------------------------------------

// assign value to filename attribute
void Score_File::set_filename(string name)
{
	filename = name;
	return;
}
// get filename value
string Score_File::get_filename()
{
	return filename;
}
// assign value to num_scores
void Score_File::set_num_scores(int num)
{
	num_scores = num;
	return;
}
// get value of num_scores
int Score_File::get_num_scores()
{
	return num_scores;
}
// assign value to top_n
void Score_File::set_top_n(int num)
{
	top_n = num;
	return;
}
// get value of top_n
int Score_File::get_top_n()
{
	return top_n;
}
// set value of top score
void Score_File::set_top_score(int num)
{
	top_score = num;
	return;
}
// get value of top_score
int Score_File::get_top_score()
{
	return top_score;
}



// print function for debugging
void Score_File::test_print()
{
	cout << "This is the Score_File class. \n";
}