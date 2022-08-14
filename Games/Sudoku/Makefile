
sudoku: main.c sudoku.c
	g++ -g -c sudoku.c -o sudoku.o
	g++ -g -c main.c -o main.o
	g++ -g main.o sudoku.o -o sudoku

clean:
	rm *.o sudoku 
	rm testboards/sudoku*_out.txt
	rm Dataset/3m_out.txt

## Use 'make' followed by these options to automatically solve a given board
sudoku1: sudoku
	./sudoku testboards/sudoku1.txt testboards/sudoku1_out.txt

sudoku2: sudoku
	./sudoku testboards/sudoku2.txt testboards/sudoku2_out.txt

sudoku3: sudoku
	./sudoku testboards/sudoku3.txt testboards/sudoku3_out.txt

# make all
# all: sudoku
# 	./sudoku testboards/sudoku1.txt testboards/sudoku1_out.txt
# 	./sudoku testboards/sudoku2.txt testboards/sudoku2_out.txt
# 	./sudoku testboards/sudoku3.txt testboards/sudoku3_out.txt
process: sudoku
	./sudoku csv
