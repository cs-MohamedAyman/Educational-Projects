#include <bits/stdc++.h>
#include "utils.cpp"
using namespace std;

//This function checks if the game has a win state or not
bool check_win_grid(int grid_idx) {
    //Check if all rows are not full, the game is still running
    for (int i = 0; i < N; i++) {
        int s[N+1] = {0};
		for (int j = 0; j < N; j++) {
            s[grids[grid_idx][i][j]] ++;
			if (s[grids[grid_idx][i][j]] != 1 || grids[grid_idx][i][j] == 0)
				return false;
		}
	}
    //Check if all columns are not full, the game is still running
    for (int i = 0; i < N; i++) {
        int s[N+1] = {0};
		for (int j = 0; j < N; j++) {
            s[grids[grid_idx][j][i]] ++;
			if (s[grids[grid_idx][j][i]] != 1 || grids[grid_idx][j][i] == 0)
				return false;
		}
	}
    //Check if all boxes are not full, the game is still running
    for (int i = 0; i < N; i+=root_N) {
		for (int j = 0; j < N; j+=root_N) {
			int s[N+1] = {0};
			for (int k = i; k < i+root_N; k++) {
				for (int w = j; w < j+root_N; w++) {
					s[grids[grid_idx][k][w]] ++;
					if (s[grids[grid_idx][k][w]] != 1 || grids[grid_idx][k][w] == 0)
						return false;
				}
			}
		}
	}
    //Otherwise, there is a win state in the game, 
    //if all cases above not reached		
    return true;
}
//This function checks if the game has a win state or not
bool check_win() {
	for (int grid_idx = 0; grid_idx < n_grids[mode]; grid_idx++) {
        if (!check_win_grid(grid_idx))
            return false;
	}
    return true;
}
//This function checks if the given position is valid or not 
bool check_valid_position(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < N;
}
//This function checks if the given grid index is valid or not 
bool check_valid_grid_index(int grid_idx) {
    return 0 <= grid_idx && grid_idx < n_grids[mode];
}
//This function checks if the given cell is original or not
bool check_original_cell(int grid_idx, int i, int j) {
    return cpy_grids[grid_idx][i][j] != 0;
}
//This function checks if the given value is valid with the given cell
bool check_valid_value(int grid_idx, int i, int j, int v) {
	//Check delete case
    if (v == 0)
        return true;
	//Check invalid value
    if (v < 1 || v > N)
        return false;
	//Check duplicate in all rows
    for (int k = 0; k < N; k++)
        if (grids[grid_idx][i][k] == v)
            return false;
	//Check duplicate in all columns
    for (int k = 0; k < N; k++)
        if (grids[grid_idx][k][j] == v)
            return false;
	//Check duplicate in all boxes
    int b = i/root_N*root_N;
	int e = j/root_N*root_N;
    for (int k = b; k < b+root_N; k++)
		for (int w = e; w < e+root_N; w++)
            if (grids[grid_idx][k][w] == v)
                return false;
    //Otherwise, the given value is valid,
    //if all cases above not reached		
    return true;
}
//This function converts the given position in the grid into a box number
int cvt_grid_pos_to_box(int i, int j) {
    return i / root_N * root_N + j / root_N;
}
//This function converts the given box number into a position index in the grid
void cvt_box_to_grid_pos(int x, int &a, int &b) {
    a = x / root_N * root_N;
	b = x % root_N * root_N;
}
//This function copies a cell from the givne source grid to the given target grid
bool check_valid_value_cell(int grid_idx_s, int box_idx_s, int grid_idx_t, int box_idx_t, int i, int j, int v) {
    int i_s, j_s;
	cvt_box_to_grid_pos(box_idx_s, i_s, j_s);
    int i_t, j_t;
	cvt_box_to_grid_pos(box_idx_t, i_t, j_t);
    if (i_s <= i && i < i_s+root_N && j_s <= j && j < j_s+root_N) {
        int step_i = i_t - i_s;
        int step_j = j_t - j_s;
        return check_valid_value(grid_idx_t, i+step_i, j+step_j, v);
	}
    return true;
}
//This function checks if the given value is valid with the shared boxes in the other grids
bool check_valid_value_in_shared_boxes(int grid_idx, int i, int j, int v) {
    bool res = check_valid_value(grid_idx, i, j, v);
	for (int i = 0; i < max_shared_boxes; i++) {
		int grid_i = similar_boxes[mode][i][0], box_i = similar_boxes[mode][i][1], 
			grid_j = similar_boxes[mode][i][2], box_j = similar_boxes[mode][i][3];
		if (grid_i == -1 && box_i == -1 && grid_j == -1 && box_j == -1)
			break;
        if (grid_idx == grid_i)
            res &= check_valid_value_cell(grid_i, box_i, grid_j, box_j, i, j, v);
        if (grid_idx == grid_j)
            res &= check_valid_value_cell(grid_j, box_j, grid_i, box_i, i, j, v);
	}
    return res;
}
//This function copies a cell from the givne source grid to the given target grid
void cpy_cell(int grid_idx_s, int box_idx_s, int grid_idx_t, int box_idx_t, int i, int j, bool set_original=false) {
    int i_s, j_s;
	cvt_box_to_grid_pos(box_idx_s, i_s, j_s);
    int i_t, j_t;
	cvt_box_to_grid_pos(box_idx_t, i_t, j_t);
    if (i_s <= i && i < i_s+root_N and j_s <= j && j < j_s+root_N) {
        int step_i = i_t - i_s;
        int step_j = j_t - j_s;
        grids[grid_idx_t][i+step_i][j+step_j] = grids[grid_idx_s][i][j];
        if (set_original)
            cpy_grids[grid_idx_t][i+step_i][j+step_j] = cpy_grids[grid_idx_s][i][j];
	}
}
//This function copies the shared boxes in the other grids
void cpy_cell_in_shared_boxes(int grid_idx, int i, int j, int v) {
	for (int i = 0; i < max_shared_boxes; i++) {
		int grid_i = similar_boxes[mode][i][0], box_i = similar_boxes[mode][i][1], 
			grid_j = similar_boxes[mode][i][2], box_j = similar_boxes[mode][i][3];
		if (grid_i == -1 && box_i == -1 && grid_j == -1 && box_j == -1)
			break;
        if (grid_idx == grid_i)
            cpy_cell(grid_i, box_i, grid_j, box_j, i, j);
        if (grid_idx == grid_j)
            cpy_cell(grid_j, box_j, grid_i, box_i, i, j);
	}
}
//This function sets the given value to the given cell
void set_cell(int grid_idx, int i, int j, int v) {
    grids[grid_idx][i][j] = v;
    cpy_cell_in_shared_boxes(grid_idx, i, j, v);
}
//This function gets the similar boxes the other grids
void get_similar_boxes(int grid_idx, int box_idx, int shared_boxes[max_shared_boxes][2]) {
	int idx = 0;
	for (int i = 0; i < max_shared_boxes; i++) {
		int grid_i = similar_boxes[mode][i][0], box_i = similar_boxes[mode][i][1], 
			grid_j = similar_boxes[mode][i][2], box_j = similar_boxes[mode][i][3];
		if (grid_i == -1 && box_i == -1 && grid_j == -1 && box_j == -1) {
            shared_boxes[idx][0] = -1, shared_boxes[idx][1] = -1;
			idx ++;
			break;
		}
        if (grid_idx == grid_i && box_idx == box_i) {
            shared_boxes[idx][0] = grid_j, shared_boxes[idx][1] = box_j;
			idx ++;
		}
        if (grid_idx == grid_j && box_idx == box_j) {
            shared_boxes[idx][0] = grid_i, shared_boxes[idx][1] = box_i;
			idx ++;
		}
	}
}
//This function copies the given box in the shared boxes in the other grids
void cpy_box_in_shared_boxes(int grid_idx, int box_idx, int shared_boxes[max_shared_boxes][2], bool set_original=false) {
	for (int k = 0; k < max_shared_boxes; k++) {
		int grid_k = shared_boxes[k][0], box_k = shared_boxes[k][1];
		if (grid_k == -1 && box_k == -1)
			break;
        int a, b;
		cvt_box_to_grid_pos(box_idx, a, b);
		for (int i = a; i < a+root_N; i++)
			for (int j = b; j < b+root_N; j++)
                cpy_cell(grid_idx, box_idx, grid_k, box_k, i, j, true);
	}
}
//This function checks if the given box is empty or not
bool is_empty_box(int grid_idx, int box_idx) {
    int a, b;
	cvt_box_to_grid_pos(box_idx, a, b);
    for (int i = a; i < a+root_N; i++) {
		for (int j = b; j < b+root_N; j++) {
            if (grids[grid_idx][i][j] != 0)
                return false;
		}
	}
    return true;
}
//This function checks if the given box is divided into empty cells and non-empty cells or not
bool is_half_box(int grid_idx, int box_idx) {
    int empty_cells = 0;
    int a, b;
	cvt_box_to_grid_pos(box_idx, a, b);
    for (int i = a; i < a+root_N; i++) {
		for (int j = b; j < b+root_N; j++) {
            if (grids[grid_idx][i][j] == 0)
                empty_cells ++;
		}
	}
    return empty_cells == (N+1) / 2;
}
//This function copies the all boxes of the given grid in the shared boxes in the other grids
void cpy_similar_boxes(int grid_idx) {
    for (int i = 0; i < N; i+=root_N) {
		for (int j = 0; j < N; j+=root_N) {
            int box_idx = cvt_grid_pos_to_box(i, j);
            int shared_boxes[max_shared_boxes][2];
			get_similar_boxes(grid_idx, box_idx, shared_boxes);
            cpy_box_in_shared_boxes(grid_idx, box_idx, shared_boxes, true);
		}
	}
}
//This function solves the grid
bool solve_grid(int grid_idx, int i, int j) {
    if (j == N) {
        i += 1;
        j = 0;
	}
    if (i == N)
        return true;
    if (check_original_cell(grid_idx, i, j))
        return solve_grid(grid_idx, i, j+1);
    for (int k = 1; k < N+1; k++) {
        if (check_valid_value_in_shared_boxes(grid_idx, i, j, k)) {
            grids[grid_idx][i][j] = k;
            cpy_grids[grid_idx][i][j] = k;
            if (solve_grid(grid_idx, i, j+1))
                return true;
            grids[grid_idx][i][j] = 0;
            cpy_grids[grid_idx][i][j] = 0;
		}
	}
    return false;
}
//This function generates cells in the grids
void generate_cells(int grid_idx=0) {
    for (int k = 0; k < N; k+=root_N) {
        int box_idx = cvt_grid_pos_to_box(k, k);
        if (!is_empty_box(grid_idx, box_idx))
            continue;
		for (int i = 0; i < root_N; i++) {
			for (int j = 0; j < root_N; j++) {
                int n = rand() % N + 1;
                while (!check_valid_value_in_shared_boxes(grid_idx, k+i, k+j, n) ||
                      check_original_cell(grid_idx, k+i, k+j)) {
                    n = rand() % N + 1;
				}
                grids[grid_idx][k+i][k+j] = n;
                cpy_grids[grid_idx][k+i][k+j] = n;
			}
		}
	}
}
//This function removes cells in the grids
void remove_cells(int grid_idx=0) {
    for (int k = 0; k < (N+1)/2; k++) {
		for (int i = 0; i < N; i+=root_N) {
			for (int j = 0; j < N; j+=root_N) {
                int box_idx = cvt_grid_pos_to_box(i, j);
                if (is_half_box(grid_idx, box_idx))
                    continue;
                int t1 = rand() % root_N;
                int t2 = rand() % root_N;
                while (!check_original_cell(grid_idx, i+t1, j+t2)) {
					t1 = rand() % root_N;
					t2 = rand() % root_N;
				}
                grids[grid_idx][i+t1][j+t2] = 0;
                cpy_grids[grid_idx][i+t1][j+t2] = 0;
			}
		}
	}
}
//This function generates cells in the given grid
void generate_grids() {
    //Generate cells in the grid
    generate_cells();
	for (int grid_idx = 0; grid_idx < n_grids[mode]; grid_idx++) {
        //Solve the complete grid
        solve_grid(grid_idx, 0, 0);
        //Copy the similar boxes in the another grids
        cpy_similar_boxes(grid_idx);
	}
	for (int grid_idx = 0; grid_idx < n_grids[mode]; grid_idx++) {
        //Remove cells in the grid to be solved
        remove_cells(grid_idx);
        //Copy the similar boxes in the another grids
        cpy_similar_boxes(grid_idx);
	}
}
//This function reads a valid position and value inputs
void read_input(int &grid_idx, int &i, int &j, int &v) {
	cout << "Enter the row index and column index and value: ";
	cin >> grid_idx >> i >> j >> v;
    while (!check_valid_position(i, j) || !check_valid_value(grid_idx, i, j, v) || check_original_cell(grid_idx, i, j)) {
		cout << "Enter a valid row index and column index and value: ";
		cin >> grid_idx >> i >> j >> v;
	}
}
//MAIN FUNCTION
void play_game() {
    cout << "Multi-Sudoku Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {
        //Prints the grids
        print_grids();
        //Read an input from the player
		int grid_idx, i, j, v;
        read_input(grid_idx, i, j, v);
        //Set the input position with the value
        set_cell(grid_idx, i, j, v);
        //Check if the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grids();
			//Announcement of the final statement
            cout << "Congrats, You won!\n";
            break;
		}
	}
}
int main() {
	while (true) {
		contract_modes();
		print_modes();
		set_config();
		grid_clear();
		generate_grids();
		play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
	}
}
