#include <malloc.h>
#include <string.h>
#include "playground.h"
#include "text_manipulation.h"
#include "drawings.h"


char* prepare_scetch(char* input_str) {
	// count max line len and number of lines
	int max_line_len = 0;
	int line_len = 1;
	int lines = 0;
	int i = 0;
	while (input_str[i] != '\0') {
		line_len++;
		if(input_str[i] == '\n') {
			lines++;
			if(line_len > max_line_len) {
				max_line_len = line_len;
			}
			line_len = 0;
		}
		i++;
	}
	
	// calculate new array size and allocate
	// all lines have to have the same length and even length
	if(max_line_len % 2 == 0) {
		max_line_len++;
	}
	char* prepared_str = malloc(lines * (max_line_len+1) + 4);
	memset(prepared_str, 0, lines * (max_line_len + 1) + 4);
	
	// copy to new array
	int input_str_count = 0;
	int output_str_count = 0;
	int eol = 0;
	for(i = 0; i < lines; i++) {
		for(int j = 0; j < max_line_len-1; j++) {
			
			if(input_str[input_str_count] == '\n') {
				eol = 1;
			}
			if(eol == 1) {
				prepared_str[output_str_count] = ' ';
			}
			else {
				prepared_str[output_str_count] = input_str[input_str_count];
				input_str_count++;
			}
			output_str_count++;
		}
		eol = 0;
		prepared_str[output_str_count] = '\n';
		input_str_count++;
		output_str_count++;
	}
	
	return prepared_str;
	
}

char* render_pixel_art(char* input_str) {
	
	char* render_str = prepare_scetch(input_str);

	// count lines
	int lines = 0;
	int i = 0;
	while (render_str[i] != '\0') {
		if(render_str[i] == '\n') {
			lines++;
		}
		i++;
	}
	
	// find len of a line (has to be equal for all lines)
	int line_len = 0;
	do {
		line_len++;
	} while(render_str[line_len] != '\n');
	
	// allocate output string
	// (4 old chars are 1 new text) , text can be 3 chars
	char* output_str = malloc((lines * line_len /4 * 3) + lines);
	memset(output_str, 0, (lines * line_len / 4 * 3) + lines);
	int output_str_count = 0;
	
	int line1count = 0;
	int line2count = line_len + 1;
	for (int i = 0; i < (lines/2); i++) {
		// get two lines each loop
		while (render_str[line1count] != '\n') {
			// full block
			if (render_str[line1count] == 'x' && render_str[line1count+1] == 'x' && render_str[line2count] == 'x' && render_str[line2count+1] == 'x') {
				copy_unicode(FULL_BLOCK, output_str, &output_str_count);
			}
			// upper half
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == 'x' && render_str[line2count] == ' ' && render_str[line2count+1] == ' ') {
				copy_unicode(UPPER_HALF, output_str, &output_str_count);
			}
			// lower half
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == ' ' && render_str[line2count] == 'x' && render_str[line2count+1] == 'x') {
				copy_unicode(LOWER_HALF, output_str, &output_str_count);
			}
			// left half
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == ' ' && render_str[line2count] == 'x' && render_str[line2count+1] == ' ') {
				copy_unicode(LEFT_HALF, output_str, &output_str_count);
			}
			// right half
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == 'x' && render_str[line2count] == ' ' && render_str[line2count+1] == 'x') {
				copy_unicode(RIGHT_HALF, output_str, &output_str_count);
			}
			// 1/4 lower left
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == ' ' && render_str[line2count] == 'x' && render_str[line2count+1] == ' ') {
				copy_unicode(LOWER_LEFT, output_str, &output_str_count);
			}
			// 1/4 lower right
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == ' ' && render_str[line2count] == ' ' && render_str[line2count+1] == 'x') {
				copy_unicode(LOWER_RIGHT, output_str, &output_str_count);
			}
			// 1/4 upper left
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == ' ' && render_str[line2count] == ' ' && render_str[line2count+1] == ' ') {
				copy_unicode(UPPER_LEFT, output_str, &output_str_count);
			}
			// 1/4 upper right
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == 'x' && render_str[line2count] == ' ' && render_str[line2count+1] == ' ') {
				copy_unicode(UPPER_RIGHT, output_str, &output_str_count);
			}
			// 3/4 not upper right
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == ' ' && render_str[line2count] == 'x' && render_str[line2count+1] == 'x') {
				copy_unicode(NOT_UPPER_RIGHT, output_str, &output_str_count);
			}
			// 3/4 not lower right
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == 'x' && render_str[line2count] == 'x' && render_str[line2count+1] == ' ') {
				copy_unicode(NOT_LOWER_RIGHT, output_str, &output_str_count);
			}
			// 3/4 not lower left
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == 'x' && render_str[line2count] == ' ' && render_str[line2count+1] == 'x') {
				copy_unicode(NOT_LOWER_LEFT, output_str, &output_str_count);
			}
			// 3/4 not upper left
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == 'x' && render_str[line2count] == 'x' && render_str[line2count+1] == 'x') {
				copy_unicode(NOT_UPPER_LEFT, output_str, &output_str_count);
			}
			// cross 1
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == ' ' && render_str[line2count] == ' ' && render_str[line2count+1] == 'x') {
				copy_unicode(CROSS1, output_str, &output_str_count);
			}
			// cross 2
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == 'x' && render_str[line2count] == 'x' && render_str[line2count+1] == ' ') {
				copy_unicode(CROSS2, output_str, &output_str_count);
			}
			// color change char
			else if (render_str[line1count] == '|' || render_str[line1count+1] == '|' || render_str[line2count] == '|' || render_str[line2count+1] == '|') {
				add_text("|", output_str, &output_str_count);
			}
			// empty
			else {
				add_text(" ", output_str, &output_str_count);
			}
			// increment
			line1count += 2;
			line2count += 2;
		}
		add_text("\n", output_str, &output_str_count);
		line1count = line2count + 1;
		line2count = line2count + line_len + 2;
	}
	// last line if odd number of lines
	if (lines % 2 == 1) {
		while (render_str[line1count] != '\n') {
			// upper half
			if (render_str[line1count] == 'x' && render_str[line1count+1] == 'x') {
				copy_unicode(UPPER_HALF, output_str, &output_str_count);
			}
			// 1/4 upper left
			else if (render_str[line1count] == 'x' && render_str[line1count+1] == ' ') {
				copy_unicode(UPPER_LEFT, output_str, &output_str_count);
			}
			// 1/4 upper right
			else if (render_str[line1count] == ' ' && render_str[line1count+1] == 'x') {
				copy_unicode(UPPER_RIGHT, output_str, &output_str_count);
			}
			// color change char
			else if (render_str[line1count] == '|' || render_str[line1count+1] == '|') {
				add_text("|", output_str, &output_str_count);
			}
			// empty
			else {
				add_text(" ", output_str, &output_str_count);
			}
			// increment
			line1count += 2;
		}
		add_text("\n", output_str, &output_str_count);
	}
	add_text("\0", output_str, &output_str_count);

	free(render_str);
	
	return output_str;
}

