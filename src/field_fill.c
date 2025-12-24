#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "playground.h"
#include "check_logic.h"

int random_lentil(void) {
	
	int rand_field = (rand() % LENTILS_NUM) + 1;
	
	return rand_field;
}

int random_field_index(void) {
	int rand_field_index = (rand() % (ROWS*COLUMNS));
	
	return rand_field_index;
}

// fill one field, shift from left border
void fill_horizontal_left(playground* my_playground, int last_index) {
	int row = last_index / COLUMNS;
	int col = last_index % COLUMNS;
	
	// find first valid column
	int move_col = col-1;
	while(move_col >= 0 && (my_playground->matrix[row][move_col] == EMPTY || my_playground->matrix[row][move_col] == LEFT_PIGEON || my_playground->matrix[row][move_col] == RIGHT_PIGEON)) {
		move_col--;
	}
	
	// fill if border or pigeons on border
	if(move_col < 0) {
		if ((my_playground->matrix[row][0] == LEFT_PIGEON || my_playground->matrix[row][0] == RIGHT_PIGEON) && (my_playground->matrix[row][1] == LEFT_PIGEON || my_playground->matrix[row][1] == RIGHT_PIGEON)) {
			my_playground->matrix[row][2] = random_lentil();
		}
		else if (my_playground->matrix[row][0] == LEFT_PIGEON || my_playground->matrix[row][0] == RIGHT_PIGEON) {
			my_playground->matrix[row][1] = random_lentil();
		}
		else {
			my_playground->matrix[row][0] = random_lentil();
		}
	}
	// move one to right (skip pigeons)
	else if((my_playground->matrix[row][move_col+1] == LEFT_PIGEON || my_playground->matrix[row][move_col+1] == RIGHT_PIGEON) && (my_playground->matrix[row][move_col+2] == LEFT_PIGEON || my_playground->matrix[row][move_col+2] == RIGHT_PIGEON)) {
		my_playground->matrix[row][move_col+3] = my_playground->matrix[row][move_col];
		my_playground->matrix[row][move_col] = EMPTY;
	}	
	else if(my_playground->matrix[row][move_col+1] == LEFT_PIGEON || my_playground->matrix[row][move_col+1] == RIGHT_PIGEON) {
		my_playground->matrix[row][move_col+2] = my_playground->matrix[row][move_col];
		my_playground->matrix[row][move_col] = EMPTY;
	}
	else {
		my_playground->matrix[row][move_col+1] = my_playground->matrix[row][move_col];
		my_playground->matrix[row][move_col] = EMPTY;
	}
}

// fill one field, shift from right border
void fill_horizontal_right(playground* my_playground, int first_index) {
	int row = first_index / COLUMNS;
	int col = first_index % COLUMNS;
	
	// find first valid column
	int move_col = col+1;
	while(move_col < COLUMNS && (my_playground->matrix[row][move_col] == EMPTY || my_playground->matrix[row][move_col] == LEFT_PIGEON || my_playground->matrix[row][move_col] == RIGHT_PIGEON)) {
		move_col++;
	}
	
	// fill if border
	if(move_col >= COLUMNS) {
		if ((my_playground->matrix[row][COLUMNS-1] == LEFT_PIGEON || my_playground->matrix[row][COLUMNS - 1] == RIGHT_PIGEON) && (my_playground->matrix[row][COLUMNS-2] == LEFT_PIGEON || my_playground->matrix[row][COLUMNS-2] == RIGHT_PIGEON)) {
			my_playground->matrix[row][COLUMNS-3] = random_lentil();
		}
		else if (my_playground->matrix[row][COLUMNS-1] == LEFT_PIGEON || my_playground->matrix[row][COLUMNS-1] == RIGHT_PIGEON) {
			my_playground->matrix[row][COLUMNS-2] = random_lentil();
		}
		else {
			my_playground->matrix[row][COLUMNS-1] = random_lentil();
		}
	}
	// move one to left (skip pigeons)
	else if((my_playground->matrix[row][move_col-1] == LEFT_PIGEON || my_playground->matrix[row][move_col-1] == RIGHT_PIGEON) && (my_playground->matrix[row][move_col-2] == LEFT_PIGEON || my_playground->matrix[row][move_col-2] == RIGHT_PIGEON)) {
		my_playground->matrix[row][move_col-3] = my_playground->matrix[row][move_col];
		my_playground->matrix[row][move_col] = EMPTY;
	}	
	else if(my_playground->matrix[row][move_col-1] == LEFT_PIGEON || my_playground->matrix[row][move_col-1] == RIGHT_PIGEON) {
		my_playground->matrix[row][move_col-2] = my_playground->matrix[row][move_col];
		my_playground->matrix[row][move_col] = EMPTY;
	}
	else {
		my_playground->matrix[row][move_col-1] = my_playground->matrix[row][move_col];
		my_playground->matrix[row][move_col] = EMPTY;
	}
}

