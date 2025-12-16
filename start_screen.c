#include <malloc.h>
#include <string.h>
#include "playground.h"
#include "start_screen.h"
#include "text_manipulation.h"
#include "drawings.h"

char* render_startscreen(char* message) {
	int key_color = 0;
	
	// allocate                      
	char* output_str = malloc((WIDTH_STARTSCREEN_HOR+SPACE)*WIDTH_STARTSCREEN_VER + 800);
	int output_str_count = 0;

	add_text("\n\n", output_str, &output_str_count);
	
	// top border
	for(int s=0; s < SPACE; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text(CORNER_TOP_LEFT, output_str, &output_str_count);
	for(int j=0; j < WIDTH_STARTSCREEN_HOR; j++) {
		add_text(HORIZONTAL_LINE, output_str, &output_str_count);
	}
	add_text(CORNER_TOP_RIGHT, output_str, &output_str_count);
	add_text("\n", output_str, &output_str_count);
	
	int text_count = 0;
	int text_row_index;
	// body
	for(int i=0; i < WIDTH_STARTSCREEN_VER; i++) {
		for(int s=0; s < SPACE; s++) {
			add_text(" ", output_str, &output_str_count);
		}
		add_text(VERTICAL_LINE, output_str, &output_str_count);
		for(int j=0; j < TEXT_SPACE; j++) {
			add_text(" ", output_str, &output_str_count);
		}
		
		text_row_index = 0;
		while(i > 0 && message[text_count] != '\n' && message[text_count] != '\0' && text_row_index < WIDTH_STARTSCREEN_HOR-2*TEXT_SPACE) {
			if(message[text_count] == '|') {
				if(key_color == 0) {
					set_color(KEY, output_str, &output_str_count);
					key_color = 1;
				}
				else {
					set_color(CLEAR, output_str, &output_str_count);
					key_color = 0;
				}
			}
			else {
				add_char(message[text_count], output_str, &output_str_count);
				if(!(!strncmp(&message[text_count], "ä", 2) || !strncmp(&message[text_count], "Ä", 2) || !strncmp(&message[text_count], "ö", 2) || !strncmp(&message[text_count], "Ö", 2) || !strncmp(&message[text_count], "ü", 2) || !strncmp(&message[text_count], "Ü", 2) || !strncmp(&message[text_count], "ß", 2))) {
					text_row_index++;
				}
			}
			text_count++;
		}
		
		if(key_color == 1) {
			set_color(CLEAR, output_str, &output_str_count);
			key_color = 0;
		}
		
		if(message[text_count] == '\n') {
			text_count++;
		}
		
		while(text_row_index < WIDTH_STARTSCREEN_HOR-2*TEXT_SPACE) {
			add_text(" ", output_str, &output_str_count);
			text_row_index++;
		}
		
		for(int j=0; j < TEXT_SPACE; j++) {
			add_text(" ", output_str, &output_str_count);
		}
		
		add_text(VERTICAL_LINE, output_str, &output_str_count);
		add_text("\n", output_str, &output_str_count);
	}
	// bottom border
	for(int s=0; s < SPACE; s++) {
		add_text(" ", output_str, &output_str_count);
	}
	add_text(CORNER_BOTTOM_LEFT, output_str, &output_str_count);
	for(int j=0; j < WIDTH_STARTSCREEN_HOR; j++) {
		add_text(HORIZONTAL_LINE, output_str, &output_str_count);
	}
	add_text(CORNER_BOTTOM_RIGHT, output_str, &output_str_count);
	
	add_text("\n", output_str, &output_str_count);
	
	return output_str;
}