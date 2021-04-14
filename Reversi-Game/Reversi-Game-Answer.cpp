#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int M = 8;
const int n_players = 2;
char marks[n_players] = {'B', 'W'};
int count_cells[n_players];
char grid[N][M];
int possible_cells[N*M][2];
int possible_cells_size;

//This function prints the grid of Dots-and-Boxes as the game progresses
void print_grid() {
    cout << "Player 1: " << marks[0] << "  vs  Player 2: " << marks[1] << "\n";
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
	for (int i = 0; i< n_players; i++)
        cout << "Player " << marks[i] << " has " << count_cells[i] << " cells\n";
    for (int i = 0; i < M-1; cout << "------", i++);
    cout << "--\n";
}
//This function checks if the grid is full or not
bool check_full() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
            if (grid[i][j] == '.')
                return false;
    return true;
}
//This function checks if the game has a tie state or not
bool check_player_ability() {
    return possible_cells_size != 0;
}
//This function checks if given cell is chosen or not 
bool check_chosen(int i, int j) {
	for (int k = 0; k < possible_cells_size; k++)
		if (possible_cells[k][0] == i && possible_cells[k][1] == j)
			return true;
	return false;
}
//This function checks if given cell is empty or not 
bool check_empty(int i, int j) {
	return grid[i][j] == '.';
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i && i < N and 0 <= j && j < M;
}
//This function sets the given mark to the given cell
void set_cell(int i, int j, char mark) {
	grid[i][j] = mark;
}
//This function gets the most cell in the given direction
void get_most_cell(int i, int j, int dx, int dy, bool player, char target_mark, int &most_i, int &most_j) {
    int cnt = 0;
    while (check_valid_position(i, j) && grid[i][j] == marks[1-player]) {
        i += dx;
        j += dy;
        cnt ++;
	}
    if (check_valid_position(i, j) && grid[i][j] == target_mark && cnt > 0)
		most_i = i, most_j = j;
	else
		most_i = -1, most_j = -1;	
}
//This function gets the most cells in the all directions
void get_most_cells(int i, int j, bool player, char target_mark, int most_cells[N*M][2]) {
	int idx = 0;
    int dirs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
	for (int k = 0; k < 8; k++) {
		int dx = dirs[k][0], dy = dirs[k][1];
        int most_i, most_j;
		get_most_cell(i+dx, j+dy, dx, dy, player, target_mark, most_i, most_j);
        if (most_i == -1 && most_j == -1)
            continue;
        most_cells[idx][0] = most_i, most_cells[idx][1] = most_j;
		idx ++;
	}
    most_cells[idx][0] = -1, most_cells[idx][1] = -1;
}
//This function switches the neighbor cells of the given cell
void switch_cells(int i, int j, bool player) {
    count_cells[player] ++;
    int most_cells[N*M][2];
	get_most_cells(i, j, player, marks[player], most_cells);
	for (int k = 0; k < N*M; k++) {
		int most_i = most_cells[k][0], most_j = most_cells[k][1];
        if (most_i == -1 && most_j == -1)
            break;
        int dx = (most_i > i? 1 : most_i < i? -1 : 0);
        int dy = (most_j > j? 1 : most_j < j? -1 : 0);
        int curr_i = i, curr_j = j;
        count_cells[player] --;
        count_cells[1-player] ++;
        while (abs(curr_i - most_i) + abs(curr_j - most_j) > 0) {
            grid[curr_i][curr_j] = marks[player];
            count_cells[player] ++;
            count_cells[1-player] --;
            curr_i += dx;
            curr_j += dy;
		}
	}
}
//This function generates the possible cells to be chosen 
void generate_possible_cells(bool player) {
	possible_cells_size = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
            if (grid[i][j] != marks[player])
                continue;
			int most_cells[N*M][2];
            get_most_cells(i, j, player, '.', most_cells);
			for (int k = 0; k < N*M; k++) {
				int most_i = most_cells[k][0], most_j = most_cells[k][1];
				if (most_i == -1 && most_j == -1)
					break;
				possible_cells[possible_cells_size][0] = most_i;
				possible_cells[possible_cells_size][1] = most_j;
				possible_cells_size ++;
			}
		}
	}
	for (int i = 0; i < possible_cells_size; i++) {
		for (int j = i+1; j < possible_cells_size; j++) {
			if (possible_cells[i][0] == possible_cells[j][0] && possible_cells[i][1] == possible_cells[j][1]) {
				possible_cells[j][0] = possible_cells[possible_cells_size-1][0];
				possible_cells[j][1] = possible_cells[possible_cells_size-1][1];
				possible_cells_size --;
				i --;
				break;
			}
		}
	}
}
//This function marks the possible cells in the grid
void mark_possible_cells() {
	for (int k = 0; k < possible_cells_size; k++) {
		int i = possible_cells[k][0], j = possible_cells[k][1];
        grid[i][j] = '?';
	}
}
//This function unmarks the possible cells in the grid
void unmark_possible_cells() {
	for (int k = 0; k < possible_cells_size; k++) {
		int i = possible_cells[k][0], j = possible_cells[k][1];
        grid[i][j] = '.';
	}
}
//This function clears the game structures
void grid_clear() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			grid[i][j] = '.';
    grid[N/2][M/2-1] = grid[N/2-1][M/2] = marks[0];
    grid[N/2-1][M/2-1] = grid[N/2][M/2] = marks[1];
	for (int i = 0; i < n_players; i++)
		count_cells[i] = 2;
}
//This function reads a valid position input
void read_input(int &i, int &j) {
    cout << "Enter the row index and column index: ";
    cin >> i >> j;
    while (!check_valid_position(i, j) || !check_empty(i, j) || !check_chosen(i, j)) {
		cout << "Enter a valid row index and a valid column index: ";
		cin >> i >> j;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "Reversi Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Generate the possible cells to be chosen 
        generate_possible_cells(player);
        //Mark the possible cells
        mark_possible_cells();
        //Prints the grid
        print_grid();
        //Unmark the possible cells
        unmark_possible_cells();
        cout << "Player " << marks[player] << " is playing now\n";
        //Keep the player if there is not an ability with the other player
        if (!check_player_ability()) {
            cout << "Sorry, you can not play on this turn!\n";
            //Player number changes after each turn
            player = 1 - player; 
            continue;
		}
        //Read an input position from the player
        int i, j;
		read_input(i, j);
        //Set the player mark in the input position
        set_cell(i, j, marks[player]);
        //Switch the neighbor cells of the given cell
        switch_cells(i, j, player);
        //Check if the grid has a full state
        if (check_full()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
			int max_count_boxes = *max_element(count_cells, count_cells+n_players);
            if (count(count_cells, count_cells+n_players, max_count_boxes) == 1) {
				int idx_max_player = find(count_cells, count_cells+n_players, max_count_boxes) - count_cells;
                cout << "Congrats, Player " << marks[idx_max_player] << " is won!\n";
			}
            else
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
