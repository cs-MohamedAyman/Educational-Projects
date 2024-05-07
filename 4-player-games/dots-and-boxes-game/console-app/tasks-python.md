# Tasks

## Import Libraries and Define Global Variables

```python
N, M = 5, 5
n_players = 2
marks = ['X', 'O']
count_boxes, grid, horizontal_grid, vertical_grid = [], [], [], []
```

## Display the Grid

```python
#This function prints the grid of Dots-and-Boxes as the game progresses
def print_grid():
    for i in range(n_players):
        print('Player %d: %c  ' % (i+1, marks[i]), end='')
        if i < n_players-1:
            print('vs  ', end='')
    print()
    print('--' + '------' * (M-1))
    for i in range(N):
        print(' . ', end = '')
        for j in range(M):
            print('---' if horizontal_grid[i][j] else '   ', end = '')
            if j < M-1:
                print(' . ', end = '')
        print()
        for j in range(M+1):
            print(' |  ' if vertical_grid[i][j] else '    ', end = '')
            if i < N-1 and j < M-1:
                print(grid[i][j] if grid[i][j] != '.' else ' ', end='')
            print(' ', end = '')
        print()
    for i in range(n_players):
        print('Player %c is %d'% (marks[i], count_boxes[i]))
    print('--' + '------' * (M-1))
```

## Read User Input

```python
#This function checks if the given position is valid in the grid or not
def check_valid_position(i, j):
    pass

#This function checks if given side is valid or not
def check_valid_side(i1, j1, i2, j2):
    pass

#This function checks if given horizontal side is empty or not
def check_empty_horizontal_side(i, j):
    pass

#This function checks if given vertical side is empty or not
def check_empty_vertical_side(i, j):
    pass

#This function arranges the points of the side
def arrange_side_points(i1, j1, i2, j2):
    pass

#This function checks if the given side is empty or not
def check_empty_side(i1, j1, i2, j2):
    pass

#This function reads a valid and arranged side input
def read_input():
    i1, j1, i2, j2 = map(int, input('Enter the two points of the side: ').split())
    i1, j1, i2, j2 = arrange_side_points(i1, j1, i2, j2)
    while not check_valid_position(i1, j1) or not check_valid_position(i2, j2) or \
          not check_valid_side(i1, j1, i2, j2) or not check_empty_side(i1, j1, i2, j2):
        i1, j1, i2, j2 = map(int, input('Enter a valid two points of the side: ').split())
        i1, j1, i2, j2 = arrange_side_points(i1, j1, i2, j2)
    return i1, j1, i2, j2
```

## Check the Game Full State

```python
#This function checks if the grid is full or not
def check_full():
    pass
```

## Set the Given Side

```python
#This function sets a horizontal side
def set_horizontal_side(i, j):
    pass

#This function sets a vertical side
def set_vertical_side(i, j):
    pass

#This function sets the given side
def set_side(i1, j1, i2, j2):
    if i1 == i2:
        set_horizontal_side(i1, j1)
    if j1 == j2:
        set_vertical_side(i1, j1)
```

## Set the Neighbor Boxes

```python
#This function sets a mark to the given completed box
def set_box(i, j, player):
    pass

#This function checks if the given box is complete or not
def is_complete_box(i, j):
    pass

#This function checks and sets the completed box
def set_neighbor_box(i1, j1, i2, j2, player):
    pass

#This function checks and sets the neighbor completed boxes
def set_neighbor_boxes(i1, j1, i2, j2, player):
    get_boxes = 0
    if i1 == i2:
        get_boxes |= set_neighbor_box(i1, j1, i2, j2, player)
        get_boxes |= set_neighbor_box(i1-1, j1, i2-1, j2, player)
    if j1 == j2:
        get_boxes |= set_neighbor_box(i1, j1, i2, j2, player)
        get_boxes |= set_neighbor_box(i1, j1-1, i2, j2-1, player)
    return get_boxes
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
    #Read an input position from the player
    print('Player %s is playing now' % marks[player])
    i1, j1, i2, j2 = read_input()
    #Set the input position with the mark
    set_side(i1, j1, i2, j2)
    #Set the neighbor boxes with the mark
    box_complete = set_neighbor_boxes(i1, j1, i2, j2, player)
    return  box_complete

#Get the next Player number
def next_player(player):
    return (player + 1) % n_players

#MAIN FUNCTION
def play_game():
    print("Dots-and-Boxes Game!")
    print("Welcome...")
    print("============================")
    player = 0
    while True:
        #Prints the grid
        print_grid()
        #Take turn of the current player
        box_complete = take_turn(player)
        #Check if the state of the grid has a complete state
        if check_full():
            #Prints the grid
            print_grid()
            #Announcement of the final statement
            if count_boxes.count(max(count_boxes)) == 1:
                idx_max_player = count_boxes.index(max(count_boxes))
                print('Congrats, Player %s is won!' % marks[idx_max_player])
            else:
                print("Woah! That's a tie!")
            break
        #Keep the player if there is a complete box
        if not box_complete:
            #Player number changes after each turn
            player = next_player(player)

while True:
    grid_clear()
    play_game()
    c = input('Play Again [Y/N] ')
    if c not in 'yY':
        break
```
