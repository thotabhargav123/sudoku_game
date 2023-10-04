#include "sudokus.h"

using namespace std;

int main()
{
	bool help_taken = false, playtime = true;
	while (playtime)
	{
		system("cls");
		playtime = false;
		char difficulty;
		HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hconsole, 6);
		cout << "\n\n\n\n\n";
		cout << "\t\t\t\t--------------------------------\n";
		cout << "\t\t\t\t|        SUDOKO-PUZZLE         |\n";
		cout << "\t\t\t\t--------------------------------\n";
		cout << "\t\t\t\tEnter the Level you want to play: ";
		cout << "\n\t\t\t\t\t1) Press '1' for EASY.";
		cout << "\n\t\t\t\t\t2) Press '2' for MEDIUM.";
		cout << "\n\t\t\t\t\t3) Press '3' for HARD.";
		cout << "\n\t\t\t\tSELECT YOUR CHOICE: ";
		cin >> difficulty;

		while (difficulty < '1' || difficulty > '3')
		{
			SetConsoleCursorPosition(hconsole, { 20, 12 });
			cout << "PLEASE ENTER A NUMBER FROM (1-3) only: ";
			cin >> difficulty;
		}
		SetConsoleTextAttribute(hconsole, 15);
		sudokus obj(difficulty);
		obj.generate_sudoku();
		obj.start_menu();
		short pg = obj.get_progress();

		while ( pg < 81  and obj.get_lifes() > 0 and help_taken == false)
		{
			obj.print_sudoku();
			obj.calculate_progress();
			pg = obj.get_progress();
			cout << "\t\t\t\t Progress: " << pg <<"\n\n";
			string r, c, value;
			cout << "\t\tEnter the Row Number to be selected: ";
			cin >> r;
			if (r == "-1" or r == "-2")
			{
				if (r == "-1")
				{
					obj.show_solution();
					help_taken = true;
				}
				if (r == "-2")obj.start_menu();
				continue;
			}

			while (obj.invalids(r))
			{
				obj.print_sudoku();
				obj.calculate_progress();
				pg = obj.get_progress();
				cout << "\t\t\t\t Progress: " << pg << "\n\n";
				cout << "\t\tPlease enter a VALID Row number from (1-9): ";
				cin >> r;
			}
			obj.print_sudoku();
			obj.calculate_progress();
			pg = obj.get_progress();
			cout << "\t\t\t\t Progress: " << pg << "\n\n";
			cout << "\t\t\t Row Selected: " << r << "\n";
			cout << "\t\tEnter the Column Number to be selected: ";
			cin >> c;
			if (c == "-1" or c == "-2")
			{
				if (c == "-1")
				{
					obj.show_solution();
					help_taken = true;
				}
				if (c == "-2")obj.start_menu();
				continue;
			}

			while (obj.invalids(c))
			{
				obj.print_sudoku();
				obj.calculate_progress();
				pg = obj.get_progress();
				cout << "\t\t\t\t Progress: " << pg << "\n\n";
				cout << "\t\t\t Row Selected: " << r << "\n";
				cout << "\t\tPlease enter a VALID Column number from (1-9): ";
				cin >> c;
			}
			obj.print_sudoku();
			obj.calculate_progress();
			pg = obj.get_progress();
			cout << "\t\t\t\t Progress: " << pg << "\n\n";
			cout << "\t\t\t Row Selected: " << r << "\n";
			cout << "\t\t\t Column Selected: " << c << "\n";
			cout << "\t\tEnter the value to be entered: ";
			cin >> value;

			while (obj.invalids(value))
			{
				obj.print_sudoku();
				obj.calculate_progress();
				pg = obj.get_progress();
				cout << "\t\t\t\t Progress: " << pg << "\n\n";
				cout << "\t\t\t Row Selected: " << r << "\n";
				cout << "\t\t\t Column Selected: " << c << "\n";
				cout << "\t\tPlease enter a VALID value from (1-9): ";
				cin >> value;
			}
			short i = (r[0] - '0') - 1, j = (c[0] - '0') - 1;
			char k = value[0];
			if (obj.get_value_fixed(i, j))
			{
				cout << "\t\tYOU CAN'T CHNAGE FIXED VALUES.";
				cout << "\n\t Press a key to continue.";
				k = _getch();
			}
			else
			{
				if (obj.get_value_org(i, j) == k)
				{
					obj.set_value_sudoku(i, j, k);
				}
				else
				{
					cout << "\t\tThe value you entered is INCORRECT.\n";
					obj.decrement_lifes();
					cout << "\t\t You have " << obj.get_lifes() << " lifes remaining";
					cout << "\n\t\t Press a key to continue.";
					k = _getch();
				}
			}
			obj.calculate_progress();
			pg = obj.get_progress();
		}
		obj.show_solution();
		obj.print_sudoku();
		if (help_taken or obj.get_lifes() == 0)
		{
			cout << "\t\tYOU FAILED TO COMPLETE THE SUDOKU PUZZLE.\n";
		}
		else
		{
			cout << "\t\t CONGRATULATIONS!!!! YOU HAVE SOLVED THE SUDOKU PUZZLE.\n";
		}
		string in;
		cout << "\t\tIf you want to play again press 'y' else any other to exit.";
		cin >> in;
		if (in[0] == 'y')
		{
			playtime = true;
			help_taken = false;
		}
	}
	return 0;
}