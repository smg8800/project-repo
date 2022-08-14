#include <stdio.h>
#include "sudoku.h"
/*
* Sean Geary
* Sudoku
----------------------
* Given a semi-filled or empty sudoku board, this program solves the board using 
* recursion with backtracking. With the help of some other functions, the main function
* solve_sudoku handles all of the logic to solve a board. This function first checks if
* the input board is full (base case). If it is full, the board is 
* complete and a 1 is returned. Otherwise another function, find_zero, searches 
* the board and stores the location of the first zero found into variables i and j
* using pointers. When a location is found, a for loop checks what numbers will work
* there. The function is_val_valid combines the uses of functions is_val_in_row,
* is_val_in_col, and is_val_in_3x3_zone to check by the rules of sudoku if placing
* the number there is legal. After the number is placed, the solve_sudoku function is called.
* The recursion continues until the base case, at which point the problem will be 
* solved. Otherwise, if the number does not work, the cell is reset to 0 to prepare
* to try a new number (backtracking).
* To run this, type 'make' followed by sudokuN where N is 1-3, the provided puzzles.
* To run a custom puzzle, create it in a text file like the provided and to solve it type
* ./sudoku path_to_puzzle.txt output_path.txt
* Additionally this program is able to process a file containing many sudoku puzzles.
* The function process_csv() will open the file and read line by line, acquiring the
* unsolved puzzle. This puzzle is parsed into a sudoku board and we proceed to call
* solve_sudoku() on it, and also write to an output text file the puzzle before and
* after being solved, with the puzzle number displayed.
* The dataset of 3 million sudoku boards was downloaded from https://www.kaggle.com/datasets/radcliffe/3-million-sudoku-puzzles-with-ratings?resource=download.
* To run this, type 'make process' into the terminal.
*/


// returns true if the sudoku board is full
int is_full(const int sudoku[9][9]) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) { // loop through whole board
      if (sudoku[i][j] == 0) { 
        return 0; // if any spot is unfilled ( == 0), board is not full; return 0
      }
    }
  }
  return 1; // if there are no 0's on the board, it is full and the puzzle is solved
}

// returns 0; stores in i, j the indices of the first 0 found in the grid
int find_zero(const int sudoku[9][9], int* x, int* y) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) { // loop through whole board
      if (sudoku[i][j] == 0) { // we have found a 0 that we would like to place a number into
        *x = i; // address of x now contains index i
        *y = j; // address of y now contains index j
        return 0;
      }
    }
  }
  return 0;
}

// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  int j;
  for (j = 0; j < 9; j++) { // loop through the given row
    if (sudoku[i][j] == val) { // if val already exists in the row, return true
      return 1;
    }
  }
  return 0; // val not found in row
}

// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  int i;
  for (i = 0; i < 9; i++) { // loop through the given column
    if (sudoku[i][j] == val) { // if val already exists in the col, return true
      return 1; 
    }
  }
  
  return 0; // val not found in column
}

// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  int q = (i / 3) * 3; // using the fact that division rounds down, divide the indices by 3
  int w = (j / 3) * 3; // to round then multiply by 3 to get the corner of the 3x3 zone
  int f, g;
  for (f = q; f < q + 3; f++) {
    for (g = w; g < w + 3; g++) { // loop through 3x3 cell that contains the given (i, j)
        if (sudoku[f][g] == val) { // if val already exists in the 3x3 zone, return true;
          return 1;
        }
    }
  }
  return 0; // val not found in 3x3 zone
}

// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  if (is_val_in_3x3_zone(val, i, j, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_row(val, i, sudoku)) {
    return 0; // combine functions to check if val is valid. If any of these checks returns false, this function returns false.
  }
  return 1; // val not found in row i, col j, or 3x3 zone of (i, j)
}

// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) { // include int *n if debugging
  // (*n)++;
  // printf("%d\n", *n); debug
  // print_sudoku(sudoku);
  if (is_full(sudoku)) { return 1;} // if the board is full, the puzzle is solved, return 1

  int i, j, num;
  find_zero(sudoku, &i, &j); // find the next 0 and store the indices in i and j
  for (num = 1; num <= 9; num++) { // loop through numbers 1-9
    if (is_val_valid(num, i, j, sudoku)) { // checks if numbers we are looping through are valid at that spot
      sudoku[i][j] = num; // if valid, we place the number there
      if (solve_sudoku(sudoku)) { // recursive call
        return 1; // if it solves it, return 1
        }
      sudoku[i][j] = 0; // number did not solve, reset cell to 0; backtracking step
      }
    }
  return 0; // return 0 if the board is not solved
}

// Prints sudoku board to terminal
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// Read text file sudoku board
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

// Write sudoku board to text file
void write_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "w");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fprintf(reader, "%d ", sudoku[i][j]);
    }
    fprintf(reader, "\n");
  }
  fclose(reader);
}

#define MAXCHAR 1000

// collects information from input CSV file, solve all puzzles, and outputs the unsolved and solved puzzles to a text file
void process_csv(const char fpath[], const char outpath[]) {
  int num = 0;
  FILE * reader = fopen(fpath, "r");
  FILE *reader2 = fopen(outpath, "w");
  assert(reader2 != NULL);
  assert(reader != NULL);
  char row[MAXCHAR];
  int i = 0;
  fgets(row, MAXCHAR, reader); // get first row that has column names

  // get each line from file and process line
  while (!feof(reader)) {
    num++;
    char *line;
    fgets(row, MAXCHAR, reader);
    int sudoku[9][9];
    i = 0;
    line = strtok(row, ","); // separates four parts of CSV file
    char * temp;
    char temp2;
    while (line != NULL) {
      if (i == 1) { // we have part of the line that contains the unsolved puzzle
        for(int k =0; k<9; k++) {
          for(int j=0; j<9; j++) {
            temp = &line[k*9 + j];
            temp2 =  temp[0];
            sudoku[k][j] = atoi(&temp2); // placing input information into correct spot on board
          }
        }
        break; // can break from current line ib while loop since we have already gotten all we need
      }
      line = strtok(NULL, ",");
      i++;
    }

    // print sudoku board before and after solving into output text file
    int i, j;
    fprintf(reader2, "Puzzle no. %d\n", num);
    for(i=0; i<9; i++) {
      for(j=0; j<9; j++) {
        fprintf(reader2, "%d ", sudoku[i][j]);
      }
      fprintf(reader2, "\n");
    }
    fprintf(reader2, "\n");

    solve_sudoku(sudoku); // solve the puzzle

    fprintf(reader2, "Solution: \n");
    for(i=0; i<9; i++) {
      for(j=0; j<9; j++) {
        fprintf(reader2, "%d ", sudoku[i][j]);
      }
      fprintf(reader2, "\n");
    }
    fprintf(reader2, "\n\n\n");
    // printf("Number processed: %d\n", num); // debug
  }
  // close files being read/written
  fclose(reader);
  fclose(reader2);
}
