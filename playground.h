#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

#define ROWS 6
#define COLUMNS 6

#define ROW_SIZE 102

#define WIDTH_HOR 11
#define WIDTH_VER 5

#define SPACE_HOR 14
#define SPACE_VER 1
#define SPACE_SIDEBAR_HOR 8
#define SPACE_SIDEBAR_VER 4

#define TEXT_FIELD_VER 15
#define TEXT_FIELD_VER_ALIGN 11

#define DEFAULT_GOAL 15

typedef enum direction {
	UP = 30,
	RIGHT = 31,
	DOWN = 32,
	LEFT = 33,
	ESC = 40,
	SNEAK_ESC = 41,
	ENTER = 42,
} direction;

typedef enum cursor_stat {
	CURSOR_HIDDEN = 100,
	CURSOR_CHOICE = 101,
	CURSOR_LOCKED = 102
} cursor_stat;

#define LENTILS_NUM 6
typedef enum field_color {
    CLEAR = -1,
	EMPTY = 0,
	DRED = 1,
	GREEN = 2,
	ORANGE = 3,
	GREY = 4,
	YELLOW = 5,
	BRIGHTRED = 6,
	MAGENTA = 7,
	CYAN = 8,
	LEFT_PIGEON = 10,
	RIGHT_PIGEON = 11,
	KEY = 20,
	BLINK = 21
} field_color;

typedef struct sidebar {
	int score_red;
	int goal_red;
	int score_green;
	int goal_green;
	int score_orange;
	int goal_orange;
	int score_grey;
	int goal_grey;
	int score_yellow;
	int goal_yellow;
	int score_brightred;
	int goal_brightred;
} sidebar;

typedef struct playground {
	cursor_stat cursor1visible;
	cursor_stat cursor2visible;
	int cursor1_row;
	int cursor1_col;
	direction cursor2_pos;
	field_color matrix[ROWS][COLUMNS];
	int blink_matrix[ROWS][COLUMNS];
	int left_pigeon_onfield;
	int right_pigeon_onfield;
	sidebar* my_sidebar;
	char* bottom_message;
} playground;

void init_playground(playground* my_playground);
void clear_playground(playground* my_playground);
char* render_sidebar(sidebar* my_sidebar);
char* render_playground(playground* my_playground);

#endif