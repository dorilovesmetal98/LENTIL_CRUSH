#ifndef _PIXEL_ART_H_
#define _PIXEL_ART_H__

#include "playground.h"

char* render_pixel_art(char* input_str);
char* color_header(char* header_str, field_color* colors);
char* full_header(char* color_header_str, playground* my_playground);

#endif