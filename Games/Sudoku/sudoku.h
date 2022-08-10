#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int is_val_in_row(const int val, const int i, const int sudoku[9][9]);

int is_val_in_col(const int val, const int i, const int sudoku[9][9]);

int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]);

int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]);

int solve_sudoku(int sudoku[9][9]);

void print_sudoku(int sudoku[9][9]);

void parse_sudoku(const char fpath[], int sudoku[9][9]);

void write_sudoku(const char fpath[], int sudoku[9][9]);

#endif
