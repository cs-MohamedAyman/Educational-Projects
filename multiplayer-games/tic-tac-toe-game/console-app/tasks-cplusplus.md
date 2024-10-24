# Tasks

## Import Libraries and Define Global Variables

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const int n_players = 2;
const char marks[n_players] = {'X', 'O'};
char grid[N][N];
```

## Display the Grid

```cpp
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
```

## Read User Input

```cpp
//This function checks if given cell is empty or not
bool check_empty(int i, int j) {

}
//This function checks if given position is valid or not
bool check_valid_position(int i, int j) {

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
```

## Check the Game Win State

```cpp
//This function checks if the game has a win state or not
bool check_win() {

}
```

## Check the Game Tie State

```cpp
//This function checks if the game has a tie state or not for the given mark
bool check_tie_player(char mark) {

}
//This function checks if the game has a tie state or not
bool check_tie() {
    bool all_tie = true;
    for (int i = 0; i < n_players; i++)
        if (!check_tie_player(marks[i]))
            all_tie = false;
    return all_tie;
}
```

## Clear the Grid

```cpp
//This function clears the game structures
void grid_clear() {

}
```

## Set a Cell with the Given Symbol

```cpp
//This function sets the given mark to the given cell
void set_cell(int i, int j, char mark) {

}
```

## Main Function

```cpp
//Take turn of the given player
void take_turn(bool player) {
    //Read an input position from the player
    cout << "Player " << marks[player] << " is playing now\n";
    int i, j;
    read_input(i, j);
    //Set the player mark in the input position
    set_cell(i, j, marks[player]);
}
//Get the next Player number
bool next_player(bool player) {
    return 1 - player;
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
        //Take turn of the current player
        take_turn(player);
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
        player = next_player(player);
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
```
