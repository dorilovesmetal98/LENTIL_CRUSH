#ifndef DRAWINGS_H
#define DRAWINGS_H

#include "playground.h"

static char LENTIL[] = "\n"
					   "       xxxxxxxx       \n"
				       "    xxxxxxxxxxxxxx    \n"
					   "  xxxxxxxxxxxxxxxxxx  \n"
				       " xxxxxxxxxxxxxxxxxxxx \n"
				       "  xxxxxxxxxxxxxxxxxx  \n"
				       "    xxxxxxxxxxxxxx    \n"
				       "       xxxxxxxx       \n";
				
static char SMALL_LENTIL[] = "   xxxxxxx    \n"
							 " xxxxxxxxxxx  \n"
					         "xxxxxxxxxxxxx \n"
					         " xxxxxxxxxxx  \n"
					         "   xxxxxxx    \n";

static int left_pigeon_width =	9;			  
static char left_pigeon[] = "          xxx    \n"
					        "         xx xxx  \n"
				            "         xxxxxxx \n"
					        "         xxxxx   \n" 
					        "         xxxx    \n"
					        "        xxxxxx   \n" 
					        "        xxxxxxx  \n"
					        "      xxxxxxxxxx \n"
					        "     xxxxxxxxxxx \n"
					        "    xxxxxxxxxxxx \n"
					        "   xxxxxxxxxxxxxx\n"
				            "   xxxxxxxxxxxxxx\n"
							"  xxxxxxxxxxxxxx \n"
							" xxxxxxxxxxxxxx  \n"
							"    xxxx  x  x   \n"
							"         xxx xx  \n";
				  
static char right_pigeon[] = "    xxxx        \n"
					 "   xxx xx        \n"
				     "  xxxxxxx        \n"
					 "    xxxxx        \n" 
					 "     xxxx        \n"
					 "    xxxxxx       \n" 
					 "   xxxxxxx       \n"
					 "  xxxxxxxxxx     \n"
					 "  xxxxxxxxxxx    \n"
					 "  xxxxxxxxxxxx   \n"
					 " xxxxxxxxxxxxxx  \n"
					 " xxxxxxxxxxxxxx  \n"
					 "  xxxxxxxxxxxxxx \n"
					 "   xxxxxxxxxxxxxx\n"
					 "    x  x  xxxx   \n"
					 "   xx xxx        \n";

static int header_width = 84;							  
static char header[] = "                                                                                         |                                                                               \n"
					   "                                                                                         |                                                                               \n"
					   "                                                                                         |                                                                               \n"
					   "                                                                                         |                                                                               \n"
					   "          xx            xxxxxxxxxxxx  xxxx      xx  xxxxxxxxxxxx   xx   xx               |       xxxxxxxx   xxxxxxxxx     xx       xx    xxxxxxxx  xx        xx          \n"
					   "          xx            xx            xxxxxx    xx       xx        xx   xx               |     xxx       x  xx      xx    xx       xx  xx          xx        xx          \n"
				       "          xx            xx            xx  xxx   xx       xx        xx   xx               |     x            xx      xx    xx       xx    xx        xx        xx          \n"
				       "          xx            xxxxxxxxxx    xx   xxx  xx       xx        xx   xx               |     x            xxxxxxxxx     xx       xx      xx      xxxxxxxxxxxx          \n"
				       "          xx            xx            xx    xxx xx       xx        xx   xx               |     x            xx     xx     xx       xx        xx    xx        xx          \n"
				       "          xx            xx            xx     xxxxx       xx        xx   xx               |     xxx       x  xx      xx     xx     xxx          xx  xx        xx          \n"
				       "          xxxxxxxxxxxx  xxxxxxxxxxxx  xx      xxxx       xx        xx   xxxxxxxxxxxx     |       xxxxxxxx   xx       xxx    xxxxxxx x  xxxxxxxx    xx        xx          \n";

static field_color header_colors[] = {MAGENTA, CYAN};
					   
#endif