#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const int M = 3;
const int a_row = 3;
const int n_players = 2;
const int marks[n_players] = {1, 2};
const char char_S = 'S';
const char char_O = 'O';
const char chars[2] = {char_S, char_O};
char grid[N][N];
int count_wins[n_players];

//This function prints the grid of SOS Game as the game progresses
void print_grid() {
    cout << "Player " << marks[0] << ":  vs  Player " << marks[1] << ":\n";
    cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < M; cout << "---", i++);
        cout << "--\n";
    }
    cout << "Player " << marks[0] << " is " << count_wins[0] << '\n';
    cout << "Player " << marks[1] << " is " << count_wins[1] << '\n';
    cout << "--";
    for (int i = 0; i < M-1; cout << "------", i++);
	cout << "\n";
}
//This function checks if the game has a complete state or not
bool check_complete() {
	string s;
	string possible_cases[7] = {".OS", "S.S", "SO.", "...", "S..", ".O.", "..S"};
    //Check if there is an accpted row
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-a_row+1; j++) {
			s = "";
			for (int k = j; k < j+a_row; k++)
				s += grid[i][k];
			for (int t = 0; t < 7; t++)
				if (s == possible_cases[t])
					return false;
		}
    }
    //Check if there is an accpted column
    for (int i = 0; i < M; i++) {
		for (int j = 0; j < N-a_row+1; j++) {
			s = "";
			for (int k = j; k < j+a_row; k++)
				s += grid[k][i];
			for (int t = 0; t < 7; t++)
				if (s == possible_cases[t])
					return false;
		}
    }
    //Check if there is an accpted left diagonal
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j+a_row-1 >= M)
                continue;
			s = "";
			for (int k = 0; k < a_row; k++) {
				s += grid[i+k][j+k];
			}
			for (int t = 0; t < 7; t++)
				if (s == possible_cases[t])
					return false;
		}
	}
    //Check if there is an accpted right diagonal
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j-a_row+1 < 0)
                continue;
			s = "";
			for (int k = 0; k < a_row; k++) {
				s += grid[i+k][j-k];
			}
			for (int t = 0; t < 7; t++)
				if (s == possible_cases[t])
					return false;
		}
	}
    //Otherwise, there isn't a tie state in the game, 
    //if all cases above not reached	
	return true;
}
//This function checks if given cell is empty or not 
bool check_empty(int i, int j) {
	return grid[i][j] == '.';
}
//This function checks if given char is valid or not 
bool check_mark(char c) {
	return c == chars[0] || c == chars[1];
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i && i < N && 0 <= j && j < M;
}
//This function sets the given mark to the given cell
void set_cell(int i, int j, char mark) {
	grid[i][j] = mark;
}
//This function updates the number of complete words of the given player
bool update_num_complete_words(int i, int j, bool player) {
    bool res = false;
    if (grid[i][j] == char_O) {
        if (check_valid_position(i, j-1) && grid[i][j-1] == char_S &&
            check_valid_position(i, j+1) && grid[i][j+1] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i-1, j) && grid[i-1][j] == char_S &&
            check_valid_position(i+1, j) && grid[i+1][j] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i-1, j-1) && grid[i-1][j-1] == char_S &&
            check_valid_position(i+1, j+1) && grid[i+1][j+1] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i-1, j+1) && grid[i-1][j+1] == char_S &&
            check_valid_position(i+1, j-1) && grid[i+1][j-1] == char_S) {
            count_wins[player] ++;
            res = true;
		}
	}
    else {
        if (check_valid_position(i, j+1) && grid[i][j+1] == char_O &&
            check_valid_position(i, j+2) && grid[i][j+2] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i, j-1) && grid[i][j-1] == char_O &&
            check_valid_position(i, j-2) && grid[i][j-2] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i+1, j) && grid[i+1][j] == char_O &&
            check_valid_position(i+2, j) && grid[i+2][j] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i-1, j) && grid[i-1][j] == char_O &&
            check_valid_position(i-2, j) && grid[i-2][j] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i+1, j+1) && grid[i+1][j+1] == char_O &&
            check_valid_position(i+2, j+2) && grid[i+2][j+2] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i-1, j-1) && grid[i-1][j-1] == char_O &&
            check_valid_position(i-2, j-2) && grid[i-2][j-2] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i-1, j+1) && grid[i-1][j+1] == char_O &&
            check_valid_position(i-2, j+2) && grid[i-2][j+2] == char_S) {
            count_wins[player] ++;
            res = true;
		}
        if (check_valid_position(i+1, j-1) && grid[i+1][j-1] == char_O &&
            check_valid_position(i+2, j-2) && grid[i+2][j-2] == char_S) {
            count_wins[player] ++;
            res = true;
		}
	}
    return res;
}
//This function clears the game structures
void grid_clear() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = '.';
    for (int i = 0; i < n_players; i++)
		count_wins[i] = 0;
}
//This function reads a valid position input
void read_input(int &i, int &j, char &c) {
	cout << "Enter the row index and column index and mark: ";
	cin >> i >> j >> c;
    while (!check_valid_position(i, j) || !check_empty(i, j) || !check_mark(c)) {
		cout << "Enter a valid row index and column index and mark: ";
		cin >> i >> j >> c;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "SOS Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input position from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i, j; char c;
		read_input(i, j, c);
        //Set the player mark in the input position
        set_cell(i, j, c);
        //Update the number of complete words
        bool word_complete = update_num_complete_words(i, j, player);
        //Check if the grid has a complete state
        if (check_complete()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
			int max_count_boxes = *max_element(count_wins, count_wins+n_players);
            if (count(count_wins, count_wins+n_players, max_count_boxes) == 1) {
				int idx_max_player = find(count_wins, count_wins+n_players, max_count_boxes) - count_wins;
                cout << "Congrats, Player " << marks[idx_max_player] << " is won!\n";
			}
            else
                cout << "Woah! That's a tie!\n";
            break;
		}
		//Keep the player if there is a complete word
        if (!word_complete) {
            //Player number changes after each turn
            player = (player + 1) % n_players;
		}
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