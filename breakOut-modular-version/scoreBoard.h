#ifndef scoreBoard_included
#define scoreBoard_included

void drawChar8x12(u_char rcol, u_char rrow, char c,
		  u_int fgColorBGR, u_int bgColorBGR);

void drawString8x12(u_char col, u_char row, char *string,
		    u_int fgColorBGR, u_int bgColorBGR);

void update_score();
#endif // included
