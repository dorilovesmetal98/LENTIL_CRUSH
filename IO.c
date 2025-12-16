#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "drawings.h"
#include "pixel_art.h"
#include "playground.h"
#include "start_screen.h"

void plot_startscreen(playground* my_playground, char* message) {
	// ### RENDERING ###
	// render header text
	char* header_str = render_pixel_art(header);
	// color_header text
	char* color_header_str = color_header(header_str, header_colors);
	// add pigeons to header
	char* full_header_str = full_header(color_header_str, my_playground);
	// render start screen
	char* startscreen_str = render_startscreen(message);
	
	// ### PRINT ###
	// clear terminal
	system("clear");
	// top newline
	printf("\n");
	// header
	printf(full_header_str);
	// start screen
	printf(startscreen_str);
	// bottom newline
	printf("\n");
	
	// ### FREE ###
	free(header_str);
	free(color_header_str);
	free(full_header_str);
	free(startscreen_str);
}

void plot_game(playground* my_playground) {
	
	// ### RENDERING ###
	// render header text
	char* header_str = render_pixel_art(header);
	// color_header text
	char* color_header_str = color_header(header_str, header_colors);
	// add pigeons to header
	char* full_header_str = full_header(color_header_str, my_playground);
	// render playground
	char* playground_str = render_playground(my_playground);
	
	// ### PRINT ###
	// clear terminal
	system("clear");
	// top newline
	printf("\n");
	// header
	printf(full_header_str);
	// playground
	printf(playground_str);
	// bottom newline
	printf("\n");
	
	// ### FREE ###
	free(header_str);
	free(color_header_str);
	free(full_header_str);
	free(playground_str);
}

static struct termios new_io;
static struct termios old_io;
static int raw () {
  if ((tcgetattr(STDIN_FILENO, &old_io)) == -1)
    return -1;
  new_io = old_io;
  new_io.c_iflag = new_io.c_iflag & ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  new_io.c_oflag = new_io.c_iflag & ~(OPOST);
  new_io.c_cflag = new_io.c_cflag & ~(CSIZE | PARENB);
  new_io.c_lflag = new_io.c_lflag & ~(ECHO|ICANON|IEXTEN|ISIG);
  new_io.c_cflag = new_io.c_cflag | CS8;
  new_io.c_cc[VMIN]  = 1;
  new_io.c_cc[VTIME] = 0;
  if ((tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_io)) == -1)
    return -1;
  return 0;
}

void reset() {
  tcsetattr (STDIN_FILENO, TCSANOW, &old_io);
}



char keyboard_input(void) {
	char keys[3];
	memset(keys, 0, 3);
	char input;
	
	raw();
	
	read(0, &keys, 3); 

	if(keys[0] == 13) {
		input = ENTER;
	}
	else if(keys[0] == 'x') {
		input = SNEAK_ESC;
	}
	else if(keys[0] == 'y' || keys[0] == 'Y') {
		input = 'y';
	}
	else if(keys[0] == 'n' || keys[0] == 'N') {
		input = 'n';
	}
	else if(keys[0] == 27) {
		if(keys[1] == 0) {
			input = ESC;
		}
		else {
			switch(keys[2]) {
				case 65:	// up
					input = UP;
					break;
				case 67:	// right
					input = RIGHT;
					break;
				case 68:	// left
					input = LEFT;
					break;
				case 66:	// down
					input = DOWN;
					break;
			}
		}
	}
	else {
		input = 0;
	}
	
	fflush(stdin);
	reset();
	
	return input;
}