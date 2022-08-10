#include "sudoku.h"

int main(int argc, char **argv) {

  int sudoku[9][9];

  if(argc != 3) {
    printf("To use program, type as: ./sudoku sudoku_instance.txt output_instance.txt\n");
    printf("To build and run all files, type: make all\n");
    return 0;
  }

  printf("------------------\n");
  parse_sudoku(argv[1], sudoku);
  printf("Input sudoku:\n");
  print_sudoku(sudoku);
  // int * n;
  // int p = 0; debug
  // n = &p;
  
  if (solve_sudoku(sudoku)) {
    printf("Output solved sudoku:\n");
    print_sudoku(sudoku);
    printf("------------------\n");
    write_sudoku(argv[2], sudoku);
  } else {
    printf("------------------\n");
    printf("Solution not found\n");
  }
  
  return 0;
}
