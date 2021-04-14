#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const int n_players = 2;
const char marks[n_players] = {'X', 'O'};
char grid[N][N];

//This function prints the grid of Tic-Tac-Toe Game as the game progresses
void print_grid() {
    cout << "Player 1: " << marks[0] << "  vs  Player 2: " << marks[1] << "\n";
    cout << "--";
    for (int i = 0; i < N; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < N; cout << "---", i++);
        cout << "--\n";
    }
}
//This function checks if the game has a win state or not
bool check_win() {
    char s;
    int cnt;
    //Check if there is a row with full with same characters, 
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
		s = grid[i][0];
		cnt = 0;
        for (int j = 0; j < N; j++)
			if (s == grid[i][j])
			    cnt ++;
		if (cnt == N && s != '.')
			return true;
    }
    //Check if there is a column with full with same characters, 
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
		s = grid[0][i];
		cnt = 0;
        for (int j = 0; j < N; j++)
			if (s == grid[j][i])
			    cnt ++;
		if (cnt == N && s != '.')
			return true;
    }
    //Check if the left diagonal is full with same characters, 
	//the game is over and the player with that character has won
    s = grid[0][0];
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (s == grid[i][i])
		    cnt ++;
	if (cnt == N && s != '.')
		return true;
    //Check if the right diagonal is full with same characters, 
	//the game is over and the player with that character has won
    s = grid[N-1][0];
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (s == grid[i][N-i-1])
		    cnt ++;
	if (cnt == N && s != '.')
		return true;
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
    return false;
}
//This function checks if the game has a tie state or not for the given mark
bool check_tie_player(char mark) {
    int cnt;
    //Check if there is a row with a single type of characters
    for (int i = 0; i < N; i++) {
		cnt = 0;
        for (int j = 0; j < N; j++)
			if (grid[i][j] != '.' && mark != grid[i][j])
			    cnt ++;
		if (cnt == 0)
			return false;
    }
    //Check if there is a column with a single type of characters
    for (int i = 0; i < N; i++) {
		cnt = 0;
        for (int j = 0; j < N; j++)
			if (grid[j][i] != '.' && mark != grid[j][i])
			    cnt ++;
		if (cnt == 0)
			return false;
    }
    //Check if the left diagonal is a single type of characters
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (grid[i][i] != '.' && mark != grid[i][i])
		    cnt ++;
	if (cnt == 0)
		return false;
    //Check if the right diagonal is a single type of characters
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (grid[i][N-i-1] != '.' && mark != grid[i][N-i-1])
		    cnt ++;
	if (cnt == 0)
		return false;
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
	return true;
}
//This function checks if the game has a tie state or not
bool check_tie() {
    bool all_tie = true;
    for (int i = 0; i < n_players; i++)
        if (!check_tie_player(marks[i]))
            all_tie = false;
    return all_tie;
}
//This function checks if given cell is empty or not 
bool check_empty(int i, int j) {
	return grid[i][j] == '.';
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i && i < N && 0 <= j && j < N;
}
//This function sets the given mark to the given cell
void set_cell(int i, int j, char mark) {
	grid[i][j] = mark;
}
//This function clears the game structures
void grid_clear() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = '.';
}
//This function reads a valid position input
void read_input(int &i, int &j) {
	cout << "Enter the row index and column index: ";
	cin >> i >> j;
    while (!check_valid_position(i, j) || !check_empty(i, j)) {
		cout << "Enter a valid row index and a valid column index: ";
		cin >> i >> j;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "Tic-Tac-Toe Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input position from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i, j;
		read_input(i, j);
        //Set the player mark in the input position
        set_cell(i, j, marks[player]);
        //Check if the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
			//Announcement of the final statement
            cout << "Congrats, Player " << marks[player] << " is won!\n";
            break;
        }
        //Check if the grid has a tie state
        if (check_tie()) {
            //Prints the grid
            print_grid();
			//Announcement of the final statement
            cout << "Woah! That's a tie!\n";
            break;
        }
        //Player number changes after each turn
        player = 1 - player;
    }
}
int main() {
    while (true) {
    	grid_clear();
    	play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
    }
}
