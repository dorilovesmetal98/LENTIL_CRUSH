#include <stdlib.h>
#include <time.h>

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

void random_pigeons(playground* my_playground) {
	srand(time(NULL));

	// pigeons appear with 30%
	// pigeons disappear with 30%
	if(left_pigeon_onfield(my_playground) && random_bool_percent(30)) {
		left_pigeon_fly_off_field();
		fill_animated(my_playground, 0);
	}
	else if(random_bool_percent(30)) {
		left_pigeon_fly_on_field();
	}
	
	if(right_pigeon_onfield(my_playground) && random_bool_percent(30)) {
		right_pigeon_fly_off_field();
		fill_animated(my_playground, 0);
	}
	else if(random_bool_percent(30)) {
		right_pigeon_fly_on_field();
	}	
}

int random_stepsis(playground* my_playground) {
	srand(time(NULL));
	// stepsister reshuffles with 10%
	if(random_bool_percent(10)) {
		// also reset pigeons
		my_playground->left_pigeon_onfield = 0;
		my_playground->right_pigeon_onfield = 0;
		set_bottom_message("Deine Stiefschwester tritt mit ihren Riesenlatschen alle Linsen durcheinander.");
		fill_animated_all(my_playground);
		return 1;
	}
	return 0;
}

int main() {
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif

	init_game();
	
	playground* my_playground = get_playground();
	match* temp_match = get_temp_match();
	
	char input_key;
	
	startscreen_animated(my_playground);
	do {
		input_key = keyboard_input();
	} while(!(input_key == 'y' || input_key == 'n' || input_key == ESC || input_key == SNEAK_ESC));
	
	if(input_key == 'y') {
		startscreen_count_animated(my_playground);
	}
	else if(input_key == 'n' || input_key == ESC) {
		startscreen_rant_animated(my_playground);
	}
	else {
		plot_startscreen(my_playground, esc_rant2);
		return 0;
	}
	
	fill_animated_all(my_playground);
	
	activate_cursor1();
	set_bottom_message("LETS GO!");
	plot_game(my_playground);
	
	int matching;
	while(1) {
		do {
			input_key = keyboard_input();
		} while(!(input_key == ENTER || input_key == UP || input_key == DOWN || input_key == LEFT || input_key == RIGHT || input_key == ESC || input_key == SNEAK_ESC));
		
		if(input_key == ENTER) {
			if(enter_cursor()) {
				clear_bottom_message();
				set_blink_cursor();
				plot_game(my_playground);
				slowdown_sleep(0.6);
				swap_lentils();
				unset_blink_cursor();
				plot_game(my_playground);
				slowdown_sleep(0.3);
				deactivate_cursor();
				activate_cursor1();
				
				random_pigeons(my_playground);
				plot_game(my_playground);
				
				if(random_stepsis(my_playground)) {
					continue;
				}
				
				matching = detect_match(temp_match, my_playground);
				while(matching) {
					set_blink_match();
					plot_game(my_playground);
					slowdown_sleep(0.4);
					if(update_score()) {
						slow_down();
					}
					unset_blink_match();
					empty_match();
					plot_game(my_playground);
					slowdown_sleep(0.2);
					fill_animated(my_playground, temp_match);
					matching = detect_match(temp_match, my_playground);
				}
			}
		}
		else if(input_key == ESC) {
			escscreen_animated(my_playground);
			slow_down();
		}
		else if(input_key == SNEAK_ESC) {
			plot_startscreen(my_playground, esc_rant2);
			fsleep(0.7);
			break;
		}
		else {
			move_cursor(input_key);
		}
		plot_game(my_playground);
	}
	
	clear_game();
		
	return 0;
}
