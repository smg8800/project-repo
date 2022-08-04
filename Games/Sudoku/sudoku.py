import random
import math

#
# Sean Geary
# Sudoku
# ----------------------
# Given a semi-filled or empty sudoku board, this program solves the board using 
# recursion with backtracking. With the help of some other functions, the main function
# solve_sudoku handles all of the logic to solve a board. This function first checks if
# the input board is full (base case). If it is full, the board is 
# complete and a 1 is returned. Otherwise another function, find_zero, searches 
# the board and stores the location of the first zero found into variables i and j
# using pointers. When a location is found, a for loop checks what numbers will work
# there. The function is_val_valid combines the uses of functions is_val_in_row,
# is_val_in_col, and is_val_in_3x3_zone to check by the rules of sudoku if placing
# the number there is legal. After the number is placed, the solve_sudoku function is called.
# The recursion continues until the base case, at which point the problem will be 
# solved. Otherwise, if the number does not work, the cell is reset to 0 to prepare
# to try a new number (backtracking). Due to Python limitations, there is a maximum
# allowed number of recursive steps, so the program is not always successful on more
# difficult arrangements. Will potentially refactor into C/C++.
# -----------------------
# Potentially plan to simulate many different games with different amounts of
# squares already filled in randomly. Gather data to display how 'difficult'
# the game is based on the starting board.


# returns true if the sudoku board is full
def is_full(sudoku):
    for i in range(9):
        for j in range(9): # loop through whole board
            if (sudoku[i][j] == 0):
                return 0 # if any spot is unfilled ( == 0), board is not full; return 0

    return 1 # if there are no 0's on the board, it is full and the puzzle is solved

# returns 0; stores in i, j the indices of the first 0 found in the grid
def find_zero(sudoku):
    for i in range(9):
        for j in range(9): # loop through whole board
            if (sudoku[i][j] == 0): # we have found a 0 that we would like to place a number into
                # print("Found zero at " + str(i) + "," + str(j))
                return (i,j)
    return 0

# Return true if "val" already existed in ith row of array sudoku.
def is_val_in_row(val, i, sudoku):
    for j in range(9): # loop through the given row
        if (sudoku[i][j] == val): # if val already exists in the row, return true
            return 1
    return 0 # val not found in row

# Return true if "val" already existed in jth column of array sudoku.
def is_val_in_col(val, j, sudoku):
    for i in range(9): # loop through the given column
        if (sudoku[i][j] == val): # if val already exists in the col, return true
            return 1
    return 0 # val not found in column

# Return true if val already existed in the 3x3 zone corresponding to (i, j)
def is_val_in_3x3_zone(val, i, j, sudoku):
   

    q = (i // 3) * 3  # divide and floor the indices by 3
    w = (j // 3) * 3  # then multiply by 3 to get the corner of the 3x3 zone
    for f in range(q, q+3):
        for g in range(w, w+3): # loop through 3x3 cell that contains the given (i, j)
            if (sudoku[f][g] == val): # if val already exists in the 3x3 zone, return true;
                return 1
    return 0 # val not found in 3x3 zone

# Return true if the val is can be filled in the given entry.
def is_val_valid(val, i, j, sudoku):

    if (is_val_in_3x3_zone(val, i, j, sudoku) or is_val_in_col(val, j, sudoku) or is_val_in_row(val, i, sudoku)):
        return 0 # combine functions to check if val is valid. If any of these checks returns false, this function returns false.
    return 1 # val not found in row i, col j, or 3x3 zone of (i, j)

# Solve the given sudoku instance.
def solve_sudoku(sudoku):
    # n+=1
    # print(n)
    # print_sudoku(sudoku)
    if (is_full(sudoku)):
        print_sudoku(sudoku)
        return 1 # if the board is full, the puzzle is solved, return 1

  #int i, j, num
    zero_idx_pair = find_zero(sudoku) # find the next 0 and store the indices in i and j
    i = zero_idx_pair[0]
    j = zero_idx_pair[1]
    for num in range(1,10): # loop through numbers 1-9
        if (is_val_valid(num, i, j, sudoku)): # checks if numbers we are looping through are valid at that spot
            sudoku[i][j] = num # if valid, we place the number there
            if (solve_sudoku(sudoku)): # recursive call
                return 1 # if board is solved, return 1
            sudoku[i][j] = 0 # number did not solve, reset cell to 0; backtracking step

    return 0 # return 0 if the board is not solved


# Prints sudoku board to terminal
def print_sudoku(sudoku):

    for i in range(9):
        for j in range(9):
            print(str(sudoku[i][j]), end =' ')
        print()

def generate_sudoku():
    
    rc = 9
    difficulty = 40
    new_board = [[0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],]
    num = math.floor(random.random()*difficulty)
    placed = 0
    for i in range(num):
        randx = math.floor(random.random()*rc)
        randy = math.floor(random.random()*rc)
        rand = math.floor(random.random()*rc) + 1
        if new_board[randx][randy] == 0:
            if is_val_valid(rand, randx, randy, new_board):
                placed += 1
                new_board[randx][randy] = rand
    # print(num)
    # print(placed)
    print_sudoku(new_board)
    # print(solve_sudoku(new_board))
    return new_board


# main function: creates an empty sudoku board and generates
# another board that is random, then solves both
def main():

    test = [[0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0],]

    print(solve_sudoku(test))
    print(solve_sudoku(generate_sudoku()))

main()
