#include <stdio.h>
#include <stdlib.h>


const int WIDTH = 80;
const int HEIGHT = 29;

const char ALIVE_CELL = '@';
const char DEAD_CELL = '.';


int get_proper_coord(int coord, int limit) {
	if (coord > limit - 1)
		return coord % limit;
	else if (coord < 0)
		return limit + coord;
	else
		return coord;
}


int cell_alive(char board[HEIGHT][WIDTH + 1], int y, int x) {
	int checking_x = get_proper_coord(x, WIDTH);
	int checking_y = get_proper_coord(y, HEIGHT);

	// printf("\n%d %d\n", checking_x, checking_y);

	return (board[checking_y][checking_x] == ALIVE_CELL);
}


int count_neighbours(char board[HEIGHT][WIDTH + 1], int y, int x) {
	int neighbours_number = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			neighbours_number += cell_alive(board, y + i, x + j);
		}
	}
	/*
	if (neighbours_number > 0) {
	 printf("\n%d\n", neighbours_number);
	}
	*/
	return neighbours_number - cell_alive(board, y, x);
}


int cell_survives(char board[HEIGHT][WIDTH + 1], int y, int x) {
	int neighbours_number = count_neighbours(board, y, x);

	if (neighbours_number < 2 || neighbours_number > 3)
		return 0;
	else if (neighbours_number == 2)
		return cell_alive(board, y, x);
	else
		return 1;
}


void initialize_board(char board[HEIGHT][WIDTH + 1]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = DEAD_CELL;
		}

		board[i][WIDTH] = '\0';
	}
}


void display_board(char board[HEIGHT][WIDTH + 1]) {
	for (int i = 0; i < HEIGHT; i++) {
		if (i < 9)
			printf(" %d)  ", i + 1);
		else
			printf("%d)  ", i + 1);

		printf("%s\n", board[i]);
	}
}


void copy_one_dim_array(char array1[WIDTH + 1], char array2[WIDTH + 1]) {
	for (int i = 0; i < WIDTH; i++) {
		array1[i] = array2[i];
	}
}

void array_copy(char ar1[HEIGHT][WIDTH + 1], char ar2[HEIGHT][WIDTH + 1]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			ar1[i][j] = ar2[i][j];
		}
	}
}


void generate_next_board(char current_board[HEIGHT][WIDTH + 1], char next_board[HEIGHT][WIDTH + 1]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			// printf("\nI am okay\n");
			if (cell_survives(current_board, i, j))
				next_board[i][j] = ALIVE_CELL;
			else
				next_board[i][j] = DEAD_CELL;
		}
	}
}


void sleep() {
	int x = 0;
	for (int i = 0; i < 1000000000; i++) {
		x++;
	}
}

int main(int argc, char *argv[]) {
	/**/
	char current_board[HEIGHT][WIDTH+1];
	char next_board[HEIGHT][WIDTH+1];

	initialize_board(current_board);
	initialize_board(next_board);

	display_board(current_board);
	// return 0;

	current_board[10][10] = ALIVE_CELL;
	current_board[9][10] = ALIVE_CELL;
	current_board[10][9] = ALIVE_CELL;
	current_board[11][10] = ALIVE_CELL;
	current_board[11][11] = ALIVE_CELL;

	display_board(current_board);
	// printf("%s", current_board);
	// return 0;

	for (int i = 0; i < 100000; i++) {
		sleep();
		//system("clear");
		//system("cls");
		generate_next_board(current_board, next_board);
		array_copy(current_board, next_board);
		display_board(current_board);
	}
	// */
	return 0;
}