char* color_header(char* header_str, field_color* colors) {
	int color_counter = 0;
	
	char* output_str = malloc(strlen(header_str)*3);
	int output_str_count = 0;
	
	set_color(colors[color_counter], output_str, &output_str_count);
	int i = 0;
	while(header_str[i] != '\0') {
		if(header_str[i] == '\n') {
			color_counter = 0;
			set_color(CLEAR, output_str, &output_str_count);
			add_char('\n', output_str, &output_str_count);
			if(header_str[i+1] != '\0') {
				set_color(colors[color_counter], output_str, &output_str_count);
			}
			i++;
		}
		else if(header_str[i] == '|') {
			color_counter++;
			set_color(colors[color_counter], output_str, &output_str_count);
			i++;
		}
		else if(header_str[i] == ' ') {
			add_char(' ', output_str, &output_str_count);
			i++;
		}
		else {
			copy_unicode(&header_str[i], output_str, &output_str_count);
			i += 3;
		}
		
	}
	
	add_char('\0', output_str, &output_str_count);
	
	return output_str;
}

char* full_header(char* color_header_str, playground* my_playground) {
	char* left_pigeon_str = render_pixel_art(left_pigeon);
	char* right_pigeon_str = render_pixel_art(right_pigeon);
	
	char* output_str = malloc(2*(strlen(left_pigeon_str)+strlen(right_pigeon_str)+strlen(color_header_str)));
	int output_str_count = 0;
	
	int index = 0;
	int row = 0;
	while(1) {
		index = row_start(left_pigeon_str, row);
		// left pigeon or space
		if(my_playground->left_pigeon_onfield == 0 && index != -1) {
			while(left_pigeon_str[index] != '\n' && left_pigeon_str[index] != '\0') {
				add_char(left_pigeon_str[index], output_str, &output_str_count);
				index++;
			}
		}
		else {
			for(int j=0; j < left_pigeon_width; j++) {
				add_char(' ', output_str, &output_str_count);
			}
		}
		// font
		index = row_start(color_header_str, row);
		if(index == -1) {
			for(int j=0; j < header_width; j++) {
				add_char(' ', output_str, &output_str_count);
			}
		}
		else {
			while(color_header_str[index] != '\n' && color_header_str[index] != '\0') {
				add_char(color_header_str[index], output_str, &output_str_count);
				index++;
			}
		}
		index = row_start(right_pigeon_str, row);
		// right pigeon or space
		if(my_playground->right_pigeon_onfield == 0) {
			while(right_pigeon_str[index] != '\n' && right_pigeon_str[index] != '\0') {
				add_char(right_pigeon_str[index], output_str, &output_str_count);
				index++;
			}
		}
		else {
			while(right_pigeon_str[index] != '\n' && right_pigeon_str[index] != '\0') {
				add_char(' ', output_str, &output_str_count);
				index++;
			}
		}
		
		if(right_pigeon_str[index+1] == '\0') {
			break;
		}
		
		add_char('\n', output_str, &output_str_count);
		row++;
	}
	add_char('\0', output_str, &output_str_count);
	
	free(left_pigeon_str);
	free(right_pigeon_str);
	
	return output_str;
}
		