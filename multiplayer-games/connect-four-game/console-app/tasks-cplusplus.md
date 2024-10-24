# Tasks

## Import Libraries and Define Global Variables

```cpp
include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int M = 7;
const int n_players = 2;
char marks[n_players] = {'X', 'O'};
char grid[N][M];
```

## Display the Grid

```cpp
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
```

## Read User Input

```cpp
//This function checks if given position is valid or not
bool check_valid_column(int i) {

}
//This function checks if given cell is empty or not
bool check_empty(int i) {

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

## Set a Cell with the Given Symbol

```cpp
//This function sets the given mark to the given column
void set_cell(int i, char mark) {

}
```

## Clear the Grid

```cpp
//This function clears the game structures
void grid_clear() {

}
```

## Main Function

```cpp
//Take turn of the given player
void take_turn(int player) {
    //Read an input from the player
    cout << "Player " << marks[player] << " is playing now\n";
    int i;
    read_input(i);
    //Set the input position with the mark
    set_cell(i, marks[player]);
}
//Get the next Player number
int next_player(int player) {
    return (player + 1) % n_players;
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
        //Take turn of the current player
        take_turn(player);
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
