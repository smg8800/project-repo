#include <stdio.h>
#include "updateBoard.h"

/*
* Sean Geary
* netid: smgeary2
* ECE220 MP6
* 10/14/20
*
* Conway's Game of Life
------------------------------
* This program implements Conway's Game of Life, a 0 player game that involves the
* evolution of cells on a game board. A cell can be either alive or dead, and 
* whether they remain alive/dead or change depends on the previous state of the game.
* I implemented three functions, countLiveNeighbor, updateBoard, and aliveStable.
* countLiveNeighbor counts the amount of living cells surrounding a given cell.
* Using the given cell location, I checked all cells in a 3x3 grid with the target
* cell in the center, making sure not to count it as a neighbor. After checking all
* cells, the number of live cells is returned. In order to implement updateBoard, I
* initially just went through the game board, checked if the cell was supposed to
* change states, then changed them. I realized that if we update the cells in this
* manner, it could cause errors for other cells. So instead I created a new array
* to hold the changes needed to be made. Once the entire board is checked, then
* the temporary array is copied into the main board. To implement aliveStable, I again
* created a copy of the board. I then called the updateBoard function on the copy, 
* then I iterated through the board to check if the original board was different
* from the copy with one update. If they are the same, then the game is over.
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col) {
    int i, j, currRow = row - 1, currCol = col - 1, live = 0; // set currRow and currCol so we start in the 'upper left corner'
    for (i = 0; i < 3; i++, currRow++) {
        if (currRow >= 0 && currRow < boardRowSize) { // make sure its a valid row
            for (j = 0; j < 3; j++, currCol++) {
                if (currCol >= 0 && currCol < boardColSize) { // make sure its a valid column
                    if (!(currRow == row && currCol == col)) { // make sure it isn't the cell whose neighbors we are finding
                        if (board[currRow*boardColSize + currCol] == 1) { // check if the cell is alive
                            live++; // since the cell is alive, increment live
                        }
                    }
                }
            }
            currCol = col - 1; // need to reset the currCol for each row
        }
    }
    return live;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int i, j, currRow = 0, currCol = 0;
    int interim_board[boardRowSize*boardColSize]; // create a copy of the board so we can
    for (i = 0; i < boardRowSize; i++) {          // gather all changes then apply them all at once
        for (j = 0; j < boardColSize; j++) {
            interim_board[i*boardColSize+j] = board[i*boardColSize+j]; // copying
        }
    }
    for (i = 0; i < boardRowSize; i++, currRow++) { // iterate through game board
        for (j = 0; j < boardColSize; j++, currCol++) {
            if (board[currRow*boardColSize + currCol] == 0) { // cell is dead: will change if has 3 live neighbors
                if (countLiveNeighbor(board, boardRowSize, boardColSize, currRow, currCol) == 3) {
                    interim_board[currRow*boardColSize + currCol] = 1; // dead cell with 3 live neighbors becomes alive
                }
            } else if (board[currRow*boardColSize + currCol] == 1) { // cell is alive: will change if it does not have 2 or 3 live neighbors
                if (countLiveNeighbor(board, boardRowSize, boardColSize, currRow, currCol) < 2 ||
                    countLiveNeighbor(board, boardRowSize, boardColSize, currRow, currCol) > 3) {
                    interim_board[currRow*boardColSize + currCol] = 0; // live cell with < 2 or > 3 live neighbors dies
                }
            }
        }
        currCol = 0; // reset the column for each iteration of rows
    }
    for (i = 0; i < boardRowSize; i++) { // iterate through game board
        for (j = 0; j < boardColSize; j++) {
            board[i*boardColSize+j] = interim_board[i*boardColSize+j]; // copy the temp board back into the actual board all at once
        }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize) {

    int i, j; // currRow = 0, currCol = 0;
    int temp_board[boardRowSize*boardColSize]; // create a copy of the board to test on

    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            temp_board[i*boardColSize+j] = board[i*boardColSize+j]; // copy original elements into test board
        }
    }
    updateBoard(temp_board, boardRowSize, boardColSize); // call updateBoard on the test board as not to change
    for (i = 0; i < boardRowSize; i++) {                 // the original if it is not stable yet
        for (j = 0; j < boardColSize; j++) {
            if (temp_board[i*boardColSize+j] != board[i*boardColSize+j]) {
                return 0; // if the elements at a given point change, we know that the board is not stable yet - return 0
            }
        }
    }
    return 1; // by this point every element has been checked and confirmed to not have changed
}

				
				
			

