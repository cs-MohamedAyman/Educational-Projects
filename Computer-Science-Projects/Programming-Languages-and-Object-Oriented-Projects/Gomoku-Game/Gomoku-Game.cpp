#include <bits/stdc++.h>
using namespace std;

const int N = 9;
const int M = 9;
const int a_row = 5;
const int n_players = 2;
char marks[n_players] = {'B', 'W'};
char grid[N][M];

//This function prints the grid of Gomoku as the game progresses
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
    int cnt;
    //Check if there is an accepted row
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-a_row+1; j++) {
			s = grid[i][j];
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (s == grid[i][k])
					cnt ++;
			if (cnt == a_row && s != '.')
				return true;
		}
    }
    //Check if there is an accepted column
    //the game is over and the player with that character has won
    for (int i = 0; i < M; i++) {
		for (int j = 0; j < N-a_row+1; j++) {
			s = grid[j][i];
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (s == grid[k][i])
					cnt ++;
			if (cnt == a_row && s != '.')
				return true;
		}
    }
    //Check if there is an accepted left diagonal
    //the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j+a_row-1 >= M)
                continue;
            s = grid[i][j];
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (s == grid[i+k][j+k])
					cnt ++;
			}
			if (cnt == a_row && s != '.')
				return true;
		}
	}
    //Check if there is an accepted right diagonal
    //the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j-a_row+1 < 0)
                continue;
            s = grid[i][j];
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (s == grid[i+k][j-k])
					cnt ++;
			}
			if (cnt == a_row && s != '.')
				return true;
		}
	}
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached	
    return false;
}
//This function checks if the game has a tie state or not for the given mark
bool check_tie_player(char mark) {
    int cnt;
    //Check if there is an accpted row
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-a_row+1; j++) {
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (grid[i][k] == '.' || mark == grid[i][k])
					cnt ++;
			if (cnt == a_row)
				return false;
		}
    }
    //Check if there is an accpted column
    for (int i = 0; i < M; i++) {
		for (int j = 0; j < N-a_row+1; j++) {
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (grid[k][i] == '.' || mark == grid[k][i])
					cnt ++;
			if (cnt == a_row)
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
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (grid[i+k][j+k] == '.' || mark == grid[i+k][j+k])
					cnt ++;
			}
			if (cnt == a_row)
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
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (grid[i+k][j-k] == '.' || mark == grid[i+k][j-k])
					cnt ++;
			}
			if (cnt == a_row)
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
bool check_empty(int i, int j) {
	return grid[i][j] == '.';
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i && i < N && 0 <= j && j < M;
}
//This function sets the given mark to the given column
void set_cell(int i, int j, char mark) {
	grid[i][j] = mark;
}
//This function clears the game structures
void grid_clear() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
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
    cout << "Gomoku Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    int player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i, j;
		read_input(i, j);
        //Set the input position with the mark
        set_cell(i, j, marks[player]);
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
