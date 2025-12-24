#ifndef _CHECK_LOGIC_H_
#define _CHECK_LOGIC_H__

#include "game_control.h"

int random_bool_percent(unsigned int percentage);
int check_neighbors(playground* my_playground, int test_value, int row, int col);
int detect_match(match* temp_match, playground* my_playground);
int detect_first_empty(playground* my_playground);
int detect_last_empty(playground* my_playground);
int left_pigeon_onfield(playground* my_playground);
int right_pigeon_onfield(playground* my_playground);

#endif