#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "pixel_art.h"
#include "drawings.h"
#include "playground.h"
#include "text_manipulation.h"

void set_cursor_color(playground* my_playground, char* str, int* str_count, int row, int col) {
	// cursor 1
	if(my_playground->cursor1visible && my_playground->cursor1_row == row && my_playground->cursor1_col == col) {
		set_color(my_playground->cursor1visible, str, str_count);
	}
	// cursor 2
	if(my_playground->cursor2visible) {
		switch(my_playground->cursor2_pos) {
			case UP:
				if (row >= 0 && (my_playground->cursor1_row - 1) == row && my_playground->cursor1_col == col) {
					set_color(my_playground->cursor2visible, str, str_count);
				}
				break;
			case DOWN:
				if (row < ROWS && (my_playground->cursor1_row + 1) == row && my_playground->cursor1_col == col) {
					set_color(my_playground->cursor2visible, str, str_count);
				}
				break;
			case LEFT:
				if (col >= 0 && my_playground->cursor1_row == row && (my_playground->cursor1_col-1) == col) {
					set_color(my_playground->cursor2visible, str, str_count);
				}
				break;
			case RIGHT:
				if (col < COLUMNS && my_playground->cursor1_row == row && (my_playground->cursor1_col+1) == col) {
					set_color(my_playground->cursor2visible, str, str_count);
				}
				break;
		}
	}
}

void init_sidebar(sidebar* my_sidebar) {
	my_sidebar->score_red = 0;
	my_sidebar->score_green = 0;
	my_sidebar->score_orange = 0;
	my_sidebar->score_grey = 0;
	my_sidebar->score_yellow = 0;
	my_sidebar->score_brightred = 0;
	
	my_sidebar->goal_red = DEFAULT_GOAL;
	my_sidebar->goal_green = DEFAULT_GOAL;
	my_sidebar->goal_orange = DEFAULT_GOAL;
	my_sidebar->goal_grey = DEFAULT_GOAL;
	my_sidebar->goal_yellow = DEFAULT_GOAL;
	my_sidebar->goal_brightred = DEFAULT_GOAL;
}

void init_playground(playground* my_playground) {
	my_playground->cursor1visible = CURSOR_HIDDEN;
	my_playground->cursor2visible = CURSOR_HIDDEN;
	my_playground->cursor1_row = 0;
	my_playground->cursor1_col = 0;
	my_playground->cursor2_pos = DOWN;
	memset(my_playground->blink_matrix, 0, ROWS*COLUMNS);
	my_playground->left_pigeon_onfield = 0;
	my_playground->right_pigeon_onfield = 0;
	my_playground->my_sidebar = malloc(sizeof(sidebar));
	init_sidebar(my_playground->my_sidebar);
	my_playground->bottom_message = malloc(((COLUMNS+1) * WIDTH_HOR + 2) * sizeof(char));
}

void clear_playground(playground* my_playground) {
	free(my_playground->my_sidebar);
	free(my_playground->bottom_message);
}

void render_sidebar_block(char* small_lentil, field_color color, int score, int goal, char* str, int* str_count) {
	int i = 0;
	while(small_lentil[i] != '\0') {
		for(int s=0; s < SPACE_SIDEBAR_HOR; s++) {
			add_text(" ", str, str_count);
		}
		set_color(color, str, str_count);
		while(small_lentil[i] != '\n' && small_lentil[i] != '\0') {
			if(small_lentil[i] != ' ') {
				copy_unicode(&small_lentil[i], str, str_count);
				i += 3;
			}
			else {
				add_text(" ", str, str_count);
				i++;
			}
		}
		set_color(CLEAR, str, str_count);
		add_text("\n", str, str_count);
		
		i++;
	}
	char* score_string = malloc(SPACE_SIDEBAR_HOR + 30);
	sprintf(score_string, "       %d / %d", score, goal);
	set_color(color, str, str_count);
	add_text(score_string, str, str_count);
	set_color(CLEAR, str, str_count);
	add_text("\n", str, str_count);
	free(score_string);
}

