#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const char marks[2] = {'X', 'O'};
char small_grid[N][N];
char big_grid[N*N][N*N];
int curr_box = -1, next_box = -1;

//This function prints the grid of Tic-Tac-Toe Game as the game progresses
void print_grid() {
    cout << "Player 1: " << marks[0] << "  vs  Player 2: " << marks[1] << "\n";
    for (int i = 0; i < N*N*3+N*3; cout << "-", i++);
    cout << "-\n";
    for (int i = 0; i < N*N; i++) {
        cout << "|  ";
        for (int j = 0; j < N*N; j++) {
            if (j % N == 0 and j > 0)
				cout << "|  ";
            cout << big_grid[i][j] << "  ";
		}
        cout << "|\n";
        if (i % N == N - 1) {
			for (int i = 0; i < N*N*3+N*3; cout << "-", i++);
			cout << "-\n";
		}
    }

}
//This function converts the given position in the big grid into a box number
int cvt_big_grid_pos_to_box(int i, int j) {
    return i / N * N + j / N;
}
//This function converts the given box number into a position index in the big grid
void cvt_box_to_big_grid_pos(int x, int &i, int &j) {
    i = x / N * N;
    j = x % N * N;
}
//This function converts the given position in the small grid into a box number
int cvt_small_grid_pos_to_box(int i, int j) {
    return i * N + j;
}
//This function converts the given box number into a position index in the small grid
void cvt_box_to_small_grid_pos(int x, int &i, int &j) {
    i = x / N;
	j = x % N;
}
//This function converts the given position in the big grid into a position index in the big grid
void cvt_big_grid_pos_to_big_grid_pos(int &i, int &j) {
	int box_idx = cvt_big_grid_pos_to_box(i, j);
	cvt_box_to_big_grid_pos(box_idx, i, j);
}
//This function converts the given position in the big grid into a position index in the small grid
void cvt_big_grid_pos_to_small_grid_pos(int &i, int &j) {
	int box_idx = cvt_big_grid_pos_to_box(i, j);
	cvt_box_to_small_grid_pos(box_idx, i, j);
}
//This function checks if the game has a win state or not
bool check_win(char grid[N][N], int r=0, int c=0) {
    char s;
    int cnt;
    //Convert the given position in the big grid into a position index in the big grid
	cvt_big_grid_pos_to_big_grid_pos(r, c);
    //Check if there is a row with full with same characters, 
    //the game is over and the player with that character has won
	for (int i = r; i < r+N; i++) {
		s = grid[i][c];
		cnt = 0;
        for (int j = c; j < c+N; j++)
			if (s == grid[i][j])
			    cnt ++;
		if (cnt == N && s != '.')
			return true;
	}
    //Check if there is a column with full with same characters, 
    //the game is over and the player with that character has won
	for (int i = c; i < c+N; i++) {
		s = grid[r][i];
		cnt = 0;
        for (int j = r; j < r+N; j++)
			if (s == grid[j][i])
			    cnt ++;
		if (cnt == N && s != '.')
			return true;
	}
    //Check if the left diagonal is full with same characters, 
    //the game is over and the player with that character has won
    s = grid[r][c];
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (s == grid[r+i][c+i])
		    cnt ++;
	if (cnt == N && s != '.')
		return true;
    //Check if the right diagonal is full with same characters, 
    //the game is over and the player with that character has won
    s = grid[r][c+N-1];
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (s == grid[r+i][c+N-i-1])
		    cnt ++;
	if (cnt == N && s != '.')
		return true;
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
    return false;
}
//This function checks if the game has a win state or not
bool check_win(char grid[N*N][N*N], int r=0, int c=0) {
    char s;
    int cnt;
    //Convert the given position in the big grid into a position index in the big grid
	cvt_big_grid_pos_to_big_grid_pos(r, c);
    //Check if there is a row with full with same characters, 
    //the game is over and the player with that character has won
	for (int i = r; i < r+N; i++) {
		s = grid[i][c];
		cnt = 0;
        for (int j = c; j < c+N; j++)
			if (s == grid[i][j])
			    cnt ++;
		if (cnt == N && s != '.')
			return true;
	}
    //Check if there is a column with full with same characters, 
    //the game is over and the player with that character has won
	for (int i = c; i < c+N; i++) {
		s = grid[r][i];
		cnt = 0;
        for (int j = r; j < r+N; j++)
			if (s == grid[j][i])
			    cnt ++;
		if (cnt == N && s != '.')
			return true;
	}
    //Check if the left diagonal is full with same characters, 
    //the game is over and the player with that character has won
    s = grid[r][c];
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (s == grid[r+i][c+i])
		    cnt ++;
	if (cnt == N && s != '.')
		return true;
    //Check if the right diagonal is full with same characters, 
    //the game is over and the player with that character has won
    s = grid[r][c+N-1];
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (s == grid[r+i][c+N-i-1])
		    cnt ++;
	if (cnt == N && s != '.')
		return true;
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
    return false;
}
//This function checks if the game has a tie state or not
bool check_tie(char grid[N][N], char mark, int r=0, int c=0) {
    char s;
    int cnt;
	//Convert the given position in the big grid into a position index in the big grid
	cvt_big_grid_pos_to_big_grid_pos(r, c);
	//Check if there is a row with a single type of characters
    for (int i = r; i < r+N; i++) {
		s = mark;
		cnt = 0;
        for (int j = c; j < c+N; j++)
			if (grid[i][j] != '.' && s != grid[i][j])
			    cnt ++;
		if (cnt == 0)
			return false;
    }
    //Check if there is a column with a single type of characters
    for (int i = c; i < c+N; i++) {
		s = mark;
		cnt = 0;
        for (int j = r; j < r+N; j++)
			if (grid[j][i] != '.' && s != grid[j][i])
			    cnt ++;
		if (cnt == 0)
			return false;
    }
    //Check if the left diagonal is a single type of characters
	s = mark;
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (grid[r+i][c+i] != '.' && s != grid[r+i][c+i])
		    cnt ++;
	if (cnt == 0)
		return false;
    //Check if the right diagonal is a single type of characters
	s = mark;
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (grid[r+i][c+N-i-1] != '.' && s != grid[r+i][c+N-i-1])
		    cnt ++;
	if (cnt == 0)
		return false;
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
	return true;
}
//This function checks if the game has a tie state or not
bool check_tie(char grid[N*N][N*N], char mark, int r=0, int c=0) {
    char s;
    int cnt;
	//Convert the given position in the big grid into a position index in the big grid
	cvt_big_grid_pos_to_big_grid_pos(r, c);
	//Check if there is a row with a single type of characters
    for (int i = r; i < r+N; i++) {
		s = mark;
		cnt = 0;
        for (int j = c; j < c+N; j++)
			if (grid[i][j] != '.' && s != grid[i][j])
			    cnt ++;
		if (cnt == 0)
			return false;
    }
    //Check if there is a column with a single type of characters
    for (int i = c; i < c+N; i++) {
		s = mark;
		cnt = 0;
        for (int j = r; j < r+N; j++)
			if (grid[j][i] != '.' && s != grid[j][i])
			    cnt ++;
		if (cnt == 0)
			return false;
    }
    //Check if the left diagonal is a single type of characters
	s = mark;
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (grid[r+i][c+i] != '.' && s != grid[r+i][c+i])
		    cnt ++;
	if (cnt == 0)
		return false;
    //Check if the right diagonal is a single type of characters
	s = mark;
	cnt = 0;
    for (int i = 0; i < N; i++)
		if (grid[r+i][c+N-i-1] != '.' && s != grid[r+i][c+N-i-1])
		    cnt ++;
	if (cnt == 0)
		return false;
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached
	return true;
}
//This function checks if the given cell in the big grid is empty or not 
bool check_empty_in_big_grid(int i, int j) {
	return big_grid[i][j] == '.';
}
//This function checks if the given cell in the small grid is empty or not 
bool check_empty_in_small_grid(int i, int j) {
    return small_grid[i][j] == '.';
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i < N*N and 0 <= j < N*N;
}
//This function calculates the current selected box 
void set_next_box(int i, int j) {
    int x = i, y = j;
	cvt_big_grid_pos_to_big_grid_pos(x, y);
    int si = i - x, sj = j - y;
    next_box = cvt_small_grid_pos_to_box(si, sj);
    if (!check_empty_in_small_grid(si, sj))
        next_box = -1;
}
//This function sets the given mark to the given cell in the big grid
void set_cell_in_big_grid(int i, int j, char mark) {
    big_grid[i][j] = mark;
    curr_box = cvt_big_grid_pos_to_box(i, j);
}
//This function sets the given mark to the given box
void fill_box(int r, int c, char mark) {
    cvt_big_grid_pos_to_small_grid_pos(r, c);
	for (int i = r*N; i < r*N+N; i++)
		for (int j = c*N; j < c*N+N; j++)
            big_grid[i][j] = mark;
    small_grid[r][c] = mark;
}
//This function clears the game structures
void grid_clear() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			small_grid[i][j] = '.';
	for (int i = 0; i < N*N; i++)
		for (int j = 0; j < N*N; j++)
			big_grid[i][j] = '.';
    curr_box = -1, next_box = -1;
}
//This function reads a valid position input
void read_input(int &i, int &j) {
    string box_idx = (next_box == -1)? "any box" : "box " + to_string(next_box);
	cout << "Enter the row index and column index in " << box_idx << ": ";
	cin >> i >> j;
    int si = i, sj = j;
	cvt_big_grid_pos_to_small_grid_pos(si, sj);
    while (!check_valid_position(i, j) || !check_empty_in_big_grid(i, j) ||
          (next_box != -1 && next_box != cvt_big_grid_pos_to_box(i, j)) ||
          (next_box == -1 && !check_empty_in_small_grid(si, sj))) {
		cout << "Enter a valid row index and column index in " << box_idx << ": ";
		cin >> i >> j;
		si = i, sj = j;
		cvt_big_grid_pos_to_small_grid_pos(si, sj);
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "Ultimate Tic-Tac-Toe Game!\n";
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
        set_cell_in_big_grid(i, j, marks[player]);
        //Check if the selected box has a win state
        if (check_win(big_grid, i, j)) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement in a box
            cout << "Congrats, Player " << marks[player] << " is completed the box " << curr_box << ".\n";
            fill_box(i, j, marks[player]);
		}
        //Check if the selected box has a full state
        else if (check_tie(big_grid, marks[player], i, j) && check_tie(big_grid, marks[1-player], i, j)) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement in a box
            cout << "Woah! That's a tie in the box " << curr_box << ".\n";
            fill_box(i, j, '#');
		}
        //Calculate the next selected box 
        set_next_box(i, j);
        //Check if the small grid has a win state
        if (check_win(small_grid)) {
            //Prints the grid
            print_grid();
			//Announcement of the final statement
            cout << "Congrats, Player " << marks[player] << " is won!\n";
            break;
		}
        //Check if the grid has a tie state
        if (check_tie(small_grid, marks[player]) && check_tie(small_grid, marks[1-player])) {
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
