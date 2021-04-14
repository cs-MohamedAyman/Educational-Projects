#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int M = 7;
const int n_players = 2;
char marks[n_players] = {'X', 'O'};
char grid[N][M];

//This function prints the grid of Connect Four Game as the game progresses
void print_grid() {
	for (int i = 0; i< n_players; i++) {
        cout << "Player " << i+1 << ": " << marks[i] << "  ";
        if (i < n_players-1)
            cout << "vs  ";
	}
	cout << "\n";
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
}
//This function checks if the game has a win state or not
bool check_win() {
    char s;
    //Check if there is an accepted row
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M-3; j++) {
            s = grid[i][j];
            if (s != '.' && s == grid[i][j+1] && s == grid[i][j+2] && s == grid[i][j+3])
                return true;
        }
    }
    //Check if there is an accepted column
    //the game is over and the player with that character has won
    for (int j = 0; j < N-3; j++) {
        for (int i = 0; i < M; i++) {
            s = grid[j][i];
            if (s != '.' && s == grid[j+1][i] && s == grid[j+2][i] && s == grid[j+3][i])
                return true;
        }
    }
    //Check if there is an accepted left diagonal
    //the game is over and the player with that character has won
    for (int i = 0; i < N-3; i++) {
        for (int j = 0; j < M-3; j++) {
            s = grid[i][j];
            if (s != '.' && s == grid[i+1][j+1] && s == grid[i+2][j+2] && s == grid[i+3][j+3])
                return true;
        }
    }
    //Check if there is an accepted right diagonal
    //the game is over and the player with that character has won
    for (int i = 0; i < N-3; i++) {
        for (int j = 3; j < M; j++) {
            s = grid[i][j];
            if (s != '.' && s == grid[i+1][j-1] && s == grid[i+2][j-2] && s == grid[i+3][j-3])
                return true;
        }
    }
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
    return false;
}
//This function checks if the game has a tie state or not for the given mark
bool check_tie_player(char mark) {
    //Check if there is an accpted row
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M-3; j++) {
            if ((grid[i][j]   == mark || grid[i][j]   == '.') &&
				(grid[i][j+1] == mark || grid[i][j+1] == '.') && 
				(grid[i][j+2] == mark || grid[i][j+2] == '.') && 
				(grid[i][j+3] == mark || grid[i][j+3] == '.'))
                return false;
        }
    }
    //Check if there is an accpted column
    for (int i = 0; i < N-3; i++) {
        for (int j = 0; j < M; j++) {
            if ((grid[j][i]   == mark || grid[j][i]   == '.') &&
				(grid[j+1][i] == mark || grid[j+1][i] == '.') && 
				(grid[j+2][i] == mark || grid[j+2][i] == '.') && 
				(grid[j+3][i] == mark || grid[j+3][i] == '.'))
                return false;
        }
    }
    //Check if there is an accpted left diagonal
    for (int i = 0; i < N-3; i++) {
        for (int j = 0; j < M-3; j++) {
            if ((grid[i][j]     == mark || grid[i][j]     == '.') &&
				(grid[i+1][j+1] == mark || grid[i+1][j+1] == '.') && 
				(grid[i+2][j+2] == mark || grid[i+2][j+2] == '.') && 
				(grid[i+3][j+3] == mark || grid[i+3][j+3] == '.'))
                return false;
        }
    }
    //Check if there is an accpted right diagonal
    for (int i = 0; i < N-3; i++) {
        for (int j = 3; j < M; j++) {
            if ((grid[i][j]     == mark || grid[i][j]     == '.') &&
				(grid[i+1][j-1] == mark || grid[i+1][j-1] == '.') && 
				(grid[i+2][j-2] == mark || grid[i+2][j-2] == '.') && 
				(grid[i+3][j-3] == mark || grid[i+3][j-3] == '.'))
                return false;
        }
    }
    //Otherwise, there isn't a tie state in the game, 
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
bool check_empty(int i) {
	return grid[0][i] == '.';
}
//This function checks if given position is valid or not 
bool check_valid_column(int i) {
	return 0 <= i && i < M;
}
//This function sets the given mark to the given column
void set_cell(int i, char mark) {
    for (int j = N-1; j > -1; j--) {
		if (grid[j][i] == '.') {
			grid[j][i] = mark;
			break;
		}
    }
}
//This function clears the game structures
void grid_clear() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            grid[i][j] = '.';
}
//This function reads a valid position input
void read_input(int &i) {
    cout << "Enter the column index: ";
    cin >> i;
    while (!check_valid_column(i) || !check_empty(i)) {
        cout << "Enter a valid column index: ";
        cin >> i;
    }
}
//MAIN FUNCTION
void play_game() {
    cout << "Connect Four Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    int player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i;
		read_input(i);
        //Set the input position with the mark
        set_cell(i, marks[player]);
        //Check if the state of the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, Player " << marks[player] << " is won!\n";
            break;
        }
        //Check if the state of the grid has a tie state
        if (check_tie()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Woah! That's a tie!\n";
            break;
        }
        //Player number changes after each turn
        player = (player + 1) % n_players;
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
