#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Row
 * @brief Represents a heap for each row in the board.
 * 
 * This structure is used to represent a node in a linked list where each node
 * contains an integer value and a pointer to the next node in the list.
 * 
 * @var Row::j
 * Member 'j' stores the column index where a queen is placed in the board.
 * 
 * @var Row::next
 * Member 'next' is a pointer to the next node in the heap.
 */
struct Row {
	int j;
	struct Row *next;
};

/**
 * SIZE - An integer representing the size of the board (number of queens).
 * 
 * row - A pointer to a struct Row, which represents a row in the board.
 * 
 * count - An integer counter, initialized to 0, used to keep track of the 
 * number of solutions found or the number of recursive calls.
 */
int SIZE;
struct Row *rows;
int count = 0;

/**
 * Checks if placing a queen at the given row and column is safe.
 *
 * This function determines if a queen can be placed at the specified row and column
 * on the chessboard without being attacked by any other queens already placed on the board.
 *
 * @param row The row index where the queen is to be placed.
 * @param col The column index where the queen is to be placed.
 * @return 1 if it is safe to place the queen at the specified position, 0 otherwise.
 */
int isSafe(int row, int col) {
	for (int i = 1; i <= row; i++) {
		if (rows[i-1].j == -1) {
			break;
		}
		if (rows[i-1].j == col || abs(rows[i-1].j - col) == abs(i - row)) {
			return 0;
		}
	}
	return 1;
}

/**
 * @brief Prints the current state of the chessboard.
 *
 * This function iterates through the chessboard and prints 'Q' for a queen
 * and '_' for an empty space. The board is represented by a 2D array where
 * the presence of a queen in a specific row and column is indicated by the
 * value of `row[i-1].j`.
 *
 * @note The function assumes that the board size is defined by the macro SIZE
 *       and that the `row` array is properly initialized and populated with
 *       the positions of the queens.
 */
void printBoard(void) {
	for (int i = 1; i <= SIZE; i++) {
		for (int j = 1; j <= SIZE; j++) {
			if (rows[i-1].j == j) {
				printf("Q");
			} else {
				printf("_");
			}
		}
		printf("\n");
	}
}

/**
 * @brief Recursively attempts to place queens on the board and prints the solution when all queens are placed.
 *
 * This function uses backtracking to place queens on a chessboard such that no two queens threaten each other.
 * It starts from a given depth (row) and tries to place a queen in each column of that row. If placing a queen
 * in a column is safe (i.e., it does not threaten any previously placed queens), it places the queen and
 * recursively attempts to place queens in the subsequent rows. If a solution is found (all queens are placed),
 * it prints the board configuration.
 *
 * @param r Pointer to the current row structure where a queen is to be placed.
 * @param depth The current depth (row) in the recursive search.
 */
void Start(struct Row *r, int depth) {
	if (depth == SIZE) {
		for (int j = 1; j <= SIZE; j++) {
			if (isSafe(depth, j)) {
				r->j = j;
				count++;
				printf("%d:\n", count);
				printBoard();
				printf("\n");
				r->j = -1;

				/**
				 * Searchs for the first solution found and exits the program.
				 * If you want to find all solutions, switch the comment from the following line with the break;
				 * The program will continue to search for all possible solutions.
				 */
				exit(1);
				//break;
			}
		}
		return;
	}    
	for (int j = 1; j <= SIZE; j++) {
		if (isSafe(depth, j)) {
			r->j = j;
			r->next = r + 1;
			Start(r->next, depth + 1);
			r->next->j = -1;
			r->next = NULL;
			r->j = -1;
		}
	}
}

/**
 * @file nrainhas.c
 * @brief Implementation of the N-Queens problem using backtracking.
 *
 * This program solves the N-Queens problem, which involves placing N queens on an N×N chessboard
 * such that no two queens threaten each other. The solution is implemented using a backtracking algorithm.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments. The second argument should be the size of the chessboard (N).
 * @return Returns -1 if the program encounters an error or 1 if completes execution.
 *
 * The program expects one command-line argument specifying the size of the chessboard (N).
 * It initializes the board and starts the backtracking algorithm to find a solution.
 */
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Missing table size\n");
		return -1;
	}
	SIZE = atoi(argv[1]);

	struct Row r[SIZE];
	rows = r;

	for (int i = 0; i < SIZE; i++) {
		r[i].j = -1;
		r[i].next = NULL;
	}

	Start(r, 1);
	return 1;
}
