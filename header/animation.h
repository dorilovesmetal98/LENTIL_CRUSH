#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "game_control.h"
#include "playground.h"

#define SLOW_DOWN_INCREMENT 0.2
#define MASSIVE_SLOW_DOWN_INCREMENT 1.0

#ifdef _WIN32
#define WINDOWS_ACC_FACTOR 0.7
#endif

void fsleep(float sec);
void slow_down(void);
void massive_slow_down(void);
void slowdown_sleep(float sec);
void escscreen_animated(playground* my_playground);
void startscreen_animated(playground* my_playground);
void startscreen_count_animated(playground* my_playground);
void startscreen_rant_animated(playground* my_playground);
void fill_animated(playground* my_playground, match* temp_match);
void fill_animated_all(playground* my_playground);

#endif
