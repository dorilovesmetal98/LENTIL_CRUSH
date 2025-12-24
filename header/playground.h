#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

// field size
#define ROWS 6
#define COLUMNS 6

// number of chars
#define ROW_SIZE 102
#define WIDTH_HOR 11
#define WIDTH_VER 5

// field spaces
#define SPACE_HOR 14
#define SPACE_VER 0
#define SPACE_SIDEBAR_HOR 8
#define SPACE_SIDEBAR_VER 4

// start screen spaces
#define TEXT_FIELD_VER 15
#define TEXT_FIELD_VER_ALIGN 11

// default values
#define DEFAULT_GOAL 15
#define LENTILS_NUM 6

// directions and key inputs
#define UP 30
#define RIGHT 31
#define DOWN 32
#define LEFT 33
#define ESC 40
#define SNEAK_ESC 41
#define ENTER 42

// colors (control)
#define CLEAR -1
#define EMPTY 0
#define KEY 20
#define BLINK 21

// colors (lentils)
#define DRED 1
#define GREEN 2
#define ORANGE 3
#define GREY 4
#define YELLOW 5
#define BRIGHTRED 6
#define MAGENTA 7
#define CYAN 8

// colors (pigeons)
#define LEFT_PIGEON 10
#define RIGHT_PIGEON 11

// colors (cursor)
#define CURSOR_HIDDEN 100
#define	CURSOR_CHOICE 101
#define CURSOR_LOCKED 102

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
	int cursor1visible;
	int cursor2visible;
	int cursor1_row;
	int cursor1_col;
	int cursor2_pos;
	int matrix[ROWS][COLUMNS];
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