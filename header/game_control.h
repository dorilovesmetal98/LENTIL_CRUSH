#ifndef _GAME_CONTROL_H_
#define _GAME_CONTROL_H_

#include "playground.h"

typedef struct match {
    int start_row_index;
    int end_row_index;
	int start_column_index;
    int end_column_index;
    // 1 = row, 2 = column
    char type;
    int color;
 } match;

playground* get_playground(void);
match* get_temp_match(void);

// BOTTOM MESSAGE
void set_bottom_message(char* message);
void clear_bottom_message(void);

// BASIC GAME FUNCTIONS
void init_game();
void clear_game(void);

// CURSOR FUNCTIONS
void activate_cursor1(void);
void activate_cursor2(void);
void deactivate_cursor(void);
void move_cursor(int dir);
int enter_cursor(void);
void swap_lentils(void);
int update_score(void);
void empty_match(void);

// blink
void set_blink_cursor(void);
void set_blink_all(void);
void set_blink_match(void);
void unset_blink_cursor(void);
void unset_blink_match(void);
void unset_blink_all(void);

// PIGEONS
void left_pigeon_fly_on_field(void);
void left_pigeon_fly_off_field(void);
void right_pigeon_fly_on_field(void);
void right_pigeon_fly_off_field(void);

#endif
