#include "lcdutils.h"
#include "lcddraw.h"
#include "blocks.h"
#include "scoreBoard.h"
#include <stdio.h>

void drawChar8x12(u_char rcol, u_char rrow, char c,
		  u_int fgColorBGR, u_int bgColorBGR)

{

  u_char col = 0;

  u_char row = 0;

  u_char bit = 0x80;

  u_char oc = c - 0x20;
  lcd_setArea(rcol, rrow, rcol + 7, rrow + 11); /* relative to requested col/row */
  while (row < 12) {

    while (col < 8) {

      //u_int colorBGR = (font_8x12[oc][col] & bit) ? fgColorBGR : bgColorBGR;

      //lcd_writeColor(colorBGR);

      if(font_8x12[oc][row]  & bit){
	drawPixel(rcol + col, rrow + row, fgColorBGR);
	lcd_writeColor(fgColorBGR);
      }else{
	lcd_writeColor(bgColorBGR);
      }
      bit >>= 1;
      col++;
    }
    col = 0;
    bit = 0x80;
    row++;
  }
}



void drawString8x12(u_char col, u_char row, char *string,
		    u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9; // 9 space inbetween characters //
  }
}

void update_score()
{
  char str[10];
  sprintf(str,"%d",block_count);
  int index = 0;
  while(*(str + index))
    index++;
  str[index] = '/';
  str[index+1] = '3';
  str[index+2] = '0';    

  fillRectangle((screenWidth/2) + 19, screenHeight-12, 50, 17, COLOR_BLACK);
  drawString8x12((screenWidth/2) + 20, screenHeight-12, str, COLOR_WHITE, COLOR_BLACK);  
}