char* render_sidebar(sidebar* my_sidebar) {

	// render lentil
	char* small_lentil = render_pixel_art(SMALL_LENTIL);
	
	// allocate                      
	char* output_str = malloc(1000);
	int output_str_count = 0;
	
	// TOP SPACE
	for(int s=0; s < SPACE_SIDEBAR_VER; s++) {
		add_text("\n", output_str, &output_str_count);
	}
	
	// RED LENTIL
	render_sidebar_block(small_lentil, DRED, my_sidebar->score_red, my_sidebar->goal_red, output_str, &output_str_count);
	add_text("\n", output_str, &output_str_count);
	// GREEN LENTIL
	render_sidebar_block(small_lentil, GREEN, my_sidebar->score_green, my_sidebar->goal_green, output_str, &output_str_count);
	add_text("\n", output_str, &output_str_count);
	// ORANGE LENTIL
	render_sidebar_block(small_lentil, ORANGE, my_sidebar->score_orange, my_sidebar->goal_orange, output_str, &output_str_count);
	add_text("\n", output_str, &output_str_count);
	// GREY LENTIL
	render_sidebar_block(small_lentil, GREY, my_sidebar->score_grey, my_sidebar->goal_grey, output_str, &output_str_count);
	add_text("\n", output_str, &output_str_count);
	// YELLOW LENTIL
	render_sidebar_block(small_lentil, YELLOW, my_sidebar->score_yellow, my_sidebar->goal_yellow, output_str, &output_str_count);
	add_text("\n", output_str, &output_str_count);
	// BRIGHTRED LENTIL
	render_sidebar_block(small_lentil, BRIGHTRED, my_sidebar->score_brightred, my_sidebar->goal_brightred, output_str, &output_str_count);
	
	free(small_lentil);
	
	return output_str;
}

void attach_sidebar_line(int row, char* str, int* str_count, char* sidebar_str) {
	int index = row_start(sidebar_str, row);
	if (index == -1) {
		return;
	}
	while(sidebar_str[index] != '\n' && sidebar_str[index] != '\0') {
		add_char(sidebar_str[index], str, str_count);
		index++;
	}
}

