#include <stdlib.h>
#include <stdio.h>
#include "playground.h"
#include "game_control.h"

int random_bool_percent(unsigned int percentage) {
	if(percentage > 100) {
		return 1;
	}
	
	unsigned int random_number = (rand() % 100);
	
	if(random_number < percentage) {
		return 1;
	}
	else {
		return 0;
	}
}

// checks if a test field value (of field (row,col)) is distinct to all neighbors
int check_neighbors(playground* my_playground, int test_value, int row, int col) {
	if(row < 0 || row >= ROWS || col < 0 || col >= COLUMNS) {
		return -1;
	}

	if(row > 0 && my_playground->matrix[row-1][col] == test_value) {
		return 0;
	}
	if(row < (ROWS-1) && my_playground->matrix[row+1][col] == test_value) {
		return 0;
	}
	if(col > 0 && my_playground->matrix[row][col-1] == test_value) {
		return 0;
	}
	if(col < (COLUMNS-1) && my_playground->matrix[row][col+1] == test_value) {
		return 0;
	}
	
	return 1;
}

// if cursor movable

int compare_row(playground* my_playground, int row, int col, int equal) {
	if(COLUMNS-col < equal) {
		return 0;
	}

	int matching = 1;
	for(int j=col+1; j < COLUMNS; j++) {
		if(my_playground->matrix[row][col] == my_playground->matrix[row][j]) {
			matching++;
		}
		else {
			break;
		}
	}
	if(matching < equal) {
		return 0;
	}
	return matching;
}

int compare_column(playground* my_playground, int row, int col, int equal) {
	if(ROWS-row < equal) {
		return 0;
	}

	int matching = 1;
	for(int i=row+1; i < ROWS; i++) {
		if(my_playground->matrix[row][col] == my_playground->matrix[i][col]) {
			matching++;
		}
		else {
			break;
		}
	}
	if(matching < equal) {
		return 0;
	}
	return matching;
}

int detect_match(match* temp_match, playground* my_playground) {
	int found_match = 0; // 0 = no match, 1 = Row match, 2 = Column Match
	int match_count = 0;
	int i,j;
	
	for(i=0; i < ROWS && found_match == 0; i++) {
		for(j=0; j < COLUMNS && found_match == 0; j++) {
			match_count = compare_row(my_playground,i,j,3);
			if(match_count) {
				found_match = 1;
			}
			else {
				match_count = compare_column(my_playground,i,j,3);
				if(match_count) {
					found_match = 2;
				}
			}
		}
	}
	
	i--;
	j--;
	
	if(found_match != 0) {
		temp_match->start_row_index = i;
		temp_match->start_column_index = j;
		temp_match->color=my_playground->matrix[i][j];
	}
	else {
		temp_match->type = 0;
		return found_match;
	}
	
	if(found_match == 1) {
		temp_match->type=1;
		temp_match->end_column_index = j + match_count - 1;
	}
	else if(found_match == 2) {
		temp_match->type=2;
		temp_match->end_row_index = i + match_count - 1;
	}
	
	return found_match;
}

int detect_first_empty(playground* my_playground) {
	int first_empty = -1;
	for(int i=0; i < ROWS && first_empty==-1; i++) {
		for(int j=0; j < COLUMNS && first_empty==-1; j++) {
			if(my_playground->matrix[i][j] == EMPTY) {
				first_empty = i*COLUMNS + j;
			}
		}
	}
	return first_empty;
}

int detect_last_empty(playground* my_playground) {
	int last_empty = -1;
	for(int i=ROWS-1; i >=0 && last_empty==-1; i--) {
		for(int j=COLUMNS-1; j >= 0 && last_empty==-1; j--) {
			if(my_playground->matrix[i][j] == EMPTY) {
				last_empty = i*COLUMNS + j;
			}
		}
	}
	return last_empty;
}

int left_pigeon_onfield(playground* my_playground) {
	return my_playground->left_pigeon_onfield;
}

int right_pigeon_onfield(playground* my_playground) {
	return my_playground->right_pigeon_onfield;
}