#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "animation.h"
#include "check_logic.h"
#include "field_fill.h"
#include "game_control.h"
#include "IO.h"
#include "playground.h"
#include "start_screen.h"

#ifdef _WIN32
#include <Windows.h>
#endif

float slow_down_factor = 1.0;

void fsleep(float sec) {
	#ifdef _WIN32
	// Sleep on Windows takes Milliseconds
	Sleep(sec * 1e3);
	#else
	struct timespec req;
	struct timespec rem;

	time_t sec_int = (time_t) sec;
	long nanosec = (long) (sec*1e9) - (sec_int*1e9);

	req.tv_sec = sec_int;
	req.tv_nsec = nanosec;

	nanosleep(&req, &rem);
	#endif
}

void slowdown_sleep(float sec) {
	if(sec == 0) {
		sec = (slow_down_factor-1);
	}
	else {
		sec = sec * slow_down_factor;
	}
	fsleep(sec);
}

void slow_down(void) {
	slow_down_factor = slow_down_factor + SLOW_DOWN_INCREMENT;
}

void escscreen_animated(playground* my_playground) {
	char* temp_str = malloc(strlen(esc_rant)+2);
	memset(temp_str, 0, strlen(esc_rant)+2);
	for(int i=0; i < strlen(esc_rant); i++) {
		temp_str[i] = esc_rant[i];
		if(esc_rant[i] != ' ' && esc_rant[i] != '\n' && intro[i] != '|') {
			plot_startscreen(my_playground, temp_str);
			fsleep(0.01);
		}
	}
	for(int i=5; i > 0; i--) {
		sprintf(temp_str, "%s%d", esc_rant, i);
		plot_startscreen(my_playground, temp_str);
		fsleep(1);
	}
	free(temp_str);
}

void startscreen_animated(playground* my_playground) {
	char* temp_str = malloc(strlen(intro)+2);
	memset(temp_str, 0, strlen(intro)+2);
	for(int i=0; i < strlen(intro); i++) {
		temp_str[i] = intro[i];
		if(intro[i] != ' ' && intro[i] != '\n' && intro[i] != '|') {
			plot_startscreen(my_playground, temp_str);
			fsleep(0.01);
		}
	}
	free(temp_str);
}

void startscreen_count_animated(playground* my_playground) {
	char* temp_str = malloc(strlen(intro_count)+2);
	memset(temp_str, 0, strlen(intro_count)+2);
	for(int i=0; i < strlen(intro_count); i++) {
		temp_str[i] = intro_count[i];
		if(intro_count[i] != ' ' && intro_count[i] != '\n' && intro[i] != '|') {
			plot_startscreen(my_playground, temp_str);
			fsleep(0.02);
		}
	}
	for(int i=3; i > 0; i--) {
		sprintf(temp_str, "%s%d", intro_count, i);
		plot_startscreen(my_playground, temp_str);
		fsleep(1);
	}
	free(temp_str);
}

void startscreen_rant_animated(playground* my_playground) {
	char* temp_str = malloc(strlen(intro_rant)+2);
	memset(temp_str, 0,strlen(intro_rant)+2);
	for(int i=0; i < strlen(intro_rant); i++) {
		temp_str[i] = intro_rant[i];
		if(intro_rant[i] != ' ' && intro_rant[i] != '\n' && intro[i] != '|') {
			plot_startscreen(my_playground, temp_str);
			fsleep(0.01);
		}
	}
	for(int i=7; i > 0; i--) {
		sprintf(temp_str, "%s%d", intro_rant, i);
		plot_startscreen(my_playground, temp_str);
		fsleep(1);
	}
	free(temp_str);
}

void fill_animated(playground* my_playground, match* temp_match) {
	int empty_index;
	if(!temp_match || temp_match->type == 2) {
		// pick random from top or bottom
		if(random_bool_percent(50)) {
			empty_index = detect_last_empty(my_playground);
			while(empty_index != -1) {
				fill_vertical_top(my_playground, empty_index);
				empty_index = detect_last_empty(my_playground);
				plot_game(my_playground);
				slowdown_sleep(0.04);
			}
		}
		else {
			empty_index = detect_first_empty(my_playground);
			while(empty_index != -1) {
				fill_vertical_bottom(my_playground, empty_index);
				empty_index = detect_first_empty(my_playground);
				plot_game(my_playground);
				slowdown_sleep(0.04);
			}
		}
	}
	else if(temp_match->type == 1) {
		// pick random if from left or right
		if(random_bool_percent(50)) {
			empty_index = detect_last_empty(my_playground);
			while(empty_index != -1) {
				fill_horizontal_left(my_playground, empty_index);
				empty_index = detect_last_empty(my_playground);
				plot_game(my_playground);
				slowdown_sleep(0.04);
			}
		}
		else {
			empty_index = detect_first_empty(my_playground);
			while(empty_index != -1) {
				fill_horizontal_right(my_playground, empty_index);
				empty_index = detect_first_empty(my_playground);
				plot_game(my_playground);
				slowdown_sleep(0.04);
			}
		}
	}
}

void fill_animated_all(playground* my_playground) {
	empty_matrix(my_playground);
	plot_game(my_playground);
	slowdown_sleep(0.2);
	srand(time(NULL));

	for(int i=0; i < ROWS; i++) {
		for(int j=0; j < COLUMNS; j++) {
			fill_one(my_playground, i, j);
			plot_game(my_playground);
			slowdown_sleep(0.04);
		}
	}
}