char* render_playground(playground* my_playground) {

	int total_row_count = 0;

	// render lentil
	char* lentil = render_pixel_art(LENTIL);
	
	// render pigeons
	char* left_pigeon_str = render_pixel_art(left_pigeon);
	char* right_pigeon_str = render_pixel_art(right_pigeon);
	
	// render sidebar
	char* sidebar_str = render_sidebar(my_playground->my_sidebar);
	
	// allocate
	// (vertical= table content + top line & middle lines + bottom line + message + empty line + keys)
	int vertical = ROWS*WIDTH_VER*3 + ROWS + 1 + 1 + 1 + 3;
	char* output_str = malloc(vertical * (ROW_SIZE + 10));
	int output_str_count = 0;
	
	// TOP SPACE
	for(int s=0; s < SPACE_VER; s++) {
		add_linebreak(output_str, &output_str_count);
	}
	
	// BUILD PLAYGROUND - ATTACH SIDEBAR LINE BEFORE EACH NEWLINE
	
	// TOP BORDER
	// leading space
	for(int s=0; s < SPACE_HOR; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text(CORNER_TOP_LEFT, output_str, &output_str_count);
	for(int j=0; j < COLUMNS; j++) {
		for(int q=0; q < WIDTH_HOR; q++) {
			add_text(HORIZONTAL_LINE, output_str, &output_str_count);
		}
		if(j < COLUMNS-1) {
			add_text(TOP_T, output_str, &output_str_count);
		}
	}
	add_text(CORNER_TOP_RIGHT, output_str, &output_str_count);
	attach_sidebar_line(total_row_count, output_str, &output_str_count, sidebar_str);
	total_row_count++;
	add_linebreak(output_str, &output_str_count);

	// CELLS
	// i = matrix row index, j = matrix column index
	// p = relative row index inside a cell, q = relative column index inside a cell
	int index;
	for(int i=0; i < ROWS; i++) {		
		for(int p=0; p < WIDTH_VER; p++) {
			// leading space
			for(int s=0; s < SPACE_HOR; s++) {
				add_text(" ", output_str, &output_str_count);
			}
			for(int j=0; j < COLUMNS; j++) {
				add_text(VERTICAL_LINE, output_str, &output_str_count);
				
				// set cell color
				set_color(my_playground->matrix[i][j], output_str, &output_str_count);
				// set cursor
				set_cursor_color(my_playground, output_str, &output_str_count, i, j);
				// blinking?
				if(my_playground->blink_matrix[i][j] == 1) {
					set_color(BLINK, output_str, &output_str_count);
				}
				
				for(int q=0; q < WIDTH_HOR; q++) {
					// ACTUAL CELL CONTENT
				
					// EMPTY CELL?
					if(my_playground->matrix[i][j] == EMPTY) {
						add_text(" ", output_str, &output_str_count);
						continue;
					}
					
					// PIGEON?
					if(my_playground->matrix[i][j] == LEFT_PIGEON) {
						index = actual_index(left_pigeon_str, q, p);
						if(index != -1 && left_pigeon_str[index] != ' ' && left_pigeon_str[index] != '\n' && left_pigeon_str[index] != '\0') {
						copy_unicode(&left_pigeon_str[index], output_str, &output_str_count);
					}
						else {
							add_text(" ", output_str, &output_str_count);
						}
					}
					else if(my_playground->matrix[i][j] == RIGHT_PIGEON) {
						index = actual_index(right_pigeon_str, q, p);
						if(index != -1 && right_pigeon_str[index] != ' ' && right_pigeon_str[index] != '\n' && right_pigeon_str[index] != '\0') {
						copy_unicode(&right_pigeon_str[index], output_str, &output_str_count);
					}
						else {
							add_text(" ", output_str, &output_str_count);
						}
					}
					else {
						index = actual_index(lentil, q, p);
						if(index != -1 && lentil[index] != ' ' && lentil[index] != '\n' && lentil[index] != '\0') {
							copy_unicode(&lentil[index], output_str, &output_str_count);
						}
						else {
							add_text(" ", output_str, &output_str_count);
						}
					}
				}
				
				// reset color
				set_color(CLEAR, output_str, &output_str_count);
			}
			add_text(VERTICAL_LINE, output_str, &output_str_count);
			attach_sidebar_line(total_row_count, output_str, &output_str_count, sidebar_str);
			total_row_count++;
			add_linebreak(output_str, &output_str_count);
		}
		if(i < ROWS-1) {
			// middle borders
			// leading space
			for(int s=0; s < SPACE_HOR; s++) {
				add_text(" ", output_str, &output_str_count);
			}
			add_text(LEFT_T, output_str, &output_str_count);
			for(int j=0; j < COLUMNS; j++) {
				for(int q=0; q < WIDTH_HOR; q++) {
					add_text(HORIZONTAL_LINE, output_str, &output_str_count);
				}
				if(j < COLUMNS-1) {
					add_text(MIDDLE_CROSS, output_str, &output_str_count);
				}
			}
			add_text(RIGHT_T, output_str, &output_str_count);
			attach_sidebar_line(total_row_count, output_str, &output_str_count, sidebar_str);
			total_row_count++;
			add_linebreak(output_str, &output_str_count);
		}
	}
	// BOTTOM BORDER
	// leading space
	for(int s=0; s < SPACE_HOR; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text(CORNER_BOTTOM_LEFT, output_str, &output_str_count);
	for(int j=0; j < COLUMNS; j++) {
		for(int q=0; q < WIDTH_HOR; q++) {
			add_text(HORIZONTAL_LINE, output_str, &output_str_count);
		}
		if(j < COLUMNS-1) {
			add_text(BOTTOM_T, output_str, &output_str_count);
		}
	}
	add_text(CORNER_BOTTOM_RIGHT, output_str, &output_str_count);
	attach_sidebar_line(total_row_count, output_str, &output_str_count, sidebar_str);
	total_row_count++;
	add_linebreak(output_str, &output_str_count);
	
	// bottom message
	for(int s=0; s < SPACE_HOR; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text(my_playground->bottom_message, output_str, &output_str_count);
	add_linebreak(output_str, &output_str_count);
	add_linebreak(output_str, &output_str_count);
	
	// BOTTOM KEYS INFO
	for(int s=0; s < SPACE_HOR; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text("       ", output_str, &output_str_count);
	set_color(KEY, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	add_text(ARROW_UP, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	set_color(CLEAR, output_str, &output_str_count);
	add_linebreak(output_str, &output_str_count);
	
	for(int s=0; s < SPACE_HOR; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text("    ", output_str, &output_str_count);
	set_color(KEY, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	add_text(ARROW_LEFT, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	set_color(CLEAR, output_str, &output_str_count);
	add_text("   ", output_str, &output_str_count);
	set_color(KEY, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	add_text(ARROW_RIGHT, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	set_color(CLEAR, output_str, &output_str_count);
	add_text(" bewegen     ", output_str, &output_str_count);
	set_color(KEY, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	add_text(ARROW_ENTER, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	set_color(CLEAR, output_str, &output_str_count);
	add_text(" Feld auswählen     ", output_str, &output_str_count);
	set_color(KEY, output_str, &output_str_count);
	add_text(" ESC ", output_str, &output_str_count);
	set_color(CLEAR, output_str, &output_str_count);
	add_text(" Spiel beenden", output_str, &output_str_count);
	add_linebreak(output_str, &output_str_count);
	
	for(int s=0; s < SPACE_HOR; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text("       ", output_str, &output_str_count);
	set_color(KEY, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	add_text(ARROW_DOWN, output_str, &output_str_count);
	add_text(" ", output_str, &output_str_count);
	set_color(CLEAR, output_str, &output_str_count);

	free(left_pigeon_str);
	free(right_pigeon_str);

	free(lentil);
	free(sidebar_str);
	
	return output_str;
}
