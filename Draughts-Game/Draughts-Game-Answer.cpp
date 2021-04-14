#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int M = 8;
const int n_players = 2;
string marks[n_players][n_players] = {{"B", "W"}, {"KB", "KW"}};
int count_cells[n_players];
string grid[N][M];
bool is_king[N][M];
int possible_cells[N*M][4];
int possible_cells_size;

//This function prints the grid of Dots-and-Boxes as the game progresses
void print_grid() {
    cout << "Player 1: " << marks[0][0] << "  vs  Player 2: " << marks[0][1] << "\n";
    cout << "--";
    for (int i = 0; i < 2*M; cout << "--", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++) {
			string cell = grid[i][j].size() == 2? grid[i][j] : grid[i][j]+" ";
            cout << cell << "  ";
		}
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < 2*M; cout << "--", i++);
        cout << "--\n";
    }
	for (int i = 0; i< n_players; i++)
        cout << "Player " << marks[0][i] << " has " << count_cells[i] << " cells\n";
    cout << "--";
    for (int i = 0; i < M-1; cout << "------", i++);
    cout << "\n";
}
//This function checks if the game has a win state or not
bool check_win() {
	for (int i = 0; i < n_players; i++)
        if (count_cells[i] == 0)
            return true;
    return false;
}
//This function checks if the game has a tie state or not
bool check_player_ability() {
    return possible_cells_size != 0;
}
//This function checks if given cell is chosen or not 
bool check_chosen(int i1, int j1, int i2, int j2) {
	for (int k = 0; k < possible_cells_size; k++)
		if (possible_cells[k][0] == i1 && possible_cells[k][1] == j1 &&
		    possible_cells[k][2] == i2 && possible_cells[k][3] == j2)
			return true;
	return false;
}
//This function checks if given cell is empty or not 
bool check_empty(int i, int j) {
	return grid[i][j] == ".";
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i && i < N && 0 <= j && j < M;
}
//This function sets the given mark to the given cell
void set_cell(int i, int j, string mark) {
	grid[i][j] = mark;
}
//This function moves the given player form the source cell to the target cell
void move_cell(int i1, int j1, int i2, int j2, bool player) {
    swap(grid[i1][j1], grid[i2][j2]);
    swap(is_king[i1][j1], is_king[i2][j2]);
    if (is_king[i2][j2] == 0 && player == 1 && i2 == 0)
        is_king[i2][j2] = 1;
    if (is_king[i2][j2] == 0 && player == 0 && i2 == N-1)
        is_king[i2][j2] = 1;
    set_cell(i2, j2, marks[is_king[i2][j2]][player]);
    if (abs(i2 - i1) == 2 && abs(j2 - j1) == 2) {
        set_cell((i1+i2)/2, (j1+j2)/2, ".");
        count_cells[1-player] --;
	}
}
//This function generates the possible cells to be chosen in the attack case
void generate_possible_cells_attack_case(bool player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
            if (grid[i][j] != marks[is_king[i][j]][player])
                continue;
            int d = player? -1 : 1;
			int dirs1[2][2] = {{d, -1}, {d, 1}};
            for (int k = 0; k < 2; k++) {
				int k1 = dirs1[k][0], k2 = dirs1[k][1];
                if (check_valid_position(i+k1, j+k2) && grid[i+k1][j+k2] == marks[is_king[i+k1][j+k2]][1-player]) {
                    if (check_valid_position(i+k1*2, j+k2*2) && check_empty(i+k1*2, j+k2*2)) {
						possible_cells[possible_cells_size][0] = i;
						possible_cells[possible_cells_size][1] = j;
						possible_cells[possible_cells_size][2] = i+k1*2;
						possible_cells[possible_cells_size][3] = j+k2*2;
						possible_cells_size ++;
					}
				}
			}
			int dirs2[4][2] = {{1, -1}, {1, 1}, {-1, -1}, {-1, 1}};
            for (int k = 0; k < 4; k++) {
				int k1 = dirs2[k][0], k2 = dirs2[k][1];
                if (is_king[i][j] && check_valid_position(i+k1, j+k2) && grid[i+k1][j+k2] == marks[is_king[i+k1][j+k2]][1-player]) {
                    if (check_valid_position(i+k1*2, j+k2*2) && check_empty(i+k1*2, j+k2*2)) {
						possible_cells[possible_cells_size][0] = i;
						possible_cells[possible_cells_size][1] = j;
						possible_cells[possible_cells_size][2] = i+k1*2;
						possible_cells[possible_cells_size][3] = j+k2*2;
						possible_cells_size ++;
					}
				}
			}
		}
	}
}
//This function generates the possible cells to be chosen in the defence case
void generate_possible_cells_defence_case(bool player) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
            if (grid[i][j] != marks[is_king[i][j]][player])
                continue;
            int d = player? -1 : 1;
			int dirs1[2][2] = {{d, -1}, {d, 1}};
            for (int k = 0; k < 2; k++) {
				int k1 = dirs1[k][0], k2 = dirs1[k][1];
                if (check_valid_position(i+k1, j+k2) && check_empty(i+k1, j+k2)) {
					possible_cells[possible_cells_size][0] = i;
					possible_cells[possible_cells_size][1] = j;
					possible_cells[possible_cells_size][2] = i+k1;
					possible_cells[possible_cells_size][3] = j+k2;
					possible_cells_size ++;
				}
			}
			int dirs2[4][2] = {{1, -1}, {1, 1}, {-1, -1}, {-1, 1}};
            for (int k = 0; k < 4; k++) {
				int k1 = dirs2[k][0], k2 = dirs2[k][1];
                if (is_king[i][j] && check_valid_position(i+k1, j+k2) && check_empty(i+k1, j+k2)) {
					possible_cells[possible_cells_size][0] = i;
					possible_cells[possible_cells_size][1] = j;
					possible_cells[possible_cells_size][2] = i+k1;
					possible_cells[possible_cells_size][3] = j+k2;
					possible_cells_size ++;
				}
			}
		}
	}
}
//This function generates the possible cells to be chosen 
void generate_possible_cells(bool player) {
    possible_cells_size = 0;
    generate_possible_cells_attack_case(player);
    if (possible_cells_size) return;
    generate_possible_cells_defence_case(player);
	for (int i = 0; i < possible_cells_size; i++) {
		for (int j = i+1; j < possible_cells_size; j++) {
			if (possible_cells[i][0] == possible_cells[j][0] && possible_cells[i][1] == possible_cells[j][1] &&
			    possible_cells[i][2] == possible_cells[j][2] && possible_cells[i][3] == possible_cells[j][3]) {
				possible_cells[j][0] = possible_cells[possible_cells_size-1][0];
				possible_cells[j][1] = possible_cells[possible_cells_size-1][1];
				possible_cells[j][2] = possible_cells[possible_cells_size-1][2];
				possible_cells[j][3] = possible_cells[possible_cells_size-1][3];
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
		int i = possible_cells[k][2], j = possible_cells[k][3];
        grid[i][j] = "?";
	}
}
//This function unmarks the possible cells in the grid
void unmark_possible_cells() {
	for (int k = 0; k < possible_cells_size; k++) {
		int i = possible_cells[k][2], j = possible_cells[k][3];
        grid[i][j] = ".";
	}
}
//This function clears the game structures
void grid_clear() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			grid[i][j] = ".";
			is_king[i][j] = 0;
		}
	}
	for (int i = 0; i < n_players; i++)
		count_cells[i] = (N/2-1)*M/2;
	for (int i = 0; i < N/2-1; i++) {
		if (i % 2 == 1) {
			for (int j = 0; j < M/2; j++) {
                grid[i][2*j]   = marks[is_king[i][j]][0];
                grid[i][2*j+1] = ".";
                grid[N-i-1][2*j]   = ".";
                grid[N-i-1][2*j+1] = marks[is_king[i][j]][1];
			}
		}
		else {
			for (int j = 0; j < M/2; j++) {
                grid[i][2*j]   = ".";
                grid[i][2*j+1] = marks[is_king[i][j]][0];
                grid[N-i-1][2*j]   = marks[is_king[i][j]][1];
                grid[N-i-1][2*j+1] = ".";
			}
		}
	}
}
//This function reads a valid position input
void read_input(int &i1, int &j1, int &i2, int &j2) {
    cout << "Enter the source and target points: ";
    cin >> i1 >> j1 >> i2 >> j2;
    while (!check_valid_position(i1, j1) || !check_valid_position(i2, j2) ||
           check_empty(i1, j1) || !check_empty(i2, j2) || !check_chosen(i1, j1, i2, j2)) {
		cout << "Enter a valid source and target points: ";
		cin >> i1 >> j1 >> i2 >> j2;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "Draughts Game!\n";
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
        cout << "Player " << marks[0][player] << " is playing now\n";
        //Keep the player if there is not an ability with the other player
        if (!check_player_ability()) {
            cout << "Sorry, you can not play on this turn!\n";
            break;
		}
        //Read an input position from the player
        int i1, j1, i2, j2;
		read_input(i1, j1, i2, j2);
        //Set the player mark in the input position
        move_cell(i1, j1, i2, j2, player);
        //Check if the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            cout << "Congrats, Player " << marks[0][player] << " is won!\n";
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
