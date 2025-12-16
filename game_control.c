#include <malloc.h>
#include <string.h>
#include "playground.h"
#include "field_fill.h"
#include "game_control.h"

playground* my_playground;
match* temp_match;

playground* get_playground(void) {
	return my_playground;
}

match* get_temp_match(void) {
	return temp_match;
}

// BOTTOM MESSAGE
void set_bottom_message(char* message) {
	strncpy(my_playground->bottom_message, message, (COLUMNS+1) * WIDTH_HOR + 2);
}

void clear_bottom_message(void) {
	*my_playground->bottom_message = '\0';
}

// BASIC GAME FUNCTIONS
void init_game() {
	// ### ALLOCATE
	my_playground = malloc(sizeof(playground));
	temp_match = malloc(sizeof(match));
	
	// init playground
	init_playground(my_playground);
	
	// first random fill of playground
	empty_matrix(my_playground);
	
	// clear bottom_message
	clear_bottom_message();
}

void clear_game(void) {
	clear_playground(my_playground);
	free(my_playground);
	free(temp_match);
}

// CURSOR FUNCTIONS
void activate_cursor1(void) {
	// init pos: 0,0 - if pigeon, then 0,1, then 0,2
	
	if(my_playground->matrix[0][0] == LEFT_PIGEON || my_playground->matrix[0][0] == LEFT_PIGEON) {
		my_playground->cursor1_col = 1;
	}
	if(my_playground->matrix[0][1] == LEFT_PIGEON || my_playground->matrix[0][1] == LEFT_PIGEON) {
		my_playground->cursor1_col = 2;
	}
	
	// make visible
	my_playground->cursor1visible = CURSOR_CHOICE;
}

void lock_cursor1(void) {
	my_playground->cursor1visible = CURSOR_LOCKED;
}

void unlock_cursor1(void) {
	my_playground->cursor1visible = CURSOR_CHOICE;
}

void hide_cursor1(void) {
	my_playground->cursor1visible = CURSOR_CHOICE;
}

void lock_cursor2(void) {
	my_playground->cursor2visible = CURSOR_LOCKED;
}

void show_cursor2(void) {	
	// make cursor 2 visible
	my_playground->cursor2visible = CURSOR_CHOICE;
}

void hide_cursor2(void) {	
	my_playground->cursor2visible = CURSOR_HIDDEN;
}

void activate_cursor2(void) {	
	hide_cursor2();
	my_playground->cursor2_pos = ENTER;
}

void deactivate_cursor(void) {
	hide_cursor1();
	hide_cursor2();
}

void move_cursor(direction dir) {
	// case 1: cursor 1 is active and cursor 2 not visible -> can move freely (only if not at border and no pigeon)
	if(my_playground->cursor1visible == CURSOR_CHOICE) {
		switch(dir) {
			case UP:
				if(my_playground->cursor1_row > 0 && my_playground->matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] != RIGHT_PIGEON) {
					my_playground->cursor1_row -= 1;
				}
				break;
			case DOWN:
				if(my_playground->cursor1_row < (ROWS-1) && my_playground->matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] != RIGHT_PIGEON) {
					my_playground->cursor1_row += 1;
				}
				break;
			case LEFT:
				if(my_playground->cursor1_col > 0 && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] != RIGHT_PIGEON) {
					my_playground->cursor1_col -= 1;
				}
				break;
			case RIGHT:
				if(my_playground->cursor1_col < (COLUMNS-1) && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] != RIGHT_PIGEON) {
					my_playground->cursor1_col += 1;
				}
				break;
		}
	}
	// case 2: cursor 2 is active and cursor 1 locked -> can only move around cursor 1 (only if not at border and no pigeon)
	else if(my_playground->cursor2visible == CURSOR_CHOICE || my_playground->cursor1visible == CURSOR_LOCKED) {
		switch(dir) {
			case UP:
				if(my_playground->cursor2_pos == DOWN) {
					my_playground->cursor2_pos = ENTER;
					hide_cursor2();
				}
				else if(my_playground->cursor1_row > 0 && my_playground->matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] != RIGHT_PIGEON) {
					my_playground->cursor2_pos = UP;
					show_cursor2();
				}
				break;
			case DOWN:
				if(my_playground->cursor2_pos == UP) {
					my_playground->cursor2_pos = ENTER;
					hide_cursor2();
				}
				else if(my_playground->cursor1_row <= (ROWS-1) && my_playground->matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] != RIGHT_PIGEON) {
					my_playground->cursor2_pos = DOWN;
					show_cursor2();
				}
				break;
			case LEFT:
				if(my_playground->cursor2_pos == RIGHT) {
					my_playground->cursor2_pos = ENTER;
					hide_cursor2();
				}
				else if(my_playground->cursor1_col > 0 && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] != RIGHT_PIGEON) {
					my_playground->cursor2_pos = LEFT;
					show_cursor2();
				}
				break;
			case RIGHT:
				if(my_playground->cursor2_pos == LEFT) {
					my_playground->cursor2_pos = ENTER;
					hide_cursor2();
				}
				else if(my_playground->cursor1_col <= (COLUMNS-1) && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] != LEFT_PIGEON && my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] != RIGHT_PIGEON) {
					my_playground->cursor2_pos = RIGHT;
					show_cursor2();
				}
				break;
		}
	}
}

