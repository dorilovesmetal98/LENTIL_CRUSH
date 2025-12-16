#include <string.h>
#include "playground.h"
#include "colors.h"

void add_text(char* symbol, char* str, int* str_count) {

	strcpy(&str[*str_count], symbol);
	*str_count = *str_count + strlen(symbol);
}

void add_char(char symbol, char* str, int* str_count) {
	strncpy(&str[*str_count], &symbol, 1);
	*str_count = *str_count + 1;
}

void copy_unicode(char* symbol, char* str, int* str_count) {
	strncpy(&str[*str_count], symbol, 3);
	*str_count = *str_count + 3;
}

void set_color(field_color value, char* str, int* str_count) {
	switch (value) {
		case EMPTY:
			return;
		case DRED:
			add_text(RED, str, str_count);
			break;
		case GREEN:
			add_text(GRN, str, str_count);
			break;
		case YELLOW:
			add_text(YEL, str, str_count);
			break;
		case GREY:
			add_text(GRY, str, str_count);
			break;
		case ORANGE:
			add_text(ORA, str, str_count);
			break;
		case BRIGHTRED:
			add_text(BRD, str, str_count);
			break;
		case CURSOR_CHOICE:
			add_text(WHT_BG, str, str_count);
			break;
		case CURSOR_LOCKED:
			add_text(CYN_BG, str, str_count);
			break;
		case KEY:
			add_text(GRY_BG, str, str_count);
			break;
		case MAGENTA:
			add_text(MAG, str, str_count);
			break;
		case CYAN:
			add_text(CYN, str, str_count);
			break;
		case BLINK:
			add_text(BLINKY, str, str_count);
			break;
		case CLEAR:
			add_text(RESET, str, str_count);
			break;
	}
}

// get start index of a given row number
int row_start(char* str, int row) {
	// find row start index
	int row_start = -1;
	if(row != 0) {
		int row_count = 0;
		int i = 0;
		while (str[i] != '\0') {
			if(str[i] == '\n') {
				row_count++;
				if(row_count == row) {
					row_start= i+1;
					break;
				}
			}
			i++;
		}
		if(row_start == -1) {
			return -1;
		}
	}
	else {
		row_start = 0;
	}
	if(str[row_start] == '\0') {
		return -1;
	}	
	
	return row_start;
}

// input: index of text, output: actual char index (unicode text is 3 chars)
// stops at end of line (to not produce an overflow at playground render)
int actual_index(char* str, int index, int row) {
	
	int actual_index = row_start(str, row);
	
	for(int i=0; i < index; i++) {
		if(str[actual_index] == '\0' || str[actual_index] == '\n') {
			return -1;
		}
		if(str[actual_index] == ' ') {
			actual_index++;
		}
		else {
			actual_index += 3;
		}
	}
	
	return actual_index;
}