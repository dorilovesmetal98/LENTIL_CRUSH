#ifndef _TEXT_MANIPULATION_H_
#define _TEXT_MANIPULATION_H__

// arrows
#define ARROW_LEFT			"\xE2\x86\x90"
#define ARROW_RIGHT			"\xE2\x86\x92"
#define ARROW_UP			"\xE2\x86\x91"
#define ARROW_DOWN			"\xE2\x86\x93"
#define ARROW_ENTER			"\xE2\x86\xB5"

// unicode blocks
#define FULL_BLOCK       	"\xE2\x96\x88"
#define UPPER_HALF       	"\xE2\x96\x80"
#define LOWER_HALF       	"\xE2\x96\x84"
#define LEFT_HALF        	"\xE2\x96\x8C"
#define RIGHT_HALF       	"\xE2\x96\x90"
#define LOWER_LEFT       	"\xE2\x96\x96"
#define LOWER_RIGHT      	"\xE2\x96\x97"
#define UPPER_LEFT       	"\xE2\x96\x98"
#define UPPER_RIGHT      	"\xE2\x96\x9D"
#define NOT_UPPER_RIGHT  	"\xE2\x96\x99"
#define NOT_LOWER_RIGHT  	"\xE2\x96\x9B"
#define NOT_LOWER_LEFT   	"\xE2\x96\x9C"
#define NOT_UPPER_LEFT   	"\xE2\x96\x9F"
#define CROSS1			 	"\xE2\x96\x9A"
#define CROSS2			 	"\xE2\x96\x9E"

// unicode boxes
#define CORNER_TOP_LEFT	 	"\xE2\x94\x8F"
#define CORNER_TOP_RIGHT 	"\xE2\x94\x93"
#define CORNER_BOTTOM_LEFT	"\xE2\x94\x97"
#define CORNER_BOTTOM_RIGHT	"\xE2\x94\x9B"

#define HORIZONTAL_LINE	 	"\xE2\x94\x81"
#define VERTICAL_LINE	 	"\xE2\x94\x83"

#define TOP_T	 		 	"\xE2\x94\xB3"
#define BOTTOM_T	 		"\xE2\x94\xBB"
#define LEFT_T	 		 	"\xE2\x94\xA3"
#define RIGHT_T	 		 	"\xE2\x94\xAB"

#define MIDDLE_CROSS		"\xE2\x95\x8B"

void add_text(char* symbol, char* str, int* str_count);
void add_char(char symbol, char* str, int* str_count);
void add_linebreak(char* str, int* str_count);
void copy_unicode(char* symbol, char* str, int* str_count);
void set_color(int value, char* str, int* str_count);
int row_start(char* str, int row);
int actual_index(char* str, int index, int row);

#endif