// 0 = still waiting for second cursor, 1 = full match
int enter_cursor(void) {
	// check for pigeons
	if(my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col] == LEFT_PIGEON || my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col] == RIGHT_PIGEON) {
		return 0;
	}
	// case 1: cursor 1 is active, will be locked an cursor 2 will be activated
	else if(my_playground->cursor1visible == CURSOR_CHOICE) {
		lock_cursor1();
		activate_cursor2();
		return 0;
	}
	// case 2: cursor 1 is locked and cursor 2 is hidden, cursor1 will be unlocked
	else if(my_playground->cursor1visible == CURSOR_LOCKED && my_playground->cursor2visible == CURSOR_HIDDEN) {
		unlock_cursor1();
		return 0;
	}
	// case 3: cursor 1 is locked and cursor 2 is active, both will be locked
	else if(my_playground->cursor1visible == CURSOR_LOCKED && my_playground->cursor2visible == CURSOR_CHOICE) {
		lock_cursor2();
		return 1;
	}
}  

void swap_lentils(void) {
	field_color temp = my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col];
	switch(my_playground->cursor2_pos) {
		case UP:
			my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col] = my_playground->matrix[my_playground->cursor1_row-1][my_playground->cursor1_col];
			my_playground->matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] = temp;
			break;
		case DOWN:
			my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col] = my_playground->matrix[my_playground->cursor1_row+1][my_playground->cursor1_col];
			my_playground->matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] = temp;
			break;
		case LEFT:
			my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col] = my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col-1];
			my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] = temp;
			break;
		case RIGHT:
			my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col] = my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col+1];
			my_playground->matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] = temp;
			break;	
	}
}

int update_score(void) {
	if(temp_match->type != 0) {
		int points;
		if(temp_match->type == 1) {
			points = temp_match->end_column_index - temp_match->start_column_index + 1;
		}
		else if(temp_match->type == 2) {
			points = temp_match->end_row_index - temp_match->start_row_index + 1;
		}
		switch(temp_match->color) {
			case DRED:
				my_playground->my_sidebar->score_red += points;
				if(my_playground->my_sidebar->score_red >= my_playground->my_sidebar->goal_red) {
					my_playground->my_sidebar->goal_red = my_playground->my_sidebar->goal_red * 2;
					return 1;
				}
				break;
			case GREEN:
				my_playground->my_sidebar->score_green += points;
				if(my_playground->my_sidebar->score_green >= my_playground->my_sidebar->goal_green) {
					my_playground->my_sidebar->goal_green = my_playground->my_sidebar->goal_green * 2;
					return 1;
				}
				break;
			case YELLOW:
				my_playground->my_sidebar->score_yellow += points;
				if(my_playground->my_sidebar->score_yellow >= my_playground->my_sidebar->goal_yellow) {
					my_playground->my_sidebar->goal_yellow = my_playground->my_sidebar->goal_yellow * 2;
					return 1;
				}
				break;
			case GREY:
				my_playground->my_sidebar->score_grey += points;
				if(my_playground->my_sidebar->score_grey >= my_playground->my_sidebar->goal_grey) {
					my_playground->my_sidebar->goal_grey = my_playground->my_sidebar->goal_grey * 2;
					return 1;
				}
				break;
			case ORANGE:
				my_playground->my_sidebar->score_orange += points;
				if(my_playground->my_sidebar->score_orange >= my_playground->my_sidebar->goal_orange) {
					my_playground->my_sidebar->goal_orange = my_playground->my_sidebar->goal_orange * 2;
					return 1;
				}
				break;
			case BRIGHTRED:
				my_playground->my_sidebar->score_brightred += points;
				if(my_playground->my_sidebar->score_brightred >= my_playground->my_sidebar->goal_brightred) {
					my_playground->my_sidebar->goal_brightred = my_playground->my_sidebar->goal_brightred * 2;
					return 1;
				}
				break;
		}
	}
	return 0;
}

