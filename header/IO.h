#ifndef _IO_H_
#define _IO_H_

void clear_screen(void);
void init_screen(void);
void plot_startscreen(playground* my_playground, char* message);
void plot_game(playground* my_playground);
char keyboard_input(void);

#endif