# Tasks

## Import Libraries and Define Global Variables

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const int M = 3;
const int a_row = 3;
const int n_players = 2;
const int marks[n_players] = {1, 2};
const char char_S = 'S';
const char char_O = 'O';
const char chars[2] = {char_S, char_O};
char grid[N][N];
int count_wins[n_players];
```

## Display the Grid

```cpp
//This function prints the grid of SOS Game as the game progresses
void print_grid() {
    cout << "Player " << marks[0] << ":  vs  Player " << marks[1] << ":\n";
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
    cout << "Player " << marks[0] << " is " << count_wins[0] << '\n';
    cout << "Player " << marks[1] << " is " << count_wins[1] << '\n';
    cout << "--";
    for (int i = 0; i < M-1; cout << "------", i++);
    cout << "\n";
}
```

## Read User Input

```cpp
//This function checks if given position is valid or not
bool check_valid_position(int i, int j) {

}
//This function checks if given cell is empty or not
bool check_empty(int i, int j) {

}
//This function checks if given char is valid or not
bool check_mark(char c) {

}
//This function reads a valid position input
void read_input(int &i, int &j, char &c) {
    cout << "Enter the row index and column index and mark: ";
    cin >> i >> j >> c;
    while (!check_valid_position(i, j) || !check_empty(i, j) || !check_mark(c)) {
        cout << "Enter a valid row index and column index and mark: ";
        cin >> i >> j >> c;
    }
}
```

## Check the Game Complete State

```cpp
//This function checks if the game has a complete state or not
bool check_complete() {

}
```

## Updates the Number of Complete Words of the Given Player

```cpp
//This function updates the number of complete words of the given player
bool update_num_complete_words(int i, int j, bool player) {

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
bool take_turn(int player) {
    //Read an input position from the player
    cout << "Player " << marks[player] << " is playing now\n";
    int i, j; char c;
    read_input(i, j, c);
    //Set the player mark in the input position
    set_cell(i, j, c);
    //Update the number of complete words
    bool word_complete = update_num_complete_words(i, j, player);
    return word_complete;
}
//Get the next Player number
int next_player(int player) {
    return 1 - player;
}
//Get the index of the winner Player
int select_winner() {
    int idx_max_player = -1
    int max_count_boxes = *max_element(count_wins, count_wins+n_players);
    if (count(count_wins, count_wins+n_players, max_count_boxes) == 1)
        idx_max_player = find(count_wins, count_wins+n_players, max_count_boxes) - count_wins;
    return idx_max_player;
}
//MAIN FUNCTION
void play_game() {
    cout << "SOS Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Take turn of the current player
        word_complete = take_turn(player);
        //Check if the grid has a complete state
        if (check_complete()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            int idx_max_player = select_winner();
            if (idx_max_player != -1)
                cout << "Congrats, Player " << marks[idx_max_player] << " is won!\n";
            else
                cout << "Woah! That's a tie!\n";
            break;
        }
        //Keep the player if there is a complete word
        if (!word_complete) {
            //Player number changes after each turn
            player = next_player(player);
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
}```
