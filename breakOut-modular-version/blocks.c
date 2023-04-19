#include "lcdutils.h"
#include "lcddraw.h"
#include "blocks.h"
#include "ball.h"




int blockLife[5][6] =  {{1,1,1,1,1,1},
			{1,1,1,1,1,1},
			{1,1,1,1,1,1},
			{1,1,1,1,1,1},
			{1,1,1,1,1,1}};
int blockColor[5][6]=
  {{COLOR_RED,COLOR_GREEN,COLOR_GOLD,COLOR_PINK,COLOR_PURPLE,COLOR_BROWN},
   {COLOR_LIME_GREEN,COLOR_RED,COLOR_KHAKI,COLOR_GREEN_YELLOW,COLOR_LIGHT_BLUE,COLOR_CYAN},
   {COLOR_MAGENTA,COLOR_TURQUOISE,COLOR_ORANGE,COLOR_TAN,COLOR_DEEP,COLOR_PURPLE},
   {COLOR_PINK,COLOR_BEIGE,COLOR_FIREBRICK,COLOR_SIENNA,COLOR_GOLDENROD,COLOR_VIOLET},
   {COLOR_RED,COLOR_GREEN,COLOR_GOLD,COLOR_PINK,COLOR_PURPLE,COLOR_BROWN}};
int block_count = 0;

int block_ball[2] = {0,0}; // row and col //


void draw_Blocks(int row, int col, int color)
{
  fillRectangle(col-1, row-1, 20, 15, color);
}

void update_blocks()
{
  int row = 0;  // block row
  for (int i = 0; i < (screenHeight/2); i+= 16) { // Height of block
    int col = 0; // block column
    for (int j = 2; j < (screenWidth-20); j += 21){ // Width of the block
      if (blockLife[row][col] == 1)  // block still alive
	draw_Blocks(i,j,blockColor[row][col]);
      else // block destroyed
	draw_Blocks(i,j, COLOR_BLACK);
      col++;
    }
    row++;
  }
}

char ball_block_collision()
{
  int row = 0;  // block row

  for (int i = 0; i < (screenHeight/2); i+= 16) { // Height of block

    int col = 0; // block column

    for (int j = 2; j < (screenWidth-20); j += 21){ // Width of the block

      if(blockLife[row][col] == 1 && ball_position[0] >= i &&  ball_position[0] <= i + 15  &&  ball_position[1] >= j  && ball_position[1] <= j + 20) { // ball hit row

	blockLife[row][col] = 0;

	block_count++;

	if (ball_position[0] >= i &&  ball_position[0] <= i + 15)
	  block_ball[0] = 1; // row hit

	if (ball_position[1] >= j  && ball_position[1] <= j + 20)
	  block_ball[1] = 1; // column hit

	return 1;
      }
      col++;
    }
    row++;
  }
  block_ball[0] = 0;
  block_ball[1] = 0;
  return 0;
}