// fill one field, shift from top border
void fill_vertical_top(playground* my_playground, int last_index) {
	int row = last_index / COLUMNS;
	int col = last_index % COLUMNS;
	
	// find first valid column
	int move_row = row-1;
	while(move_row >= 0 && (my_playground->matrix[move_row][col] == EMPTY || my_playground->matrix[move_row][col] == LEFT_PIGEON || my_playground->matrix[move_row][col] == RIGHT_PIGEON)) {
		move_row--;
	}
	
	// fill if border
	if(move_row < 0) {
		if ((my_playground->matrix[0][col] == LEFT_PIGEON || my_playground->matrix[0][col] == RIGHT_PIGEON) && (my_playground->matrix[1][col] == LEFT_PIGEON || my_playground->matrix[1][col] == RIGHT_PIGEON)) {
			my_playground->matrix[2][col] = random_lentil();
		}
		else if (my_playground->matrix[0][col] == LEFT_PIGEON || my_playground->matrix[0][col] == RIGHT_PIGEON) {
			my_playground->matrix[1][col] = random_lentil();
		}
		else {
			my_playground->matrix[0][col] = random_lentil();
		}
	}
	// move one down (skip pigeons)
	else if((my_playground->matrix[move_row+1][col] == LEFT_PIGEON || my_playground->matrix[move_row+1][col] == RIGHT_PIGEON) && (my_playground->matrix[move_row+2][col] == LEFT_PIGEON || my_playground->matrix[move_row+2][col] == RIGHT_PIGEON)) {
		my_playground->matrix[move_row+3][col] = my_playground->matrix[move_row][col];
		my_playground->matrix[move_row][col] = EMPTY;
	}	
	else if(my_playground->matrix[move_row+1][col] == LEFT_PIGEON || my_playground->matrix[move_row+1][col] == RIGHT_PIGEON) {
		my_playground->matrix[move_row+2][col] = my_playground->matrix[move_row][col];
		my_playground->matrix[move_row][col] = EMPTY;
	}
	else {
		my_playground->matrix[move_row+1][col] = my_playground->matrix[move_row][col];
		my_playground->matrix[move_row][col] = EMPTY;
	}
}

// fill one field, shift from bottom border
void fill_vertical_bottom(playground* my_playground, int first_index) {
	int row = first_index / COLUMNS;
	int col = first_index % COLUMNS;
	
	// find first valid column
	int move_row = row+1;
	while(move_row < ROWS && (my_playground->matrix[move_row][col] == EMPTY || my_playground->matrix[move_row][col] == LEFT_PIGEON || my_playground->matrix[move_row][col] == RIGHT_PIGEON)) {
		move_row++;
	}
	
	// fill if border
	if(move_row >= ROWS) {
		if ((my_playground->matrix[ROWS-1][col] == LEFT_PIGEON || my_playground->matrix[ROWS-1][col] == RIGHT_PIGEON) && (my_playground->matrix[ROWS-2][col] == LEFT_PIGEON || my_playground->matrix[ROWS-2][col] == RIGHT_PIGEON)) {
			my_playground->matrix[ROWS-3][col] = random_lentil();
		}
		else if (my_playground->matrix[ROWS-1][col] == LEFT_PIGEON || my_playground->matrix[ROWS-1][col] == RIGHT_PIGEON) {
			my_playground->matrix[ROWS-2][col] = random_lentil();
		}
		else {
			my_playground->matrix[ROWS-1][col] = random_lentil();
		}
	}
	// move one down (skip pigeons)
	else if((my_playground->matrix[move_row-1][col] == LEFT_PIGEON || my_playground->matrix[move_row-1][col] == RIGHT_PIGEON) && (my_playground->matrix[move_row-2][col] == LEFT_PIGEON || my_playground->matrix[move_row-2][col] == RIGHT_PIGEON)) {
		my_playground->matrix[move_row-3][col] = my_playground->matrix[move_row][col];
		my_playground->matrix[move_row][col] = EMPTY;
	}	
	else if(my_playground->matrix[move_row-1][col] == LEFT_PIGEON || my_playground->matrix[move_row-1][col] == RIGHT_PIGEON) {
		my_playground->matrix[move_row-2][col] = my_playground->matrix[move_row][col];
		my_playground->matrix[move_row][col] = EMPTY;
	}
	else {
		my_playground->matrix[move_row-1][col] = my_playground->matrix[move_row][col];
		my_playground->matrix[move_row][col] = EMPTY;
	}
}

void empty_matrix(playground* my_playground) {
	for(int i=0; i < ROWS; i++) {
		for(int j=0; j < COLUMNS; j++) {
			my_playground->matrix[i][j] = EMPTY;
		}
	}
}

void fill_one(playground* my_playground, int row, int col) {
	int current_field;
	do {
		current_field = random_lentil();
	} while(!check_neighbors(my_playground, current_field, row, col));
	my_playground->matrix[row][col] = current_field;
}

void fill_matrix(playground* my_playground) {
	// fill empty
	empty_matrix(my_playground);
	// fill random values
	srand(time(NULL));
	int current_field;
	for(int i=0; i < ROWS; i++) {
		for(int j=0; j < COLUMNS; j++) {
			do {
				current_field = random_lentil();
			} while(!check_neighbors(my_playground, current_field, i, j));
			my_playground->matrix[i][j] = current_field;
		}
	}
}