#ifndef _FIELD_FILL_H_
#define _FIELD_FILL_H__

int random_field_index(void);
void fill_horizontal_left(playground* my_playground, int index);
void fill_horizontal_right(playground* my_playground, int index);
void fill_vertical_top(playground* my_playground, int index);
void fill_vertical_bottom(playground* my_playground, int index);
void empty_matrix(playground* my_playground);
void fill_one(playground* my_playground, int row, int col);
void fill_matrix(playground* my_playground);

#endif