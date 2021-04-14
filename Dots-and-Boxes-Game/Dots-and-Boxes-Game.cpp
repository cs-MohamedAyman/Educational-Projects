#include <bits/stdc++.h>
using namespace std;

const int N = 5;
const int M = 5;
const int n_players = 2;
char marks[n_players] = {'X', 'O'};
int count_boxes[n_players];
char grid[N-1][M-1];
bool horizontal_grid[N+1][M];
bool vertical_grid[N][M+1];

//This function prints the grid of Dots-and-Boxes as the game progresses
void print_grid() {
	for (int i = 0; i< n_players; i++) {
        cout << "Player " << i+1 << ": " << marks[i] << "  ";
        if (i < n_players-1)
            cout << "vs  ";
	}
	cout << "\n";
	cout << "--";
	for (int i = 0; i < M-1; cout << "------", i++);
	cout << "\n";
	for (int i = 0; i < N; i++) {
        cout << " . ";
		for (int j = 0; j < M; j++) {
            (horizontal_grid[i][j])? cout << "---" : cout << "   ";
            if (j < M-1)
                cout << " . ";
		}
        cout << "\n";
		for (int j = 0; j < M+1; j++) {
            (vertical_grid[i][j])? cout << " |  " : cout << "    ";
            if (i < N-1 && j < M-1)
                (grid[i][j] != '.')? cout << grid[i][j] : cout << " ";
            cout << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i< n_players; i++)
        cout << "Player " << marks[i] << " is " << count_boxes[i] << "\n";
	cout << "--";
	for (int i = 0; i < M-1; cout << "------", i++);
	cout << "\n";
}
//This function checks if the grid is full or not
bool check_full() {
	int total = 0;
	for (int i = 0; i < n_players; i++)
		total += count_boxes[i];
    return total == (N-1) * (M-1);
}
//This function checks if given horizontal side is empty or not 
bool check_empty_horizontal_side(int i, int j) {
	return horizontal_grid[i][j] == 0;
}
//This function checks if given vertical side is empty or not 
bool check_empty_vertical_side(int i, int j) {
	return vertical_grid[i][j] == 0;
}
//This function checks if the given side is empty or not 
bool check_empty_side(int i1, int j1, int i2, int j2) {
    if (i1 == i2)
        return check_empty_horizontal_side(i1, j1);
    if (j1 == j2)
        return check_empty_vertical_side(i1, j1);
}
//This function checks if the given position is valid in the grid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i < N and 0 <= j < M;
}
//This function checks if given side is valid or not 
bool check_valid_side(int i1, int j1, int i2, int j2) {
    return abs(i1 - i2) + abs(j1 - j2) == 1 &&
           check_valid_position(i1, j1) &&
           check_valid_position(i2, j2);
}
//This function sets a horizontal side
void set_horizontal_side(int i, int j) {
	horizontal_grid[i][j] = 1;
}
//This function sets a vertical side
void set_vertical_side(int i, int j) {
	vertical_grid[i][j] = 1;
}
//This function sets the given side
void set_side(int i1, int j1, int i2, int j2) {
    if (i1 == i2)
        set_horizontal_side(i1, j1);
    if (j1 == j2)
        set_vertical_side(i1, j1);
}
//This function checks if the given box is complete or not
bool is_complete_box(int i, int j) {
    return horizontal_grid[i][j] + horizontal_grid[i+1][j] +
           vertical_grid[i][j] + vertical_grid[i][j+1] == 4;
}
//This function sets a mark to the given completed box
void set_box(int i, int j, int player) {
    grid[i][j] = marks[player];
    count_boxes[player] += 1;
}
//This function checks and sets the completed box
bool set_neighbor_box(int i1, int j1, int i2, int j2, int player) {
    if (!check_valid_side(i1, j1, i2, j2) ||
        !is_complete_box(i1, j1))
        return 0;
    set_box(i1, j1, player);
    return 1;
}
//This function checks and sets the neighbor completed boxes
bool set_neighbor_boxes(int i1, int j1, int i2, int j2, int player) {
    bool get_boxes = 0;
    if (i1 == i2) {
        get_boxes |= set_neighbor_box(i1, j1, i2, j2, player);
        get_boxes |= set_neighbor_box(i1-1, j1, i2-1, j2, player);
	}
    if (j1 == j2) {
        get_boxes |= set_neighbor_box(i1, j1, i2, j2, player);
        get_boxes |= set_neighbor_box(i1, j1-1, i2, j2-1, player);
	}
    return get_boxes;
}
//This function arranges the points of the side
void arrange_side_points(int &i1, int &j1, int &i2, int &j2) {
	int t1 = min(i1, i2), t2 = min(j1, j2);
	int t3 = max(i1, i2), t4 = max(j1, j2);
	i1 = t1, j1 = t2, i2 = t3, j2 = t4;
}
//This function clears the game structures
void grid_clear() {
	for (int i = 0; i < n_players; i++)
		count_boxes[i] = 0;
	for (int i = 0; i < N-1; i++)
		for (int j = 0; j < M-1; j++)
			grid[i][j] = '.';
	for (int i = 0; i < N+1; i++)
		for (int j = 0; j < M; j++)
			horizontal_grid[i][j] = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M+1; j++)
			vertical_grid[i][j] = 0;
}
//This function reads a valid position input
void read_input(int &i1, int &j1, int &i2, int &j2) {
    cout << "Enter the two points of the side: ";
    cin >> i1 >> j1 >> i2 >> j2;
    arrange_side_points(i1, j1, i2, j2);
    while (!check_valid_position(i1, j1) || !check_valid_position(i2, j2) ||
           !check_valid_side(i1, j1, i2, j2) || !check_empty_side(i1, j1, i2, j2)) {
		cout << "Enter a valid two points of the side: ";
		cin >> i1 >> j1 >> i2 >> j2;
		arrange_side_points(i1, j1, i2, j2);
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "Dots-and-Boxes Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    int player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i1, j1, i2, j2;
		read_input(i1, j1, i2, j2);
        //Set the input position with the mark
        set_side(i1, j1, i2, j2);
        //Set the neighbor boxes with the mark
        bool box_complete = set_neighbor_boxes(i1, j1, i2, j2, player);
        //Check if the state of the grid has a complete state
        if (check_full()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
			int max_count_boxes = *max_element(count_boxes, count_boxes+n_players);
            if (count(count_boxes, count_boxes+n_players, max_count_boxes) == 1) {
				int idx_max_player = find(count_boxes, count_boxes+n_players, max_count_boxes) - count_boxes;
                cout << "Congrats, Player " << marks[idx_max_player] << " is won!\n";
			}
            else
                cout << "Woah! That's a tie!\n";
            break;
		}
		//Keep the player if there is a complete box
        if (!box_complete) {
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
