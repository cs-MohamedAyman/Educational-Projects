#include <bits/stdc++.h>
using namespace std;

const int N = 3;
int grid[N][N];

//This function prints the grid of 8 Puzzle Game as the game progresses
void print_grid() {
	for (int i = 0; i < (N * N + N + 1); cout << "-", i++);
	cout << "\n";
	for (int i = 0; i < N; i++) {
        cout << "|";
		for (int j = 0; j < N; j++) {
			string e = "";
            if (grid[i][j] == 0) {
				for (int t = 0; t < N; e += " ", t++);
			}
            else {
                int str_len = to_string(grid[i][j]).size();
                int r1 = (N - str_len + 1) / 2;
                int r2 = (N - str_len) - r1;
				for (int t = 0; t < r1; e += " ", t++);
				e += to_string(grid[i][j]);
				for (int t = 0; t < r2; e += " ", t++);
			}
			cout << e << "|";
		}
		cout << "\n";
		for (int t = 0; t < (N * N + N + 1); cout << "-", t++);
		cout << "\n";
	}
}
//This function generates cells in the given grid
void generate_grid() {
    for (int i = 1; i < N*N; i++) {
		int a = rand() % N;
		int b = rand() % N;
		while (grid[a][b] != 0) {
			a = rand() % N;
			b = rand() % N;
		}
		grid[a][b] = i;
	}
}
//This function rotates the grid by 90 degree anti-clockwise
void rotate_90() {
	for (int i = 0; i < N/2; i++) {
		for (int j = i; j < N-i-1; j++) {
            int k              = grid[i][j];
            grid[i][j]         = grid[N-j-1][i];
            grid[N-j-1][i]     = grid[N-i-1][N-j-1];
            grid[N-i-1][N-j-1] = grid[j][N-i-1];
            grid[j][N-i-1]     = k;
		}
	}
}
//This function checks if the game state reachs the win state or not 
bool check_win() {
    int idx = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
            if (grid[i][j] != idx % (N*N))
                return false;
            idx ++;
		}
	}
    return true;
}
//This function checks if the current right direction has a movement state or not
bool check_available_direction() {
	for (int i = 0; i < N; i++) {
        int j = 0;
        while (j < N && grid[i][j] == 0) j +=1;
        while (j < N && grid[i][j] != 0) j +=1;
        if (j < N) return true;
	}
    return false;
}
//This function checks if the given direction has a movement state or not
bool check_available_move(int d) {
    bool res = false;
    //check direction right
    if (d == 3) res = check_available_direction();
    rotate_90();
    //check direction down
    if (d == 5) res = check_available_direction();
    rotate_90();
    //check direction left
    if (d == 1) res = check_available_direction();
    rotate_90();
    //check direction up
    if (d == 2) res = check_available_direction();
    rotate_90();
    return res;
}
//This function moves the grid with the left direction 
void move() {
	for (int i = 0; i < N; i++)
		for (int j = 1; j < N; j++)
            if (grid[i][j] != 0 && grid[i][j-1] == 0) {
				swap(grid[i][j], grid[i][j-1]);
				return;
			}
}
//This function moves the grid with the given direction 
void move_direction(int d) {
    //move direction left
    if (d == 1) move();
    rotate_90();
    //move direction up
    if (d == 2) move();
    rotate_90();
    //move direction right
    if (d == 3) move();
    rotate_90();
    //move direction down
    if (d == 5) move();
    rotate_90();
}
//This function checks if the given direction is valid or not 
bool check_valid_direction(int i) {
	return i == 1 || i == 2 || i == 3 || i == 5;
}
//This function clears the game structures
void grid_clear() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			grid[i][j] = 0;
}
//This function reads a valid direction
void read_input(int &i) {
    cout << "Enter the direction: ";
	cin >> i;
    while (!check_valid_direction(i) || !check_available_move(i)) {
        cout << "Enter a valid direction: ";
		cin >> i;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "8 Puzzle Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
		int i;
		read_input(i);
        //Move with the input direction
        move_direction(i);
        //Check if the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, You won!\n";
			break;
		}
	}
}
int main() {
	while (true) {
		grid_clear();
        generate_grid();
		play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
	}
}
