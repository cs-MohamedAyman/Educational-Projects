# Tasks

## Import Libraries and Define Global Variables

```python
N, M = 6, 7
n_players = 2
marks = ['X', 'O']
grid = []
```

## Display the Grid

```python
#This function prints the grid of Connect Four Game as the game progresses
def print_grid():
    for i in range(n_players):
        print('Player %d: %c  ' % (i+1, marks[i]), end='')
        if i < n_players-1:
            print('vs  ', end='')
    print()
    print('--' + '---' * M + '--')
    for i in range(N):
        print(end='|  ')
        for j in range(M):
            print(grid[i][j], end='  ')
        print(end='|')
        print()
        print('--' + '---' * M + '--')
```

## Read User Input

```python
#This function checks if given position is valid or not
def check_valid_column(i):
    pass

#This function checks if given cell is empty or not
def check_empty(i):
    pass

#This function reads a valid position input
def read_input():
    i = int(input('Enter the column index: '))
    while not check_valid_column(i) or not check_empty(i):
        i = int(input('Enter a valid column index: '))
    return i
```

## Check the Game Win State

```python
#This function checks if the game has a win state or not
def check_win():
    pass
```

## Check the Game Tie State

```python
#This function checks if the game has a tie state or not for the given mark
def check_tie_player(mark):
    pass

#This function checks if the game has a tie state or not
def check_tie():
    all_tie = True
    for i in range(n_players):
        if not check_tie_player(marks[i]):
            all_tie = False
    return all_tie
```

## Set a Cell with the Given Symbol

```python
#This function sets the given mark to the given column
def set_cell(i, mark):
    pass
```

## Clear the Grid

```python
#This function clears the game structures
def grid_clear():
    pass
```

## Main Function

```python
#Take turn of the given player
def take_turn(player):
    #Read an input from the player
    print('Player %s is playing now' % marks[player])
    i = read_input()
    #Set the input column with the mark
    set_cell(i, marks[player])

#Get the next Player number
def next_player(player):
    return (player + 1) % n_players

#MAIN FUNCTION
def play_game():
    print("Connect Four Game!")
    print("Welcome...")
    print("============================")
    player = 0
    while True:
        #Prints the grid
        print_grid()
        #Take turn of the current player
        take_turn(player)
        #Check if the grid has a win state
        if check_win():
            #Prints the grid
            print_grid()
            #Announcement of the final statement
            print('Congrats, Player %s is won!' % marks[player])
            break
        #Check if the grid has a tie state
        if check_tie():
            #Prints the grid
            print_grid()
            #Announcement of the final statement
            print("Woah! That's a tie!")
            break
        #Player number changes after each turn
        player = next_player(player)

while True:
    grid_clear()
    play_game()
    c = input('Play Again [Y/N] ')
    if c not in 'yY':
        break
```