void empty_match(void) {
	if(temp_match->type == 1) {
		for(int j=temp_match->start_column_index; j <= temp_match->end_column_index; j++) {
			my_playground->matrix[temp_match->start_row_index][j] = EMPTY;
		}
	}
	else if(temp_match->type == 2) {
		for(int i=temp_match->start_row_index; i <= temp_match->end_row_index; i++) {
			my_playground->matrix[i][temp_match->start_column_index] = EMPTY;
		}
	}
}

// BLINK FUNCTIONS
void set_blink_cursor(void) {
	my_playground->blink_matrix[my_playground->cursor1_row][my_playground->cursor1_col] = 1;

	switch(my_playground->cursor2_pos) {
		case UP:
			my_playground->blink_matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] = 1;
			break;
		case DOWN:
			my_playground->blink_matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] = 1;
			break;
		case LEFT:
			my_playground->blink_matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] = 1;
			break;
		case RIGHT:
			my_playground->blink_matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] = 1;
			break;	
	}
}

void set_blink_match(void) {
	if(temp_match->type == 1) {
		for(int j=temp_match->start_column_index; j <= temp_match->end_column_index; j++) {
			my_playground->blink_matrix[temp_match->start_row_index][j] = 1;
		}
	}
	else if(temp_match->type == 2) {
		for(int i=temp_match->start_row_index; i <= temp_match->end_row_index; i++) {
			my_playground->blink_matrix[i][temp_match->start_column_index] = 1;
		}
	}
}

void set_blink_all(void) {
	memset(my_playground->blink_matrix, 1, ROWS*COLUMNS);
}

void unset_blink_cursor(void) {
	my_playground->blink_matrix[my_playground->cursor1_row][my_playground->cursor1_col] = 0;
	switch(my_playground->cursor2_pos) {
		case UP:
			my_playground->blink_matrix[my_playground->cursor1_row-1][my_playground->cursor1_col] = 0;
			break;
		case DOWN:
			my_playground->blink_matrix[my_playground->cursor1_row+1][my_playground->cursor1_col] = 0;
			break;
		case LEFT:
			my_playground->blink_matrix[my_playground->cursor1_row][my_playground->cursor1_col-1] = 0;
			break;
		case RIGHT:
			my_playground->blink_matrix[my_playground->cursor1_row][my_playground->cursor1_col+1] = 0;
			break;	
	}
}

void unset_blink_match(void) {
	if(temp_match->type == 1) {
		for(int j=temp_match->start_column_index; j <= temp_match->end_column_index; j++) {
			my_playground->blink_matrix[temp_match->start_row_index][j] = 0;
		}
	}
	else if(temp_match->type == 2) {
		for(int i=temp_match->start_row_index; i <= temp_match->end_row_index; i++) {
			my_playground->blink_matrix[i][temp_match->start_column_index] = 0;
		}
	}
}

void unset_blink_all(void) {
	memset(my_playground->blink_matrix, 0, ROWS*COLUMNS);
}

// PIGEONS
void left_pigeon_fly_on_field(void) {
	if(my_playground->left_pigeon_onfield == 0) {
		int current_index;
		int current_row;
		int current_column;
		do {
			current_index = random_field_index();
			current_row = current_index / COLUMNS;
			current_column = current_index % COLUMNS;
		} while(my_playground->matrix[current_row][current_column] == RIGHT_PIGEON);
		my_playground->matrix[current_row][current_column] = LEFT_PIGEON;
		my_playground->left_pigeon_onfield = 1;
	}
}

void left_pigeon_fly_off_field(void) {
	if(my_playground->left_pigeon_onfield == 1) {
		int i,j;
		for(i=0; i < ROWS; i++) {
			for(j=0; j < COLUMNS; j++) {
				if(my_playground->matrix[i][j] == LEFT_PIGEON) {
					my_playground->matrix[i][j] = EMPTY;
					my_playground->left_pigeon_onfield = 0;
					return;
				}
			}
		}
	}
}

void right_pigeon_fly_on_field(void) {
	if(my_playground->right_pigeon_onfield == 0) {
		int current_index;
		int current_row;
		int current_column;
		do {
			current_index = random_field_index();
			current_row = current_index / COLUMNS;
			current_column = current_index % COLUMNS;
		} while(my_playground->matrix[current_row][current_column] == LEFT_PIGEON);
		my_playground->matrix[current_row][current_column] = RIGHT_PIGEON;
		my_playground->right_pigeon_onfield = 1;
	}
}

void right_pigeon_fly_off_field(void) {
	if(my_playground->right_pigeon_onfield == 1) {
		int i,j;
		for(i=0; i < ROWS; i++) {
			for(j=0; j < COLUMNS; j++) {
				if(my_playground->matrix[i][j] == RIGHT_PIGEON) {
					my_playground->matrix[i][j] = EMPTY;
					my_playground->right_pigeon_onfield = 0;
					return;
				}
			}
		}
	}
}