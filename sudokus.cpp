#include "sudokus.h"
// intilizating the object
sudokus::sudokus(char input)
{
    srand(time(NULL));
    difficulty = 1 + (input - '0') % 3;
    progress = 55 - (input - '0') * 10 + rand() % 10;
    lifes = 7 - (input - '0') * 2;
    short k = rand() % 3;
    if (k == 0)
    {
        org = { 
            {'4','3','5','2','6','9','7','8','1'},
            {'6','8','2','5','7','1','4','9','3'},   
            {'1','9','7','8','3','4','5','6','2'},
            {'8','2','6','1','9','5','3','4','7'},
            {'3','7','4','6','8','2','9','1','5'},
            {'9','5','1','7','4','3','6','2','8'},
            {'5','1','9','3','2','6','8','7','4'},
            {'2','4','8','9','5','7','1','3','6'},
            {'7','6','3','4','1','8','2','5','9'} 
        };

    }
    else if (k == 1)
    {
        org = {
            {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
            {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
            {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
            {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
            {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
            {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
            {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
            {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
            {'3', '4', '5', '2', '8', '6', '1', '7', '9'}
        };
    }
    else
    {
        org = {
            {'4', '8', '3', '9', '2', '1', '6', '5', '7'},
            {'9', '6', '7', '3', '4', '5', '8', '2', '1'},
            {'2', '5', '1', '8', '7', '6', '4', '9', '3'},
            {'5', '4', '8', '1', '3', '2', '9', '7', '6'},
            {'7', '2', '9', '5', '6', '4', '1', '3', '8'},
            {'1', '3', '6', '7', '9', '8', '2', '4', '5'},
            {'3', '7', '2', '6', '8', '9', '5', '1', '4'},
            {'8', '1', '4', '2', '5', '3', '7', '6', '9'},
            {'6', '9', '5', '4', '1', '7', '3', '8', '2'}
        };
    }
	sudoku = vector<vector<char>>(9, vector<char>(9, '_'));
    fixed = vector<vector<bool>>(9, vector<bool>(9, false));
}
// to get the number of lifes
short sudokus::get_lifes()
{
    return lifes;
}
// to decrement the lifes
void sudokus::decrement_lifes()
{
    lifes--;
    return;
}
// to get value of fixed at a position
bool sudokus::get_value_fixed(short i, short j)
{
    return fixed[i][j];
}
// to get value of org at a position
char sudokus::get_value_org(short i, short j)
{
    return org[i][j];
}
// to set value of sudoku at a position
void sudokus::set_value_sudoku(short i, short j, char k)
{
    sudoku[i][j] = k;
}
// to create new sudoku: part 1
void sudokus::shuffle()
{
	srand(time(NULL));
	short col = rand() % 3, add_col = 1 + rand() % 2;
	short row = rand() % 3, add_row = 1 + rand() % 2;
    // changes 3 columns with another 3 
    for (short i = 0; i < 9; i++)
    {
        swap(org[i][col * 3], org[i][(3 * col + 3 * add_col) % 9]);
        swap(org[i][3 * col + 1], org[i][(3 * col + 3 * add_col + 1) % 9]);
        swap(org[i][3 * col + 2], org[i][(3 * col + 3 * add_col + 2) % 9]);
    }
    // changes 3 row with another 3
    for (short i = 0; i < 9; i++)
    {
        swap(org[3 * row][i], org[(3 * row + 3 * add_row) % 9][i]);
        swap(org[3 * row + 1][i], org[(3 * row + 3 * add_row + 1) % 9][i]);
        swap(org[3 * row + 2][i], org[(3 * row + 3 * add_row + 2) % 9][i]);
    }
}
// to create new sudoku: part 2
void sudokus::switching()
{
    // switching random 2 number in every row
    srand(time(NULL));
    short x1 = 1 + rand() % 9, x2 = 1 + rand() % 9;
    char l1 = '0' + x1, l2 = '0' + x2;
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            if (org[i][j] == l1) org[i][j] = l2;
            else if (org[i][j] == l2) org[i][j] = l1;
        }
    }
}
//to generate a sudoko
void sudokus::generate_sudoku()
{
    srand(time(NULL));
    shuffle();switching();
    shuffle();switching();
    shuffle();switching();
    set<pair<short, short>>choose;
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            choose.insert({ i, j });
            sudoku[i][j] = '_';
        }
    }
    short k = progress;
    while (k-- and !choose.empty())
    {
        set<pair<short, short>>::iterator it = choose.begin();
        advance(it, rand() % choose.size());
        short i = it->first, j = it->second;
        sudoku[i][j] = org[i][j];
        fixed[i][j] = true;
        fixed_points.insert(*it);
        choose.erase(it);
    }
}
// to cal progress of game
void sudokus::calculate_progress()
{
    short temp = 0;
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            if (org[i][j] == sudoku[i][j])
            {
                temp++;
            }
        }
    }
    progress = temp;
}
//to clear console
void sudokus::clear()
{
    system("cls");
    return;
}
// to print sudoku
void sudokus::print_sudoku()
{
    clear();
    instructions();
    print_lifes();
    short y = 5;
    cursor_position(40, y);
    cout << "   ";
    for (short i = 1; i <= 9; i++)
    {
        cout << " " << i;
        if (i % 3 == 0)
        {
            cout << "  ";
        }
    }
    cout << "\n";
    cursor_position(40, y);
    for (short i = 0; i < 9; i++)
    {
        if (i % 3 == 0) {
            print_line();
            cursor_position(40, y);
        }
        cout << i + 1 << " ";
        for (short j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
            {
                cout << "| ";
            }
            short k = 1 + i / 3 + j / 3;
            if (fixed[i][j])change_color(k);
            else change_color(6);
            cout << sudoku[i][j] << " ";
            change_color(15);
            if (j == 8)
            {
                cout << "| ";
            }
        }
        cout << "\n";
        cursor_position(40, y);
    }
    print_line();
}
// to print lifes
void sudokus::print_lifes()
{
    short y = 3; 
    cursor_position(90, y);
    for (short i = 1; i <= lifes; i++)
    {
        cout << "$" << " ";
    }

}
// to get the progress
short sudokus::get_progress()
{
    return progress;
}
// to change the text
void sudokus::change_color(short num)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, num);
}
// to print line
void sudokus::print_line()
{
    cout << "  ";
    for (int j = 0; j < 8; j++)
    {
        cout << "---";
    }
    cout << "-\n";
    return;
}
// to change the position of the cursor
void sudokus::cursor_position(short posx, short &posy)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursor = { posx, posy };
    posy++;
    SetConsoleCursorPosition(hconsole, cursor);
    return;
}
// to print starting menu
void sudokus::start_menu()
{
    clear();
    short y = 5;
    change_color(14);
    cursor_position(40, y);
    cout << "-------------------------\n";
    cursor_position(40, y);
    cout << "|     SUDOKU'S RULES    |\n";
    cursor_position(40, y);
    cout << "-------------------------\n";
    cursor_position(20, y);
    cout << "1)Each of the digits 1-9 must occur exactly once in each row.";
    cursor_position(20, y);
    cout << "2)Each of the digits 1-9 must occur exactly once in each column.";
    cursor_position(20, y);
    cout << "3)Each of the digits 1-9 must occur exactly once in each of the 9 ";
    cursor_position(20, y);
    cout<<"  3x3 sub-boxes of the grid.";
    cursor_position(20, y);
    cout << "4)You have to complete the game before your lifes runout.";
    cursor_position(20, y);
    cout << "5)You will charged with 1 life for every wrong value entered";
    cursor_position(20, y);
    cout << "6)You have " << get_lifes() << " lifes remaining";
    cursor_position(20, y);
    cout << "7)Your lifes are represented as '$'.";
    cursor_position(20, y);
    cout << "8)You can see your remaining lifes at the top-right corner.";
    y += 2;
    cursor_position(30, y);
    cout << "PRESS ANY KEY TO START......";
    change_color(15);
    char k = _getch();
}
// to show the solution
void sudokus::show_solution()
{
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            sudoku[i][j] = org[i][j];
        }
    }
    return;
}
// to check for invalid inputs
bool sudokus::invalids(string s)
{
    set<string>check = { "1","2","3","4","5","6","7","8","9" };
    bool k = check.count(s);
    return !k;
}
// to show primary intrusctions 
void sudokus::instructions()
{
    short y = 2;
    cursor_position(15, y);
    change_color(10);
    cout << "Enter '-1' as Row/Column number to show the solution at any time.\n";
    cursor_position(15, y);
    cout << "Enter '-2' as Row/Column number to show rules at any time.\n";
    change_color(15);
    return;
}