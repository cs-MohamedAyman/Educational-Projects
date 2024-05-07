# Tasks

## Import Libraries and Define Global Variables

```python
N, M = 3, 3
a_row = 3
n_players = 2
marks = ['1', '2']
char_S, char_O = 'S', 'O'
chars = [char_S, char_O]
count_wins, grid = [], []
```

## Display the Grid

```python
#This function prints the grid of SOS Game as the game progresses
def print_grid():
    print("Player %s:  vs  Player %s:" % (marks[0], marks[1]))
    print('--' + '---' * M + '--')
    for i in range(N):
        print(end='|  ')
        for j in range(M):
            print(grid[i][j], end='  ')
        print(end='|')
        print()
        print('--' + '---' * M + '--')
    print('Player %s is %d'% (marks[0], count_wins[0]))
    print('Player %s is %d'% (marks[1], count_wins[1]))
    print('--' + '------' * (M-1))
```

## Read User Input

```python
#This function checks if given position is valid or not
def check_valid_position(i, j):
    pass

#This function checks if given cell is empty or not
def check_empty(i, j):
    pass

#This function checks if given char is valid or not
def check_mark(c):
    pass

#This function reads a valid position input
def read_input():
    i, j, c = input('Enter the row index and column index and mark: ').split()
    i, j, c = int(i), int(j), c.upper()
    while not check_valid_position(i, j) or not check_empty(i, j) or not check_mark(c):
        i, j, c = input('Enter a valid row index and column index and mark: ').split()
        i, j, c = int(i), int(j), c.upper()
    return i, j, c
```

## Check the Game Complete State

```python
#This function checks if the game has a complete state or not
def check_complete():
    pass
```

## Updates the Number of Complete Words of the Given Player

```python
#This function updates the number of complete words of the given player
def update_num_complete_words(i, j, player):
    pass
```

## Clear the Grid

```python
#This function clears the game structures
def grid_clear():
    pass
```

## Set a Cell with the Given Symbol

```python
#This function sets the given mark to the given cell
def set_cell(i, j, mark):
    pass
```

## Main Function

```python
#Take turn of the given player
def take_turn(player):
    #Read an input position from the player
    print('Player %s is playing now' % (marks[player]))
    i, j, c = read_input()
    #Set the player mark in the input position
    set_cell(i, j, c)
    #Update the number of complete words
    word_complete = update_num_complete_words(i, j, player)
    return word_complete

#Get the next Player number
def next_player(player):
    return 1 - player

#Get the index of the winner Player
def select_winner():
    idx_max_player = -1
    if count_wins.count(max(count_wins)) == 1:
        idx_max_player = count_wins.index(max(count_wins))
    return idx_max_player

#MAIN FUNCTION
def play_game():
    print("SOS Game!")
    print("Welcome...")
    print("============================")
    player = 0
    while True:
        #Prints the grid
        print_grid()
        #Take turn of the current player
        word_complete = take_turn(player)
        #Check if the grid has a complete state
        if check_complete():
            #Prints the grid
            print_grid()
            #Announcement of the final statement
            idx_max_player = select_winner()
            if idx_max_player != -1:
                print('Congrats, Player %s is won!' % marks[idx_max_player])
            else:
                print("Woah! That's a tie!")
            break
        #Keep the player if there is a complete word
        if not word_complete:
            #Player number changes after each turn
            player = next_player(player)

while True:
    grid_clear()
    play_game()
    c = input('Play Again [Y/N] ')
    if c not in 'yY':
        break
```
