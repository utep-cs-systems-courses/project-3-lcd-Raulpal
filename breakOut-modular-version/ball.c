#include "lcdutils.h"
#include "lcddraw.h"

int ball_position[2] = {screenHeight/2, screenWidth/2}; 

int next_position[2] = {(screenHeight/2)+1, (screenWidth/2)+1}; 

int ball_velocity[2] = {1,1}; // x = columns, y = row direction

// row and col bounds//
int colLimits[2] = {1,screenWidth};

int rowLimits[2] = {1,screenHeight};


// draw size of ball 5x5 //
void draw_ball(int row, int col, int color) 
{
  fillRectangle(col-1, row-1, 5, 5, color);
}

// update balls position //
void update_ball(int color) 
{
  for (int position = 0; position < 2; position++)
    if (ball_position[position] != next_position[position]) // Position changed //
      goto re_draw_ball;
  
  return;

 re_draw_ball:

  draw_ball(ball_position[0], ball_position[1], COLOR_BLACK); // Erase ball at row and column //

  for (int position = 0; position < 2; position++)

    ball_position[position] = next_position[position];

  draw_ball(ball_position[0], ball_position[1], color); // Draw ball at new row and column//
}
