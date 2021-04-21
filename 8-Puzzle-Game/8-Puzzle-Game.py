import random
N = 3
grid = []

#This function prints the grid of 8 Puzzle Game as the game progresses
def print_grid():
    print('-' * (N * N + N + 1))
    for i in range(N):
        print(end='|')
        for j in range(N):
            if grid[i][j] == 0:
                e = ' ' * N
            else:
                str_len = len(str(grid[i][j]))
                r1 = (N - str_len + 1) // 2
                r2 = (N - str_len) - r1
                e = (' ' * r1) + str(grid[i][j]) + (' ' * r2)
            print(e, end='|')
        print()
        print('-' * (N * N + N + 1))

#This function generates cells in the given grid
def generate_grid():
    for i in range(1, N*N):
        a = random.randint(0, N-1)
        b = random.randint(0, N-1)
        while grid[a][b] != 0:
            a = random.randint(0, N-1)
            b = random.randint(0, N-1)
        grid[a][b] = i

#This function rotates the grid by 90 degree anti-clockwise
def rotate_90():
    for i in range(N//2):
        for j in range(i, N-i-1):
            k                  = grid[i][j]
            grid[i][j]         = grid[N-j-1][i]
            grid[N-j-1][i]     = grid[N-i-1][N-j-1]
            grid[N-i-1][N-j-1] = grid[j][N-i-1]
            grid[j][N-i-1]     = k

#This function checks if the game state reachs the win state or not 
def check_win():
    idx = 1
    for i in range(N):
        for j in range(N):
            if grid[i][j] != idx % (N*N):
                return False
            idx += 1
    return True

#This function checks if the current right direction has a movement state or not
def check_available_direction():
    for i in range(N):
        j = 0
        while j < N and grid[i][j] == 0: 
            j +=1
        while j < N and grid[i][j] != 0: 
            j +=1
        if j < N:
            return True
    return False

#This function checks if the given direction has a movement state or not
def check_available_move(d):
    res = False
    #check direction right
    if d == 3: res = check_available_direction()
    rotate_90()
    #check direction down
    if d == 5: res = check_available_direction()
    rotate_90()
    #check direction left
    if d == 1: res = check_available_direction()
    rotate_90()
    #check direction up
    if d == 2: res = check_available_direction()
    rotate_90()
    return res

#This function moves the grid with the left direction 
def move():
    for i in range(N):
        for j in range(1, N):
            if grid[i][j] != 0 and grid[i][j-1] == 0:
                grid[i][j], grid[i][j-1] = grid[i][j-1], grid[i][j]
                return

#This function moves the grid with the given direction 
def move_direction(d):
    #move direction left
    if d == 1: move()
    rotate_90()
    #move direction up
    if d == 2: move()
    rotate_90()
    #move direction right
    if d == 3: move()
    rotate_90()
    #move direction down
    if d == 5: move()
    rotate_90()

#This function checks if the given direction is valid or not 
def check_valid_direction(i):
	return i in [1, 2, 3, 5]

#This function clears the game structures
def grid_clear():
	global grid
	grid = [[0] * N for i in range(N)]

#This function reads a valid direction
def read_input():
    i = int(input('Enter the direction: '))
    while not check_valid_direction(i) or not check_available_move(i):
        i = int(input('Enter a valid direction: '))
    return i


#MAIN FUNCTION
def play_game():
    print("8 Puzzle Game!")
    print("Welcome...")
    print("============================")
    while True:
        #Prints the grid
        print_grid()
        #Read an input from the player
        i = read_input()
        #Move with the input direction
        move_direction(i)
        #Check if the grid has a win state
        if check_win():
            #Prints the grid
            print_grid()
            #Announcement of the final statement
            print('Congrats, You won!')
            break

while True:
    grid_clear()
    generate_grid()
    play_game()
    c = input('Play Again [Y/N] ')
    if c not in 'yY':
        break
