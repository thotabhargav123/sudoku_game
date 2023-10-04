#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

class sudokus
{
private:
	vector<vector<char>>org; // original reference sudoku 
	vector<vector<char>>sudoku; // sudoku that is to be shown for solving
	vector<vector<bool>>fixed; // vitited array type to mark the intial values.
	set<pair<short, short>>fixed_points;
	char difficulty;
	short progress;
	short lifes;
	
public:
	sudokus(char);
	short get_lifes();
	void decrement_lifes();
	bool get_value_fixed(short, short);
	char get_value_org(short, short);
	void set_value_sudoku(short, short, char);
	void shuffle();
	void switching();
	void generate_sudoku();
	void calculate_progress();
	void clear();
	void print_sudoku();
	void print_lifes();
	short get_progress();
	void change_color(short);
	void print_line();
	void cursor_position(short, short&);
	void start_menu();
	void show_solution();
	bool invalids(string);
	void instructions();
};

